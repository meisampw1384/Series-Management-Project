
#include "CompressedTrie.h"

CompressedTrie::CompressedTrie() {
    root = new CompressedTrieNode();
}

CompressedTrie::~CompressedTrie() {
    clear(root);
}

void CompressedTrie::clear(CompressedTrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        clear(node->children[i]);
    }
    delete node;
}

void CompressedTrie::insert(const string& key, Media* media) {
    CompressedTrieNode* current = root;
    for (char c : key) {
        int index = c - 'a';
        if (!current->children[index]) {
            current->children[index] = new CompressedTrieNode(string(1, c));
        }
        current = current->children[index];
    }
    current->media = media;
}

void CompressedTrie::searchPrefix(const string& prefix, Media* results[], int& count) {
    CompressedTrieNode* current = root;
    for (char c : prefix) {
        int index = c - 'a';
        if (!current->children[index]) {
            count = 0;  
            return;
        }
        current = current->children[index];
    }

    count = 0;
    auto collect = [&](CompressedTrieNode* node, auto& collect) -> void {
        if (node->media) {
            results[count++] = node->media;
        }
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                collect(node->children[i], collect);
            }
        }
    };
    collect(current, collect);
}
