#include <algorithm>
#include <iostream>
#include <vector>
#include <tuple>
#include "filter.h"

static std::ostream &operator<<(std::ostream &os, const ip_t &ip) {
    os << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3];
    return os;
}

int main(int argc, char const *argv[]) {
    try {
        ip_pool_t ip_pool = get_ip_pool(std::cin);
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<decltype(ip_pool.at(0))>());

        // Выводим весь список.
        for (const auto &ip : ip_pool) {
            std::cout << ip << std::endl;
        }

        // Выводим все ip в которых первый байт = 1.
        for (const auto &ip : ip_pool) {
            params_t vec{std::make_tuple(0, 1)};
            if (check_and(ip, vec)) {
                std::cout << ip << std::endl;
            }
        }

        // Выводим все ip в которых первый байт = 46, а второй = 70.
        for (const auto &ip : ip_pool) {
            params_t vec{std::make_tuple(0, 46), std::make_tuple(1, 70)};
            if (check_and(ip, vec)) {
                std::cout << ip << std::endl;
            }
        }

        // Выводим все ip в которых хотя бы один байт равет 46.
        for (const auto &ip : ip_pool) {
            if (check_any(ip, 46)) {
                std::cout << ip << std::endl;
            }
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}