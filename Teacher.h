#include <iostream>
#include <fstream>
using namespace std;
#ifndef TEACHER_H
#define TEACHER_H
#include "SystemUser.h"

//class design for teacher(relation with user class)
class Teacher:public SystemUser
{
// private data members of class
private: 
char employment_status;
int years_ofExperience;
// public methods and constructors of class 


public:
bool isAuthorised;
fstream credentials_file= fstream("teacher_database.dat", ios::in | ios::out);
//Courses Course;
Teacher(); // default constructor
Teacher(char, int); // parameter constructor
Teacher(const Teacher&); // copy constructor
/* getters/setters for members */ 
char getEmploymentStatus() const;
void setEmploymentStatus(char);
int getExperience() const;
void setExperience(int);
void CreateQuiz(); // quiz creation option
void addQuestions(); // modify quiz option
int assignGrades(); // marks after quiz 
bool TeacherAuthentication();
virtual bool ReadFileData();
virtual void SystemLogin();
};
#endif