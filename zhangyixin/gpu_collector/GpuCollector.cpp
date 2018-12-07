#include "GpuCollector.h"

/*
 * functionName：get_gpu_string
 * description：Executing commands to obtain GPU information in the form of string
 * parameter: none
 * returnType: GPU information in the form of string
 */
string GpuCollector::get_gpu_string() {
    Try<Subprocess> s = subprocess(
            "lshw -numeric -class video",
            Subprocess::FD(STDIN_FILENO),
            Subprocess::PIPE(),
            Subprocess::FD(STDERR_FILENO));
    Future<string> info = io::read(s.get().out().get());
    m_gpu_info = info.get();
    return m_gpu_info;
}
/*
 * functionName：get_gpu_string
 * description：Separate and save the collected GPU information and encapsulate each information with protobuf
 * parameter: string m_gpu_info
 * returnType: void
 */
void GpuCollector::split_gpu_string(string m_gpu_info) {
  //  GpuClass gpu_class = GpuClass("none","none","none","none","none","none","none","none","none","none","none");  /*Initialization GpuClass*/
    vector<string> tokens = strings::split(m_gpu_info,"\n"); /*Divide gpu information from the command line by "\n" */
    vector<string>::iterator vec_iter;
  //  vector<GpuClass>::iterator gpu_itr;
    GpuInfo *gpuInfo;
    int index = 0; /*The number of GPU*/

    for(vec_iter = tokens.begin(); vec_iter != tokens.end(); vec_iter++){
        if(strings::contains(*vec_iter, "display")){
            index++;
        }
        std::string romove_bs = strings::trim(*vec_iter," "); /*Remove spaces on both sides of each message*/
        vector<string> line_token = strings::tokenize(romove_bs, ":", 2); /*Separate each message with a ":" */

        for(vector<string>::iterator vec = line_token.begin();vec!=line_token.end();vec++){
            if(*vec == "description"){
          //      m_gpu_class.push_back(gpu_class); /*Initialization m_gpu_class*/
         //       m_gpu_class[index-1].set_description(strings::trim(*(vec+1)," ")); /*Save the information that is the right of the ":" to the member variable of gpuClass*/

                gpuInfo = m_gpu_proto.add_gpu_info();
                gpuInfo->set_description(strings::trim(*(vec+1)," "));  /*Save the information that is the right of the ":" to the corresponding protobuf*/

            }
            else if(*vec == "product"){
         //       m_gpu_class[index-1].set_product(strings::trim(*(vec+1)," "));
                gpuInfo->set_product(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "vendor"){
           //     m_gpu_class[index-1].set_vendor(strings::trim(*(vec+1)," "));
                gpuInfo->set_vendor(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "physical id"){
         //       m_gpu_class[index-1].set_physical_id(strings::trim(*(vec+1)," "));
                gpuInfo->set_physical_id(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "bus info"){
         //       m_gpu_class[index-1].set_bus_info(strings::trim(*(vec+1)," "));
                gpuInfo->set_bus_info(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "version"){
        //        m_gpu_class[index-1].set_version(strings::trim(*(vec+1)," "));
                gpuInfo->set_version(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "width"){
        //        m_gpu_class[index-1].set_width(strings::trim(*(vec+1)," "));
                gpuInfo->set_width(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "clock"){
         //       m_gpu_class[index-1].set_clock(strings::trim(*(vec+1)," "));
                gpuInfo->set_clock(strings::trim(*(vec+1)," "));

            }
            else if(*vec == "capabilities"){
         //       m_gpu_class[index-1].set_capabilities(strings::trim(*(vec+1)," "));
                gpuInfo->set_capabilities(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "configuration"){
        //        m_gpu_class[index-1].set_configuration(strings::trim(*(vec+1)," "));
                gpuInfo->set_configuration(strings::trim(*(vec+1)," "));
            }
            else if(*vec == "resources"){
         //       m_gpu_class[index-1].set_resources(strings::trim(*(vec+1)," "));
                gpuInfo->set_resources(strings::trim(*(vec+1)," "));

            }

        }
    }


}

//vector<GpuClass> GpuCollector::get_gpu_class() {
//    return m_gpu_class;
//
//}

GpuCollection GpuCollector::get_gpu_proto() {
    return m_gpu_proto;
}
