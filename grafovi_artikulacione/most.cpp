#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<bool> visited;
std::vector<int> in;
std::vector<int> low;

int times = 0;

std::vector<std::pair<int, int>> bridges;

void dfs(int curr, int parent){
    visited[curr] = true;
    in[curr] = low[curr] = times++;

    for(auto next : adj[curr]){
        if(next == parent)
            continue;

        if(visited[next])
            low[curr] = std::min(low[next], in[curr]);
        else{
            dfs(next, curr);

            low[curr] = std::min(low[curr], low[next]);

            if(low[next] > in[curr])
                bridges.emplace_back(curr, next);
        }
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;

    adj.resize(n);
    visited.resize(n, false);
    in.resize(n);
    low.resize(n);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, -1);

    std::cout << "\nBridges:\n";
    for(auto b : bridges){
        std::cout << b.first << ' ' << b.second << '\n';
    }

    return 0;
}