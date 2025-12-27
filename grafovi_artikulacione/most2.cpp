#include <iostream>
#include <vector>
#include <utility>

std::vector<std::vector<int>> adj;
std::vector<int> parent;
std::vector<bool> visited;
std::vector<int> in;
std::vector<int> low;

std::vector<std::pair<int, int>> bridges;

int timer = 0;

void dfs(int curr){
    visited[curr] = true;
    in[curr] = timer;
    low[curr] = timer;
    timer++;

    for(auto next : adj[curr]){
        if(visited[next]){
            if(next != parent[curr])
                if(in[next] < low[curr])
                    low[curr] = in[next];
        }else{
            parent[next] = curr;
            dfs(next);

            if(low[next] < low[curr])
                low[curr] = low[next];

            if(low[next] > in[curr])
                bridges.emplace_back(curr, next);
        }
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;

    adj.resize(n);
    parent.resize(n, -1);
    visited.resize(n, false);
    in.resize(n);
    low.resize(n);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0);

    std::cout << "Bridges: \n";
    for(auto bridge : bridges)
        std::cout << bridge.first << ' ' << bridge.second << '\n';

    return 0;
}