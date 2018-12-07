#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXBUFSIZE 1024

typedef struct CPUTime
{
    char cpu_name[20];
    unsigned int user_time;
    unsigned int nice_time;
    unsigned int system_time;
    unsigned int idle_time;
} CpuOccupy ;

double m_cpu_usage;

void cal_cpu_usage (CpuOccupy *first_info, CpuOccupy *second_info){
    double fir_total_time, sec_total_time;
    double user_sub, sys_sub;

    fir_total_time = (double) (first_info->user_time + first_info->nice_time + first_info->system_time +first_info->idle_time);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    sec_total_time = (double) (second_info->user_time + second_info->nice_time + second_info->system_time +second_info->idle_time);//第二次(用户+优先级+系统+空闲)的时间再赋给od

    user_sub = (double) (second_info->user_time - first_info->user_time);    //用户第一次和第二次的时间之差再赋给id
    sys_sub = (double) (second_info->system_time - first_info->system_time);//系统第一次和第二次的时间之差再赋给sd

    m_cpu_usage = ((sys_sub+user_sub)*100.0)/(sec_total_time-fir_total_time); //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
}
void get_cpu_used_info (CpuOccupy *o) {
    FILE *fd;
    char buff[MAXBUFSIZE];
    fd = fopen ("/proc/stat", "r"); //这里只读取stat文件的第一行及cpu总信息，如需获取每核cpu的使用情况，请分析stat文件的接下来几行。
    fgets (buff, sizeof(buff), fd);
    sscanf (buff, "%s %u %u %u %u", o->cpu_name, &o->user_time, &o->nice_time,&o->system_time, &o->idle_time);
    printf(buff);
    fclose(fd);
}
int main(){
    CpuOccupy ocpu,ncpu;
    //获取cpu使用率信息
    get_cpu_used_info(&ocpu);
    sleep(1);
    get_cpu_used_info(&ncpu);
    cal_cpu_usage(&ocpu, &ncpu);
    printf("cpu used:%4.2f \n", m_cpu_usage);
}