//
// Created by lemaker on 2/3/19.
//

#include <iostream>

#include "actor.hpp"

using namespace actor;
using std::cout;
using std::cin;
using std::endl;

int main(){

    ActorBase actorBase;

    process::UPID pid1;
    MyExitedEvent* exitEvent1_p = new MyExitedEvent(pid1);
    actorBase.enqueue(exitEvent1_p);
    cout<<actorBase.eventCount<MyMessageEvent>()<<endl;

    MyMessage message1;
    message1.body = "first";
    MyMessageEvent* messageEvent1_p = new MyMessageEvent(&message1);
    MyMessage message2;
    message2.body = "second";
    MyMessageEvent* messageEvent2_p = new MyMessageEvent(&message2);

    actorBase.enqueue(messageEvent1_p);
    actorBase.enqueue(messageEvent2_p);



    cout<<"actor main"<<endl;
}