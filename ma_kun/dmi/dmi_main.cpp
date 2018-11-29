//
// Created by marcie on 18-11-26.
//

#include <iostream>
#include <dmimeminfo.h>

int main(){
    DmiMemInfo dmiMemInfo;
    dmiMemInfo.get_dmiinfo_rows();
    dmiMemInfo.select_meminfo(dmiMemInfo.tokens);
    dmiMemInfo.show_meminfo(dmiMemInfo.dmiInfo);
}