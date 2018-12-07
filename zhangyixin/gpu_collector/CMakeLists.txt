#set(Gpu_SRC GpuClass.cpp GpuClass.h)
set(Gpu_Collector_SRC GpuCollector.cpp GpuCollector.h)

#[[
add_executable(yx_gpu gpu_info.cpp)
target_link_libraries(yx_gpu yx_GpuInfo_pro ${XIN_LIBS})]]

add_executable(yx_gpu_collector  ${Gpu_Collector_SRC} collector_test.cpp)
target_link_libraries(yx_gpu_collector yx_GpuCollection_pro ${XIN_LIBS})
