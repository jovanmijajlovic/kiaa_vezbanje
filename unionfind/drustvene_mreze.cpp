#include <iostream>
#include <vector>

std::vector<int> parent;
std::vector<int> size;

void UF_init(int n){
    parent.resize(n + 1);
    size.resize(n + 1, 1);

    for(int i = 1; i <= n; i++){
        parent[i] = i;
    }
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

    if(size[fx] < size[fy]){
        parent[fx] = fy;
        size[fy] += size[fx];
    }
    else{
        parent[fy] = fx;
        size[fx] += size[fy];
    }
}

int main(){
    int n, q;
    std::cin >> n >> q;

    UF_init(n);

    while(q--){
        char op;
        std::cin >> op;

        if(op == 'M'){
            int a, b;
            std::cin >> a >> b;
            UF_union(a, b);
        }
        if(op == 'Q'){
            int a;
            std::cin >> a;
            std::cout << size[UF_find(a)] << '\n';
        }
    }

    return 0;
}