//
// Created by lemaker on 2/7/19.
//

#ifndef LIBPROCESS_START_MYGC_HPP
#define LIBPROCESS_START_MYGC_HPP

#include "actor.hpp"

namespace actor{

    class MyGarbageCollector:public Actor<MyGarbageCollector>{
    public:
        MyGarbageCollector():ActorBase("__gc__"){}
        virtual ~MyGarbageCollector(){}
    protected:
        virtual void exited(const process::UPID& pid){
            if(actors.count(pid) > 0){
                const ActorBase* actor = actors[pid];
                actors.erase(pid);
                delete actor;
            }
        }
    private:
        std::map<process::UPID, ActorBase*> actors;
    };
}
#endif //LIBPROCESS_START_MYGC_HPP
