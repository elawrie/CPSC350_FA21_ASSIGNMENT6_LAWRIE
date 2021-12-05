#ifndef ROLLBACK_H
#define ROLLBACK_H

#include <iostream>
#include "Student.h"
#include "Faculty.h"

using namespace std;

class RollbackObject{
public:
  RollbackObject();
  RollbackObject(string action, string treeType, Student* student, Faculty* faculty);

  ~RollbackObject();

  string getAction();
  string getTreeType();
  Student* getStudent();
  Faculty* getFaculty();

private:
  string m_action;
  string m_treeType;
  Student* m_student;
  Faculty* m_faculty;

};

#endif
