#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Media.h"
using namespace std;

struct HashNode 
{
    string key;
    Media* mediaList[100];
    int count;
    HashNode* next;

    HashNode(string k) : key(k), count(0), next(nullptr) {}
};

class HashTable 
{
private:
    static const int TABLE_SIZE = 100;
    HashNode* table[TABLE_SIZE];

    int hashFunction(const string& key) 
    {
        int hash = 0;
        for (char c : key) 
        {
            hash = (hash * 31 + c) % TABLE_SIZE; 
        }
        return hash;
    }

public:
    HashTable();
    void insert(const string& key, Media* media);
    void search(const string& key_country,const string& key_language,const string& key_genre, const int& key_year, const int& key_score);
    void delete_media(const string& key, Media* media);
};

#endif