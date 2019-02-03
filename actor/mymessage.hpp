//
// Created by lemaker on 2/3/19.
//

#ifndef LIBPROCESS_START_MYMESSAGE_H
#define LIBPROCESS_START_MYMESSAGE_H

#include <string>

#include <process/pid.hpp>

namespace actor{
    struct MyMessage{
        std::string name;
        process::UPID from;
        process::UPID to;
        std::string body;
    };
}
#endif //LIBPROCESS_START_MYMESSAGE_H
