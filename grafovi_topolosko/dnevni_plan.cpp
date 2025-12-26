#include <iostream>
#include <vector>
#include <queue>

int topolosko(std::vector<std::vector<int>> &adj, std::vector<int> &inDeg, int n){
    std::queue<int> q;
    for(int i = 1; i <= n; i++){
        if(inDeg[i] == 0)
            q.push(i);
    }

    if(q.empty())
        return -1;

    q.push(-1);

    int dan = 0;
    while(!q.empty()){
        int curr = q.front();
        q.pop();

        if(curr == -1){
            dan++;
            if(q.empty())
                break;
            q.push(-1);
            continue;
        }

        for(auto next : adj[curr]){
            inDeg[next]--;
            if(inDeg[next] == 0)
                q.push(next);
        }
    }

    for(int i = 1; i <= n; i++)
        if(inDeg[i] > 0)
            return -1;

    return dan;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> inDeg(n + 1);
    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        inDeg[v]++;
    }

    std::cout << topolosko(adj, inDeg, n) << '\n';

    return 0;
}