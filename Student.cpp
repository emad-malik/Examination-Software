#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Student.h"
#include "Teacher.h"
#include "Authentication.h"
#include "SystemUser.h"

/////////implementing Student class functions//////////
Student::Student()
{
    studentAge= 0;
    program_enrolled= " ";
    current_semester= 0;
    current_status= ' ';
    student_CNIC= 0000;
    date_ofBirth= " ";
}
Student::Student(int studentAge, string program_enrolled, int current_semester, char current_status, long int student_CNIC, string date_ofBirth)
{
    this->studentAge= studentAge;
    this->program_enrolled= program_enrolled;
    this->current_semester= current_semester;
    this->current_status= current_status;
    this->student_CNIC= student_CNIC;
    this->date_ofBirth= date_ofBirth;
}
Student::Student(const Student& student_obj)
{
    studentAge= student_obj.studentAge;
    program_enrolled= student_obj.program_enrolled;
    current_semester= student_obj.current_semester;
    current_status= student_obj.current_status;
    student_CNIC= student_obj.student_CNIC;
    date_ofBirth= student_obj.date_ofBirth;
}
int Student::getAge() const
{
    return studentAge;
}
void Student::setAge(int studentAge)
{
    this->studentAge= studentAge;
}
string Student::getProgram() const
{
    return program_enrolled;
}
void Student::setProgram(string program_enrolled)
{
    this->program_enrolled= program_enrolled;
}
int Student::getSemester() const
{
    return current_semester;
}
void Student::setSemester(int current_semester)
{
    this->current_semester= current_semester;
}
char Student::getStatus() const
{
    return current_status;
}
void Student::setStatus(char current_status)
{
    this->current_status= current_status;
}
long int Student::getCNIC() const
{
    return student_CNIC;
}
void Student::setCNIC(long int student_CNIC)
{
    this->student_CNIC= student_CNIC;
}
string Student::getDOB() const
{
    return date_ofBirth;
}
void Student::setDOB(string date_ofBirth)
{
    this->date_ofBirth= date_ofBirth;
}
bool Student::ReadFileData()
{
    int number_ofStudents= 0, total_rows= 0, total_column= 0, current_row= 0, current_column= 0;
	// opening student data file to read data
	ifstream file_in;
	file_in.open("student_registration.txt");
	// check for failure to open file
    if(!file_in.is_open())
    {
        return false; // operation failed
    }
	/* checking rows and columns in student data file 
	   each cell is iterated and cell count is incremented
	   not that current_column is reset to zero */  
	string fileLine;
	while(getline(file_in, fileLine)) 
	{
		stringstream lineStream(fileLine);
		string fileCells;
		current_column= 0;
		while(getline(lineStream, fileCells, ',')) 
		{
			current_column++;
		}
		total_column= max(total_column, current_column);
		total_rows++;
    }
	// Allocating dynamic memory
    string** registrationData= new string*[total_rows];
    for(int iter= 0; iter<total_rows; iter++) 
	{
		registrationData[iter]= new string[total_column];
    }
	// reading data from csv file imported as .txt file 
    file_in.clear();
    file_in.seekg(0, ios::beg);
    while (getline(file_in, fileLine)) 
	{
		stringstream lineStream(fileLine);
		string fileCells;
		current_column= 0;
		while(getline(lineStream, fileCells, ',')) 
		{
			// storing in dynamic array
			registrationData[current_row][current_column]= fileCells; 
			current_column++;
		}
		current_row++;
		number_ofStudents++;
	}
    // freeing dynamic memory
    for(int iter= 0; iter<total_rows; iter++)  
	{
		delete[] registrationData[iter];
    }
    delete[] registrationData;
	
	//cout<<"Number of students: "<<number_ofStudents - 3<<endl; // 3 extra attributes in file
    // Closing file after reading
    file_in.close();
	return true; // successful operation
}
void Student::ReadStudentCourses()
{
    cout<<"Courses enrolled: "<<this->userCourse<<endl;
          
}

void Student::SystemLogin()
{
    // Read student data file and create binary files for login credentials
    Student student;
    student.ReadFileData();
    student.createLoginDatabase();
    // Authenticate user
  while (1)
  {
    Authentication S;
    student_authorized= S.isAuthorized;
    this->userName= S.userName;
    this->user_password= S.user_password;
    this->userCourse= S.userCourse;
  if (student_authorized)
  {
    cout<<endl<<"Courses enrolled:"<<userCourse<<endl;
    break;
  }
  else
    cout<<"\n\u001b[31mUnauthorized access. Try again.\u001b[0m\n";
  }
    
    //auth.Authentication();
}