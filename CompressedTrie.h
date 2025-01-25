#ifndef COMPRESSED_TRIE_H
#define COMPRESSED_TRIE_H

#include "Media.h" // Assuming you have a Media class defined

class CompressedTrieNode
{
public:
    std::string value;
    Media *mediaList[100];            // Array to hold multiple Media objects (up to 100)
    int mediaCount;                   // To keep track of how many Media objects are stored in the node
    CompressedTrieNode *children[26]; // Children nodes (for each letter a-z)

    // Constructor
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
