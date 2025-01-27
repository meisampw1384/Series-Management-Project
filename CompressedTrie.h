#ifndef COMPRESSED_TRIE_H
#define COMPRESSED_TRIE_H

#include "Media.h"

class CompressedTrieNode
{
public:
    std::string value;
    Media *mediaList[100];
    int mediaCount;
    CompressedTrieNode *children[26];

    CompressedTrieNode(std::string val = "");
};

class CompressedTrie
{
private:
    CompressedTrieNode *root;

public:
    CompressedTrie();
    ~CompressedTrie();

    void clear(CompressedTrieNode *node);
    void insert(const std::string &key, Media *media);
    void searchPrefix(const std::string &prefix, Media *results[], int &count);
    int getAllMedia(Media *results[]);
    void collectMedia(CompressedTrieNode *node, Media *results[], int &count);
};

#endif
