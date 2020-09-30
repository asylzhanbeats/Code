//
//  main.cpp
//  div1_NU
//
//  Created by Assylzhan Nurlybekuly on 9/7/20.
//  Copyright © 2020 Assylzhan Nurlybekuly. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <map>

#define ll              long long
#define vii             vector<int>
#define vll             vector<ll>
#define mii             map<int, int>
#define mll             map<ll, ll>
#define si              set<int>
#define sl              set<ll>
#define umi             unordered_map<int, int>
#define uml             unordered_map<ll, ll>
#define usi             unordered_set<int>
#define usl             unordered_set<ll>
#define maxpq           priority_queue<int>
#define minpq           priority_queue<int,vii,greater<int>()>
#define pii             pair<int, int>
#define pll             pair<ll, ll>
#define pb              push_back
#define pf              push_front
#define mp              make_pair
#define endl            "\n"
#define desc            greater<int>()
#define F               first
#define S               second
#define mod             1000000007
#define pi              3.141592653589793238
#define setbits(x)      __builtin_popcountll(x)
#define zerobits(x)     __builtin_ctzll(x)
#define FASTIO          ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;

vector<vector<int>> neighbors; // graph by neighbors

vector<int> low;  // node low-link value: lowest rank the node can reach by DFS (inlcuding itself)
vector<vector<int>> bridges; // critical connections

// build graph by creating neighbor lists
void buildGraph(int n, vector<vector<int>>& connections) {
    neighbors.resize(n);
    for (const auto& edge : connections) {
        neighbors[edge[0]].push_back(edge[1]);
        neighbors[edge[1]].push_back(edge[0]);
    }
}

// DFS to label ranks and compute low-link values for all nodes
// while identifying bridges if low[node] > rank[parent]
void dfs(int node, int parent, int& r,vector<int>& rank)
{
    if (rank[node] > 0) return; // skip visited nodes
    
    rank[node] = low[node] = r++; // initialize rank and low-link
    
    for (int neighbor : neighbors[node]) {
        if (neighbor == parent) continue;
        
        if (rank[neighbor] == 0) dfs(neighbor, node, r,rank); // DFS
        low[node] = min(low[node], low[neighbor]); // update low-link
    }
    
    // condition to identify bridges
    if (parent != -1 && low[node] > rank[parent])
        bridges.push_back({parent, node} );
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<int> rank;
    rank.resize(n);
    low.resize(n);
    buildGraph(n, connections);
    
    int r = 1; // initial rank of node 0
    dfs(0, -1/*no parent*/, r,rank);
    
    return bridges;
}
    int main()  {
        
        vector<vector<int>> connnections = {{0,1},{1,2},{2,0},{1,3}};
        int n = 4;
        vector<vector<int>> criticalEdges = criticalConnections(n, connnections);
        
        for (auto edge: criticalEdges){
            cout<<edge[0]<<" "<<edge[1]<<endl;
        }
       
    
        return 0;
    }











