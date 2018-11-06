//
// Created by weiguow on 18-10-31.
//
#include <iostream>
#include <sstream>
#include <memory>
#include <string>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>

#include <Student_pro.pb.h>

using namespace process;

using namespace process::http;

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::chrono::seconds;

using process::Future;
using process::Promise;

using process::http::Request;
using process::http::OK;
using process::http::InternalServerError;


class Student_Client : public ProtobufProcess<Student_Client> {
public:

    Student_Client() : ProcessBase("Student_Client") {}

    UPID server;

    virtual void initialize() {

        install<Student_pro>(&Student_Client::report_from_server, &Student_pro::name);
    }

    void report_from_server(const string &name) {
        cout << "report from server" << endl;
        cout << name << endl;
    }

    void send_server_a_message() {
        cout << "学生信息是" << endl;

        //按照消息体的形式定义消息,自带set_name方法？？是的
        Student_pro s;
        s.set_name("weiguo");
        s.set_id(2);
        s.set_age(23);

        cout << "name:" << s.name() <<" 学号：" << s.id() << " 年龄：" << s.age() << endl;
        send(server, s);
    }

};

int main() {
    Student_Client client;
    process::spawn(client);
    cout << "Running client on " << process::address().ip << ":" << process::address().port << endl;  //显示ip地址和端口
    cout << "PID" << endl;
    cout << "please input the master UPID:" << endl;

    //输入服务端的ip地址和端口号
    string master_str;  //
    std::cin >> master_str;

    //调用UPID构造方法,输入参数mater_str
    UPID masterUPID(master_str);

    client.server = masterUPID;  //声明client的服务器是masterUPID

    client.send_server_a_message();  //client向server发送消息


    process::wait(client.self());

//    client.report_from_server();

    return 0;
}


