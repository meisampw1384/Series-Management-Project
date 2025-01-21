#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Media.h"
using namespace std;

struct HashNode 
{
    string key;                  // The attribute (e.g., genre, language)
    Media* mediaList[100];       // List of Media objects for this key
    int count;                   // Number of media entries in this bucket
    HashNode* next;              // Handle collisions with chaining

    HashNode(string k) : key(k), count(0), next(nullptr) {}
};

class HashTable 
{
private:
    static const int TABLE_SIZE = 100;   // Fixed size for simplicity
    HashNode* table[TABLE_SIZE];         // Array of pointers for chaining

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;  // Basic hash function
        }
        return hash;
    }

public:
    HashTable();
    void insert(const string& key, Media* media);
    void search(const string& key_country,const string& key_language,const string& key_genre);
    void delete_media(const string& key, Media* media);
};

#endif