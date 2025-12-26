#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct Node{
    std::unordered_map<char, Node*> children;
    bool end;
    std::string word;
};

void addWord(Node *trie, const std::string &word){
    for(auto c : word){
        if(trie->children.find(c) == trie->children.end())
            trie->children[c] = new Node();

        trie = trie->children[c];
    }
    trie->end = true;
    trie->word = word;
}

void print(Node *trie){
    if(trie->end)
        std::cout << trie->word << ' ';
    for(auto [_, node] : trie->children)
        print(node);
}

void completeWord(Node *trie, const std::string &prefix){
    for(auto c : prefix){
        if(trie->children.find(c) != trie->children.end())
            trie = trie->children[c];
        else if(!trie->end){
            std::cout << -1 << '\n';
            return;
        }
    }

    print(trie);
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

    std::string pref;
    std::cin >> pref;
    completeWord(trie, pref);

    free(trie);
    return 0;
}
