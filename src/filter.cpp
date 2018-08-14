#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include "filter.h"

std::vector<std::string> split(const std::string &str, char ch) {
    std::vector<std::string> result;
    std::string::size_type   start = 0;
    std::string::size_type   stop  = str.find_first_of(ch);

    while (stop != std::string::npos) {
        result.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop  = str.find_first_of(ch, start);
    }

    result.push_back(str.substr(start));
    return result;
}

ip_pool_t get_ip_pool(std::istream &inputStream) {
    ip_pool_t result;

    for (std::string line; getline(inputStream, line);) {
        auto lines = split(line, '\t');
        auto ip    = split(lines.at(0), '.');

        if (ip.size() != 4) {
            continue;
        }

        ip_t v;

        for (const auto &str: ip) {
            int i;
            try {
                i = std::stoi(str);
            }
            catch (const std::exception &e) {
                i = -1;
            }

            if (i >= 0 && i <= 255) {
                v.push_back(i);
            }
        }

        if (v.size() == 4) {
            result.push_back(v);
        }
    }

    return result;
}

bool check_and(const ip_t &ip, const params_t &params) {
    bool result = true;

    for (const auto &param: params) {
        int index;
        int value;

        std::tie(index, value) = param;
        if (ip.at(index) != value) {
            result = false;
        }
    }
    return result;
}

bool check_any(const ip_t &ip, int value) {
    bool result = false;

    for (const auto &v: ip) {
        if (v == value) {
            result = true;
        }
    }
    return result;
}