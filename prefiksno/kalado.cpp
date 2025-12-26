#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node{
    std::unordered_map<char, Node*> children;
    bool end;
};

void addWord(Node *trie, const std::string &word){
    for(auto c : word){
        if(trie->children.find(c) == trie->children.end())
            trie->children[c] = new Node();

        trie = trie->children[c];
    }

    trie->end = true;
}

int findPrefix(Node *trie, const std::string &prefix, int d){
    for(int i = 0; i < d;){
        if(trie->children.find(prefix[i]) != trie->children.end())
            trie = trie->children[prefix[i++]];
        else
            return 0;
    }

    return 1;
}

void free(Node *trie){
    if(trie != nullptr){
        for(auto [_, node] : trie->children)
            free(node);

        delete trie;
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> words(n);
    for(int i = 0; i < n; i++)
        std::cin >> words[i];

    Node *trie = new Node();
    for(int i = 0; i < n; i++)
        addWord(trie, words[i]);

    for(int i = 0; i < m; i++){
        std::string s;
        int d;
        std::cin >> s >> d;

        std::cout << findPrefix(trie, s, d) << '\n';
    } 

    free(trie);

    return 0;
}