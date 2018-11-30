//
// Created by zyx on 18-11-26.
//
#include "GpuCollector.h"

int main(){
    GpuCollector gpuCollector;
 //   cout<<gpuCollector.get_gpu_string()<<endl;

    gpuCollector.split_gpu_string(gpuCollector.get_gpu_string());

    vector<GpuClass> gpuClass = gpuCollector.get_gpu_class();

    for(auto itr = gpuClass.begin();itr!=gpuClass.end();itr++){
        cout<<"--------------------------------------"<<endl;
        //cout<<*gpu_itr.operator->()->get_description()<<endl;
        cout<<itr.operator->()->get_description()<<endl;
        cout<<itr.operator->()->get_product()<<endl;
        cout<<itr.operator->()->get_physical_id()<<endl;
        cout<<itr.operator->()->get_bus_info()<<endl;
        cout<<itr.operator->()->get_version()<<endl;
        cout<<itr.operator->()->get_width()<<endl;
        cout<<itr.operator->()->get_clock()<<endl;
        cout<<itr.operator->()->get_configuration()<<endl;
        cout<<itr.operator->()->get_capabilities()<<endl;
        cout<<itr.operator->()->get_resources()<<endl;
    }

    GpuInfo proto = gpuCollector.get_gpu_proto();
    GpuResult *inx;
    cout<<"size : "<<proto.gpu_result_size()<<endl;
    for(int i; i<proto.gpu_result_size(); i++){
        inx = proto.mutable_gpu_result(i);
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
