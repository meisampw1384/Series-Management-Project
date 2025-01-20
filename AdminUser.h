
#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"
#include "Media.h"
#include "CompressedTrie.h"
class AdminUser:public User {
public:
    AdminUser();
    ~AdminUser();
    void addMovie(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie);
    void addSeries(Media* mediaList[],int &mediaCount,CompressedTrie &compressedTrie);
    void displayMenu(Media* mediaList[], int& mediaCount,CompressedTrie &compressedTrie);

};

#endif 
