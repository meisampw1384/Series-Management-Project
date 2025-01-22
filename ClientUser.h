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
    SplayTree * SuggestionTree;
    Media *favoriteList[1000];
    int favoriteCount;

public:
    ClientUser(const string &uname, const string &pwd);
    ClientUser();
    void setUname(const string &uname);
    void setPwd(const string &pwd);
    void displayMenu(HashTable *hashTable, Media *mediaList[],int &media_count);
    void searchMedia(string prefix);
    int levenshteinDistance(const string &a, const string &b);
    void advancedSearch();
    void setTrie(CompressedTrie *trie);
    void setSplayTree(SplayTree *splayTree);
    void setSuggestionTree(SplayTree *SuggestionTree);
    void displayAllMedia(Media *mediaList[],int &media_count);
    void filterMedia(HashTable *hashTable);
    void addToFavorites(Media *media);
    void removeFromFavorites(Media *media);
    void displayFavorites();
    void sortFavorites();
    void surpriseme(HashTable * hasgtable);
    ~ClientUser();
};

#endif
