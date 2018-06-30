#include "../lib/version.h"
#include "gtest/gtest.h"

TEST(test_case, check_version)
{
    EXPECT_GT(version(), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}