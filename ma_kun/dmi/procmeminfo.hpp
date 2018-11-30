#ifndef LIBPROCESS_START_CPU_INFO_H
#define LIBPROCESS_START_CPU_INFO_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <stout/strings.hpp>
#include <process/subprocess.hpp>
#include <process/io.hpp>

#include <ProcInfo.pb.h>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::vector;
using std::list;
using process::subprocess;
using process::Subprocess;
using process::Future;

class ProcMemInfo {
protected:
    string MemTotal;
    string MemFree;
    string MemAvailable;
    string Buffers;
    string Cached;
    string SwapTotal;
    string SwapFree;
    string Hugepagesize;
    string DirectMap4k;
    string DirectMap2M;
    string DirectMap1G;

public:
    /*
     * storing strings during processing.
     */
    vector<string> tokens;

    ProcInfo procInfo;

    const string &getMemTotal() const {
        return MemTotal;
    }

    void setMemTotal(const string &MemTotal){
        ProcMemInfo::MemTotal = MemTotal;
    }

    const string &getMemFree() const {
        return MemFree;
    }

    void setMemFree(const string &MemFree){
        ProcMemInfo::MemFree = MemFree;
    }
    const string &getMemAvailable() const {
        return MemAvailable;
    }

    void setMemAvailable(const string &MemAvailable){
        ProcMemInfo::MemAvailable = MemAvailable;
    }
    const string &getBuffers() const {
        return Buffers;
    }

    void setBuffers(const string &Buffers){
        ProcMemInfo::Buffers = Buffers;
    }
    const string &getCached() const {
        return Cached;
    }

    void setCached(const string &Cached){
        ProcMemInfo::Cached = Cached;
    }
    const string &getSwapTotal() const {
        return SwapTotal;
    }

    void setSwapTotal(const string &SwapTotal){
        ProcMemInfo::SwapTotal = SwapTotal;
    }
    const string &getSwapFree() const {
        return SwapFree;
    }

    void setSwapFree(const string &SwapFree){
        ProcMemInfo::SwapFree = SwapFree;
    }
    const string &getHugepagesize() const {
        return Hugepagesize;
    }

    void setHugepagesize(const string &Hugepagesize){
        ProcMemInfo::Hugepagesize = Hugepagesize;
    }
    const string &getDirectMap4k() const {
        return DirectMap4k;
    }

    void setDirectMap4k(const string &DirectMap4k){
        ProcMemInfo::DirectMap4k = DirectMap4k;
    }
    const string &getDirectMap2M() const {
        return DirectMap2M;
    }

    void setDirectMap2M(const string &DirectMap2M){
        ProcMemInfo::DirectMap2M = DirectMap2M;
    }
    const string &getDirectMap1G() const {
        return DirectMap1G;
    }

    void setDirectMap1G(const string &DirectMap1G){
        ProcMemInfo::DirectMap1G = DirectMap1G;
    }

    friend ostream &operator<<(std::ostream &stream, ProcMemInfo &procMemInfo) {
        return stream << "MemTotal:" << procMemInfo.MemTotal << "\n"
                      << "MemFree:" << procMemInfo.MemFree << "\n"
                      << "MemAvailable:" << procMemInfo.MemAvailable << "\n"
                      << "Buffers:" << procMemInfo.Buffers << "\n"
                      << "Cached:" << procMemInfo.Cached << "\n"
                      << "SwapTotal:" << procMemInfo.SwapTotal << "\n"
                      << "SwapFree:" << procMemInfo.SwapFree << "\n"
                      << "Hugepagesize:" << procMemInfo.Hugepagesize << "\n"
                      << "DirectMap4k:" << procMemInfo.DirectMap4k << "\n"
                      << "DirectMap2M:" << procMemInfo.DirectMap2M << "\n"
                      << "DirectMap1G:" << procMemInfo.DirectMap1G << endl;
    }

    /*ProcMemInfo(string _MemTotal, string _MemFree, string _MemAvailable,
            string _Buffers, string _Cached, string _SwapTotal,
            string _SwapFree, string _Hugepagesize, string _DirectMap4k,
            string _DirectMap2M, string _DirectMap1G):
        MemTotal(_MemTotal), MemFree(_MemFree), MemAvailable(_MemAvailable),
        Buffers(_Buffers), Cached(_Cached), SwapTotal(_SwapTotal),
        SwapFree(_SwapFree), Hugepagesize(_Hugepagesize), DirectMap4k(_DirectMap4k),
        DirectMap2M(_DirectMap2M), DirectMap1G(_DirectMap1G){}*/
    ProcMemInfo(){

    }

    ~ProcMemInfo(){

    }


/*    list<ProcMemInfo> get_mem_info() {
        std::list<ProcMemInfo> results;

        std::ifstream file("/proc/meminfo");

        if (!file.is_open()) {
            cout << "Failed to open /proc/meminfo" << endl;
        } else cout<<"Open /proc.meminfo Succeed !"<<endl;

*//*        // Placeholders as we parse the file.
        Option<string> MemTotal;
        Option<string> MemFree;
        Option<string> MemAvailable;
        Option<string> Buffers;
        Option<string> Cached;
        Option<string> SwapTotal;
        Option<string> SwapFree;
        Option<string> Hugepagesize;
        Option<string> DirectMap4k;
        Option<string> DirectMap2M;
        Option<string> DirectMap1G;*//*

        std::string line;
        while (std::getline(file, line)) {
            line = strings::trim(line);
            std::vector<std::string> split = strings::split(line, ":");


            if (split.size() < 2) {
                cout << "Unexpected format in /proc/meminfo: " << endl;
            }
            cout<<line<<endl;
            for(auto iter = split.begin(); iter != split.end();iter++) {
                cout<<*iter<<endl;

            }
        }



        return results;
    }*/

    vector<string> get_procinfo_rows(){
        Try<Subprocess> s = subprocess(
                "cat /proc/meminfo",
                Subprocess::FD(STDIN_FILENO),
                Subprocess::PIPE(),
                Subprocess::FD(STDERR_FILENO));
        Future<string> info = process::io::read(s.get().out().get());
        /*
         * convert format to string.
         */
        string info_string = info.get();
        /*
         * divide strings by "\n", that is divide it into rows.
         */
        tokens = strings::tokenize(info_string,"\n");
        return tokens;
    }

    ProcInfo select_procinfo_string(vector<string> tokens){
        for (int i = 0; i < tokens.size(); i++) {
            vector<string> tokens_string = strings::tokenize(tokens[i],":");
            for (auto iter = tokens_string.begin(); iter != tokens_string.end(); iter++) {
                string nospace = strings::trim(*iter);
                if(nospace == "MemTotal"){
                    iter++;
                    procInfo.set_memtotal(strings::trim(*iter));
                }
                if(nospace == "MemFree"){
                    iter++;
                    procInfo.set_memfree(strings::trim(*iter));
                }
            }
        }
        return procInfo;
    }

    void show_meminfo_string(ProcInfo procInfo1){
        cout<<"************************************"<<endl;
        cout<<"MemTotal："<<procInfo1.memtotal()<<endl;
        cout<<"MemFree："<<procInfo1.memfree()<<endl;
        cout<<"************************************"<<endl;
    }
};

#endif //LIBPROCESS_START_CPU_INFO_H