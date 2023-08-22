#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Teacher.h"
using namespace std;
#ifndef COURSE_H
#define COURSE_H
// course class design(relation with teacher class)
class Courses:public Teacher
{
// private data members
protected:

string course_code;
string assigned_teacher;
// public member functions
public:
Courses(); // default constructor
Courses(Teacher &T); // parameter constructor
Courses(string, string, string); // parameter constructor
string getCourseID();
void setCourseID(string);
string getTeacherName(); // get assigned teacher name
void setTeacherName(string); // set assigned teacher name
bool ReadCourses(); 
};
#endif
