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

std::string longestPref(Node *trie){
    std::string pref = "";

    while(trie->children.size() == 1 && !trie->end){
        auto [c, node] = *trie->children.begin();

        pref += c;
        trie = node;
    }

    return pref;
}

void free(Node *trie){
    if(trie != nullptr){
        for(auto [_, node] : trie->children)
            free(node);

        delete trie;
    }
}

int main(){
    int n;
    std::cin >> n;

    std::vector<std::string> words(n);

    for(int i = 0; i < n; i++)
        std::cin >> words[i];

    Node *trie = new Node();
    for(int i = 0; i < n; i++)
        addWord(trie, words[i]);

    std::cout << longestPref(trie) << '\n';

    free(trie);

    return 0;
}