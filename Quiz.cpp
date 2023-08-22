#include <cctype>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std;
#include "QuestionBank.h"
#include "Quiz.h"

///////implementing functions///////


Quiz::Quiz()
{

    Time_Limit= getTimeLimit();
    Num_Questions= getTotalQuestions();
    quiz_file.open("Quiz.txt", ios::in  | ios:: out );

  
}
void Quiz::setQuiz(Teacher &T)
{
  
    setTotalQuestions();
    setTimeLimit();
    Time_Limit= getTimeLimit();
    Num_Questions= getTotalQuestions();
    userCourse= T.userCourse;
    quiz_file<<userCourse<<";"<<Num_Questions<<";"<<Time_Limit<<endl;
  
}
void Quiz::accessQuiz(Student &S)
{
  
int iter= 0, answer_counter= 0;
  string line,answer,Available_Course,time,NumQues;
  userCourse= S.userCourse;

    fstream file("Quiz.txt", ios::in);
  file.clear();
    file.seekg(0, ios:: beg);
    if (!file.is_open())
      cout<<"Error opening file";
    
    ReadQuestionsFile(); //stores mcq and true false arrays

  //code to access our availabe quizzes 
while (getline(file, line))
{
    stringstream ss(line);
    getline(ss, Available_Course, ';');  // Extract course before ';'
    getline(ss, time, ';');  // Extract number of questions before ';'
    getline(ss, NumQues, ';');

    if (userCourse == Available_Course)
    {
        try {
            Time_Limit = stoi(time);
            Num_Questions = stoi(NumQues);
        } catch (const exception& e) {
            cerr << "\u001b[31mError: invalid time values." << e.what() << endl;
        }
        break;
    }
}

//cout<<userCourse<<"  "<<Available_Course;
  if ( userCourse!=Available_Course)
    cout<<"\n You have no pending quizzes!"<<endl;
  else
  {
  auto start_time = chrono::steady_clock::now();
   
  for (iter= 0;iter<Num_Questions; iter++)
    {
    
      int random_index= rand() % Num_Questions;
      cout<<MCQS[random_index]<<endl<<endl;
      cin>>answer;
      
      cout << "\u001b[2J"; //clears screen
      if((answer) == AnswersMCQ[random_index])
      {
        answer_counter++;
      }
        // Check if time limit has been exceeded
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time);
        if (elapsed_time.count() >= Time_Limit)
        {
            cout<<"Time's up!"<<endl;
            break;
        } 
    }
    
    cout << "You answered " << answer_counter << " questions correctly." << endl;
    cout << "Time taken: " << chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - start_time).count() << " seconds." << endl;
   // return false;

  }
}
