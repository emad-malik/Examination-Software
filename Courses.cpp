#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Teacher.h"
#include "SystemUser.h"
#include "Courses.h"
////////implementing functions////////
Courses::Courses()
{
    userName= " ";
    userCourse= " ";
}
Courses::Courses(Teacher &T)
{
  
    course_code= T.userCourse;
    assigned_teacher= T.userName;
    this->userName=T.userName; 
    this->user_password=T.user_password;
  
    ReadCourses();
}
Courses::Courses(string userName, string assigned_teacher, string course_code)
{
    this->userName= userName;
    this->assigned_teacher= assigned_teacher;
    this->course_code= course_code;
}
string Courses::getTeacherName()
{
    return userName;
}
void Courses::setTeacherName(string userName)
{
    this->userName= userName;
}
string Courses::getCourseID()
{
    return course_code;
}
void Courses::setCourseID(string course_code)
{
    this->course_code= course_code;
}
bool Courses::ReadCourses()
{
    ifstream file_in("teacher_database.dat");
    if (!file_in.is_open())
    {
        return false;
    }
    string fileLine, TempUser, TempPass;
    while (getline(file_in, fileLine))
    {
        stringstream fileStream(fileLine);
        getline(fileStream, TempUser, ';');  // Extract id before '@'
      
        getline(fileStream, TempPass, ';');  // Extract password before ';'
      
        getline(fileStream, userCourse, '\n');  // Extract the course name
        if((this->userName == TempUser) && (this->user_password == TempPass))
        {
            cout<<"Course name: "<<userCourse<<endl;
          return true;
        }
    }
    file_in.close();
    return true; // successful operation  
}
