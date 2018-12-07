//
// Created by marcie on 18-11-26.
//

#include <iostream>
#include <MemoryCollector.hpp>
#include <procmeminfo.hpp>

int main(){
    MemoryCollector memoryCollector;
    ProcMemInfo procMemInfo;
    procMemInfo.get_procinfo_rows();
    procMemInfo.select_procinfo_string(procMemInfo.tokens);
    procMemInfo.show_meminfo_string(procMemInfo.procInfo);

    memoryCollector.get_dmiinfo_rows();
    memoryCollector.select_meminfo(memoryCollector.tokens);
    memoryCollector.show_meminfo(memoryCollector.memoryCollection);
}