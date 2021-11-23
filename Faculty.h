#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "TemplateDLL.h"

using namespace std;

class Faculty{
public:
  Faculty();
  Faculty(int id, string name, string level, string department);
  ~Faculty();

  bool operator<(const Faculty& f);
private:
  int m_facultyID;
  string m_name;
  string m_levelField;
  string m_department;
  TemplateDLL<int> *m_advisees;




};

#endif
