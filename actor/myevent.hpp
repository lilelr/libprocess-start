//
// Created by lemaker on 2/3/19.
//

#ifndef LIBPROCESS_START_MYEVENT_H
#define LIBPROCESS_START_MYEVENT_H

#include <memory>

#include <process/future.hpp>
#include <process/http.hpp>
#include <process/socket.hpp>

#include <stout/abort.hpp>
#include <stout/lambda.hpp>

#include "mymessage.hpp"
namespace actor{

    class ActorBase;
    struct MyMessageEvent;
    struct MyDispatchEvent;
    struct MyExitedEvent;
    struct MyTerminateEvent;

    struct MyEventVisitor{
        virtual ~MyEventVisitor(){}
        virtual void visit(const MyMessageEvent&){}
        virtual void visit(const MyDispatchEvent&){}
        virtual void visit(const MyExitedEvent&){}
        virtual void visit(const MyTerminateEvent&){}

    };

    struct MyEvent{
        virtual ~MyEvent(){}

        virtual void visit(MyEventVisitor* visitor) const =0;

        template <typename T>
        bool is() const{
            bool result = false;
            struct IsVisitor : MyEventVisitor{
                explicit IsVisitor(bool* _result):res(_result){}
                virtual void visit(const T&){
                    *res = true;
                }
                bool* res;
            }visitor(&result);

            visit(&visitor);
        }
    };

    struct MyMessageEvent:MyEvent{
        explicit MyMessageEvent(MyMessage* _message):message(_message){}

        MyMessageEvent(const MyMessageEvent& that):message(that.message == nullptr ? nullptr: new MyMessage(*that.message) ){}


        virtual ~MyMessageEvent(){
            delete message;
        }

        virtual void visit(MyEventVisitor *visitor) const override {
                visitor->visit(*this);
        }

        MyMessage* const message;

    private:
        MyMessageEvent& operator=(const MyMessageEvent&);
    };

    struct MyDispatchEvent: MyEvent{
        MyDispatchEvent(const process::UPID& _pid, const std::shared_ptr<lambda::function<void(ActorBase*)>>& _f,
        const Option<const std::type_info*>& _functionType):pid(_pid),f(_f),functionType(_functionType){

        }

        virtual void visit(MyEventVisitor *visitor) const override {
            visitor->visit(*this);
        }

        const process::UPID pid;
        const std::shared_ptr<lambda::function<void(ActorBase*)>>& f;
        const Option<const std::type_info*>& functionType;
    };

    struct MyExitedEvent: MyEvent{
        explicit MyExitedEvent(const process::UPID& _pid):pid(_pid){

        }

        virtual void visit(MyEventVisitor *visitor) const override {
            visitor->visit(*this);
        }


        const process::UPID pid;

    private:
        MyExitedEvent& operator=(const MyExitedEvent& that);
    };

    struct MyTerminateEvent : MyEvent{
        explicit MyTerminateEvent(const process::UPID& _pid):from(_pid){}

        virtual void visit(MyEventVisitor *visitor) const override {
            visitor->visit(*this);
        }

        const process::UPID from;

    private:
        MyTerminateEvent(const MyTerminateEvent&);
        MyTerminateEvent&operator=(const MyTerminateEvent&);

    };
}

#endif //LIBPROCESS_START_MYEVENT_H
