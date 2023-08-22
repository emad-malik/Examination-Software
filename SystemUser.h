#include <iostream>
#include <fstream>
using namespace std;
#ifndef SYSTEMUSER_H
#define SYSTEMUSER_H
// user class design
class SystemUser
{
// data members
protected: 

string userRollNum;
bool isRegistered;
string user_email;

fstream credentials_file;
public:
string userName;
string userCourse;
string user_password;
SystemUser(); // default constructor
SystemUser(string, string); // parameter constructor
virtual bool ReadFileData()= 0; // pure virtual function which reads data
virtual void createLoginDatabase(); // function which creates id/pass file
virtual string GenerateRandomPassword(); // random password generator
virtual void SystemLogin()= 0; // login for user
static void Redirect();
};
#endif