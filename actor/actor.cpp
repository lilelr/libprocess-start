//
// Created by lemaker on 2/3/19.
//

#include "actor.hpp"


#include <errno.h>
#include <limits.h>

#ifndef __WINDOWS__

#include <netdb.h>

#endif // __WINDOWS__

#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __WINDOWS__

#include <unistd.h>

#include <arpa/inet.h>

#endif // __WINDOWS__

#include <glog/logging.h>

#ifndef __WINDOWS__

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>

#endif // __WINDOWS__

#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory> // TODO(benh): Replace shared_ptr with unique_ptr.
#include <mutex>
#include <queue>
#include <string>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <queue>

#include <process/address.hpp>
#include <process/check.hpp>
#include <process/clock.hpp>
#include <process/defer.hpp>
#include <process/filter.hpp>
#include <process/future.hpp>
#include <process/gc.hpp>
#include <process/help.hpp>
#include <process/id.hpp>
#include <process/io.hpp>
#include <process/logging.hpp>
#include <process/mime.hpp>
#include <process/owned.hpp>
#include <process/profiler.hpp>
#include <process/reap.hpp>
#include <process/sequence.hpp>
#include <process/socket.hpp>
#include <process/statistics.hpp>
#include <process/system.hpp>
#include <process/time.hpp>
#include <process/timer.hpp>

#include <stout/duration.hpp>
#include <stout/flags.hpp>
#include <stout/foreach.hpp>
#include <stout/lambda.hpp>
#include <stout/net.hpp>
#include <stout/numify.hpp>
#include <stout/option.hpp>
#include <stout/os.hpp>
#include <stout/os/strerror.hpp>
#include <stout/path.hpp>
#include <stout/stringify.hpp>
#include <stout/strings.hpp>
#include <stout/synchronized.hpp>
#include <stout/thread_local.hpp>
#include <stout/os/int_fd.hpp>

#include "gate.hpp"
#include "mygc.hpp"
#include "actor_reference.hpp"
#include "myevent_loop.hpp"
#include "encoder.hpp"
//#include "decoder.hpp"

using std::string;
using std::map;
using std::list;
using std::vector;
using std::deque;
using std::queue;


using process::network::inet::Address;
using process::network::inet::Socket;

using process::network::internal::SocketImpl;
//using process::wait; // Necessary on some OS's to disambiguate.
namespace actor {

    class ActorManager;

    class SocketManager;

    static std::atomic_bool initialize_started(false);
    static std::atomic_bool initialize_complete(false);

    static const int LISTEN_BACKLOG = 5000;

    static Socket *__s__ = nullptr;

    static std::mutex *socket_mutex = new std::mutex();

    static process::Future<Socket> future_accept;

    static Address __address__ = Address::ANY_ANY();

    // Active SocketManager (eventually will probably be thread-local).
    static SocketManager *socket_manager = nullptr;

    static ActorManager *actor_manager = nullptr;

    static Gate *gate = new Gate();

    MyGarbageCollector *gc = nullptr;

    THREAD_LOCAL ActorBase *__actor__ = nullptr;

    class SocketManager {
    public:
        SocketManager();

        ~SocketManager();

        void finalize();

        void accepted(const Socket &socket);

        void link(ActorBase *actor, const process::UPID &to, const ActorBase::RemoteConnection remote,
                  const SocketImpl::Kind &kind = SocketImpl::DEFAULT_KIND());

        void send(Encoder *encoder, bool persist, const Socket &socket);

        Encoder *next(int_fd s);

        void close(int_fd s);


        void exited(const Address &address);

        void exited(ActorBase *actor);


    private:
        struct {
            // For links, we maintain a bidirectional mapping between the
            // "linkers" (Processes) and the "linkees" (remote / local UPIDs).
            // For remote socket addresses, we also need a mapping to the
            // linkees for that socket address, because socket closure only
            // notifies at the address level.
            hashmap<process::UPID, hashset<ActorBase *>> linkers;
            hashmap<ActorBase *, hashset<process::UPID>> linkees;
            hashmap<Address, hashset<process::UPID>> remotes;
        } links;

        // Helper function for link().
        void link_connect(
                const process::Future<Nothing> &future,
                Socket socket,
                const process::UPID &to);

        // Helper function for send().
        void send_connect(
                const process::Future<Nothing> &future,
                Socket socket,
                MyMessage *message);

        // Collection of all active sockets (both inbound and outbound).
        hashmap<int_fd, Socket> sockets;

        // Collection of sockets that should be disposed when they are
        // finished being used (e.g., when there is no more data to send on
        // them). Can contain both inbound and outbound sockets.
        hashset<int_fd> dispose;

        // Map from socket to socket address for outbound sockets.
        hashmap<int_fd, Address> addresses;

        // Map from socket address to temporary sockets (outbound sockets
        // that will be closed once there is no more data to send on them).
        hashmap<Address, int_fd> temps;

        // Map from socket address (ip, port) to persistent sockets
        // (outbound sockets that will remain open even if there is no more
        // data to send on them).  We distinguish these from the 'temps'
        // collection so we can tell when a persistent socket has been lost
        // (and thus generate ExitedEvents).
        hashmap<Address, int_fd> persists;

        // Map from outbound socket to outgoing queue.
        hashmap<int_fd, queue<Encoder *>> outgoing;

        // Protects instance variables.
        std::recursive_mutex mutex;
    };

    class ActorManager {
    public:
        explicit ActorManager(const Option<string> &delegate);

        void finalize();

        ~ ActorManager();

        long init_threads();

        ActorBase *dequeue();

        void cleanup(ActorBase *actor);

        void resume(ActorBase *actor) {
            __actor__ = actor;

            LOG(INFO) << " Resuming " << actor->pid << "at ";

            bool terminate = false;
            bool blocked = false;

            CHECK(actor->state == ActorBase::BOTTOM || actor->state == ActorBase::READY);

            if (actor->state == ActorBase::BOTTOM) {
                actor->state = ActorBase::RUNNING;
                try { actor->initialize(); }
                catch (...) {
                    terminate = true;
                }
            }

            while (!terminate && !blocked) {
                MyEvent *event = nullptr;

                synchronized(actor->mutex)
                    {
                        if (actor->events.size() > 0) {
                            event = actor->events.front();
                            actor->events.pop_front();
                            actor->state = ActorBase::RUNNING;
                        } else {
                            actor->state = ActorBase::BLOCKED;
                            blocked = true;
                        }
                    }

                if (!blocked) {
                    CHECK(event != nullptr);
                }

                terminate = event->is<MyTerminateEvent>();

                try {
                    actor->serve(*event);
                } catch (const std::exception &e) {
                    std::cerr << "libactor: " << actor->pid << "terminatng due to " << e.what() << std::endl;
                    terminate = true;
                } catch (...) {
                    std::cerr << "libactor: " << actor->pid << "terminatng due to unknown exception" << std::endl;
                    terminate = true;
                }

                delete event;
                if (terminate) {
                    cleanup(actor);
                }

            }


        }

        bool wait(const process::UPID &pid);

        void terminate(const process::UPID &pid, bool inject, ActorBase *sender = nullptr);

    private:

        ActorReference use(const process::UPID &pid);

        const Option<std::string> delegate;

        map<string, ActorBase *> actors;
        std::recursive_mutex actors_mutex;
        map<ActorBase *, Gate *> gates;

        list<ActorBase *> runq;
        std::recursive_mutex runq_mutex;

        std::atomic_long running;

        vector<std::thread *> threads;

        std::atomic_bool joining_threads;

        std::atomic_bool finalizing;

    };


    SocketManager::SocketManager() {}

    SocketManager::~SocketManager() {}

    void SocketManager::accepted(const Socket &socket) {
        synchronized(mutex)
            {
                CHECK(sockets.count(socket) == 0);
                sockets.emplace(socket, socket);
            }
    }


    namespace internal {

        void _send(
                const process::Future<size_t> &result,
                Socket socket,
                Encoder *encoder,
                size_t size);


        void send(Encoder *encoder, Socket socket) {
            switch (encoder->kind()) {
                case Encoder::DATA: {
                    size_t size;
                    const char *data = static_cast<DataEncoder *>(encoder)->next(&size);
                    socket.send(data, size)
                            .onAny(lambda::bind(
                                    &internal::_send,
                                    lambda::_1,
                                    socket,
                                    encoder,
                                    size));
                    break;
                }
                case Encoder::FILE: {
                    off_t offset;
                    size_t size;
                    int_fd fd = static_cast<FileEncoder *>(encoder)->next(&offset, &size);
                    socket.sendfile(fd, offset, size)
                            .onAny(lambda::bind(
                                    &internal::_send,
                                    lambda::_1,
                                    socket,
                                    encoder,
                                    size));
                    break;
                }
            }
        }


        void _send(
                const process::Future<size_t> &length,
                Socket socket,
                Encoder *encoder,
                size_t size) {
            if (length.isDiscarded() || length.isFailed()) {
                socket_manager->close(socket);
                delete encoder;
            } else {
                // Update the encoder with the amount sent.
                encoder->backup(size - length.get());

                // See if there is any more of the message to send.
                if (encoder->remaining() == 0) {
                    delete encoder;

                    // Check for more stuff to send on socket.
                    Encoder *next = socket_manager->next(socket);
                    if (next != nullptr) {
                        send(next, socket);
                    }
                } else {
                    send(encoder, socket);
                }
            }
        }

    } // namespace internal {

    Encoder *SocketManager::next(int_fd s) {
        if (sockets.count(s) > 0) {
            CHECK(outgoing.count(s) > 0);

            if (!outgoing[s].empty()) {
                Encoder *encoder = outgoing[s].front();
                outgoing[s].pop();
                return encoder;
            } else {
                outgoing.erase(s);

                if (dispose.count(s) > 0) {
                    Option<Address> address = addresses.get(s);
                    if (address.isSome()) {
                        CHECK(temps.count(address.get()) > 0 && temps[address.get()] == s);
                        temps.erase(address.get());
                        addresses.erase(s);
                    }

                    dispose.erase(s);

                    auto iterator = sockets.find(s);

                    // We don't actually close the socket (we wait for the Socket
                    // abstraction to close it once there are no more references),
                    // but we do shutdown the receiving end so any DataDecoder
                    // will get cleaned up (which might have the last reference).

                    // Hold on to the Socket and remove it from the 'sockets'
                    // map so that in the case where 'shutdown()' ends up
                    // calling close the termination logic is not run twice.
                    Socket socket = iterator->second;
                    sockets.erase(iterator);

                    Try<Nothing> shutdown = socket.shutdown();
                    if (shutdown.isError()) {
                        LOG(ERROR) << "Failed to shutdown socket with fd " << socket.get()
                                   << ", address " << (socket.address().isSome()
                                                       ? stringify(socket.address().get())
                                                       : "N/A")
                                   << ": " << shutdown.error();
                    }
                }
            }
        }
        return nullptr;

    }

    namespace internal {
        void ignore_recv_data(const process::Future<size_t> &length, Socket socket, char *data, size_t size) {

            if (length.isDiscarded() || length.isFailed()) {
                socket_manager->close(socket);
                delete[] data;
                return;
            }

            if (length.get() == 0) {
                socket_manager->close(socket);
                delete[] data;
                return;
            }

            socket.recv(data, size).onAny(lambda::bind(&ignore_recv_data, lambda::_1, socket, data, size));

        }

        // Forward declaration.
        void send(Encoder *encoder, Socket socket);
    }

    // Helper function for link().
    void SocketManager::link_connect(
            const process::Future<Nothing> &future,
            Socket socket,
            const process::UPID &to) {

        if (future.isDiscarded() || future.isFailed()) {
            LOG(INFO) << "Failed to link, connect: " << future.failure();

            socket_manager->close(socket);
            return;
        }

        synchronized(mutex)
            {
                if (sockets.count(socket) <= 0) {
                    return;
                }

                size_t size = 80 * 1024;
                char *data = new char[size];
                socket.recv(data, size).onAny(
                        lambda::bind(&internal::ignore_recv_data, lambda::_1, socket, data, size));

            }
        Encoder *encoder = socket_manager->next(socket);

        if (encoder != nullptr) {
            internal::send(encoder, socket);
        }


    }

    void SocketManager::close(int_fd s) {
        synchronized (mutex)
            {
                if (sockets.count(s) > 0) {
                    if (outgoing.count(s) > 0) {
                        while (!outgoing[s].empty()) {
                            Encoder *encoder = outgoing[s].front();
                            delete encoder;
                            outgoing[s].pop();
                        }

                        outgoing.erase(s);
                    }

                    Option<Address> address = addresses.get(s);
                    if (address.isSome()) {

                        if (persists.count(address.get()) > 0 && persists[address.get()] == s) {
                            persists.erase(address.get());
                            exited(address.get());
                        } else if (temps.count(address.get()) > 0 && temps[address.get()] == s) {
                            temps.erase(address.get());
                        }

                        addresses.erase(s);
                    }

                    dispose.erase(s);
                    auto iterator = sockets.find(s);

                    Socket socket = iterator->second;
                    sockets.erase(iterator);

                    Try<Nothing> shutdown = socket.shutdown();
                    if (shutdown.isError()) {
                        LOG(ERROR) << "Failed to shutdown socket with fd " << socket.get()
                                   << ", address"
                                   << (socket.address().isSome() ? stringify(socket.address().get()) : "N/A") << " : "
                                   << shutdown.error();
                    }
                }
            }
    }

    void SocketManager::exited(const Address &address) {
        // TODO(benh): It would be cleaner if this routine could call back
        // into ProcessManager ... then we wouldn't have to convince
        // ourselves that the accesses to each Process object will always be
        // valid.
        synchronized (mutex)
            {
                if (!links.remotes.contains(address)) {
                    return; // No linkees for this socket address!
                }

                foreach (const process::UPID &linkee, links.remotes[address]) {
                    // Find and notify the linkers.
                    CHECK(links.linkers.contains(linkee));

                    foreach (ActorBase *linker, links.linkers[linkee]) {
                        linker->enqueue(new MyExitedEvent(linkee));

                        // Remove the linkee pid from the linker.
                        CHECK(links.linkees.contains(linker));

                        links.linkees[linker].erase(linkee);
                        if (links.linkees[linker].empty()) {
                            links.linkees.erase(linker);
                        }
                    }

                    links.linkers.erase(linkee);
                }

                links.remotes.erase(address);
            }
    }


    void SocketManager::exited(ActorBase *actor) {
        // An exited event is enough to cause the process to get deleted
        // (e.g., by the garbage collector), which means we can't
        // dereference process (or even use the address) after we enqueue at
        // least one exited event. Thus, we save the process pid.
        const process::UPID pid = actor->pid;

//        // Likewise, we need to save the current time of the process so we
//        // can update the clocks of linked processes as appropriate.
//        const Time time = Clock::now(actor);

        synchronized (mutex)
            {
                // If this process had linked to anything, we need to clean
                // up any pointers to it. Also, if this process was the last
                // linker to a remote linkee, we must remove linkee from the
                // remotes!
                if (links.linkees.contains(actor)) {
                    foreach (const process::UPID &linkee, links.linkees[actor]) {
                        CHECK(links.linkers.contains(linkee));

                        links.linkers[linkee].erase(actor);
                        if (links.linkers[linkee].empty()) {
                            links.linkers.erase(linkee);

                            // The exited process was the last linker for this linkee,
                            // so we need to remove the linkee from the remotes.
                            if (linkee.address != __address__) {
                                CHECK(links.remotes.contains(linkee.address));

                                links.remotes[linkee.address].erase(linkee);
                                if (links.remotes[linkee.address].empty()) {
                                    links.remotes.erase(linkee.address);
                                }
                            }
                        }
                    }
                    links.linkees.erase(actor);
                }

                // Find the linkers to notify.
                if (!links.linkers.contains(pid)) {
                    return; // No linkers for this process!
                }

                foreach (ActorBase *linker, links.linkers[pid]) {
                    CHECK(linker != actor) << "Process linked with itself";
//                Clock::update(linker, time);
                    linker->enqueue(new MyExitedEvent(pid));

                    // Remove the linkee pid from the linker.
                    CHECK(links.linkees.contains(linker));

                    links.linkees[linker].erase(pid);
                    if (links.linkees[linker].empty()) {
                        links.linkees.erase(linker);
                    }
                }

                links.linkers.erase(pid);
            }
    }

    void SocketManager::finalize() {
        CHECK(__s__ = nullptr);
        CHECK(gc == nullptr);

        int_fd socket = -1;
        do {
            synchronized(mutex)
                {
                    socket = !sockets.empty() ? sockets.begin()->first : -1;
                }
        } while (socket >= 0);
    }

    ActorManager::ActorManager(const Option<string> &_delegate) : delegate(_delegate), running(0),
                                                                  joining_threads(false), finalizing(false) {

    }

    void ActorManager::finalize() {
        CHECK(gc != nullptr);

        finalizing.store(true);

        while (true) {
            process::UPID pid;

            synchronized (actors_mutex)
                {
                    ActorBase *actor = nullptr;
                    foreachvalue (ActorBase *candidate, actors) {
                                            if (candidate == gc) {
                                                continue;
                                            }

                                            actor = candidate;
                                            pid = candidate->self();
                                            break;
                                        }

                    if (actor == nullptr) {
                        break;
                    }
                }

            actor::my_terminate(pid, false);

        }

        actor::my_terminate(gc, false);

        synchronized(actors_mutex)
            {
                delete gc;
                gc = nullptr;
            }

        joining_threads.store(true);
        gate->open();
        MyEventLoop::stop();


        foreach(std::thread *thread, threads) {
            thread->join();
            delete thread;
        }

    }

    ActorManager::~ActorManager() {}

    void ActorManager::terminate(const process::UPID &pid, bool inject, ActorBase *sender) {
        if (ActorReference actor = use(pid)) {
            if (sender != nullptr) {
                actor->enqueue(new MyTerminateEvent(sender->self()));
            } else {
                actor->enqueue(new MyTerminateEvent(process::UPID()));
            }
        }
    }

    void ActorManager::cleanup(ActorBase *actor) {
        LOG(INFO) << "Cleaning up " << actor->pid;


        deque<MyEvent *> events;
        synchronized(actor->mutex)
            {
                actor->state = ActorBase::TERMINATING;
                events = actor->events;
                actor->events.clear();
            }

        while (!events.empty()) {
            MyEvent *event = events.front();
            events.pop_front();
            delete event;
        }

        Gate *gate = nullptr;
        synchronized(actors_mutex)
            {
                synchronized(actor->mutex)
                    {
                        CHECK(actor->events.empty());
                        actors.erase(actor->pid.id);

                        map<ActorBase *, Gate *>::iterator it = gates.find(actor);
                        if (it != gates.end()) {
                            gate = it->second;
                            gates.erase(it);
                        }
                        CHECK(actor->refs.load() == 0);
                        actor->state = ActorBase::TERMINATED;
                    }
            }

        if (gate != nullptr) {
            gate->open();
        }
    }

    ActorReference ActorManager::use(const process::UPID &pid) {
        if (pid.address == __address__) {
            synchronized(actors_mutex)
                {
                    if (actors.count(pid.id) > 0) {
                        return ActorReference(actors[pid.id]);
                    }
                }
        }

        return ActorReference(nullptr);
    }

    ActorBase *ActorManager::dequeue() {
        ActorBase *actor = nullptr;

        synchronized(runq_mutex)
            {
                if (!runq.empty()) {
                    actor = runq.front();
                    runq.pop_front();
                    running.fetch_add(1);
                }
            }
        return actor;
    }

    long ActorManager::init_threads() {
        long num_worker_threads = std::max(8L, os::cpus().isSome() ? os::cpus().get() : 1);
        threads.reserve(num_worker_threads + 1);

        struct {
            void operator()() const {
                do {
                    ActorBase *actor = actor_manager->dequeue();
                    if (actor == nullptr) {
                        Gate::state_t old = gate->approach();
                        actor = actor_manager->dequeue();
                        if (actor == nullptr) {
                            if (m_joining_threads.load()) {
                                break;
                            }
                            gate->arrive(old);
                            continue;
                        } else {
                            gate->leave();
                        }
                    }
                    actor_manager->resume(actor);

                } while (true);

            }

            const std::atomic_bool &m_joining_threads;
        } worker{joining_threads};

        for (long i = 0; i < num_worker_threads; i++) {
            threads.emplace_back(new std::thread(worker));
        }

        threads.emplace_back(new std::thread(&MyEventLoop::run));
        return num_worker_threads;
    }


    bool ActorManager::wait(const process::UPID &pid) {
        Gate *gate = nullptr;
        Gate::state_t old;

        ActorBase *actor = nullptr;

        synchronized(actors_mutex)
            {
                if (actors.count(pid.id) > 0) {
                    actor = actors[pid.id];
                    CHECK(actor->state != ActorBase::TERMINATED);

                    if (gates.find(actor) == gates.end()) {
                        gates[actor] = new Gate();
                    }

                    gate = gates[actor];
                    old = gate->approach();


                    if (actor->state == ActorBase::BOTTOM || actor->state == ActorBase::READY) {
                        synchronized(runq_mutex)
                            {
                                list<ActorBase *>::iterator it = find(runq.begin(), runq.end(), actor);
                                if (it != runq.end()) {
                                    runq.erase(it);
                                    running.fetch_add(1);
                                } else {
                                    actor = nullptr;
                                }
                            }
                    } else {
                        actor = nullptr;
                    }
                }
            }

        if (actor != nullptr) {
            LOG(INFO) << " Donating thread to " << actor->pid << " while waiting";

            ActorBase *donator = __actor__;
            actor_manager->resume(actor);
            __actor__ = donator;
        }

        if (gate != nullptr) {
            int remaining = gate->arrive(old);
            if (remaining == 0) {
                delete gate;
            }

            return true;
        }

        return false;
    }


    ActorBase::ActorBase(const std::string &id) {
        state = ActorBase::BOTTOM;

    }

    ActorBase::~ActorBase() {

    }


    void ActorBase::visit(const MyMessageEvent &myMessageEvent) {

    }

    void ActorBase::visit(const MyDispatchEvent &myDispatchEvent) {

    }

    void ActorBase::visit(const MyExitedEvent &myExitedEvent) {

    }

    void ActorBase::visit(const MyTerminateEvent &myTerminateEvent) {

    }

    void ActorBase::enqueue(MyEvent *event, bool inject) {
        CHECK(event != nullptr);

        synchronized(mutex)
            {
                if (state != TERMINATING && state != TERMINATED) {
                    if (!inject) {
                        events.push_back(event);
                    } else {
                        events.push_front(event);
                    }

                    if (state == BLOCKED) {
                        state = READY;
                    }

                    CHECK(state == BOTTOM || state == READY || state == RUNNING);
                } else {
                    delete event;
                }
            }
    }

    bool initialize(const Option<std::string> &delegate) {
        if (initialize_started.load() && initialize_complete.load()) {
            // initialize_started = true && initialize_complete = true
            return false;
        } else {
            bool expected = false;

            if (!initialize_started.compare_exchange_strong(expected, true)) {
                // initialize_started = true but initialize_complete = false
                while (!initialize_complete.load());

                return false;
            }
            // initialize_started transfer from false to true, but initialize_complete = false, go to line 149
        }
        signal(SIGPIPE, SIG_IGN);
        actor_manager = new ActorManager(delegate);

        long num_worker_threads = actor_manager->init_threads();

        MyEventLoop::initialize();

        __address__ = Address::ANY_ANY();


    }

    inline void my_terminate(const ActorBase &actor, bool inject) {
        my_terminate(actor.self(), inject);
    }

    inline void my_terminate(const ActorBase *actor, bool inject) {
        my_terminate(actor->self(), inject);
    }

    void my_terminate(const process::UPID &pid, bool inject) {
        actor_manager->terminate(pid, inject, __actor__);
    }

}