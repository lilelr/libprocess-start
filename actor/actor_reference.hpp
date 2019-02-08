//
// Created by lemaker on 2/8/19.
//

#ifndef LIBPROCESS_START_ACTOR_REFERENCE_HPP
#define LIBPROCESS_START_ACTOR_REFERENCE_HPP

#include "actor.hpp"
namespace actor{
    class ActorReference{
    public:
        ActorReference():actor(nullptr){}

        ~ ActorReference(){
            cleanup();
        }
        ActorReference(const ActorReference& that){
            copy(that);
        }

        ActorReference& operator=(const ActorReference& that){
            if(this != &that){
                cleanup();
                copy(that);
            }
            return *this;
        }

        ActorBase* operator->() const{
            return actor;
        }

        operator ActorBase*() const{
            return actor;
        }

        operator bool() const{
            return actor!=nullptr;
        }

    private:
        friend class ActorManager;
        explicit ActorReference(ActorBase* _actor):actor(_actor){
           if(actor!=nullptr){
           actor->refs.fetch_add(1);
           }
        }

        void copy(const ActorReference& that){
            actor = that.actor;

            if(actor != nullptr){
                CHECK(actor->refs.load() > 0);
                actor->refs.fetch_add(1);
            }
        }

        void cleanup(){
            if(actor != nullptr){
                actor->refs.fetch_sub(1);
            }
        }

        ActorBase* actor;
    };
}
#endif //LIBPROCESS_START_ACTOR_REFERENCE_HPP
