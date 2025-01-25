
#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"
#include "Media.h"
#include "CompressedTrie.h"
#include "SplayTree.h"
#include "HashTable.h"
#include "ClientUser.h"
class AdminUser : public User
{
public:
    AdminUser();
    ~AdminUser();
    void addMovie(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable);
    void deleteMedia(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable, SplayTree &splayTree, const string &type,ClientUser users[],int number_of_user);
    void addSeries(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable);
    void displayMenu(Media *mediaList[], int &mediaCount, CompressedTrie &compressedTrie, HashTable &hashTable,SplayTree &splayTree,ClientUser users[],int number_of_user);
};

#endif
