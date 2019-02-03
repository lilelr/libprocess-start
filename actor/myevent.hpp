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

        MyMessage* const message;
    };

}

#endif //LIBPROCESS_START_MYEVENT_H
