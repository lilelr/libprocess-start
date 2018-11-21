//
// Created by zyx on 18-11-21.
//

#ifndef LIBPROCESS_START_GPU_H
#define LIBPROCESS_START_GPU_H
#include <string>

using std::string;
/*
 * 类名：GpuClass
 *
 * */
class GpuClass {
public:

    explicit GpuClass(string description,string product,string vendor,string physical_id,string bus_info,string version,string width,string clock,string capabilities,string configuration,string resources);

    void set_description(string description) ;
    string get_description() ;

    void set_product(string product) ;
    string get_product() ;

    void set_vendor(string vendor) ;
    string get_vendor() ;

    void set_physical_id(string physical_id) ;
    string get_physical_id() ;

    void set_bus_info(string bus_info) ;
    string get_bus_info() ;

    void set_version(string version) ;
    string get_version() ;

    void set_width(string width) ;
    string get_width() ;

    void set_clock(string clock) ;
    string get_clock() ;

    void set_capabilities(string capabilities) ;
    string get_capabilities() ;

    void set_configuration(string configuration) ;
    string get_configuration() ;

    void set_resources(string resources) ;
    string get_resources() ;
    //  void executive_command();  //执行命令
    // void split_all_string(string all_info);
    // void split_part_string(string info); //将结果拆分
    //  void printf_test(); //测试输出

protected:
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


#endif //LIBPROCESS_START_GPU_H
