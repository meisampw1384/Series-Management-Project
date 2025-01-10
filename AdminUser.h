
#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "User.h"

class AdminUser:public User {
public:
    AdminUser();
    ~AdminUser();
    void displayMenu();

};

#endif 
