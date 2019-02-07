//
// Created by lemaker on 2/3/19.
//

#ifndef LIBPROCESS_START_ACTOR_HPP
#define LIBPROCESS_START_ACTOR_HPP

#include <stdint.h>

#include <map>
#include <queue>
#include <vector>

#include <process/mime.hpp>
#include <process/owned.hpp>
#include <process/pid.hpp>

#include <stout/duration.hpp>
#include <stout/lambda.hpp>
#include <stout/option.hpp>
#include <stout/synchronized.hpp>
#include <stout/thread_local.hpp>
#include <process/clock.hpp>
#include <process/address.hpp>


#include "mymessage.hpp"
#include "myevent.hpp"

namespace actor {

    class ActorBase : public MyEventVisitor {
    public:

        explicit ActorBase(const std::string& id="");

        virtual ~ActorBase();

        process::UPID self() const {return pid;}

        void enqueue(MyEvent* event, bool inject = false);
        template<typename T>
        size_t eventCount(){
            size_t count = 0U;
            synchronized(mutex){
                count = std::count_if(events.begin(),events.end(),isEventType<T>);
            }
            return count;
        }

    protected:
        // Invoked when an event is serviced.
        virtual void serve(const MyEvent& event){
            event.visit(this);
        }
//
    //   Callbacks used to bisit (i.e. handle) specific event
        virtual void visit(const MyMessageEvent &);

        virtual void visit(const MyDispatchEvent &);

        virtual void visit(const MyExitedEvent &);

        virtual void visit(const MyTerminateEvent &);

        /**
 * Invoked when a actor gets spawned.
 */
        virtual void initialize() {}

        /**
         * Invoked when a actor is terminated.
         *
         * **NOTE**: this does not get invoked automatically if
         * `visit(const TerminateEvent&)` is overridden.
         */
        virtual void finalize() {}


        void send(const process::UPID& to,
                  const std::string& name,
                  const char* data = nullptr,
                    size_t length = 0);


    private:
//        friend class process::SocketManager;
        //
        enum {
            BOTTOM,
            READY,
            RUNNING,
            BLOCKED,
            TERMINATING,
            TERMINATED
        } state;

        template<typename T>
        static bool isEventType(const MyEvent *event) {
            return event->is<T>();
        }



        std::recursive_mutex mutex;
        std::map<std::string, process::UPID> delegates;
        std::deque<MyEvent*> events;
        std::atomic_long refs;
        process::UPID pid;
    };

    template <typename T>
    class Actor:public virtual ActorBase{
    public:
        ~Actor(){}

        process::PID<T> self() const{
            return process::PID<T>(static_cast<const T*>(this));
        }

    protected:
        typedef T Self;
        typedef T This;
    };

/**
* Initialize the library.
*
* **NOTE**: `actor` uses Google's `glog` and you can specify options
* for it (e.g., a logging directory) via environment variables.
 * */

    bool initialize(const Option<std::string>& delegate = None());
}
#endif //LIBPROCESS_START_ACTOR_HPP
