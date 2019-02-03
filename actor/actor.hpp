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
        void enqueue(MyEvent* event, bool inject = false);
        template<typename T>
        size_t eventCount(){
            size_t count = 0U;
            synchronized(mutex){
                count = std::count_if(events.begin(),events.end(),isEventType<T>);
            }
            return count;
        }

//    protected:
//
//        virtual void visit(const MyMessageEvent &);
//
//        virtual void visit(const MyDispatchEvent &);
//
//        virtual void visit(const MyExitedEvent &);
//
//        virtual void visit(const MyTerminateEvent &);


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
}
#endif //LIBPROCESS_START_ACTOR_HPP
