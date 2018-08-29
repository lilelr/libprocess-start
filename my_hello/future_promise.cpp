
#include <iostream>
#include <sstream>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>

#include <addressbook.pb.h>
#include "Offer.pb.h"

using namespace process;

using namespace process::http;

using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;

using std::string;
using namespace std;


int main(int argc, char** argv)
{
    Promise<int> promise;

    // Set up a callback to discard the future if
    // requested (this is not always possible!).
    promise.future().onDiscard([&]() {
        promise.discard();
    });

    Future<int> future = promise.future();

//    CHECK_PENDING(future);

    future.discard();

//    CHECK_DISCARDED(future); // NO LONGER PENDING!

    return 0;
}