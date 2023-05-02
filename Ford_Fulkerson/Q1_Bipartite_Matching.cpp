/**
 * @file Q1_Bipartite_Matching.cpp
 * @brief This file contains the code for the first question of the assignment.
 * @details The question is to find the maximum number of edges that can be added to a bipartite graph such that the graph remains bipartite.
 * @details The solution to this problem is to find the maximum matching in the given graph and then subtract the number of edges in the maximum matching from the total number of edges in the graph.
 * @details The maximum matching is found using the Ford Fulkerson algorithm.
 * @details The time complexity of the Ford Fulkerson algorithm is O(Ef) where E is the number of edges in the graph and f is the maximum flow in the graph.
 */
#include <algorithm>
#include <fstream>
#include <climits>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;
#define ll long long int
#define endl "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
const ll inf = 1e18;
const ll mod = 1e9 + 7;

/**
 * @brief This is the structure for the edge of the graph.
 * @details It contains the source, destination, capacity and flow of the edge.
 */
struct Edge
{
    int v, u, capacity, flow;
};

/**
 * @brief This function adds an edge to the graph.
 * @param v The source of the edge.
 * @param u The destination of the edge.
 * @param capacity The capacity of the edge.
 * @param graph The graph to which the edge is to be added.
 */
void add_edge(int v, int u, int capacity, vector<vector<Edge>> &graph)
{
    Edge e1 = {v, u, capacity, 0};
    Edge e2 = {u, v, 0, 0};
    graph[v].pb(e1);
    graph[u].pb(e2);
}

/**
 * @brief This function performs a bfs on the graph.
 * @details It returns true if there is a path from s to t in the residual graph.
 * @details It also stores the parent of each node in the parent vector.
 */
bool bfs(vector<vector<Edge>> &graph, vector<int> &parent, int s, int t)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for (auto &e : graph[u])
        {
            int v = e.u;
            if (!visited[v] && e.capacity > e.flow)
            {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    return visited[t];
}

/**
 * @brief This function augments the path found by the bfs.
 * @details It returns the minimum flow in the path.
 * @details It also updates the flow of the edges in the path.
 */
int augment(vector<vector<Edge>> &graph, vector<int> &parent, int s, int t)
{
    int n = graph.size();
    int min_flow = INT_MAX;
    for (int v = t; v != s; v = parent[v])
    {
        int u = parent[v];
        for (auto &e : graph[u])
        {
            if (e.u == v)
            {
                min_flow = min(min_flow, e.capacity - e.flow);
                break;
            }
        }
    }
    for (int v = t; v != s; v = parent[v])
    {
        int u = parent[v];
        for (auto &e : graph[u])
        {
            if (e.u == v)
            {
                e.flow += min_flow;
                break;
            }
        }
        for (auto &e : graph[v])
        {
            if (e.u == u)
            {
                e.flow -= min_flow;
                break;
            }
        }
    }
    return min_flow;
}

/**
 * @brief This function finds the maximum flow in the graph.
 * @details It returns the maximum flow in the graph.
 */
int ford_fulkerson(vector<vector<Edge>> &graph, int s, int t)
{
    int n = graph.size();
    vector<int> parent(n);
    int max_flow = 0;
    while (bfs(graph, parent, s, t))
    {
        int flow = augment(graph, parent, s, t);
        max_flow += flow;
    }
    return max_flow;
}

/**
 * @brief This is the main function.
 * @details It reads the input from the file and writes the output to the file.
 */
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("testcase1_2_2.txt", "r", stdin);
    freopen("output1_2.txt", "w", stdout);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<Edge>> graph(n + m + 2);
    for (int i = 1; i <= n; i++)
    {
        add_edge(0, i, 1, graph);
    }
    for (int i = 1; i <= m; i++)
    {
        add_edge(n + i, n + m + 1, 1, graph);
    }
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        u++, v++;
        add_edge(u, v, 1, graph);
    }
    cout << ford_fulkerson(graph, 0, n + m + 1) << endl;
    return 0;
}