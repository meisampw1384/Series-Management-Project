#ifndef CLIENTUSER_H
#define CLIENTUSER_H
#include "User.h"
#include "CompressedTrie.h"
class ClientUser:public User {
private:
    CompressedTrie* trie;
public:
    ClientUser(const string& uname, const string& pwd);
    ClientUser();
    void setUname(const string& uname);
    void setPwd(const string& pwd);
    void displayMenu();
    void searchMedia();
    void setTrie(CompressedTrie* trie);
    ~ClientUser();



};

#endif 
