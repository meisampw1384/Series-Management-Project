

#ifndef COMPRESSEDTRIE_H
#define COMPRESSEDTRIE_H

#include "Media.h"

class CompressedTrieNode
{
public:
    string value;
    CompressedTrieNode *children[26];
    Media *media;

    CompressedTrieNode(string val = "") : value(val), media(nullptr)
    {
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};

class CompressedTrie
{
private:
    CompressedTrieNode *root;

public:
    CompressedTrie();
    ~CompressedTrie();
    void insert(const string &key, Media *media);
    void searchPrefix(const string &prefix, Media *results[], int &count);
    void clear(CompressedTrieNode *node);
    void collectMedia(CompressedTrieNode *node, Media *results[], int &count);
    int getAllMedia(Media *results[]);
    Media* searchExact(const string& key);
};

#endif // COMPRESSEDTRIE_H
