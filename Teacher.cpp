#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Teacher.h" 
////////implementing Teacher class functions///////
Teacher::Teacher()
{  
    employment_status= ' ';
    years_ofExperience= 0;
 // TeacherAuthentication();
    
}
Teacher::Teacher(char employment_status, int years_ofExperience)
{
    this->employment_status= employment_status;
    this->years_ofExperience= years_ofExperience;
    TeacherAuthentication();
}
Teacher::Teacher(const Teacher& teacher_obj)
{
    employment_status= teacher_obj.employment_status;
    years_ofExperience= teacher_obj.years_ofExperience;
}
char Teacher::getEmploymentStatus() const
{
    return employment_status;
}
void Teacher::setEmploymentStatus(char employment_status)
{
    this->employment_status= employment_status;
}
int Teacher::getExperience() const
{
    return years_ofExperience;
}
void Teacher::setExperience(int years_ofExperience)
{
    this->years_ofExperience= years_ofExperience;
}
bool Teacher::ReadFileData()
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
	   not that current_column is reset to zero*/  
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
bool Teacher::TeacherAuthentication()
{
    
    cout<<"\nEnter your userName:";
    cin>>userName;
    cout<<"\nEnter your user_password:";
    cin>>user_password;

    string Tempuser, Temppassword;
    credentials_file.open("teacher_database.dat", ios::in);
    credentials_file.clear(); // clears any error flags
    credentials_file.seekg(0, ios:: beg); //sets readability to start of program
    string fileLine, TempUser, TempPass;
    while (getline(credentials_file, fileLine))
    {
        stringstream fileStream(fileLine);
        getline(fileStream, TempUser, ';');  // Extract id before '@'
      
        getline(fileStream, TempPass, ';');  // Extract password before ';'
      
        getline(fileStream, userCourse, '\n');  // Extract the course name and ignore it 
    if((this->userName == TempUser) && (this->user_password == TempPass))
    {
        cout<<"\u001b[32mAUTHORIZED \u001b[0m"<<endl;
        isAuthorised= true;
        return isAuthorised;
    }
    }
  
    cout<< "\u001b[31mUnauthorized:Access Denied.\u001b[0m"<<endl;
    credentials_file.clear();
    credentials_file.close();
    isAuthorised= false;
    return isAuthorised;

}
void Teacher::SystemLogin()
{
    // Read teacher data file and create binary files for login credentials   
    isAuthorised =TeacherAuthentication();
    // Authenticate user
    //Authentication auth;
    //auth.AuthenticateUser();
}