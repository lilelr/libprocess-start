//
// Created by lemaker on 2020/10/16.
//
#include <process/id.hpp>
#include <process/latch.hpp>
#include <process/process.hpp>

#include <stout/duration.hpp>

#include "Mylatch.hpp"

namespace process{
    Mylatch::Mylatch() :triggered(false){
        pid = spawn(new ProcessBase(ID::generate("__latch__")), true);

    }

    Mylatch::~Mylatch(){
      bool expected = false;
      if(triggered.compare_exchange_strong(expected,true)){
          terminate(pid);
      }
    }

    bool Mylatch::trigger() {
        bool expected = false;
        if(triggered.compare_exchange_strong(expected,true)){
            terminate(pid);
            return true;
        }

        return false;
    }

    bool Mylatch::await(const Duration& d){
        if(!triggered.load()){
            process::wait(pid,d);
            return triggered.load();
        }

        return true;

    }
}
