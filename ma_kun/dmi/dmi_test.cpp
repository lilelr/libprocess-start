//
// Created by marcie on 18-11-19.
//

#include <MemoryCollector.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stout/gtest.hpp>

TEST(test1,spilt_into_rows)
{
    DmiMemInfo dmiMemInfo;
    dmiMemInfo.get_dmiinfo_rows();
    EXPECT_EQ(dmiMemInfo.tokens[0],"# dmidecode 3.1");
}

TEST(test2,select_mem_info)
{
    DmiMemInfo dmiMemInfo;
    dmiMemInfo.get_dmiinfo_rows();
    dmiMemInfo.select_meminfo(dmiMemInfo.tokens);
    EXPECT_EQ(dmiMemInfo.dmiInfo.max_size(),"32 GB");
    EXPECT_EQ(dmiMemInfo.dmiInfo.info_size(),2);
}

int main(int argc, char** argv) {
    // Initialize Google Mock/Test.
    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
    /*for (auto iter = vector_dmi.begin(); iter != vector_dmi.end(); iter++){
        string a = *iter.operator->()->get_size();
        string b = *iter.operator->()->get_type();
        string c = *iter.operator->()->get_speed();
        cout<<"当前的size,type,speed为："<<a<<"*********"<<b<<"*********"<<c<<endl;
    }
    cout<<vector_dmi.size()<<endl;
    */