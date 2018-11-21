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
#include "gpu.h"

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
void split_part_string(std::string info) {
//    GpuInfo gpu_protpo;

    //   vector<GpuClass> gpuInfo_vec(2,GpuClass("none","none","none","none","none","none","none","none","none","none","none"));

    vector<GpuClass> gpuInfo_class;
    GpuClass gpu_class = GpuClass("none","none","none","none","none","none","none","none","none","none","none");

    vector<string> tokens = strings::split(info,"\n");
    vector<string>::iterator vec_iter;
    vector<GpuClass>::iterator gpu_itr;

    GpuInfo gpuInfoproto;
    GpuResult *gpuResultproto;

    //添加到protobuf中
    //gpuResultproto = gpuInfoproto.add_gpu_result();

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
//                gpuInfo_vec.push_back(getgpuinfo);
                gpuInfo_class.push_back(gpu_class);
                gpuInfo_class[index-1].set_description(strings::trim(*(vec+1)," "));

                //添加到protobuf中
                gpuResultproto = gpuInfoproto.add_gpu_result();
                gpuResultproto->set_description(strings::trim(*(vec+1)," "));
                //gpuResultproto.set_description(strings::trim(*(vec+1)," "));
                //gpuInfo_vec[index-1].set_description(strings::trim(*(vec+1)," "));
                // m_description = *(vec+1);
                //m_description = *(vec+1);
                // vector<string>::iterator h = vec + 1;
                //  cout<<"hahaha"<<*(vec+1)<<endl;

            }
            else if(*vec == "product"){
                gpuInfo_class[index-1].set_product(strings::trim(*(vec+1)," "));
                // m_product = *(vec+1);
                gpuResultproto->set_product(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "vendor"){
                gpuInfo_class[index-1].set_vendor(strings::trim(*(vec+1)," "));
                // m_vendor = *(vec+1);
                gpuResultproto->set_vendor(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "physical id"){
                gpuInfo_class[index-1].set_physical_id(strings::trim(*(vec+1)," "));
                // m_physical_id = *(vec+1);
                gpuResultproto->set_physical_id(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "bus info"){
                gpuInfo_class[index-1].set_bus_info(strings::trim(*(vec+1)," "));
                //m_bus_info = *(vec+1);
                gpuResultproto->set_bus_info(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "version"){
                gpuInfo_class[index-1].set_version(strings::trim(*(vec+1)," "));
                // m_version = *(vec+1);
                gpuResultproto->set_version(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "width"){
                gpuInfo_class[index-1].set_width(strings::trim(*(vec+1)," "));
                // m_width = *(vec+1);
                gpuResultproto->set_width(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "clock"){
                gpuInfo_class[index-1].set_clock(strings::trim(*(vec+1)," "));
                // m_clock = *(vec+1);
                gpuResultproto->set_clock(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "capabilities"){
                gpuInfo_class[index-1].set_capabilities(strings::trim(*(vec+1)," "));
                // m_capabilities = *(vec+1);
                gpuResultproto->set_capabilities(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "configuration"){
                gpuInfo_class[index-1].set_configuration(strings::trim(*(vec+1)," "));
                // m_configuration = *(vec+1);

                gpuResultproto->set_configuration(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "resources"){
                gpuInfo_class[index-1].set_resources(strings::trim(*(vec+1)," "));

                //添加到protobuf中
                gpuResultproto->set_resources(strings::trim(*(vec+1)," "));

            }

        }
    }
    // cout<<"fsddddddddd"<<endl;

    // printf_test();
    for(auto gpu_itr = gpuInfo_class.begin();gpu_itr!=gpuInfo_class.end();gpu_itr++){
        cout<<"--------------------------------------"<<endl;

        //cout<<*gpu_itr.operator->()->get_description()<<endl;
        cout<<gpu_itr.operator->()->get_description()<<endl;
        cout<<gpu_itr.operator->()->get_product()<<endl;
        cout<<gpu_itr.operator->()->get_physical_id()<<endl;
        cout<<gpu_itr.operator->()->get_bus_info()<<endl;
        cout<<gpu_itr.operator->()->get_version()<<endl;
        cout<<gpu_itr.operator->()->get_width()<<endl;
        cout<<gpu_itr.operator->()->get_clock()<<endl;
        cout<<gpu_itr.operator->()->get_configuration()<<endl;
        cout<<gpu_itr.operator->()->get_capabilities()<<endl;
        cout<<gpu_itr.operator->()->get_resources()<<endl;
    }

    GpuResult *inx;
    cout<<"size : "<<gpuInfoproto.gpu_result_size()<<endl;
    for(int i; i<gpuInfoproto.gpu_result_size(); i++){
        inx = gpuInfoproto.mutable_gpu_result(i);
        cout<<"第"<<i<<"组"<<inx->description()<<endl;
        cout<<"第"<<i<<"组"<<inx->product()<<endl;
        cout<<"第"<<i<<"组"<<inx->vendor()<<endl;
        cout<<"第"<<i<<"组"<<inx->physical_id()<<endl;
        cout<<"第"<<i<<"组"<<inx->bus_info()<<endl;
        cout<<"第"<<i<<"组"<<inx->version()<<endl;
        cout<<"第"<<i<<"组"<<inx->width()<<endl;
        cout<<"第"<<i<<"组"<<inx->clock()<<endl;
        cout<<"第"<<i<<"组"<<inx->capabilities()<<endl;
        cout<<"第"<<i<<"组"<<inx->configuration()<<endl;
        cout<<"第"<<i<<"组"<<inx->resources()<<endl;

    }

}
void executive_command(){
    Try<Subprocess> s = subprocess(
            "lshw -numeric -class video",
            Subprocess::FD(STDIN_FILENO),
            Subprocess::PIPE(),
            Subprocess::FD(STDERR_FILENO));
    Future<string> info = io::read(s.get().out().get());
    std::string s_info;
    s_info = info.get();
    cout<<"~~~~~~"<<info.get()<<"~~~~~"<<endl;
    split_part_string(s_info);
}

int main(){
    executive_command();
}


