/*
 * simpleserver.cpp
 *
 * Created on: Jun 26, 2015
 * Author: Marco Massenzio, http://codetrips.com
 *
 * This code is explained in a blog entry at the above URL.
 */

#include <chrono>
#include <iostream>
#include <thread>

#include <process/async.hpp>
#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/defer.hpp>
#include <process/owned.hpp>


#include <stout/json.hpp>
#include <stout/numify.hpp>


using std::cerr;
using std::cout;
using std::endl;

using std::chrono::seconds;

using process::async;
using process::Future;
using process::Promise;
using process::defer;
using process::Deferred;
using process::Future;
using process::Owned;
using process::PID;
using process::Process;
using process::ProcessBase;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;


class SimpleProcess : public process::Process<SimpleProcess> {

public:
    SimpleProcess() : ProcessBase("simple") {}

    virtual void initialize();

    Future<bool> done() {
        cout << "are we done yet? " << endl;
        return shouldQuit.future();
    }

    void shutdown() {
        cout << "Shutting down server..." << endl;
        this->shouldQuit.set(true);
    }

private:
    Promise<bool> shouldQuit;
};


void SimpleProcess::initialize() {

}


int runServer() {
    int retCode;
    SimpleProcess simpleProcess;
    process::PID<SimpleProcess> pid = process::spawn(simpleProcess);


    Deferred<Future<int>(int)> deferred = defer(simpleProcess,[](int i)->int{
        // Invoke asynchronously uisng 'simpleProcess' as the execution context.
       std::cout<<"with defer, asychronously "<<" "<<i<<std::endl;
       return i;
    });

    Promise<int> promise;

    promise.future().then([](int i)->int{
        // Invoked synchronously from the execution context of the thread that completes the future!
        std::cout<<"without defer , synchronously "<<i<<std::endl;
        return i;
    });

    promise.set(42);
    promise.future().then(deferred);

    process::terminate(simpleProcess);
    process::wait(simpleProcess);
    return retCode;
}

int main(){
    int retCode = runServer();
    return 0;
}