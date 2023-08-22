#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
#ifndef QUIZ_H
#define QUIZ_H
#include "QuestionBank.h"
#include "Student.h"

// quiz class design(relation with two classes)
class Quiz:public QuestionBank 
{

protected:
fstream quiz_file;
int Num_Questions, Time_Limit, answer_counter;
public:
Quiz();
void setQuiz(Teacher &T); 
void accessQuiz(Student &S);
};
#endif