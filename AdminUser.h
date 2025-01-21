
#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"
#include "Media.h"
#include "CompressedTrie.h"
#include "HashTable.h"
class AdminUser:public User {
public:
    AdminUser();
    ~AdminUser();
    void addMovie(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable);
    void deleteMovie(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable);
    void addSeries(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable);
    void displayMenu(Media* mediaList[], int& mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable);
    void deleteSeries(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie,HashTable& hashTable);

};

#endif 
