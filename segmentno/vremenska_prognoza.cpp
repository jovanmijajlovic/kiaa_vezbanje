#include <iostream>
#include <vector>
#include <cmath>

void build(std::vector<double> &tree, const std::vector<double> &arr, const int i, const int start, const int end){
    if(start == end){
        tree[i] = arr[start];
        return;
    }

    int mid = (start + end) / 2;

    build(tree, arr, 2*i+1, start, mid);
    build(tree, arr, 2*i+2, mid + 1, end);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

void build(std::vector<double> &tree, const std::vector<double> &arr, const int n){
    build(tree, arr, 0, 0, n - 1);
}

void update(std::vector<double> &tree, const int i, const int start, const int end, const int index, const double val){
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

void update(std::vector<double> &tree, const int n, const int index, const double val){
    update(tree, 0, 0, n - 1, index, val);
}

double query(std::vector<double> &tree, const int i, const int start, const int end, const int l, const int r){
    if(start > r || end < l)
        return 0;

    if(start >= l && end <= r)
        return tree[i];

    int mid = (start + end) / 2;

    double left_sum = query(tree, 2*i+1, start, mid, l, r);
    double right_sum = query(tree, 2*i+2, mid + 1, end, l, r);

    return left_sum + right_sum;
}

double query(std::vector<double> &tree, const int n, const int l, const int r){
    return query(tree, 0, 0, n - 1, l, r);
}

int main(){
    int n;
    std::cin >> n;

    std::vector<double> arr(n);
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    const int height = ceil(log2(n));
    const int size = 2 * pow(2, height) - 1;
    std::vector<double> tree(size);
    build(tree, arr, n);

    int m;
    std::cin >> m;
    char op;
    while(m--){
        std::cin >> op;
        if(op == 'u'){
            int i;
            double k;
            std::cin >> i >> k;
            update(tree, n, i - 1, k);
        }
        if(op == 'p'){
            int a, b;
            std::cin >> a >> b;
            std::cout << query(tree, n, a - 1, b - 1) / (b - a + 1) << '\n';
        }
    }

    return 0;
}