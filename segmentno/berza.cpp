#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <utility>

void build(std::vector<std::pair<int, int>> &tree, std::vector<int> &arr, const int i, const int start, const int end){
    if(start == end){
        tree[i] = {arr[start], 1};
        return;
    }

    int mid = (start + end) / 2;

    build(tree, arr, 2*i+1, start, mid);
    build(tree, arr, 2*i+2, mid + 1, end);

    const auto [max_left, count_left] = tree[2*i+1];
    const auto [max_right, count_right] = tree[2*i+2];

    if(max_left > max_right)
        tree[i] = {max_left, count_left};
    else if(max_left < max_right)
        tree[i] = {max_right, count_right};
    else
        tree[i] = {max_left, count_left + count_right};
}

void build(std::vector<std::pair<int, int>> &tree, std::vector<int> &arr, const int n){
    build(tree, arr, 0, 0, n - 1);
}

std::pair<int, int> query(std::vector<std::pair<int, int>> &tree, const int i, const int start, const int end, const int l, const int r){
    if(start > r || end < l)
        return {std::numeric_limits<int>::min(), 0};

    if(start >= l && end <= r)
        return tree[i];

    int mid = (start + end) / 2;

    const auto [max_left, count_left] = query(tree, 2*i+1, start, mid, l, r);
    const auto [max_right, count_right] = query(tree, 2*i+2, mid + 1, end, l, r);

    if(max_left > max_right)
        return {max_left, count_left};
    else if(max_left < max_right)
        return {max_right, count_right};
    else
        return {max_left, count_left + count_right};
}

std::pair<int, int> query(std::vector<std::pair<int, int>> &tree, const int n, const int l, const int r){
    return query(tree, 0, 0, n - 1, l, r);
}

void update(std::vector<std::pair<int, int>> &tree, const int i, const int start, const int end, const int index, const int val){
    if(start == end){
        tree[i] = {val, 1};
        return;
    }

    int mid = (start + end) / 2;

    if(index <= mid)
        update(tree, 2*i+1, start, mid, index, val);
    else
        update(tree, 2*i+2, mid + 1, end, index, val);

    const auto [max_left, count_left] = tree[2*i+1];
    const auto [max_right, count_right] = tree[2*i+2];

    if(max_left > max_right)
        tree[i] = {max_left, count_left};
    else if(max_left < max_right)
        tree[i] = {max_right, count_right};
    else
        tree[i] = {max_left, count_left + count_right};
}

void update(std::vector<std::pair<int, int>> &tree, const int n, const int index, const int val){
    update(tree, 0, 0, n - 1, index, val);
}

int main(){
    int n, q;
    std::cin >> n >> q;

    std::vector<int> arr(n);
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    const int height = ceil(log2(n));
    const int size = 2 * pow(2, height) - 1;
    std::vector<std::pair<int, int>> tree(size);

    build(tree, arr, n);
    
    while(q--){
        char op;
        std::cin >> op;
        if(op == 'u'){
            int i, v;
            std::cin >> i >> v;
            update(tree, n, i, v);
        }
        if(op == 'm'){
            int l, r;
            std::cin >> l >> r;
            auto par = query(tree, n, l, r);
            std::cout << par.first << ' ' << par.second << '\n';
        }
    }

    return 0;
}