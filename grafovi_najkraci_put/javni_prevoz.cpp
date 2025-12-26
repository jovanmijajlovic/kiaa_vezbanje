#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

#define INF std::numeric_limits<int>::max()

struct compare{
    bool operator()(std::pair<int, int> &p1, std::pair<int, int> &p2){
        return p1.second > p2.second;
    }
};

int dijkstra(std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<int> &distances, std::vector<bool> &found, int start, int end){
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> hip;

    distances[start] = 0;
    hip.push({start, distances[start]});

    while(!hip.empty()){
        auto [curr, _] = hip.top();
        hip.pop();

        if(found[curr])
            continue;

        found[curr] = true;

        for(auto [next, dist_next] : adj[curr]){
            if(!found[next]){

                int cena = dist_next < distances[curr] ? 0 : (dist_next - distances[curr]);
                if(distances[next] > distances[curr] + cena){
                    distances[next] = distances[curr] + cena;
                    hip.push({next, distances[next]});
                }
            }
        }
    }


    return distances[end];
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    std::vector<int> distances(n + 1, INF);
    std::vector<bool> found(n + 1, false);

    for(int i = 0; i < m; i++){
        int u, v, cena;
        std::cin >> u >> v >> cena;

        adj[u].emplace_back(v, cena);
        adj[v].emplace_back(u, cena);
    }

    std::cout << dijkstra(adj, distances, found, 1, n) << '\n';

    return 0;
}