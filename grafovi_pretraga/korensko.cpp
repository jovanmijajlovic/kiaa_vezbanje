#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <utility>

std::vector<std::pair<int, int>> dfs(std::vector<std::vector<int>> &graph, int n, std::vector<bool> &visited, int start){
    std::vector<std::pair<int, int>> edges;

    std::stack<int> stek;
    stek.push(start);
    visited[start] = true;

    while(!stek.empty()){
        int curr = stek.top();
        stek.pop();
        for(auto next : graph[curr]){
            if(!visited[next]){
                stek.push(next);
                visited[next] = true;
                edges.emplace_back(curr, next);
            }
        }    
    }
    
    std::sort(edges.begin(), edges.end());
    return edges;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n);
    std::vector<bool> visited(n, false);

    for(int i = 1; i < n; i++){
        int u, v;
        std::cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    std::cin >> start;

    std::vector<std::pair<int, int>> edges = dfs(graph, n, visited, start);

    for(auto edge : edges){
        std::cout << edge.first << ' ' << edge.second << '\n';
    }

    return 0;
}