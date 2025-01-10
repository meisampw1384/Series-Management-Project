#ifndef CLIENTUSER_H
#define CLIENTUSER_H
#include "User.h"

class ClientUser:public User {
public:
    ClientUser(const string& uname, const string& pwd);
    ClientUser();
    void setUname(const string& uname);
    void setPwd(const string& pwd);
    ~ClientUser();



};

#endif 
