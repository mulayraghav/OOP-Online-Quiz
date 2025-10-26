#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
public:
    User(string uname = "", string pass = "") : username(uname), password(pass) {}
    virtual void login() = 0;  // Pure virtual
};

#endif
