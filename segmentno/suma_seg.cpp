#include <iostream>
#include <vector>
#include <cmath>

void build(std::vector<int> &tree, std::vector<int> &arr, const int i, const int start, const int end){
    if(start == end){
        tree[i] = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    build(tree, arr, 2*i+1, start, mid);
    build(tree, arr, 2*i+2, mid + 1, end);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

void build(std::vector<int> &tree, std::vector<int> &arr, int n){
    build(tree, arr, 0, 0, n - 1);
}

int query(std::vector<int> &tree, const int i, const int start, const int end, const int l, const int r){
    if(start > r || end < l)
        return 0;

    if(start >= l && end <= r)
        return tree[i];

    int mid = (start + end) / 2;

    int sum_left = query(tree, 2*i+1, start, mid, l, r);
    int sum_right = query(tree, 2*i+2, mid + 1, end, l, r);

    return sum_left + sum_right;
}

int query(std::vector<int> &tree, const int n, const int l, const int r){
    return query(tree, 0, 0, n - 1, l, r);
}

void update(std::vector<int> &tree, const int i, const int start, const int end, const int index, const int val){
    if(start == end){
        tree[i] = val;
        return;
    }

    int mid = (start + end) / 2;

    if(index <= mid)
        update(tree, 2*i+1, start, mid, index, val);
    else
        update(tree, 2*i+2, mid + 1, end, index, val);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

void update(std::vector<int> &tree, const int n, const int index, const int val){
    update(tree, 0, 0, n - 1, index, val);
}

int main(){
    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    const int height = ceil(log2(n));
    const int size = 2 * pow(2, height) - 1;
    std::vector<int> tree(size);

    build(tree, arr, n);

    int m;
    std::cin >> m;
    while(m--){
        char op;
        std::cin >> op;

        if(op == 'p'){
            int i, v;
            std::cin >> i >> v;
            update(tree, n, i, v);
        }
        if(op == 'z'){
            int a, b;
            std::cin >> a >> b;
            std::cout << query(tree, n, a, b) << '\n';
        }
    }


    return 0;
}