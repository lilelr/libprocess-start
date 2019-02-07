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

#include "gate.hpp"
#include "mygc.hpp"

using std::string;
using std::map;
using std::list;
using std::vector;


using process::network::inet::Address;
using process::network::inet::Socket;

using process::network::internal::SocketImpl;
//using process::wait; // Necessary on some OS's to disambiguate.
namespace actor {


    static std::atomic_bool initialize_started(false);
    static std::atomic_bool initialize_complete(false);

    static const int LISTEN_BACKLOG = 5000;

    static Socket* __s__ = nullptr;

    static std::mutex* socket_mutex = new std::mutex();

    static process::Future<Socket> future_accept;

    static Address __address__ = Address::ANY_ANY();

    static Gate* gate =new Gate();

    MyGarbageCollector* gc = nullptr;

    THREAD_LOCAL ActorBase* __actor__ = nullptr;

class ActorManager{
public:
    explicit ActorManager(const Option<string>& delegate);
    ~ ActorManager();

private:
    const Option<std::string> delegate;

    map<string,ActorBase*>  actors;
    std::recursive_mutex actors_mutex;
    map<ActorBase*, Gate*> gates;

    list<ActorBase*> runq;
    std::recursive_mutex runq_mutex;

    std::atomic_long running;

    vector<std::thread*> threads;

    std::atomic_bool joining_threads;

    std::atomic_bool finalizing;

};

    ActorManager::ActorManager(const Option<string> & _delegate):delegate(_delegate),running(0),joining_threads(false),finalizing(false) {

    }
    ActorManager::~ActorManager() {}

   ActorBase::ActorBase(const std::string &id) {
        state = ActorBase::BOTTOM;
    }

    ActorBase::~ActorBase(){

    }

    void  ActorBase::visit(const MyMessageEvent& myMessageEvent){

    }

    void  ActorBase::visit(const MyDispatchEvent & myDispatchEvent){

    }

    void  ActorBase::visit(const MyExitedEvent & myExitedEvent){

    }

    void  ActorBase::visit(const MyTerminateEvent & myTerminateEvent){

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

    bool initialize(const Option<std::string>& delegate ){
        if(initialize_started.load() && initialize_complete.load()){
            // initialize_started = true && initialize_complete = true
            return false;
        }else{
            bool expected = false;

            if(!initialize_started.compare_exchange_strong(expected,true)){
                // initialize_started = true but initialize_complete = false
                while (!initialize_complete.load());

                return false;
            }
            // initialize_started transfer from false to true, but initialize_complete = false, go to line 149
        }
        signal(SIGPIPE, SIG_IGN);

    }
}