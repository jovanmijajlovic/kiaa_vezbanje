#include <iostream>
#include <vector>

bool dfs(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<int> &colors, int start, int color){  
    if(!visited[start]){
        visited[start] = true;
        colors[start] = color;

        for(auto next : adj[start]){
            if(colors[next] == color)
                return false;
            if(!dfs(adj, visited, colors, next, 1 - color))
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

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<int> colors(n, -1);
    if(!dfs(adj, visited, colors, 0, 0))
        std::cout << -1 << '\n';
    else{
        int g1, g2;
        for(auto c : colors){
            if(c == 0)
                g1++;
            else if(c == 1)
                g2++;
        }

        std::cout << std::min(g1, g2) << '\n';
    }


    return 0;
}