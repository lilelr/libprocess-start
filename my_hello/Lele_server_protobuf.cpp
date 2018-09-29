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

class Master:public ProtobufProcess<Master>{

public:
    Master():ProcessBase("my_master"){
    }


    virtual void initialize()
    {
//     route("/vars", &MyProcess::vars);
        route("/vars","hello ", [=] (const Request& request) {
            string body = "... vars here ...";
            OK response;
            response.headers["Content-Type"] = "text/plain";
            std::ostringstream out;
            out << body.size();
            response.headers["Content-Length"] = out.str();
            response.body = body;
            return response;
        });

//     install("stop", &MyProcess::stop);
        install("stop", [=] (const UPID& from, const string& body) {
            terminate(self());
        });

        install<Offer>(&Master::report_from_client, &Offer::key);
    }

    void report_from_client(const string& key){
        cout<<"entering into report"<<endl;
        cout<<key<<endl;
        UPID clientUPID(key);

        Offer server_offer;
        server_offer.set_key("server_key");
        server_offer.set_value("server_value");
        server_offer.set_lele_label("server_label");
        send(clientUPID,server_offer);
    }

};

int main(){
    Offer k;
    k.set_key("company");
    k.set_value("leoox");

    k.set_lele_label("OS:linux");
     process::initialize("master");
    Master master;
    process:PID<Master> cur_master =  process::spawn(master);
    cout<<"Running server on "<<process::address().ip<<":"<<process::address().port<<endl;
    cout<< "PID"<<endl;

    const PID<Master> masterPid = master.self();
    cout<<masterPid<<endl;
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