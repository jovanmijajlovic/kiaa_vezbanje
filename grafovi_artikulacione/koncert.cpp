#include <iostream>
#include <vector>

std::vector<std::vector<int>> adj;
std::vector<int> parent;
std::vector<bool> visited;
std::vector<int> in;
std::vector<int> low;

int times = 0;

std::vector<bool> artikulacione;

void dfs(int curr){
    visited[curr] = true;

    in[curr] = low[curr] = times++;
    int children = 0;

    for(auto next : adj[curr]){
        if(visited[next]){
            if(parent[curr] != next)
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
    parent.resize(n, -1);
    visited.resize(n, false);
    in.resize(n);
    low.resize(n);
    artikulacione.resize(n, false);


    std::vector<int> atmosfera(n);
    for(int i = 0; i < n; i++)
        std::cin >> atmosfera[i];

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++){
        if(!visited[i])
            dfs(i);
    }

    int vr = 0;
    for(int i = 0; i < n; i++){
        if(artikulacione[i])
            vr += atmosfera[i];
    }

    if(vr >= 0)
        std::cout << "POZITIVNA " << vr << '\n';
    else
        std::cout << "NEGATIVNA " << vr << '\n';

    return 0;
}