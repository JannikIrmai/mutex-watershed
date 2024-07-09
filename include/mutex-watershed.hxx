#pragma once

#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <set>
#include <iostream>
#include <iomanip>

#include <partition.hxx>


template<typename EDGES, typename COSTS>
typename COSTS::value_type mutex_watershed(const EDGES& edges, const COSTS& costs)
{
    assert (edges.size() == costs.size());
    // determine the number of vertices
    size_t num_vertices = 0;
    for (auto e : edges)
    {
        if (e[0] >= num_vertices)
            num_vertices = e[0] + 1;
        if (e[1] >= num_vertices)
            num_vertices = e[1] + 1;
    }

    // sort edges for decreasing absolute costs
    std::vector<size_t> edge_indices(edges.size());
    std::iota(edge_indices.begin(), edge_indices.end(), 0);
    std::sort(edge_indices.begin(), edge_indices.end(), [&](const size_t a, const size_t b){
        return std::abs(costs[a]) > std::abs(costs[b]);
    });

    std::vector<std::set<size_t>> mutexes(num_vertices);
    andres::Partition<size_t> partition(num_vertices);

    /// iterate over all edges in decreasing order of their absolute costs
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (i % std::max((size_t)1, (edges.size() / 1000)) == 0)
        std::cout << "\r" << std::setprecision(1) << std::fixed << 100.0 * i / edges.size() << " %" << std::flush;

        // get the end vertices of the edge
        size_t idx = edge_indices[i];
        size_t u = edges[idx][0];
        size_t v = edges[idx][1];

        // get the representatives of the vertices
        size_t ru = partition.find(u);
        size_t rv = partition.find(v);

        // if nodes are in the same component
        if (ru == rv)
            continue;

        // if mutex constraint is active
        if (mutexes[ru].find(rv) != mutexes[ru].end())
            continue;

        // otherwise insert mutex constraint for negative edge
        if (costs[idx] < 0)
        {
            mutexes[ru].insert(rv);
            mutexes[rv].insert(ru);
        }
        // otherwise merge components for positive edge
        else
        {
            partition.merge(u, v);
            size_t ruv = partition.find(ru);
            // update mutex representatives
            for (size_t r : {ru, rv})
            {
                if (ruv == r)
                    continue;
                mutexes[ruv].insert(mutexes[r].begin(), mutexes[r].end());
                for (const size_t & m : mutexes[r])
                {
                    mutexes[m].erase(r);
                    mutexes[m].insert(ruv);
                }  
                mutexes[r].clear();
            }
        }
    }
    std::cout << "\r";

    // compute objective value (sum of costs of edges that are cut)
    typename COSTS::value_type obj = 0;
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (partition.find(edges[i][0]) != partition.find(edges[i][1]))
            obj += costs[i];
    }
    return obj;
}