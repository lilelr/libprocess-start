/*
 * 版权所有：深圳先进研究所异构智能计算体系结构与系统研究中心
 * 作者：heldon 764165887@qq.com
 * 编写日期：18-11-26
 * 功能描述：get disk's information
 */
#include <iostream>
#include <sys/statfs.h>
#include <string>

#include <stout/path.hpp>
#include <stout/try.hpp>
#include <stout/strings.hpp>
#include <stout/jsonify.hpp>
#include <stout/protobuf.hpp>

#include <process/subprocess.hpp>
#include <process/protobuf.hpp>
#include <process/io.hpp>

#include <proto/disk_info.pb.h>

namespace io = process::io;

using process::Subprocess;
using process::subprocess;

using std::cout;
using std::endl;
using std::string;

/*
 * 类名： Disk_info
 * 作者：heldon  764165887@qq.com
 * 编写日期：18-11-26
 * 功能描述： the Class of disk information
 */
class Diskinfo {
public:
    Diskinfo(string disk_name, string disk_size, string disk_type, string disk_speed, string disk_free,
             string disk_available) : m_disk_name(disk_name), m_disk_size(disk_size), m_disk_type(disk_type),
                                      m_disk_speed(disk_speed),
                                      m_disk_free(disk_free), m_disk_available(disk_available) {}

public:
    const string &getM_disk_name() const {
        return m_disk_name;
    }

    void setM_disk_name(const string &m_disk_name) {
        Diskinfo::m_disk_name = m_disk_name;
    }

    const string &getM_disk_type() const {
        return m_disk_type;
    }

    void setM_disk_type(const string &m_disk_type) {
        Diskinfo::m_disk_type = m_disk_type;
    }

    const string &getM_disk_speed() const {
        return m_disk_speed;
    }

    void setM_disk_speed(const string &m_disk_speed) {
        Diskinfo::m_disk_speed = m_disk_speed;
    }

    const string &getM_disk_free() const {
        return m_disk_free;
    }

    const string &getM_disk_size() const {
        return m_disk_size;
    }

    void setM_disk_size(const string &m_disk_size) {
        Diskinfo::m_disk_size = m_disk_size;
    }

    void setM_disk_free(const string &m_disk_free) {
        Diskinfo::m_disk_free = m_disk_free;
    }

    const string &getM_disk_available() const {
        return m_disk_available;
    }

    void setM_disk_available(const string &m_disk_available) {
        Diskinfo::m_disk_available = m_disk_available;
    }

private:
    string m_disk_name;  /*disk's name*/
    string m_disk_size;  /*disk's size*/
    string m_disk_type;  /*disk's type*/
    string m_disk_speed; /*disk's speed*/
    string m_disk_free;  /*the rest of storage space*/
    string m_disk_available; /*disk's available storage space*/

};

class AllDisk{
public:
    /*
     * 函数名称：get_disk_info
     * 作者：heldon
     * 编写日期：2018/9/8
     * 功能描述：get disk's name,size,type,speed,rest of storage,available storag
     * 输入参数说明：none
     * 返回值说明：list<Diskinfo>
     */
        std::list<Diskinfo> get_all_disk_info() {
            Option<string> disk_name;  /*disk's name*/
            Option<string> disk_size;  /*disk's size*/
            Option<string> disk_type;  /*disk's type*/
            Option<string> disk_speed; /*disk's speed*/
            Option<string> disk_free;  /*the rest of storage space*/
            Option<string> disk_available; /*disk's available storage space*/

            /*use lsblk -J command to get disk's name,size,type by JSON format*/
            Try<Subprocess> lsblk_process = subprocess(
                    "lsblk -J",
                    Subprocess::FD(STDIN_FILENO),
                    Subprocess::PIPE(),
                    Subprocess::FD(STDERR_FILENO));

            process::Future<string> lsblk_get = io::read(lsblk_process.get().out().get());
            string lsblk_string = lsblk_get.get();

            /*change string to JSON Object */
            Try<JSON::Value> lsblk_value = JSON::parse(lsblk_string);
            JSON::Object lsblk_json_object = lsblk_value->as<JSON::Object>();

            /*define constant of name,size,type */
            const string name_t = "name";
            const string size_t = "size";
            const string type_t = "type";
            std::list<Diskinfo> results;

            /*get JSON Object's array which called "blockdevices"*/
            Try<JSON::Value> json_object_blockdevices = lsblk_json_object.values["blockdevices"];
            if (json_object_blockdevices.isSome()) {
                JSON::Value blockdevices = json_object_blockdevices.get();
                if (blockdevices.is<JSON::Array>()) {
                    std::vector<JSON::Value> blockdevices_array = blockdevices.as<JSON::Array>().values;
                    /* iterate through the array called blockdevices*/
                    for (int i = 0; i < blockdevices_array.size(); i++) {
                        JSON::Object blockdevices_array_object = blockdevices_array.at(i).as<JSON::Object>();
                        /*get thr map from the array*/
                        std::map<string, JSON::Value> blockdevices_array_object_map = blockdevices_array_object.values;
                        /*Determine whether there is a key called "type" in the map*/
                        if (blockdevices_array_object_map.count(type_t)) {
                            /*Determin whether there is a value called "disk" in the map*/
                            if (blockdevices_array_object_map[type_t].as<JSON::String>().value == "disk") {
                                /*Assign value to member variables*/
                                //cout<<"m_disk_name :"<< m_disk_name.get()<<endl;
                                disk_name = blockdevices_array_object_map.at(name_t).as<JSON::String>().value;
                                disk_size = blockdevices_array_object_map.at(size_t).as<JSON::String>().value;
                                disk_type = blockdevices_array_object_map.at(type_t).as<JSON::String>().value;


                                /*use hdparm command to get current speed of disk*/
                                string hdparm_command = "sudo -S hdparm -t /dev/" + disk_name.get();
                                Try<Subprocess> hdparm_process = subprocess(
                                        hdparm_command,
                                        Subprocess::FD(STDIN_FILENO),
                                        Subprocess::PIPE(),
                                        Subprocess::FD(STDERR_FILENO));

                                process::Future<string> hdparm_get = io::read(hdparm_process.get().out().get());
                                string hdparm_string = hdparm_get.get();
                                /*tokensize the string as blank space*/
                                std::vector<string> hdparm_token = strings::tokenize(hdparm_string, " ");
                                /*The second-to-last is disk's speed
                                  Assign value to variable*/
                                disk_speed = hdparm_token.at(hdparm_token.size() - 2);

                                /*use statfs to get disk's rest storage,available storage*/
                                struct statfs diskInfo;
                                /*find the information under the path "/home" */
                                statfs("/home", &diskInfo);

                                /*The number of bytes contained in each block*/
                                unsigned long long blocksize = diskInfo.f_bsize;
                                /*The total number of bytes, f_blocks is the number of blocks*/
                                unsigned long long totalsize = blocksize * diskInfo.f_blocks;
                                /*The size of the remaining space*/
                                unsigned long long freeDisk = diskInfo.f_bfree * blocksize;
                                /*The size of the avaliable space*/
                                unsigned long long availableDisk = diskInfo.f_bavail * blocksize; //可用空间大小

                                /*Transfer the GB unit and assign to variables*/
                                disk_free = stringify(freeDisk >> 30);
                                disk_available = stringify(availableDisk >> 30);

                                if (disk_name.isSome() && disk_size.isSome() && disk_type.isSome() && disk_speed.isSome() &&
                                    disk_free.isSome() && disk_available.isSome()) {
                                    results.push_back(
                                            Diskinfo(disk_name.get(), disk_size.get(), disk_type.get(), disk_speed.get(),
                                                     disk_free.get(),
                                                     disk_available.get()));
                                }
                            }
                                /*if there isn't a key called "type"*/
                            else
                                continue;
                        }
                    }
                }
            }
            return results;
        }

        friend std::ostream &operator<<(std::ostream &stream, AllDisk *&all_disk) {

            std::list<Diskinfo> diskinfo = all_disk->get_all_disk_info();

            for(auto i = diskinfo.begin();i != diskinfo.end();i++){
                stream << "name: "                    << i->getM_disk_name()
                       << " size: "                   << i->getM_disk_size()
                       << " type: "                   << i->getM_disk_type()      <<'\n'
                       <<"Timing disk reads speed = " << i->getM_disk_speed()     << " MB/s " << '\n'
                       << "Disk_free = "              << i->getM_disk_free()      << " GB"    << '\n'
                       << "Disk_available = "         << i->getM_disk_available() << " GB";
            }
            return stream;
        }
};

int main() {
    AllDisk *allDisk;
    cout<<allDisk<<endl;
    return 0;

}

