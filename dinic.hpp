#ifndef DINIC_HPP_
#define DINIC_HPP_

#include <vector>
#include <queue>

using namespace std;

int dinic_algorithm(const int v, const vector<vector<int>>& graph, int source, int sink);

#endif 