#include "../lib/version.h"
#include "gtest/gtest.h"
#include "../src/filter.cpp"

TEST(test_case, check_version) {
    EXPECT_GT(version(), 0);
}

TEST(test_case, split_line) {
    std::vector<std::string> input{"113.162.145.156\t111\t0\n",
                                   "157.39.22.224\t5\t6\n",
                                   "79.180.73.190\t2\t1\n",
                                   "179.210.145.4\t22\t0\n",
                                   "219.102.120.135\t486\t0\n",
                                   "67.232.81.208\t1\t0\n",
                                   "85.254.10.197\t0\t7\n",
                                   "23.240.215.189\t6\t0\n",
                                   "1.29.168.152\t17\t0\n",
                                   "185.69.186.168\t1\t3\n",
                                   "110.152.103.161\t0\t1\n",
                                   "185.182.81.131\t1\t1\n"};

    std::vector<std::vector<std::string>> reference{{"113.162.145.156", "111", "0\n"},
                                                    {"157.39.22.224",   "5",   "6\n"},
                                                    {"79.180.73.190",   "2",   "1\n"},
                                                    {"179.210.145.4",   "22",  "0\n"},
                                                    {"219.102.120.135", "486", "0\n"},
                                                    {"67.232.81.208",   "1",   "0\n"},
                                                    {"85.254.10.197",   "0",   "7\n"},
                                                    {"23.240.215.189",  "6",   "0\n"},
                                                    {"1.29.168.152",    "17",  "0\n"},
                                                    {"185.69.186.168",  "1",   "3\n"},
                                                    {"110.152.103.161", "0",   "1\n"},
                                                    {"185.182.81.131",  "1",   "1\n"}};

    for (auto i = 0; i < input.size(); ++i) {
        EXPECT_EQ(split(input.at(i), '\t'), reference.at(i)) << "where i = " << i;
    }

}

TEST(test_case, split_point) {
    std::vector<std::string> input{"1.2.3.4",
                                   "5.66.777.8",
                                   "001.002.003.004",
                                   " 100.002  .313.1"};

    std::vector<std::vector<std::string>> reference{{"1",    "2",     "3",   "4"},
                                                    {"5",    "66",    "777", "8"},
                                                    {"001",  "002",   "003", "004"},
                                                    {" 100", "002  ", "313", "1"}};

    for (auto i = 0; i < input.size(); ++i) {
        EXPECT_EQ(split(input.at(i), '.'), reference.at(i)) << "where i = " << i;
    }

}

TEST(test_case, get_ip_pool) {
    std::stringstream iss;

    iss << "113.162.145.156\t111\t0\n" <<
        "157.39.22.224\t5\t6\n" <<
        "79.180.73.190\t2\t1\n" <<
        "179.210.145.4\t22\t0\n" <<
        "219.102.120.135\t486\t0\n" <<
        "67.232.81.208\t1\t0\n" <<
        "85.254.10.197\t0\t7\n" <<
        "23.240.215.189\t6\t0\n" <<
        "1.29.168.152\t17\t0\n" <<
        "185.69.186.168\t1\t3\n" <<
        "110.152.103.161\t0\t1\n" <<
        "185.182.81.131\t1\t1\n" <<
        "...\t1\t1\n" <<
        ".182.81.131\t1\t1\n" <<
        "185..81.131\t1\t1\n" <<
        "185.182..131\t1\t1\n" <<
        "300.182.81.\t1\t1\n" <<
        "185.300.81.\t1\t1\n" <<
        "185.182.300.\t1\t1\n" <<
        "185.182.81.300\t1\t1\n" <<
        "-1.182.81.300\t1\t1\n" <<
        "1.-1.81.300\t1\t1\n" <<
        "1.182.-1.300\t1\t1\n" <<
        "1.182.81.-1\t1\t1\n" <<
        ".\t1\t1\n" <<
        "a.b.c.d\t5\t6\n";

    ip_pool_t reference{{113, 162, 145, 156},
                        {157, 39,  22,  224},
                        {79,  180, 73,  190},
                        {179, 210, 145, 4},
                        {219, 102, 120, 135},
                        {67,  232, 81,  208},
                        {85,  254, 10,  197},
                        {23,  240, 215, 189},
                        {1,   29,  168, 152},
                        {185, 69,  186, 168},
                        {110, 152, 103, 161},
                        {185, 182, 81,  131}};

    EXPECT_EQ(get_ip_pool(iss), reference);
}

TEST(test_case, check_and_one_param) {
    ip_pool_t input{{1,   2,   3,   4},
                    {2,   1,   3,   4},
                    {2,   3,   1,   4},
                    {2,   3,   4,   1},
                    {1,   1,   1,   1},
                    {0,   0,   0,   0},
                    {255, 255, 255, 255}};

    std::vector<bool> reference{
            true,
            false,
            false,
            false,
            true,
            false,
            false
    };

    params_t  param{std::make_tuple(0, 1)};
    for (auto i = 0; i < input.size(); ++i) {
        EXPECT_EQ(check_and(input.at(i), param), reference.at(i)) << "where i = " << i;
    }
}

TEST(test_case, check_and_two_params) {
    ip_pool_t input{{46,  70,  3,   4},
                    {2,   46,  70,  4},
                    {2,   3,   46,  70},
                    {2,   3,   70,  46},
                    {46,  46,  46,  46},
                    {70,  70,  70,  70},
                    {0,   0,   0,   0},
                    {255, 255, 255, 255}};

    std::vector<bool> reference{
            true,
            false,
            false,
            false,
            false,
            false,
            false,
            false
    };

    params_t  param{std::make_tuple(0, 46), std::make_tuple(1, 70)};
    for (auto i = 0; i < input.size(); ++i) {
        EXPECT_EQ(check_and(input.at(i), param), reference.at(i)) << "where i = " << i;
    }
}

TEST(test_case, check_any) {
    ip_pool_t input{{46,  70,  3,   4},
                    {2,   46,  70,  4},
                    {2,   3,   46,  70},
                    {2,   3,   70,  46},
                    {46,  46,  46,  46},
                    {70,  70,  70,  70},
                    {0,   0,   0,   0},
                    {255, 255, 255, 255}};

    std::vector<bool> reference{
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            false
    };

    for (auto i = 0; i < input.size(); ++i) {
        EXPECT_EQ(check_any(input.at(i), 46), reference.at(i)) << "where i = " << i;
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}