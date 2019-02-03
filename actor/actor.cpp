//
// Created by lemaker on 2/3/19.
//

#include "actor.hpp"


#include <errno.h>
#include <limits.h>

#ifndef __WINDOWS__

#include <netdb.h>

#endif // __WINDOWS__

#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __WINDOWS__

#include <unistd.h>

#include <arpa/inet.h>

#endif // __WINDOWS__

#include <glog/logging.h>

#ifndef __WINDOWS__

#include <netinet/in.h>
#include <netinet/tcp.h>

#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>

#endif // __WINDOWS__

#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory> // TODO(benh): Replace shared_ptr with unique_ptr.
#include <mutex>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

#include <process/address.hpp>
#include <process/check.hpp>
#include <process/clock.hpp>
#include <process/defer.hpp>
#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/executor.hpp>
#include <process/filter.hpp>
#include <process/future.hpp>
#include <process/gc.hpp>
#include <process/help.hpp>
#include <process/id.hpp>
#include <process/io.hpp>
#include <process/logging.hpp>
#include <process/mime.hpp>
#include <process/owned.hpp>
#include <process/profiler.hpp>
#include <process/reap.hpp>
#include <process/sequence.hpp>
#include <process/socket.hpp>
#include <process/statistics.hpp>
#include <process/system.hpp>
#include <process/time.hpp>
#include <process/timer.hpp>

using process::network::inet::Address;
using process::network::inet::Socket;

using process::network::internal::SocketImpl;
//using process::wait; // Necessary on some OS's to disambiguate.
namespace actor {


    static std::atomic_bool initialize_started(false);
    static std::atomic_bool initialize_complete(false);

    static const int LISTEN_BACKLOG = 5000;

    static Socket* __s__ = nullptr;

    void ActorBase::ActorBase(const std::string &id) {
//        actor::
    }

    void ActorBase::enqueue(MyEvent *event, bool inject) {
        CHECK(event != nullptr);

        synchronized(mutex)
            {
                if (state != TERMINATING && state != TERMINATED) {
                    if (!inject) {
                        events.push_back(event);
                    } else {
                        events.push_front(event);
                    }

                    if (state == BLOCKED) {
                        state = READY;
                    }

                    CHECK(state == BOTTOM || state == READY || state == RUNNING);
                } else {
                    delete event;
                }
            }
    }

    bool initialize(const Option<std::string>& delegate = None()){

    }
}