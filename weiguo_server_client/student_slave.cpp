//
// Created by weiguow on 18-10-31.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>

#include <Student_pro.pb.h>
#include <Transfile.pb.h>

using namespace process;

using namespace process::http;

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::chrono::seconds;
using std::ifstream;
using std::ios_base;

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
        install("stop", [=](const UPID &from, const string &body) {
            terminate(self());
        });
        /*
         * 函数名：install
         * 参数类型：<想要监听的message名字>
         * 注册的方法名字，以及该方法用到message参数
         * */
        install<Transfile>(&Student_Client::report_from_server, &Transfile::key);

    }

    void report_from_server(const string &key) {
        cout << "report from server" << endl;
        cout << key << endl;
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

    void send_server_a_file() {
        Transfile t;
        string client_id = this->self();
        string str_file =  read_a_python_file();
        t.set_key(client_id);
        t.set_value(str_file);
        send(server, t);
    }

    //从服务端传输一个python文件到客户端
    /*ios::app：　　　以追加的方式打开文件
　　   ios::ate：　　　文件打开后定位到文件尾，ios:app就包含有此属性
　　   ios::binary：　以二进制方式打开文件，缺省的方式是文本方式。两种方式的区别见前文
　　   ios::in：　　　 文件以输入方式打开(文件数据输入到内存)
　　   ios::out：　　　文件以输出方式打开(内存数据输出到文件)
　　   ios::nocreate： 不建立文件，所以文件不存在时打开失败
　　   ios::noreplace：不覆盖文件，所以打开文件时如果文件存在失败
　　   ios::trunc：　　如果文件存在，把文件长度设为0
     */
    string read_a_python_file() {
        string str_f;
        ifstream myfile("/home/weiguow/hello.py",ios_base::in);
        if (myfile.fail()) {
            cout << "读取文件失败" << endl;
        } else {
            char ch;
            while(myfile.get(ch)){
                str_f += ch;
            }
            if(myfile.eof()){
                cout << "文件已经全部读取完成" << endl;
                cout << "文件内容为:"<< str_f << endl;
                myfile.close();
            }
        }
        return  str_f;
    }

};

int main() {
    process::initialize("slave");  //只有初始化才会开始监听消息体

    Student_Client client;
    PID<Student_Client> cur_client = process::spawn(client);
    cout << "Running client on " << process::address().ip << ":" << process::address().port << endl;  //显示ip地址和端口
    cout << "please input the master UPID:" << endl;

    //输入服务端的ip地址和端口号
    string master_str;  //
    std::cin >> master_str;

    //调用UPID构造方法,输入参数mater_str
    UPID masterUPID(master_str);
    client.server = masterUPID;  //声明client的服务器是masterUPID
    client.send_server_a_message();  //client向server发送消息

    client.send_server_a_file();  //传输python文件

//    client.read_a_python_file();
    process::wait(client.self());
//    client.report_from_server();

    return 0;
}


