#include <iostream>
#include <vector>
#include <utility>

std::vector<std::vector<int>> adj;
std::vector<bool> visited;
std::vector<int> in;
std::vector<int> low;
std::vector<int> parent;

std::vector<bool> artikulacione;

int timer = 0;

void dfs(int curr){
    visited[curr] = true;
    in[curr] = timer;
    low[curr] = timer;
    timer++;

    int children = 0;

    for(auto next : adj[curr]){
        if(visited[next]){
            if(next != parent[curr])
                if(low[curr] > in[next])
                    low[curr] = in[next];
        }else{
            parent[next] = curr;
            children++;

            dfs(next);

            if(low[next] < low[curr])
                low[curr] = low[next];

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

    dfs(0);

    int q;
    std::cin >> q;
    while(q--){
        int x;
        std::cin >> x;

        if(artikulacione[x])
            std::cout << "Da " << adj[x].size() << '\n';
        else
            std::cout << "Ne\n";
    }

    return 0;
}