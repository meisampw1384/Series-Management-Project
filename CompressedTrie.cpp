
#include "CompressedTrie.h"

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
    current->media = media;
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
int CompressedTrie::getAllMedia(Media *results[]) {
    int count = 0;  
    collectMedia(root, results, count);  
    return count;  
}


void CompressedTrie::collectMedia(CompressedTrieNode *node, Media *results[], int &count)
{
    if (!node)
        return;

    if (node->media)
    {
        results[count++] = node->media;
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i])
        {
            collectMedia(node->children[i], results, count);
        }
    }
}


Media* CompressedTrie::searchExact(const string& key) {
    CompressedTrieNode* currentNode = root;
    int i = 0;

    while (i < key.length()) {
        bool found = false;

    
        for (int j = 0; j < 26; j++) {
            if (currentNode->children[j] != nullptr && key[i] == currentNode->children[j]->value[0]) {
                currentNode = currentNode->children[j];
                int j = 0;
                while (j < currentNode->value.length() && i < key.length() && key[i] == currentNode->value[j]) {
                    i++;
                    j++;
                }

                if (j == currentNode->value.length()) {
                    found = true;
                }
                break;
            }
        }

        if (!found) {
            return nullptr; 
        }
    }

  
    return currentNode->media;
}
