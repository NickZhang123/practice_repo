#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <type_traits>
using namespace std;

class TrieNode {
public:
    unordered_map<char, shared_ptr<TrieNode>> children;
    bool isEndOfWord = false;
};

class Trie {
private:
    shared_ptr<TrieNode> root;

    void dfs(shared_ptr<TrieNode> node, string prefix, vector<string> &results) {
        if (node->isEndOfWord) {
            results.push_back(prefix);
        }
        for (const auto &child : node->children) {
            dfs(child.second, prefix + child.first, results);
        }
    }

public:
    Trie() {
        root = make_shared<TrieNode>();
    }

    void insert(const string &word) {
        auto node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = make_shared<TrieNode>();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    vector<string> searchPrefix(const string &prefix) {
        auto node = root;
        vector<string> results;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return results;
            }
            node = node->children[ch];
        }
        dfs(node, prefix, results);
        return results;
    }
};

// 模拟后端接口
int main_trie() {
    Trie trie;
    trie.insert("apple");
    trie.insert("application");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bat");

    string query;
    cout << "Enter query: ";
    cin >> query;

    vector<string> results = trie.searchPrefix(query);
    for (const string &word : results) {
        cout << word << endl;
    }

    cout << is_rvalue_reference<decltype(std::move(trie))>::value << endl;
    cout << is_lvalue_reference<decltype(trie)>::value << endl;

    return 0;
}
