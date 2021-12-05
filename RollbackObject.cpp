#include "RollbackObject.h"

RollbackObject::RollbackObject(){}

RollbackObject::RollbackObject(string action, string treeType, Student* student, Faculty* faculty){
  m_action = action;
  m_treeType = treeType;
  m_student = student;
  m_faculty = faculty;
}

RollbackObject::~RollbackObject(){}

string RollbackObject::getAction(){
  return m_action;
}

string RollbackObject::getTreeType(){
  return m_treeType;
}

Student* RollbackObject::getStudent(){
  return m_student;
}

Faculty* RollbackObject::getFaculty(){
  return m_faculty;
}
