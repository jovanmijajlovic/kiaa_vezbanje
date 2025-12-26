#include <iostream>
#include <vector>
#include <stack>

void dfs1(std::vector<std::vector<int>> &adj, std::vector<bool> &visited, int start){    
    std::stack<int> s;
    s.push(start);
    visited[start] = true;

    while(!s.empty()){
        int curr = s.top();
        s.pop();

        for(auto next : adj[curr]){
            if(!visited[next]){
                s.push(next);
                visited[next] = true;
            }
        }
    }   
}

void dfs2(std::vector<std::vector<int>> &invAdj, std::vector<bool> &visited, int start){
    std::stack<int> s;
    s.push(start);
    visited[start] = true;

    while(!s.empty()){
        int curr = s.top();
        s.pop();

        for(auto next : invAdj[curr]){
            if(!visited[next]){
                s.push(next);
                visited[next] = true;
            }
        }
    }
}

bool kosaraju(std::vector<std::vector<int>> &adj, std::vector<std::vector<int>> &invAdj, std::vector<bool> &visited, int start, int n){
    dfs1(adj, visited, start);

    for(int i = 1; i <= n; i++){
        if(!visited[i])
            return false;
    }

    std::fill(visited.begin(), visited.end(), false);

    dfs2(invAdj, visited, start);

    for(int i = 1; i <= n; i++){
        if(!visited[i])
            return false;
    }

    return true;
}

int main(){
    int q;
    std::cin >> q;

    while(q--){
        int n, m;
        std::cin >> n >> m;

        std::vector<std::vector<int>> adj(n + 1);
        std::vector<std::vector<int>> invAdj(n + 1);
        std::vector<bool> visited(n + 1, false);
        for(int i = 0; i < m; i++){
            int smer, u, v;
            std::cin >> smer >> u >> v;

            if(smer == 1){
                adj[u].push_back(v);
                invAdj[v].push_back(u);
            }
            if(smer == 2){
                adj[u].push_back(v);
                adj[v].push_back(u);

                invAdj[v].push_back(u);
                invAdj[u].push_back(v);
            }
        }

        if(kosaraju(adj, invAdj, visited, 1, n))
            std::cout << "Da" << '\n';
        else
            std::cout << "Ne" << '\n';
    }

    return 0;
}