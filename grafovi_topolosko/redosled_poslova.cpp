#include <iostream>
#include <vector>
#include <queue>

std::vector<int> topolosko(std::vector<std::vector<int>> &adj, std::vector<int> &inDeg, int n){
    std::vector<int> redosled;

    std::queue<int> q;
    for(int i = 0; i < n; i++)
        if(inDeg[i] == 0){
            q.push(i);
            redosled.push_back(i);
        }

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(auto next : adj[curr]){
            inDeg[next]--;
            if(inDeg[next] == 0){
                q.push(next);
                redosled.push_back(next);
            }
        }
    }

    return redosled;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> inDeg(n);
    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[v].push_back(u);
        inDeg[u]++;
    }

    std::vector<int> raspored = topolosko(adj, inDeg, n);

    for(int i = 0; i < n; i++)
        std::cout << raspored[i] << '\n';

    return 0;
}