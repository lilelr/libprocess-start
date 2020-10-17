//
// Created by lemaker on 2020/10/16.
//

#ifndef LIBPROCESS_START_MYLATCH_HPP
#define LIBPROCESS_START_MYLATCH_HPP

#include <atomic>

#include <process/pid.hpp>

#include <stout/duration.hpp>

namespace process{


class Mylatch {
public:
    Mylatch();
    virtual ~Mylatch();

    bool operator==(const Mylatch& that){
        return this->pid == that.pid;
    }

    bool operator<(const Mylatch& that){
        return this->pid < that.pid;
    }

    bool trigger();
    bool await(const Duration& d = Seconds(-1));
protected:

private:
    // not copyable, not assignable
    Mylatch(const Mylatch& m);
    Mylatch& operator=(const Mylatch& m);
    std::atomic_bool triggered;
    UPID pid;
};
}

#endif //LIBPROCESS_START_MYLATCH_HPP
