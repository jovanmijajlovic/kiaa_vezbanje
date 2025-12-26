#include <iostream>
#include <vector>

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n, std::vector<int>(n));

    for(int i = 0; i < m; i++){
        int u, v, val;
        std::cin >> u >> v >> val;

        adj[u][v] = val;
    }

    return 0;
}