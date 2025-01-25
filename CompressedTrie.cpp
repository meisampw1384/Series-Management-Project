#include "CompressedTrie.h"
#include <iostream>

using namespace std;


CompressedTrieNode::CompressedTrieNode(string val) : value(val), mediaCount(0)
{
    for (int i = 0; i < 26; i++)
    {
        children[i] = nullptr;
    }
}


CompressedTrie::CompressedTrie()
{
    root = new CompressedTrieNode();
}


CompressedTrie::~CompressedTrie()
{
    clear(root);
}


void CompressedTrie::clear(CompressedTrieNode *node)
{
    if (!node)
        return;
    for (int i = 0; i < 26; i++)
    {
        clear(node->children[i]);
    }
    delete node;
}


void CompressedTrie::insert(const string &key, Media *media)
{
    CompressedTrieNode *current = root;
    for (char c : key)
    {
        int index = c - 'a';
        if (!current->children[index])
        {
            current->children[index] = new CompressedTrieNode(string(1, c));
        }
        current = current->children[index];
    }

   
    if (current->mediaCount < 100)
    {
        current->mediaList[current->mediaCount++] = media;
    }
}


void CompressedTrie::searchPrefix(const string &prefix, Media *results[], int &count)
{
    CompressedTrieNode *current = root;
    for (char c : prefix)
    {
        int index = c - 'a';
        if (!current->children[index])
        {
            count = 0;
            return;
        }
        current = current->children[index];
    }

    count = 0;
    collectMedia(current, results, count);
}


void CompressedTrie::collectMedia(CompressedTrieNode *node, Media *results[], int &count)
{
    if (!node)
        return;

  
    for (int i = 0; i < node->mediaCount; i++)
    {
        results[count++] = node->mediaList[i];
    }

   
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i])
        {
            collectMedia(node->children[i], results, count);
        }
    }
}


int CompressedTrie::getAllMedia(Media *results[])
{
    int count = 0;
    collectMedia(root, results, count);
    return count;
}



bool CompressedTrie::removeHelper(CompressedTrieNode* node, const string& key, int depth, Media* media) {
    if (!node) return false; 

    if (depth == key.length()) {
        for (int i = 0; i < node->mediaCount; i++) {
            if (node->mediaList[i] == media) {
                for (int j = i; j < node->mediaCount - 1; j++) {
                    node->mediaList[j] = node->mediaList[j + 1];
                }
                node->mediaCount--;

                
                return node->mediaCount == 0; 
            }
        }
        return false; 
    }


    int index = key[depth] - 'a';

    
    if (!node->children[index]) return false;

    
    bool shouldDeleteChild = removeHelper(node->children[index], key, depth + 1, media);

    if (shouldDeleteChild) {
        delete node->children[index];
        node->children[index] = nullptr;
        bool isEmpty = true;
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                isEmpty = false;
                break;
            }
        }

        return isEmpty && node->mediaCount == 0; 
    }

    return false; 
}


bool CompressedTrie::remove(const string &key, Media *media)
{
    return removeHelper(root, key, 0, media);
}
