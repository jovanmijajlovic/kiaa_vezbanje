#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>

#define INF std::numeric_limits<double>::max()

struct compare{
    bool operator()(std::pair<int, double> &p1, std::pair<int, double> &p2){
        return p1.second > p2.second;
    }
};

double dijkstra(std::vector<std::vector<std::pair<int, double>>> &adj, std::vector<bool> &found, std::vector<double> &distances, std::vector<int> &parent, int start, int end){
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, compare> hip;

    distances[start] = 0;

    hip.push({start, distances[start]});

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
                    parent[next] = curr;
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

    std::vector<std::vector<std::pair<int, double>>> adj(n);
    std::vector<bool> found(n, false);
    std::vector<double> distances(n, INF);

    std::vector<int> parent(n, -1);

    for(int i = 0; i < m; i++){
        int u, v;
        double t;
        std::cin >> u >> v >> t;

        adj[u].emplace_back(v, t);
    }

    int start, end;
    std::cin >> start >> end;

    std::cout << std::fixed << std::setprecision(4) << dijkstra(adj, found, distances, parent, start, end) << '\n';

    if(parent[end] == -1 && start != end)
        std::cout << "ne";
    else{
        std::stack<int> put;
        for(int i = end; i != -1; i = parent[i]){
            put.push(i);
        }
        while(!put.empty()){
            std::cout << put.top() << ' ';
            put.pop();
        }
    }

    return 0;
}