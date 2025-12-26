#include <iostream>
#include <vector>

std::vector<int> parent;
std::vector<int> size;

int groups;

void UF_init(int n){
    parent.resize(n + 1);
    size.resize(n + 1, 1);

    for(int i = 1; i <= n; i++)
        parent[i] = i;

    groups = n;
}

int UF_find(int x){
    while(x != parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }

    return x;
}

void UF_union(int x, int y){
    int fx = UF_find(x);
    int fy = UF_find(y);

    if(fx == fy)
        return;

    if(size[fx] <= size[fy]){
        parent[fx] = fy;
        size[fy] += size[fx];
    }
    else{
        parent[fy] = fx;
        size[fx] += size[fy];
    }

    groups--;
}

int main(){
    int n, m;
    std::cin >> n >> m;

    UF_init(n);

    for(int i = 0; i < m; i++){
        char op;
        std::cin >> op;

        if(op == 'U'){
            int a, b;
            std::cin >> a >> b;
            UF_union(a, b);
        }
        if(op == 'P'){
            int a, b;
            std::cin >> a >> b;
            if(UF_find(a) == UF_find(b))
                std::cout << "DA\n";
            else
                std::cout << "NE\n";
        }
        if(op == 'V'){
            int a;
            std::cin >> a;
            std::cout << size[UF_find(a)] << '\n';
        }
        if(op == 'K'){
            std::cout << groups << '\n';
        }
    }

    return 0;
}