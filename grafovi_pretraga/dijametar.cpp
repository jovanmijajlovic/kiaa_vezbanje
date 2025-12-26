#include <iostream>
#include <vector>
#include <queue>
#include <utility>

std::pair<int, int> bfs(std::vector<std::vector<int>> &adj, int start, int n){
    std::vector<int> dist(n, -1);
    
    std::queue<int> q;
    q.push(start);

    dist[start] = 0;
    int last = start;

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(auto next : adj[curr]){
            if(dist[next] == -1){
                dist[next] = dist[curr] + 1;
                q.push(next);
                last = next;
            }
        }
    }

    return {last, dist[last]};
}

int diameter(std::vector<std::vector<int>> &adj, int n){
    auto [last, _] = bfs(adj, 0, n);
    auto [second_last, diam] = bfs(adj, last, n);
    return diam;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++){
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::cout << diameter(adj, n) << '\n';

    return 0;
}