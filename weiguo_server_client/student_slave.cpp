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

#include <student_pro.pb.h>
#include <transfile.pb.h>
#include <cpuinfo_pro.pb.h>


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

        install<Transfile>(&Student_Client::report_from_server, &Transfile::key);

        install<AllCpuInfo_SingleInfo>(&Student_Client::report_cpuinfo_from_server_all, &AllCpuInfo_SingleInfo::cpuid,
                                       &AllCpuInfo_SingleInfo::coreid, &AllCpuInfo_SingleInfo::physicalid,
                                       &AllCpuInfo_SingleInfo::cpucores, &AllCpuInfo_SingleInfo::modelname,
                                       &AllCpuInfo_SingleInfo::cpumhz, &AllCpuInfo_SingleInfo::l1dcache);

    }

/************************************1.CPU information***************************************/

    /**
     * 2.to get all cpu information from master
     * */
    void send_request_cpuinfo_all() {
        AllCpuInfo_SingleInfo as;
        string client_id = this->self();
        as.set_address(client_id);
        send(server, as);
    }

    /**
     * 3.get information from server
     * */
    void report_cpuinfo_from_server(const string &cpuid, const string &coreid){
        cout << "cpuID:" << coreid << " coreID:" << coreid << endl;
    }

    /**
     * 4.get all information from server
     * */
    void report_cpuinfo_from_server_all(const string &cpuid, const string &coreid, const string &physicalid,
                                        const string &cpucores, const string &modelname, const string &cpumhz,
                                        const string &l1dcache) {
        cout << "CPU information" << endl;
        cout << "cpuID:" << cpuid << "   coreID:" << coreid << "   Physical ID:" << physicalid
             << "   cpu cores:" << cpucores << "   model name:" << modelname << "   cpu MHz:"
             << cpumhz << "   L1d cache:" << l1dcache << endl;
    }

    /**
     * 5.send for all information
     * */
     void send_server_a_key_cpu(){
         AllCpuInfo ac;
         string client_ID = this->self();
         ac.set_key_cpu(client_ID);
         send(server,ac);
     }

/***************************************************************************************/




/*****************************2.send student message************************************/
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

        cout << "name:" << s.name() << " 学号：" << s.id() << " 年龄：" << s.age() << endl;
        send(server, s);
    }

    void send_server_a_file() {
        Transfile t;
        string client_id = this->self();
        string str_file = read_a_python_file();
        t.set_key(client_id);
        t.set_value(str_file);
        send(server, t);
    }
/*****************************************************************************/





/*******************************3.send a file ***********************************/
    string read_a_python_file() {
        string str_f;
        ifstream myfile("/home/weiguow/hello.py", ios_base::in);
        if (myfile.fail()) {
            cout << "读取文件失败" << endl;
        } else {
            char ch;
            while (myfile.get(ch)) {
                str_f += ch;
            }
            if (myfile.eof()) {
                cout << "文件已经全部读取完成" << endl;
                cout << "文件内容为:" << str_f << endl;
                myfile.close();
            }
        }
        return str_f;
    }
/*********************************************************************/

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


    //向服务器发送消息请求
    client.send_server_a_message();  //client向server发送消息
    client.send_server_a_file();  //传输python文件
    client.send_request_cpuinfo_all();
    client.send_server_a_key_cpu();
    process::wait(client.self());


    return 0;
}


