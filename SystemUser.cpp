#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SystemUser.h"
#include "Teacher.h"
#include "Student.h"
#include "Courses.h"
#include "QuestionBank.h"
#include "Quiz.h"
///////implementing SystemUser class functions///////
SystemUser::SystemUser()
{
    userName= " ";
    userCourse= " ";
    userRollNum= " ";
    isRegistered= false;
    user_email= " ";
    user_password= " ";
}
SystemUser::SystemUser(string userName, string userCourse)
{
    this->userName= userName;
    this->userCourse= userCourse;
}
string SystemUser::GenerateRandomPassword()
{
// this functions helps generate a random password of desired length. the passsword must have one Uppercase, one lowercase, one special character and one number
    int  count_upper= 0, count_lower= 0, count_special= 0, count_digits= 0, counter= 0, pass_length=8;
    string userPassword= "";
    string upperCase= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowerCase= "abcdefghijklmnopqrstuvwxyz";
    string special_char= "!@#$%&";
    string digits= "0123456789";
// generating random numbers   
    for(static int index =0; index<216; index++)
        {
            srand(index); // seed the random number generator
        }
    // generate random uppercase letter
    userPassword+= upperCase[rand() % upperCase.length()];
    count_upper++;
    // generate random lowercase letter
    userPassword+= lowerCase[rand() % lowerCase.length()];
    count_lower++;
    // generate random digit
    userPassword+= digits[rand() % digits.length()];
    count_digits++;
    // generate random special character
    userPassword+= special_char[rand() % special_char.length()];
    count_special++;
    // generate remaining characters
    for(int iter= 4; iter<pass_length; iter++) 
        {
            int choice= rand() % 4;
        if((choice == 0) && (count_upper < 2)) 
        {
            userPassword+= upperCase[rand() % upperCase.length()];
            count_upper++;
        } 
        else if((choice == 1) && (count_lower < 2)) 
        {
            userPassword+= lowerCase[rand() % lowerCase.length()];
            count_lower++;
        } 
        else if((choice == 2) && (count_digits < 2)) 
        {
            userPassword+= digits[rand() % digits.length()];
            count_digits++;
        } 
        else if((choice == 3) && (count_special < 2)) 
        {
            userPassword+= special_char[rand() % special_char.length()];
            count_special++;
        } 
        else 
        {
            userPassword+= upperCase[rand() % upperCase.length()];
            count_upper++;
        }
    }
    return userPassword;
}
extern void SystemUser::createLoginDatabase()
{
//this function extracts username from "students.txt" and writes it into "login_database.dat" with a random password alongside it
    string courses[11]= { "Artificial Intelligence(CS-307)" ,  "Deep Learning(CS-601)" , "Digital Image Processing(CS-409)" , "Big Data Analytics(CS-407)" , "Research Methodology(CS-501)" , "Software Requirements Engineering(SE-301)" , "Analysis of Algorithms(CS-302)","Data Structures(CS-301)" , "Introduction To Computing(CS-102)" , "Object Oriented Programming(CS-201)" , "Programming Fundamentals(CS-101)"};
  
    fstream file_in("student_registration.txt", ios:: in);//file from where we have to read usernames
    fstream file_out("login_database.dat", ios::out); //file where we want to write our credentials
     if(!file_out.is_open()) 
     {
         cout<<"Error opening file\n";
     }
    char ch;
    int i;
    string fileLine, extra;
    while (!file_in.eof())
    {
      srand(i++);
      int random_index= rand()% 11;
        file_in.get(ch);
        if (ch== ',')
        {
            (getline(file_in, fileLine, ','));  
            file_out<<fileLine<<"@nu.edu.pk"<<';'<<GenerateRandomPassword()<<';'<<courses[random_index]<<endl;
            getline(file_in, extra); // skip the rest of the line
        }    
    } 
    file_in.seekg(0, ios:: beg); //sets readability to start of program;    
}
 void SystemUser::Redirect()
{
       while(1)
        {
    int userChoice= 0, teacherChoice= 0, studentChoice= 0;
    Student student;
    Teacher teacher;
    Quiz Q;
  
    cout<<"\033[1m\033[36m\nWelcome to FAST Examination Software.\033[7m\nThis is designed to assist both Teachers and Students. \nIt can automatically generate a quiz, and conduct quiz with time constraints. \nIt can produce results and analytics after students have attempted their quiz. \nDesigned by: Malik Emad Iqbal.";
    while(1)
        {
            cout<<"\nLogin Menu";
            cout<<"\n1. Teacher Login"<<"\n2. Student Login"<<"\n3. Exit";
            cin>>userChoice;
            if(userChoice == 3)
           {
               cout<<"\033[1m\033[36mWe wish to see you soon : )"<<endl;
               break;
           }
            if((userChoice>=1) && (userChoice<=3))
            {
                break;
            }
            else
            {
                cout<<"\u001b[31mPlease select from the given options.\u001b[0m"<<endl;
            }
        }
        
            
        
  cout << "\u001b[2J"; //clears screen
  
    if(userChoice == 1)
    {
        teacher.SystemLogin();
        Courses course(teacher);
      QuestionBank questions(course);
      if (teacher.isAuthorised)
      {
    cout<<"\nPress 1 to Access Question Bank or create Quiz";
    cout<<"\n1. Create Quiz"<<"\n2. Back to Main Menu";
    cin>>teacherChoice;
    if(teacherChoice == 1)
    {
        //Courses quiz_questions;
        cout<<"\n1. Add to Question Bank"<<"\n2. Import and view"<<"\n3. Back to Main Menu"<<"\n4. Set Quiz";
        cin>>teacherChoice;
        if(teacherChoice == 1)
        { 
            questions.addtoBank();
        }
      else if (teacherChoice == 2)
      {    
        
        questions.viewQuestions();
        
      }
      else if(teacherChoice == 3)
      {
          teacher.Redirect();
      }
      else if (teacherChoice == 4)
      {    
        
        Q.setQuiz(teacher);
        teacher.Redirect();
        
      }  
    }
    else if(teacherChoice == 2) 
    {
        teacher.Redirect();
    }
    else if(teacherChoice == 3)
    {
        teacher.Redirect();
    }
      
      }
    }
    else if(userChoice == 2)
    {
        student.SystemLogin();
        if(student.student_authorized) 
        {
        cout<<"\n1. Attempt Quiz"<<"\n2. Back to Main Menu"<<"\n ";
        cin>>studentChoice;
        if(studentChoice == 1)
        {
            Q.accessQuiz(student);
        }
    
        else if(studentChoice == 2)
        {
            student.Redirect();
        } 
        }
    }
    else if(userChoice == 3)
    {
        cout<<"\033[1m\033[36mWe wish to see you soon : )"<<endl;
      break;

    }
    else
    {
      cout<<"\u001b[31mPlease select from the given options.\u001b[0m"<<endl;
      break;
    }

        }
}