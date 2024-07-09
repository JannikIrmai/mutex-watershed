#pragma once

#include <tuple>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>


template<typename VERTEX, typename COST>
std::pair<std::vector<std::array<VERTEX, 2>>, std::vector<COST>>
load_instance(std::string file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::runtime_error("Unable to open file");

    std::string line;
    std::getline(file, line);

    assert (line == "MULTICUT");

    std::vector<std::array<VERTEX, 2>> edges;
    std::vector<COST> costs;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        VERTEX i, j;
        COST c;
        ss >> i >> j >> c;
        edges.push_back({i, j});
        costs.push_back(c);
    }
    return {edges, costs};
}
