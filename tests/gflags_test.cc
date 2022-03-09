#include "gflags/gflags.h"

#include <iostream>

#include "gtest/gtest.h"

DEFINE_string(name, "alan", "your name");

TEST(GflagsTest, TestGflags) { ASSERT_EQ(FLAGS_name, "alan"); }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
