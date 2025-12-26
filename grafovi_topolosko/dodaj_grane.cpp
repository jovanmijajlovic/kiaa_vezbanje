#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

std::vector<int> topolosko(std::vector<std::vector<int>> &adj, std::vector<int> &inDeg, int n){
    std::vector<int> redosled(n);
    
    std::queue<int> q;
    for(int i = 0; i < n; i++)
        if(inDeg[i] == 0)
            q.push(i);

    int redniBr = 1;

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(int next : adj[curr]){
            inDeg[next]--;
            if(inDeg[next] == 0){
                q.push(next);
                redosled[next] = redniBr++;
            }
        }
    }

    return redosled;
}

std::vector<std::pair<int, int>> addEdges(std::vector<std::vector<int>> &adj, std::vector<int> &inDeg, int n){
    std::vector<std::pair<int, int>> newEdges;

    std::vector<int> redosled = topolosko(adj, inDeg, n);
    std::vector<bool> visited(n);

    for(int i = 0; i < n; i++){
        int curr = redosled[i];

        std::fill(visited.begin(), visited.end(), false);

        for(auto next : adj[curr])
            visited[next] = true;

        for(int j = i + 1; j < n; j++){
            int next = redosled[j];
            if(!visited[next])
                newEdges.emplace_back(curr, next);
        }
    }

    std::sort(newEdges.begin(), newEdges.end());
    return newEdges;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> inDeg(n, 0);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        inDeg[v]++;
    }

    std::vector<std::pair<int, int>> newEdges = addEdges(adj, inDeg, n);

    for(auto grana : newEdges){
        std::cout << grana.first << ' ' << grana.second << '\n';
    }

    return 0;
}