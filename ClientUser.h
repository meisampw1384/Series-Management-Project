#ifndef CLIENTUSER_H
#define CLIENTUSER_H
#include "User.h"
#include "CompressedTrie.h"
#include "SplayTree.h"
#include "HashTable.h"
class ClientUser : public User
{
private:
    CompressedTrie *trie;
    SplayTree *splayTree;
    Media *favoriteList[1000];
    int favoriteCount;

public:
    ClientUser(const string &uname, const string &pwd);
    ClientUser();
    void setUname(const string &uname);
    void setPwd(const string &pwd);
    void displayMenu(HashTable &hashTable, Media *mediaList[]);
    void searchMedia();
    int levenshteinDistance(const string &a, const string &b);
    void advancedSearch();
    void setTrie(CompressedTrie *trie);
    void setSplayTree(SplayTree *splayTree);
    void displayAllMedia(Media *mediaList[]);
    void filterMedia(HashTable &hashTable);
    void addToFavorites(Media *media);
    void removeFromFavorites(Media *media);
    void displayFavorites();
    void sortFavorites();
    ~ClientUser();
};

#endif
