#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#include "SystemUser.h"
//class design for authentication(relation with user class)
class Authentication:public SystemUser
{

// private data members
private:

// public member functions
public:
string userCourse;
bool isAuthorized=false;
Authentication(); // default constructor
bool AuthenticateUser(); // function to authenticate
//void authorize();
virtual bool ReadFileData();
void NewUser(); // new user creation
virtual void SystemLogin();
};
#endif