#include <iostream>
#include <vector>

bool dfs(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<int> &groups, int start, int group){
    if(!visited[start]){
        visited[start] = true;
        groups[start] = group;

        for(auto next : adj[start]){
            if(groups[next] == group)
                return false;
            if(!dfs(adj, visited, groups, next, 1 - group))
                return false;
        }
    }

    return true;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<bool> visited(n, false);
    std::vector<int> groups(n, -1);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if(!dfs(adj, visited, groups, 0, 0))
        std::cout << '-';
    else{
        for(int i = 0; i < n; i++){
            if(groups[i] == 0)
                std::cout << i << ' ';
        }
    }
    
    return 0;
}