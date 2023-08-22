#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Authentication.h"
#include "SystemUser.h"
//////implementing Authentication class functions///////
Authentication::Authentication()
{
    int userChoice;
    cout<<"Do you want to create a new user?(Press 1)";
    cin>>userChoice;
    if(userChoice == 1)
    {
        NewUser();
    }
    cout<<"\nEnter your userName:";
    cin>>userName;
    cout<<"\nEnter your user_password:";
    cin>>user_password;
    AuthenticateUser();
}
void Authentication::NewUser()
{ 
    string new_UserName= "", new_userPassword= "";
     while(1)
        {
            cout<<"\nEnter New Username:";
            cin>>new_UserName;
            cout<<"\nEnter Password:";
            cin>>new_userPassword;
            if(AuthenticateUser())
            {
                cout<<"User already exists, Try again ";
            }
            else
            {
                break;
            }
        }
    while (AuthenticateUser())
    {
    cout<< "User already exists, Try again ";
    }
    // open credentials_file in append mode
    ofstream credentials_file_out("login_database.dat", ios::app);
    credentials_file_out<<endl;
  // write new username and password to end of credentials_file
    credentials_file_out<<new_UserName<<';'<<new_userPassword<<';';
    cout<<"\nNew user created! Enter your credentials again.";
}
bool Authentication::AuthenticateUser() 
{
    string userName, user_password;
    credentials_file.open("login_database.dat", ios::in);
    credentials_file.clear(); // clears any error flags
    credentials_file.seekg(0, ios:: beg); //sets readability to start of program
    while(!credentials_file.eof()) 
    { //eof is used to check if end of credentials_file has been reached yet
        getline(credentials_file, userName, ';'); // use ; as delimiter
        getline(credentials_file, user_password,';');
      getline(credentials_file, userCourse,'\n');
      // use line end as delimiter
        // remember; delimiter readed from input but not added to output
        if(!credentials_file.is_open())
        {
            cout<<"File not opened."<<endl;
            return false;
        }
      
        if((this->userName == userName) && (this->user_password == user_password))
        {
            credentials_file.close();
            cout<<"Authorised."<<endl;
            isAuthorized=true;
            return true;
        }
    }
    credentials_file.clear();
    credentials_file.close();
    return false;
}
bool Authentication::ReadFileData()
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
	
	cout<<"Number of students: "<<number_ofStudents - 3<<endl; // 3 extra attributes in file
    // Closing file after reading
    file_in.close();
	return true; // successful operation
}
void Authentication::SystemLogin()
{/*
    int userChoice= 0;
    cout<<"\nWelcome to FAST Examination Software. \nThis is designed to assist both Teachers and Students. \nDesigned by: Malik Emad Iqbal.";
    cout<<"\nPress 1 for Teacher login and Press 2 for Student Login";
    cout<<"\n1. Teacher"<<"\n2. Student";
    cin>>userChoice;
    if(userChoice == 2)
    {
        // Read student data file and create binary files for login credentials
        Student student;
        student.ReadFileData();
        student.createLoginDatabase();
        // Authenticate user
        Authentication auth;
        auth.AuthenticateUser();
    }*/ 
}