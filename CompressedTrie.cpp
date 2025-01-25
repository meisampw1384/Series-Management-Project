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
        if (node->children[i])
        {
            clear(node->children[i]);
        }
    }

 
    delete node;
}


void CompressedTrie::insert(const string &key, Media *media)
{
    CompressedTrieNode *current = root;
    int i = 0;

    while (i < key.length())
    {
        int index = key[i] - 'a';

        if (!current->children[index])
        {
            current->children[index] = new CompressedTrieNode(key.substr(i));
            current = current->children[index];
            break;
        }

        CompressedTrieNode *child = current->children[index];
        string &nodeValue = child->value;

        int commonLength = 0;
        while (commonLength < nodeValue.size() && i < key.length() && nodeValue[commonLength] == key[i])
        {
            commonLength++;
            i++;
        }

        if (commonLength < nodeValue.size())
        {
            CompressedTrieNode *splitNode = new CompressedTrieNode(nodeValue.substr(commonLength));
            for (int j = 0; j < 26; j++)
            {
                splitNode->children[j] = child->children[j];
            }

            splitNode->mediaCount = child->mediaCount;
            for (int j = 0; j < child->mediaCount; j++)
            {
                splitNode->mediaList[j] = child->mediaList[j];
            }

            child->value = nodeValue.substr(0, commonLength);
            for (int j = 0; j < 26; j++)
            {
                child->children[j] = nullptr;
            }

            child->children[splitNode->value[0] - 'a'] = splitNode;
            child->mediaCount = 0;
        }

        current = child;
    }

    if (current->mediaCount < 100)
    {
        current->mediaList[current->mediaCount++] = media;
    }
}

void CompressedTrie::searchPrefix(const string &prefix, Media *results[], int &count)
{
    CompressedTrieNode *current = root;
    int prefixIndex = 0;

    while (current && prefixIndex < prefix.length())
    {
        bool matched = true;
        const string &nodeValue = current->value;

        for (size_t i = 0; i < nodeValue.length() && prefixIndex < prefix.length(); ++i)
        {
            if (nodeValue[i] != prefix[prefixIndex])
            {
                matched = false;
                break;
            }
            ++prefixIndex;
        }

        if (!matched)
        {
            count = 0; 
            return;
        }

        if (prefixIndex < prefix.length()) 
        {
            int index = prefix[prefixIndex] - 'a';
            current = current->children[index];
        }
    }

    if (prefixIndex == prefix.length()) 
    {
        count = 0;
        collectMedia(current, results, count); 
    }
    else
    {
        count = 0;
    }
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




