#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

#define INF std::numeric_limits<int>::max()

struct compare{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2){
        return p1.second > p2.second;
    }
};

int dijkstra(std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<bool> &found, std::vector<int> &distances, int start, int n){
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> hip;

    distances[start] = 0;
    hip.push({start, 0});

    while(!hip.empty()){
        auto [curr, dist_curr] = hip.top();
        hip.pop();

        if(found[curr])
            continue;

        found[curr] = true;

        for(auto [next, dist_next] : adj[curr]){
            if(!found[next]){
                if(distances[next] > distances[curr] + dist_next){
                    distances[next] = distances[curr] + dist_next;
                    hip.push({next, distances[next]});
                }
            }
        }
    }

    int max = 0;
    for(int i = 1; i <= n; i++){
        if(distances[i] == INF) 
            return -1;
        else if(max < distances[i])
            max = distances[i];
    }

    return max;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n + 1);
    std::vector<bool> found(n + 1, false);
    std::vector<int> distances(n + 1, INF);

    for(int i = 0; i < m; i++){
        int u, v, vreme;
        std::cin >> u >> v >> vreme;

        adj[u].emplace_back(v, vreme);
    }

    int s;
    std::cin >> s;
    int maxTime = dijkstra(adj, found, distances, s, n);

    std::cout << maxTime << '\n';

    return 0;
}