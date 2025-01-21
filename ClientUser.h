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

public:
    ClientUser(const string &uname, const string &pwd);
    ClientUser();
    void setUname(const string &uname);
    void setPwd(const string &pwd);
    void displayMenu(HashTable& hashTable);
    void searchMedia();
    int levenshteinDistance(const string &a, const string &b);
    void advancedSearch();
    void setTrie(CompressedTrie *trie);
    void setSplayTree(SplayTree *splayTree);
    void filterMedia(HashTable& hashTable);
    ~ClientUser();
};

#endif
