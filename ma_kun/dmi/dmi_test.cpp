//
// Created by marcie on 18-11-19.
//

#include <signal.h>
#include <process/subprocess.hpp>
#include <process/io.hpp>
#include <stout/strings.hpp>
#include <map>

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
using std::shared_ptr;

namespace io = process::io;

/*string& trim(string &s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}*/

int main(){
    Try<Subprocess> s = subprocess(
            //"echo 0 | sudo -S dmidecode | grep -A16 'Memory Device'| grep -E 'Size|Type:|Speed'",
            //"echo 0 | sudo -S dmidecode -t memory",
            "sudo -S dmidecode -t memory",
            Subprocess::FD(STDIN_FILENO),
            Subprocess::PIPE(),
            Subprocess::FD(STDERR_FILENO));
    Future<string> info = io::read(s.get().out().get());
    string info_string = info.get();
    //cout<<info_string<<endl;
    vector<string> tokens = strings::tokenize(info_string,"\n");
    /*vector<string> tokens1;
    for (auto iter1 = tokens.begin(); iter1 != tokens.end(); iter1++) {
        tokens1.push_back(strings::trim(*iter1," "));

    }
    for (auto iter2 = tokens1.begin(); iter2 != tokens1.end(); iter2++) {
        cout<<*iter2<<endl;

    }*/
    /*cout<<tokens[0]<<endl;
    cout<<tokens[1]<<endl;
    cout<<tokens[2]<<endl;
    cout<<tokens[3]<<endl;
    cout<<tokens[4]<<endl;
    cout<<tokens[5]<<endl;
    cout<<tokens[6]<<endl;
    cout<<tokens[7]<<endl;
    cout<<tokens[8]<<endl;
    cout<<tokens[9]<<endl;
    cout<<tokens.size()<<endl;*/
    /*map<string,string> tokens_pair;
    for(int i = 0; i < tokens.size(); i++){
        tokens_pair.insert(strings::tokenize(tokens[i],":"));
        tokens_pair.insert(1,2);
    }*/
    /*vector<string> tokens_string;
    int j = 0;
    for(int i = 5; i < 9; i++){
        tokens_string = strings::tokenize(tokens[i],":");
        cout<<tokens_string[j]<<endl;
        cout<<tokens_string[j+1]<<endl;
        j=j+2;
    }*/
    //cout<<tokens_string.size()<<endl;
    map<string,string> map_info;
    //vector<int,map<string,string>> vector_map_info;
    vector<Dmidecode> vector_dmi;
    shared_ptr<string> Unknown1(new string(strings::trim("No Module Installed")));
    shared_ptr<string> Unknown2(new string(strings::trim("Unknown")));
    Dmidecode ins = Dmidecode(Unknown1,Unknown2,Unknown2);
    //int num_map = 0;
    int num_size = 0, num_type = 0, num_speed = 0;
    DmiInfo dmiInfo;
    MemInfo *tmp;
    //**********************************************************
    //Dmidecode *tmp = new Dmidecode;
    //Dmidecode *tmp = dmiInfo.add_info;
    //MemInfo *tmp = dmiInfo.add_info;
    //MemInfo *tmp = new Dmidecode;
    //MemInfo *tmp;
/*    //MemInfo *tmp = dmiInfo.mutable_info();
    shared_ptr<string> q(new string("Unknown"));
    string w = *q;
    cout<<w<<endl;
    tmp->set_type("Unknown");
    tmp->set_type("dear");
    tmp->set_speed("Nir");
    tmp->Clear();
    tmp = dmiInfo.add_info();
    tmp->set_speed("dasda");
    MemInfo *tmp1 = dmiInfo.add_info();
    tmp1->set_speed("das");
//    tmp->add_size("Unknown");
//    tmp->set_type(1,"Unknown");
//    tmp->add_speed("Unknown");
    //dmiInfo.set_allocated_info(tmp);
    //dmiInfo.add_info(tmp);
    //string ans = tmp->type;
    //cout<<tmp->size<<endl;
    cout<<dmiInfo.info().size()<<endl;
    cout<<tmp->speed()<<endl;*/
    //**********************************************************
    for (int i = 0; i < tokens.size(); i++) {
        vector<string> tokens_string = strings::tokenize(tokens[i],":");
        //cout<<"*********************************"<<tokens_string.size()<<endl;
        //vector<string> tokens_nospace = strings::trim(tokens_string[i]," ");
    //    map1.insert(tokens_string[0],tokens_string[1]);
        for (auto iter = tokens_string.begin(); iter != tokens_string.end(); iter++) {
//            cout<<*iter<<endl;
            string nospace = strings::trim(*iter);
            /*string nosapce1 = trim(*iter);
            //*iter = trim(*iter);
            //string string1 = trim(*iter);*/

            cout<<nospace<<endl;
            if(nospace == "Maximum Capacity"){
                iter++;
                dmiInfo.set_max_size(strings::trim(*iter));
            }
            if(nospace == "Size"){
                cout<<"**********************************************"<<endl;
                //map_info.insert(map<string,string>::value_type("ssss","ssss"));
                //map1.insert(const shared_ptr<string>);
                iter++;
                if (strings::trim(*iter) != "No Module Installed") {
                    map_info.insert(map<string, string>::value_type("Size", strings::trim(*iter)));
                    shared_ptr<string> size(new string(strings::trim(*iter)));
                    //shared_ptr<string> size(new string(*iter));
                    //string size1 = *iter;
                    vector_dmi.push_back(ins);
                    vector_dmi[num_size].set_size(size);
                    tmp = dmiInfo.add_info();
                    tmp->set_size(strings::trim(*iter));
                    //temp->speed = 1;
                    //dmiInfo.set_size(strings::trim(*iter));
                    num_size++;
                }
                iter--;
            }
            if(strings::trim(*iter) == "Type") {
                cout << "**********************************************" << endl;
                iter++;
                //if(strings::trim(*iter) != "Unknown") {
                if(num_size > num_type) {
                    map_info.insert(map<string, string>::value_type("Type", strings::trim(*iter)));
                    shared_ptr<string> type(new string(strings::trim(*iter)));
                    //shared_ptr<string> size1(new string(strings::trim("45363")));
                    //cout<<*size<<endl;
                //    cout<<"当前的编号为："<<num_map<<endl;
                    //vector_dmi.push_back(ins);
                    vector_dmi[num_type].set_type(type);
                    tmp->set_type(strings::trim(*iter));
                    //vector_dmi.push_back();
                    //vector_dmi[num_type].set_type(size1);
                    num_type++;
                }
                iter--;
            }
            if(strings::trim(*iter) == "Speed") {
                cout << "**********************************************" << endl;
                iter++;
                if(strings::trim(*iter) != "Unknown") {
                    map_info.insert(map<string, string>::value_type("Speed", strings::trim(*iter)));
                    shared_ptr<string> speed(new string(strings::trim(*iter)));
                    //shared_ptr<string> qwe = vector_dmi[0].get_size();;
                    vector_dmi[num_speed].set_speed(speed);
                    tmp->set_speed(strings::trim(*iter));
                    num_speed++;
                    //tmp->Clear();
                    //delete(tmp);
                    //free(tmp);
                }
                iter--;
            }
        }
    }


    cout<<"输出完毕"<<endl;
    for (auto iter = map_info.begin(); iter != map_info.end() ; iter++) {
        cout<<iter->first<<"*****"<<iter->second<<endl;

    }
    cout<<num_size<<num_type<<num_speed<<endl;
    for (auto iter = vector_dmi.begin(); iter != vector_dmi.end(); iter++){
        string a = *iter.operator->()->get_size();
        string b = *iter.operator->()->get_type();
        string c = *iter.operator->()->get_speed();
        cout<<"当前的size,type,speed为："<<a<<"*********"<<b<<"*********"<<c<<endl;
    }
    cout<<vector_dmi.size()<<endl;
    cout<<"*********************"<<endl;
    cout<<"Maximum Capacity："<<dmiInfo.max_size()<<endl;
    cout<<"当前机器有"<<dmiInfo.info().size()<<"个内存插槽"<<endl;
    cout<<"************************************"<<endl;
    for (auto iter = dmiInfo.info().begin(); iter != dmiInfo.info().end(); iter++) {
        //cout<<"Memory Device"<<iter.operator[](1)<<endl;
        cout<<"第"<<iter-dmiInfo.info().begin()+1<<"个Memory Device的信息为："<<endl;
        cout<<"Size:"<<iter.operator->()->size()<<endl;
        cout<<"Type:"<<iter.operator->()->type()<<endl;
        cout<<"Speed:"<<iter.operator->()->speed()<<endl;
        cout<<"************************************"<<endl;
    }
    /*for (auto iter = 0; iter < dmiInfo.info().size(); iter++) {
        cout<<iter+1<<endl;
        cout<<iter
    }*/
    //cout<<dmiInfo.size()<<endl;
    cout<<"执行完了！！！！！！！！！"<<endl;
}