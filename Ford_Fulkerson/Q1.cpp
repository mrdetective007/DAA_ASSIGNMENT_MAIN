// SULTAN KO SIRF SULTAN HARA SAKTA HAIN !!
/**
 *@file Q1.cpp
 *@brief this code implements the Ford Fulkerson algorithm to find the maximum flow in a graph
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
 * @brief This struct represents an edge in the graph
 * @param v the source vertex
 * @param u the destination vertex
 * @param capacity the capacity of the edge
 * @param flow the flow through the edge
 *
 */
struct Edge
{
    int v, u, capacity, flow;
};
/**
 * @brief This function adds an edge to the graph
 * @param v the source vertex
 * @param u the destination vertex
 * @param capacity the capacity of the edge
 * @param graph the graph
 *
 */
void add_edge(int v, int u, int capacity, vector<vector<Edge>> &graph)
{
    Edge e1 = {v, u, capacity, 0};
    Edge e2 = {u, v, 0, 0};
    graph[v].pb(e1);
    graph[u].pb(e2);
}
/**
 * @brief This function performs a bfs on the graph
 * @param graph the graph
 * @param parent the parent array
 * @param s the source vertex
 * @param t the sink vertex
 * @return true if there is a path from s to t
 *
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
 * @brief This function augments the path found by bfs
 * @param graph the graph
 * @param parent the parent array
 * @param s the source vertex
 * @param t the sink vertex
 * @return the minimum flow in the path
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
 * @brief This function implements the Ford Fulkerson algorithm
 * @param graph the graph
 * @param s the source vertex
 * @param t the sink vertex
 * @return the maximum flow in the graph
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
 * @brief This function prints the graph
 * @param graph the graph
 *
 */
void print_graph(vector<vector<Edge>> &graph)
{
    int n = graph.size();
    for (int u = 0; u < n - 1; u++)
    {
        cout << u << " : ";
        for (auto &e : graph[u])
        {
            if (e.flow >= 0)
            {
                cout << e.u << " " << e.flow << "/" << e.capacity << " ";
            }
        }
        cout << endl;
    }
}
/**
 * @brief This function performs a dfs on the graph
 * @param graph the graph
 * @param visited the visited array
 * @param s the source vertex
 *
 */
void dfs(vector<vector<Edge>> &graph, vector<bool> &visited, int s)
{
    visited[s] = true;
    for (auto &e : graph[s])
    {
        if (!visited[e.u] && e.capacity > e.flow)
        {
            dfs(graph, visited, e.u);
        }
    }
}
/**
 * @brief This function prints the min s-t cut
 * @param graph the graph
 * @param s the source vertex
 * @param t the sink vertex
 *
 */
void print_cut(vector<vector<Edge>> &graph, int s, int t)
{
    int n = graph.size();
    vector<bool> visited(n, false);
    dfs(graph, visited, s);
    cout << "The min s-t cut is: " << endl;
    for (int u = 0; u < n; u++)
    {
        if (visited[u])
        {
            for (auto &e : graph[u])
            {
                if (!visited[e.u])
                {
                    cout << u << "->" << e.u << endl;
                }
            }
        }
    }
}
/**
 * @brief This is the main function
 * @return 0 on exit
 *
 */
int main()
{
    freopen("testcase1.txt", "r", stdin);
    freopen("output1.txt", "w+", stdout);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<Edge>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        add_edge(u, v, c, graph);
    }
    // time analysis using chrono
    clock_t start, end;
    start = clock();
    cout << start << " " << endl;
    int max_flow = ford_fulkerson(graph, s, t);
    cout << "Maximum flow: " << max_flow << endl;
    cout << "The min s-t cut is: " << max_flow << endl;
    print_graph(graph);
    print_cut(graph, s, t);
    vector<bool> visited(n, false);
    dfs(graph, visited, s);
    cout << "The set of vertices that are reachable from s in the residual graph: ";
    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    cout << "The set of vertices that are not reachable from s in the residual graph: ";
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    end = clock();
    cout << end << endl;
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by function is : " << fixed << time_taken << setprecision(10);
    return 0;
}
