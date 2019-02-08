//
// Created by lemaker on 2/4/19.
//

#ifndef LIBPROCESS_START_MYEVENT_LOOP_HPP
#define LIBPROCESS_START_MYEVENT_LOOP_HPP
#include <stout/duration.hpp>
#include <stout/lambda.hpp>

namespace actor{
    class MyEventLoop{
    public:
        // Initializes the event loop.
        static void initialize();

        // Invoke the specified function in the event loop after the
        // specified duration.
        // TODO(bmahler): Update this to use rvalue references.
        static void delay(
                const Duration& duration,
                const lambda::function<void()>& function);

        // Returns the current time w.r.t. the event loop.
        static double time();

        // Runs the event loop.
        static void run();

        // Asynchronously tells the event loop to stop and then returns.
        static void stop();
    };
}
#endif //LIBPROCESS_START_MYEVENT_LOOP_HPP
