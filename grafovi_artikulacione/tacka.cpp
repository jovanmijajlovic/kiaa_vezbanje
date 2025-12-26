#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<bool> visited;
std::vector<int> in;
std::vector<int> low;
std::vector<int> parent;

int times = 0;

std::vector<int> artikulacione;

void dfs(int curr){
    visited[curr] = true;

    in[curr] = low[curr] = times++;

    int children = 0;

    for(auto next : adj[curr]){
        if(visited[next]){
            if(next != parent[curr])
                low[curr] = std::min(low[curr], in[next]);
        }else{
            children++;

            parent[next] = curr;

            dfs(next);

            low[curr] = std::min(low[curr], low[next]);

            if(parent[curr] != -1 && low[next] >= in[curr])
                artikulacione[curr] = true;
        }
    }

    if(parent[curr] == -1 && children > 1)
        artikulacione[curr] = true;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    adj.resize(n);
    visited.resize(n, false);
    in.resize(n);
    low.resize(n);
    parent.resize(n, -1);

    artikulacione.resize(n, false);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++)
        if(!visited[i])
            dfs(i);

    int q;
    std::cin >> q;
    while(q--){
        int start;
        std::cin >> start;

        if(artikulacione[start])
            std::cout << "Da " << adj[start].size() << '\n';
        else
            std::cout << "Ne\n";

    }

    return 0;
}