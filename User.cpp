#include "User.h"

User::User(const string uname, const string &pwd)
{
    username = uname;
    password = pwd;
}
User::User() : username(""), password("")
{
}

User::~User()
{
}

string User::getUsername()
{
    return username;
}

string User::getPassword(){
    return password;
}

void User::displayMenu(){
    
}
