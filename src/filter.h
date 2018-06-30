#pragma once

using ip_t = std::vector<int>;
using ip_pool_t = std::vector<ip_t>;
using params_t = std::vector<std::tuple<int, int> >;

ip_pool_t get_ip_pool(std::istream &inputStream);

bool check_and(const ip_t &ip, const std::vector<std::tuple<int, int> > &params);

bool check_any(const ip_t &ip, int value);