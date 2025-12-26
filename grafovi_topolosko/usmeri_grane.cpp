#include <iostream>
#include <vector>
#include <queue>

std::vector<int> redosled;

void topolosko(std::vector<std::vector<int>> &adj, std::vector<int> &inDeg, int n){
    std::queue<int> q;

    int redniBr = 0;
    
    for(int i = 0; i < n; i++)
        if(inDeg[i] == 0)
            q.push(i);

    while(!q.empty()){
        int curr = q.front();
        q.pop();

        for(auto next : adj[curr]){
            inDeg[next]--;
            if(inDeg[next] == 0){
                q.push(next);
                redosled[next] = redniBr++;
            }
        }
    }
}

int main(){
    int n, m, p;
    std::cin >> n >> m >> p;

    redosled.resize(n);
    std::vector<std::vector<int>> adj(n);
    std::vector<int> inDeg(n);

    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        inDeg[v]++;
    }
    
    topolosko(adj, inDeg, n);

    for(int i = 0; i < p; i++){
        int u, v;
        std::cin >> u >> v;

        if(redosled[u] < redosled[v])
            std::cout << "ordered: " << u << ' ' << v << '\n';
        else
            std::cout << "ordered: " << v << ' ' << u << '\n'; 
    }


    return 0;
}