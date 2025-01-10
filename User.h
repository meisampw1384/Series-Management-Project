#ifndef USER_H
#define USER_H

#include <iostream> 
using namespace std;

class User {
protected:
    string username;
    string password;
public:
    User(const string uname , const string& pwd);
    User();
    virtual ~User();
    string getUsername();
    string getPassword();
    void displayMenu();

};




#endif
