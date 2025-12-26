#include <iostream>
#include <vector>
#include <stack>

std::string dfs(std::vector<std::vector<int>> &adj, int n, int start, int end){
    std::vector<bool> visited(n + 1, false);

    std::stack<int> s;
    s.push(start);
    visited[start] = true;

    while(!s.empty()){
        int curr = s.top();
        s.pop();

        for(auto next : adj[curr]){
            if(next == end)
                return "da";
            if(!visited[next]){
                s.push(next);
                visited[next] = true;
            }
        }
    }

    return "ne";
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n + 1);
    for(int i = 0; i < m; i++){
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
    }

    int p;
    std::cin >> p;
    
    std::vector<bool> visited(n + 1, false);
    while(p--){
        int start, end;
        std::cin >> start >> end;

        std::cout << dfs(adj, n, start, end) << '\n';
    }
}