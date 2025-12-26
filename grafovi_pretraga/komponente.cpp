#include <iostream>
#include <vector>
#include <stack>

void dfs(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, int start, std::vector<int> &components, int comp){
    if(!visited[start]){
        visited[start] = true;
        components[start] = comp;

        for(auto next : adj[start])
            dfs(adj, visited, next, components, comp);
    }

}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<bool> visited(n, false);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> components(n);

    int comp = 1;
    for(int i = 0; i < n; i++){
        if(!visited[i])
            dfs(adj, visited, i, components, comp++);
    }

    for(auto comp : components){
        std::cout << comp << ' ';
    }

    return 0;
}