//
// Created by weiguow on 18-10-15.
//
#include <algorithm>
#include <string>

#include <gmock/gmock.h>

#include <stout/gtest.hpp>
#include <stout/none.hpp>
#include <stout/option.hpp>

using std::string;


TEST(NothingTest,Nothing)
{
    Try<Nothing> see(try);
    EXPECT_EQ(5u,_try);
}

int main(int argc, char** argv) {
    // Initialize Google Mock/Test.
    testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
