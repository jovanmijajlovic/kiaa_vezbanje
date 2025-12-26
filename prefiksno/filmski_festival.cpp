#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node{
    std::unordered_map<char, Node*> children;
    int count = 0;
    bool end = false;
};

void addWord(Node *trie, const std::string &word){
    for(auto c : word){
        if(trie->children.find(c) == trie->children.end())
            trie->children[c] = new Node();

        trie = trie->children[c];
        trie->count++;
    }

    trie->end = true;
}

std::string makeId(Node *trie, const std::string &word){
    std::string id = "";
    for(auto c : word){
        trie = trie->children[c];
        id += c;
        if(trie->count == 1)
            return id;
    }

    return id;
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

    for(int i = 0; i < n; i++)
        std::cout << makeId(trie, words[i]) << '\n';

    free(trie);

    return 0;
}