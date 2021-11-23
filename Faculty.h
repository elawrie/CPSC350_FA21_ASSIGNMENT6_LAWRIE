#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include "TemplateDLL.h"

using namespace std;

class Student{
public:
  Student();
  ~Student();

private:
  int m_facultyID;
  string m_name;
  string m_levelField;
  string m_department;
  TemplateDLL<T> *m_advisees;




};

#endif
