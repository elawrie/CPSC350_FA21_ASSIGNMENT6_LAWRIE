#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
public:
  Student();
  Student(int id, string name, string level, string major, double gpa, int advisor);

  ~Student();
  void print();
  bool operator<(const Student& s);
  bool operator==(const Student& s);
  int getAdvisor();
  void setAdvisor(int advisor);
  int getID();

private:
  int m_studentID;
  string m_name;
  string m_levelField;
  string m_major;
  double m_gpa;
  int m_advisor;




};

#endif
