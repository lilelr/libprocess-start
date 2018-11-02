// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License

#include <iostream>
#include <sstream>
#include <fstream>


#include <stout/os.hpp>

#ifndef __WINDOWS__
#include <stout/os/fork.hpp>
#endif // __WINDOWS__
#include <stout/os/pstree.hpp>


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

#ifndef __WINDOWS__
using os::Exec;
using os::Fork;
#endif // __WINDOWS__
using os::Process;
using os::ProcessTree;

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

class Master : public ProtobufProcess<Master> {

public:
    Master() : ProcessBase("my_master") {
    }


    virtual void initialize() {

////route("/add",)
//        route("/add", "Adds the two query arguments", [](Request request) {
//            int a = 3;
//            int b = 4;
//            std::ostringstream result;
//            result << " { " << "\"result\":" << a + b << "}";
//            JSON::Value body = JSON::parse(result.str()).get();
//            return OK(body);
//        });
//
////route("/vars", &MyProcess::vars);
//        route("/vars", "hello ", [=](const Request &request) {
//            string body = "... vars here ...";
//            OK response;
//            response.headers["Content-Type"] = "text/plain";
//            std::ostringstream out;
//            out << body.size();
//            response.headers["Content-Length"] = out.str();
//            response.body = body;
//            return response;
//        });

//install("stop", &MyProcess::stop);
        // my_master@10.211.55.4:42331/
        // http://10.211.55.4:43263/my_master/add
        route(
                "/add",
                "Adds the two query arguments",
                [](Request request) {
//                int a = numify<int>(request["a"]).get();
//                int b = numify<int>(request["b"]).get();
                    int a = 3;
                    int b = 4;
                    std::ostringstream result;
                    result << "{ \"result\": " << a + b << "}";
                    JSON::Value body = JSON::parse(result.str()).get();
                    return OK(body);
                });

//     route("/vars", &MyProcess::vars);
//        route("/vars", "hello ", [=]( Request &request) {
//            string body = "... vars here ...";
//            OK response;
//            response.headers["Content-Type"] = "text/plain";
//            std::ostringstream out;
//            out << body.size();
//            response.headers["Content-Length"] = out.str();
//            response.body = body;
//            return response;
//        });

//     install("stop", &MyProcess::stop);
        install("stop", [=](const UPID &from, const string &body) {
            terminate(self());
        });

        install<Offer>(&Master::report_from_client, &Offer::key,&Offer::value);
    }

    void report_from_client(const string &key,const string& value) {
        cout << "entering into report" << endl;
        String2Image(value,"./hello-python.py");

//        Try<ProcessTree> res = Fork(None(),Exec("./hello_world &"))();
//        Try<ProcessTree> res = Fork(None(),Exec("java -jar ./java-hello-thread.jar"))();
        Try<ProcessTree> res = Fork(None(),Exec("python3 ./hello-python.py"))();
//        cout << key << endl;
        UPID clientUPID(key);

        Offer server_offer;
        server_offer.set_key("李乐乐");
        server_offer.set_value("server_value");
        server_offer.set_lele_label("server_label");
        send(clientUPID, server_offer);
    }

    void String2Image(string binFile,const char* outImage)
    {
        fstream imgFile(outImage,ios::binary|ios::out);

        for(int i=0; i<binFile.length(); ++i)
        {
            imgFile << binFile[i];
        }

        imgFile.close();
    }

};

int main() {
    Offer k;
    k.set_key("company");
    k.set_value("leoox");
    k.set_lele_label("OS:linux");
    process::initialize("master");
    Master master;

    PID<Master> cur_master = process::spawn(master);
    cout << "Running server on " << process::address().ip << ":" << process::address().port << endl;
    cout << "PID" << endl;

    const PID<Master> masterPid = master.self();
    cout << masterPid << endl;
//   string a =  getenv("LIBPROCESS_PORT");
//    cout<<a<<endl;
//    process::dispatch(masterPid,&Master::report,k.key());
    process::wait(master.self());
//    delete master;
//    Offer k;
//    k.set_key("company");
//    k.set_value("leoox");
//    k.set_lele_label("OS:linux");
//
//
//    cout << k.key() << ":" << k.value() << ":"<<k.lele_label()<<endl;
//
//    int id;
//    cin>> id;
//    tutorial::AddressBook addressBook;
//    tutorial::Person* person1 = addressBook.add_people();
//    person1->set_id(id);
//    cout<<person1->id()<<endl;
    return 0;
}