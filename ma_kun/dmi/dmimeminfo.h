//
// Created by marcie on 18-11-26.
//

#ifndef LIBPROCESS_START_DMIMEMINFO_H
#define LIBPROCESS_START_DMIMEMINFO_H

#include <signal.h>
#include <process/subprocess.hpp>
#include <process/io.hpp>
#include <stout/strings.hpp>

#include <dmidecode.h>
#include <DmiInfo.pb.h>
#include <MemInfo.pb.h>

using process::subprocess;
using process::Subprocess;
using process::Future;

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

class DmiMemInfo {
protected:
    /*
     * the number of size,type,speed.
     */
    int num_size, num_type, num_speed;

    /*
     * defining a default Dmidecode class.
     */
    Dmidecode dflt;

    /*
     * class ptr.
     */
    MemInfo *tmp;
public:
    /*
     * message class.
     */
    DmiInfo dmiInfo;

    /*
     * storing strings during processing.
     */
    vector<string> tokens;

    /*
     * vector<Class>.
     */
    vector<Dmidecode> vector_dmi;

    /*
     * input command and get the returned information.
     */
    vector<string> get_dmiinfo_rows();

    /*
     *divide strings and filter out needed information
     * the return value type is DmiInfo (message calss).
     */
    DmiInfo select_meminfo(vector<string> tokens);

    /*
     * output dmidecode infomation by protobuf message.
     */
    void show_meminfo(DmiInfo dmiInfo);
    DmiMemInfo();
    ~DmiMemInfo();
};
#endif //LIBPROCESS_START_DMIMEMINFO_H
