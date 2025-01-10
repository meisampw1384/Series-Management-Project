#include "ClientUser.h"


ClientUser::ClientUser():User(){

}


ClientUser::ClientUser(const string& uname, const string& pwd):User(uname,pwd){

}

void ClientUser::setUname(const string& uname){
    username = uname;
}
void ClientUser::setPwd(const string& pwd){
    password = pwd;
}

ClientUser::~ClientUser(){

}
