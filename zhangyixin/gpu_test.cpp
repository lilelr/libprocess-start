//
// Created by zyx on 18-11-19.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include <process/io.hpp>
#include <stout/os.hpp>

#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include <process/protobuf.hpp>
#include <process/subprocess.hpp>
#include <stout/foreach.hpp>
#include <stout/fs.hpp>
#include <stout/try.hpp>
#include <stout/uuid.hpp>

#include <process/reap.hpp>
#include <stout/foreach.hpp>

#include <ctype.h>
#include <boost/functional/hash.hpp>
#include <stout/hashmap.hpp>

#include <map>
#include <string>

#include "GpuInfo.pb.h"
using namespace process;

//using namespace process::http; //Path 歧义

using std::cerr;
using std::cout;
using std::endl;

using os::ProcessTree;
using process::Subprocess;
using std::map;
using std::vector;
using os::Exec;
using os::Fork;
using proc::CPU;
using process::Clock;
using std::string;
using process::MAX_REAP_INTERVAL;

class GetGpuInfo {
public:
    void set_description(string m_description) {
        m_description = m_description;
    }

    string get_description() {
        return m_description;
    }

    void executive_command();  //执行命令
   // void split_all_string(string all_info);
    void split_part_string(string info); //将结果拆分
    void printf_test(); //测试输出

private:
    string m_description;
    string m_product;
    string m_vendor;
    string m_physical_id;
    string m_bus_info;
    string m_version;
    string m_width;
    string m_clock;
    string m_capabilities;
    string m_configuration;
    string m_resources;
};

void GetGpuInfo::executive_command(){
/*    Try<Subprocess> s = subprocess(
            "lshw -numeric -class video",
            Subprocess::FD(STDIN_FILENO),
            Subprocess::PIPE(),
            Subprocess::FD(STDERR_FILENO));
    Future<string> info = io::read(s.get().out().get());
    std::string s_info;
    s_info = info.get();
    cout<<"~~~~~~"<<info.get()<<"~~~~~"<<endl;*/
    string s_info = "  *-display\n"
                    "       description: 3D controller\n"
                    "       product: GK210GL [Tesla K80] [10DE:102D]\n"
                    "       vendor: NVIDIA Corporation [10DE]\n"
                    "       physical id: 0\n"
                    "       bus info: pci@0000:8c:00.0\n"
                    "       version: a1\n"
                    "       width: 64 bits\n"
                    "       clock: 33MHz\n"
                    "       capabilities: pm msi pciexpress bus_master cap_list\n"
                    "       configuration: driver=nvidia latency=0\n"
                    "       resources: iomemory:38680-3867f iomemory:386c0-386bf irq:38 memory:f7000000-f7ffffff memory:386800000000-386bffffffff memory:386c00000000-386c01ffffff\n"
                    "  *-display\n"
                    "       description: 3D controller\n"
                    "       product: GK210GL [Tesla K80] [10DE:102D]\n"
                    "       vendor: NVIDIA Corporation [10DE]\n"
                    "       physical id: 0\n"
                    "       bus info: pci@0000:8d:00.0\n"
                    "       version: a1\n"
                    "       width: 64 bits\n"
                    "       clock: 33MHz\n"
                    "       capabilities: pm msi pciexpress bus_master cap_list\n"
                    "       configuration: driver=nvidia latency=0\n"
                    "       resources: iomemory:38600-385ff iomemory:38640-3863f irq:38 memory:f6000000-f6ffffff memory:386000000000-3863ffffffff memory:386400000000-386401ffffff";
   // split_all_string(s_info);
    split_part_string(s_info);

}


void GetGpuInfo::split_part_string(std::string info) {
    GpuInfo gpu_protpo;

    vector<GetGpuInfo> gpuInfo_vec(3,GetGpuInfo());

    vector<string> tokens = strings::split(info,"\n");
    vector<string>::iterator vec_iter;
    vector<GetGpuInfo>::iterator gpu_itr;

    int index = 0; //gpu个数
  //  int i_index = 0;

    for(vec_iter = tokens.begin(); vec_iter != tokens.end(); vec_iter++){
        cout <<*vec_iter << "!!!!!"<<endl;
        if(strings::contains(*vec_iter, "display")){
            index++;
        }
        std::string romove_bs = strings::trim(*vec_iter," ");
        vector<string> line_token = strings::tokenize(romove_bs, ":", 2);

        cout<<index<<endl;
        //  cout << romove_bs << "@@@"<<endl;
        //    cout << line_token[0] << "*****"<<endl;
        for(vector<string>::iterator vec = line_token.begin();vec!=line_token.end();vec++){
            //cout <<*vec<<endl;
            if(*vec == "description"){
                gpuInfo_vec[index].set_description(*(vec+1));
                m_description = *(vec+1);
                // vector<string>::iterator h = vec + 1;
                //cout<<"hahaha"<<*(vec+1)<<endl;
            }
            else if(*vec == "product"){
                m_product = *(vec+1);
            }
            else if(*vec == "vendor"){
                m_vendor = *(vec+1);
            }
            else if(*vec == "physical id"){
                m_physical_id = *(vec+1);
            }
            else if(*vec == "bus info"){
                m_bus_info = *(vec+1);
            }
            else if(*vec == "version"){
                m_version = *(vec+1);
            }
            else if(*vec == "width"){
                m_width = *(vec+1);
            }
            else if(*vec == "clock"){
                m_clock = *(vec+1);
            }
            else if(*vec == "capabilities"){
                m_capabilities = *(vec+1);
            }
            else if(*vec == "configuration"){
                m_configuration = *(vec+1);
            }
            else if(*vec == "resources"){
                m_resources = *(vec+1);
            }
        }
    }
   // cout<<"fsddddddddd"<<endl;

   // printf_test();
    for(auto gpu_itr = gpuInfo_vec.begin();gpu_itr!=gpuInfo_vec.end();gpu_itr++){
        cout<<"fsddddddddd"<<endl;

        cout<<*gpu_itr.operator->()->get_description()<<endl;
    }
}

void GetGpuInfo::printf_test() {
    cout<<"---------------------------"<<endl;
    cout<<"description :"<<m_description<<endl;
    cout<<"product :"<<m_product<<endl;
    cout<<"vendor :"<<m_vendor<<endl;
    cout<<"physical id :"<<m_physical_id<<endl;
    cout<<"bus info :"<<m_bus_info<<endl;
    cout<<"version :"<<m_version<<endl;
    cout<<"width :"<<m_width<<endl;
    cout<<"clock :"<<m_clock<<endl;
    cout<<"capabilities :"<<m_capabilities<<endl;
    cout<<"configuration :"<<m_configuration<<endl;
    cout<<"resources :"<<m_resources<<endl;
}

int main(){
    GetGpuInfo gpuInfo;
    gpuInfo.executive_command();
/*    string ss = "resources: 1";
    vector<string> line_token1 = strings::tokenize(ss, ":", 2);
    cout << line_token1[0] << "*****"<<line_token1[1]<<endl;*/
}


