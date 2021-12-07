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

#ifndef ROLLBACK_H
#define ROLLBACK_H

#include <iostream>
#include "Student.h"
#include "Faculty.h"

using namespace std;

// defines RollbackObject class

class RollbackObject{
public:
  RollbackObject(); // default constructor
  RollbackObject(string action, string treeType, Student* student, Faculty* faculty); // overloaded constructor

  ~RollbackObject(); // destructor

  string getAction(); // accessor for the action member variable
  string getTreeType(); //accessor for the tree type member variable
  Student* getStudent(); // accessor for the student member variable
  Faculty* getFaculty(); //accessor for the facutly member variable
  void print();
private:
  string m_action; //action member variable that represents most recent action in simulation
  string m_treeType; // tree type member variable specifies in which tree the change will be made
  Student* m_student; //student member variable represents the student associated with the most recent action
  Faculty* m_faculty; // faculty member variable represents the faculty associated with the most recent action

};

#endif
