#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <chrono>
#include "QuestionBank.h"
#include "SystemUser.h"
#include "Courses.h"

////////implementing QuestionBank functions////////
QuestionBank::QuestionBank()
{ 
    choices= new string[1];
    correct_option= ' ';
    total_questions= 0;
}
QuestionBank::QuestionBank(Courses &course)
{
    userCourse = course.userCourse;
    assigned_teacher= course.userName;
    this->ReadQuestionsFile();
    //this->setTotalQuestions();
}
QuestionBank::QuestionBank(string* questionStatement, string* choices, string correct_option) 
{
    //this->questionStatement= new string[1];
    this->choices= new string[4];
    this->correct_option= correct_option;
}
int QuestionBank::getTotalQuestions()
{
    return total_questions;
}
void QuestionBank::setTotalQuestions()
{
    cout<<"Enter total number of questions."<<endl;
    cin>>total_questions;
}
void QuestionBank::setTimeLimit()
{
    int timeLimit= 0;
    cout<<"Enter quiz time in minutes."<<endl;
    cin>>timeLimit;   
}
int QuestionBank::getTimeLimit()
{
    return total_questions*60;
}
void QuestionBank :: OpenFile(fstream& file)
{
  if (userCourse == "Programming Fundamentals(CS-101)")
  file.open("pf.txt", ios ::in | ios::app);
  else if (userCourse == "Object Oriented Programming(CS-201)")
  file.open("oop.txt", ios ::in |ios::app);
  else if (userCourse == "Introduction To Computing(CS-102)")
  file.open("intocomp.txt",ios ::in | ios::app);
  else if (userCourse == "Data Structures(CS-301)")
  file.open("datast.txt", ios ::in |ios::app);
  else if (userCourse == "Analysis of Algorithms(CS-302)")
  file.open("algo.txt", ios ::in |ios::app);
  else if (userCourse == "Software Requirements Engineering(SE-301)")
  file.open("sereq.txt", ios ::in |ios::app);
  else if (userCourse == "Research Methodology(CS-501)")
  file.open("remethod.txt", ios ::in |ios::app);
  else if (userCourse == "Big Data Analytics(CS-407)")
  file.open("bdata.txt", ios ::in |ios::app);
  else if (userCourse == "Digital Image Processing(CS-409)")
  file.open("dip.txt", ios ::in |ios::app);
  else if (userCourse == "Deep Learning(CS-601)")
  file.open("deep.txt", ios ::in |ios::app);
  else if (userCourse == "Artificial Intelligence(CS-307)")
  file.open("ai.txt", ios ::in |ios::app);
  else 
    cout<< "\n [ERROR] Unable to open file. No course found.";
}
void  QuestionBank:: addtoBank()
{
    ReadQuestionsFile(); //so that we can append in our existing file
    int userChoice;
    string QuestionStatement, Options[4], answer, text_ans;
    fstream file;
    OpenFile(file);
  
    cout<<"1. Add MCQs"<<endl<<"2. Add True/False"<<endl<<"3. Add Descriptive"<<endl;
    cin>>userChoice;
    cin.ignore(); // ignore the newline character in the input buffer
    if (userChoice ==1 )
    {
        cout<< "Enter MCQ Statement: ";
        getline(cin, QuestionStatement);
        cout<< "\nEnter options: (in format A: option , B: option etc)";
    
        for (int iter=0;iter<4;iter++)
            {
                getline (cin, Options[iter]);
            }
    
    cout<< "Enter correct Option: ";
    cin>> answer;

    file<<"\n\nMCQ"<<endl;
    file<< QuestionStatement;
    for (int iter=0;iter<4;iter++)
      {
        file<<endl<<Options[iter];
      }
    file<<"`"<<answer<<endl; //wriitng according to our txt format

    ReadQuestionsFile(); 
    
    }

  else if (userChoice ==2)
  {
    cout<< "Enter True/False Statement: ";
    getline(cin, QuestionStatement);
    cout<< "\nEnter options: (in format A: option , B: option etc)";
    
    for (int iter=0;iter<2;iter++)
      {
        getline (cin, Options[iter]);
      }
    
    cout<< "Enter correct Option: ";
    cin>> answer;

    file<<"\n\nTrue/False"<<endl;
    file<< QuestionStatement;
    for (int iter=0;iter<2;iter++)
      {
        file<<endl<<Options[iter];
      }
    file<<"`"<<answer<<endl; //wriitng according to our txt format

    ReadQuestionsFile();
  }

    else if (userChoice == 3)
  {
    cout<< "Enter question statement: ";
    getline(cin, QuestionStatement);
    

    cout<< "Enter correct answer: ";
    getline(cin, text_ans);

    file<<"\n\nDescriptive"<<endl;
    file<<QuestionStatement;
    file<<"`"<<text_ans<<endl; //wriitng according to our txt format

    ReadQuestionsFile();
  }
    Redirect();
}
fstream QuestionBank::ReadQuestionsFile() 
{
    fstream file;
    string line,extra;
    m=t=s=0;
    OpenFile(file);
    while (getline(file, line)) 
        {
            if (line.find("MCQ") != string ::npos)
            // process the question and answer
            {
                getline(file, MCQS[m], '`');
                //cout<<MCQS[i]<<endl; this was just to check if array is updated
                getline(file, AnswersMCQ[m], '\n');
                m++;
            }
            else if (line.find("True/False") != string ::npos)
            // process the question and answer
            {
                getline(file, TF[t], '`');
                //cout<<TF[j]<<endl;
                getline(file, AnswersTF[t], '\n');
                t++;
            }
            else if (line.find("Descriptive") != string ::npos)
            // process the question and answer
            {
                getline(file, subjective[s], '`');
                //cout<<TF[j]<<endl;
                getline(file, subjective_answers[s], '\n');
                s++;
            }   
        }
    file.close();
    return file;  
}

void QuestionBank:: viewQuestions()
{
    string line;
    fstream questions = ReadQuestionsFile();

    OpenFile(questions);
    m=t=0;
    while (getline(questions, line))
    {
      if (line == "MCQ")
      cout<<MCQS[m++]<<endl<<endl;
      if (line == "True/False")
      cout<<TF[t++]<<endl<<endl;
      if (line == "Descriptive")
      cout<<subjective[s++]<<endl<<endl;
    }
  
    ReadQuestionsFile().close();
    Redirect();
  
}
