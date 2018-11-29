//
// Created by marcie on 18-11-26.
//

#include <dmimeminfo.h>

DmiMemInfo::DmiMemInfo(){

}

vector<string> DmiMemInfo::get_dmiinfo_rows() {
    /*
     * amount to input command and get the returned memory information.
     */
    Try<Subprocess> s = subprocess(
            "sudo -S dmidecode -t memory",
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

DmiInfo DmiMemInfo::select_meminfo(vector<string> tokens) {
    num_size = 0, num_type = 0, num_speed = 0;
    shared_ptr<string> Unknown1(new string(strings::trim("No Module Installed")));
    shared_ptr<string> Unknown2(new string(strings::trim("Unknown")));
    dflt = Dmidecode(Unknown1,Unknown2,Unknown2);
    /*
     * divide strings by ":", and filter memory information
     */
    for (int i = 0; i < tokens.size(); i++) {
        vector<string> tokens_string = strings::tokenize(tokens[i],":");
        for (auto iter = tokens_string.begin(); iter != tokens_string.end(); iter++) {
            string nospace = strings::trim(*iter);
            if(nospace == "Maximum Capacity"){
                iter++;
                dmiInfo.set_max_size(strings::trim(*iter));
            }
            if(nospace == "Size"){
                iter++;
                if (strings::trim(*iter) != "No Module Installed") {
                    shared_ptr<string> size(new string(strings::trim(*iter)));
                    vector_dmi.push_back(dflt);
                    vector_dmi[num_size].set_size(size);
                    tmp = dmiInfo.add_info();
                    tmp->set_size(strings::trim(*iter));
                    num_size++;
                }
                iter--;
            }
            if(strings::trim(*iter) == "Type") {
                iter++;
                if(num_size > num_type) {
                    shared_ptr<string> type(new string(strings::trim(*iter)));
                    vector_dmi[num_type].set_type(type);
                    tmp->set_type(strings::trim(*iter));
                    num_type++;
                }
                iter--;
            }
            if(strings::trim(*iter) == "Speed") {
                iter++;
                if(strings::trim(*iter) != "Unknown") {
                    shared_ptr<string> speed(new string(strings::trim(*iter)));
                    vector_dmi[num_speed].set_speed(speed);
                    tmp->set_speed(strings::trim(*iter));
                    num_speed++;
                }
                iter--;
            }
        }
    }
    return dmiInfo;
}

void DmiMemInfo::show_meminfo(DmiInfo dmiInfo) {
    cout<<"************************************"<<endl;
    cout<<"Maximum Capacity："<<dmiInfo.max_size()<<endl;
    cout<<"当前机器有"<<dmiInfo.info().size()<<"个内存插槽"<<endl;
    cout<<"************************************"<<endl;
    for (auto iter = dmiInfo.info().begin(); iter != dmiInfo.info().end(); iter++) {
        cout<<"第"<<iter-dmiInfo.info().begin()+1<<"个Memory Device的信息为："<<endl;
        cout<<"Size:"<<iter.operator->()->size()<<endl;
        cout<<"Type:"<<iter.operator->()->type()<<endl;
        cout<<"Speed:"<<iter.operator->()->speed()<<endl;
        cout<<"************************************"<<endl;
    }
}

DmiMemInfo::~DmiMemInfo() {
    
}

