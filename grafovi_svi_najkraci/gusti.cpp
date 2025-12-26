#include <iostream>
#include <vector>

std::vector<std::vector<int>> floydWarshall(std::vector<std::vector<int>> &adj, int n){
    std::vector<std::vector<int>> minDist = adj;

    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(minDist[i][k] + minDist[k][j] < minDist[i][j])
                    minDist[i][j] = minDist[i][k] + minDist[k][j];

    return minDist;
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n);
    for(int i = 0; i < n; i++){
        adj[i].resize(n);
        for(int j = 0; j < n; j++)
            std::cin >> adj[i][j];
    }

    std::vector<std::vector<int>> minDist = floydWarshall(adj, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            std::cout << adj[i][j] - minDist[i][j] << ' ';
        std::cout << '\n';
    }
 
    return 0;
}