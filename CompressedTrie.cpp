#include "CompressedTrie.h"
#include <iostream>

using namespace std;

// Constructor for CompressedTrieNode
CompressedTrieNode::CompressedTrieNode(string val) : value(val), mediaCount(0)
{
    for (int i = 0; i < 26; i++)
    {
        children[i] = nullptr;
    }
}

// Constructor for CompressedTrie
CompressedTrie::CompressedTrie()
{
    root = new CompressedTrieNode();
}

// Destructor for CompressedTrie
CompressedTrie::~CompressedTrie()
{
    clear(root);
}

// Recursive method to clear the trie
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

// Method to insert a media item into the trie
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

    // Add the media to the node's mediaList array if there's space
    if (current->mediaCount < 100)
    {
        current->mediaList[current->mediaCount++] = media;
    }
}

// Method to search for media based on a prefix
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

// Collect all media from the given node
void CompressedTrie::collectMedia(CompressedTrieNode *node, Media *results[], int &count)
{
    if (!node)
        return;

    // Collect all media from the node's mediaList array
    for (int i = 0; i < node->mediaCount; i++)
    {
        results[count++] = node->mediaList[i];
    }

    // Recursively collect from child nodes
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i])
        {
            collectMedia(node->children[i], results, count);
        }
    }
}

// Method to get all media from the trie
int CompressedTrie::getAllMedia(Media *results[])
{
    int count = 0;
    collectMedia(root, results, count);
    return count;
}

// Method to search for exact match
Media *CompressedTrie::searchExact(const string &key)
{
    CompressedTrieNode *currentNode = root;
    int i = 0;

    while (i < key.length())
    {
        bool found = false;

        for (int j = 0; j < 26; j++)
        {
            if (currentNode->children[j] != nullptr && key[i] == currentNode->children[j]->value[0])
            {
                currentNode = currentNode->children[j];
                int j = 0;
                while (j < currentNode->value.length() && i < key.length() && key[i] == currentNode->value[j])
                {
                    i++;
                    j++;
                }

                if (j == currentNode->value.length())
                {
                    found = true;
                }
                break;
            }
        }

        if (!found)
        {
            return nullptr;
        }
    }

    // Return the first match in the mediaList array
    if (currentNode->mediaCount > 0)
    {
        return currentNode->mediaList[0]; // Return the first media
    }

    return nullptr;
}

bool CompressedTrie::removeHelper(CompressedTrieNode* node, const string& key, int depth, Media* media) {
    if (!node) return false; // If the node is null, nothing to remove

    if (depth == key.length()) {
        // We've reached the end of the key (full name match)
        // Remove the specific media from the mediaList
        for (int i = 0; i < node->mediaCount; i++) {
            if (node->mediaList[i] == media) {
                // Found the media to remove, shift the remaining media items
                for (int j = i; j < node->mediaCount - 1; j++) {
                    node->mediaList[j] = node->mediaList[j + 1];
                }
                node->mediaCount--;  // Decrement media count

                // If no media is left at this node, check if it can be deleted
                return node->mediaCount == 0; // Return true if node is now empty
            }
        }
        return false; // Media not found in this node
    }

    // Calculate the index of the child node based on the current character in the key
    int index = key[depth] - 'a';

    // If no child exists for the current character, return false
    if (!node->children[index]) return false;

    // Recursively remove from the child node
    bool shouldDeleteChild = removeHelper(node->children[index], key, depth + 1, media);

    if (shouldDeleteChild) {
        // If the child node should be deleted, remove it
        delete node->children[index];
        node->children[index] = nullptr;

        // If the current node has no children and no media, return true for deletion
        bool isEmpty = true;
        for (int i = 0; i < 26; i++) {
            if (node->children[i]) {
                isEmpty = false;
                break;
            }
        }

        return isEmpty && node->mediaCount == 0; // Delete node only if it's completely empty
    }

    return false; // Don't delete the current node
}


bool CompressedTrie::remove(const string &key, Media *media)
{
    return removeHelper(root, key, 0, media);
}
