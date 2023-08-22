#include <iostream>
#include <fstream>
using namespace std;
#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H
#include "Courses.h"
// class design for QuestionBank class(relation with courses class)
class QuestionBank:public Courses
{
protected:
int m, t, s;
string MCQS[15];
string TF[15];
string subjective[20];
string AnswersMCQ[15], AnswersTF[15], subjective_answers[50];

string* choices;
string correct_option;
int total_questions;
public:
QuestionBank();
QuestionBank(Courses&);
QuestionBank(string*, string*, string);
fstream ReadQuestionsFile();
void addtoBank();
int getTotalQuestions();
void setTotalQuestions();
void setTimeLimit();
int getTimeLimit();
void viewQuestions();
void OpenFile(fstream&);
};
#endif