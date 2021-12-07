/*
Evelyn Lawrie
2364909
lawrie@chapman.edu
CPSC 350-01
Assignment 6

Alejandro Rea
2378582
area@chapman.edu
CPSC 350-01
Assignment 6
*/

// implements RollbackObject class

#include "RollbackObject.h"

//default constructor
RollbackObject::RollbackObject(){}

//overloaded constructor
RollbackObject::RollbackObject(string action, string treeType, Student* student, Faculty* faculty){
  m_action = action;
  m_treeType = treeType;
  m_student = student;
  m_faculty = faculty;
}

//destructor
RollbackObject::~RollbackObject(){}

/*
accessor for the action member variable
returns a string representing what action was most recently performed
*/
string RollbackObject::getAction(){
  return m_action;
}

/*
accessor for the treeType member variable
returns a string representing in what tree should the change be made
*/
string RollbackObject::getTreeType(){
  return m_treeType;
}

/*
accessor for the student member variable
returns Student* representing the student associated with the most recent action
*/
Student* RollbackObject::getStudent(){
  return m_student;
}

/*
accessor for the faculty member variable
returns Faculty* representing the faculty associated with the most recent action
*/
Faculty* RollbackObject::getFaculty(){
  return m_faculty;
}

/*
print method for printing all of the RollbackObject's information
returns void
*/
void RollbackObject::print() {
  cout << "ACTION: " << m_action << endl;
  cout << "TREE TYPE: " << m_treeType << endl;
  if (m_student != NULL) {
    m_student->print();
  }
  if (m_faculty != NULL) {
    m_faculty->print();
  }
}
