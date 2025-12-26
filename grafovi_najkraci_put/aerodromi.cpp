#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

#define INF std::numeric_limits<int>::max()

struct compare{
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2){
        return p1.first > p2.first;
    }
};

int dijkstra(std::vector<std::vector<std::pair<int, int>>> &adj, std::vector<int> &distances, std::vector<bool> &found, int start, int end, int izbegni){
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, compare> hip;

    distances[start] = 0;
    
    hip.push({distances[start], start});

    while(!hip.empty()){
        std::pair<int, int> curr = hip.top();
        hip.pop();

        if(found[curr.second])
            continue;

        found[curr.second] = true;

        for(auto next : adj[curr.second]){
            if(next.second == izbegni)
                continue;

            if(distances[next.first] > distances[curr.first] + next.second){
                distances[next.first] = distances[curr.first] + next.second;
                hip.push({distances[next.first], next.first});
            }
        }
    }

    return distances[end];
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int, int>>> adj(n);
    std::vector<int> distances(n, INF);
    std::vector<bool> found(n, false);

    for(int i = 0; i < m; i++){
        int u, v, cena;
        std::cin >> u >> v >> cena;

        adj[u].emplace_back(v, cena);
        adj[v].emplace_back(u, cena);
    }

    int q;
    std::cin >> q;

    while(q--){
        int start, end, da, ne;
        std::cin >> start >> end >> da >> ne;

        std::fill(distances.begin(), distances.end(), INF);
        std::fill(found.begin(), found.end(), false);

        int first_price = dijkstra(adj, distances, found, start, da, ne);

        std::fill(distances.begin(), distances.end(), INF);
        std::fill(found.begin(), found.end(), false);

        int price = first_price + dijkstra(adj, distances, found, da, end, ne);

        std::cout << price << '\n';
    }

    return 0;
}