/*
Evelyn lawrie
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

// implementation file for the database simulation class

#include "DatabaseSimulator.h"

// default constructor
DatabaseSimulator::DatabaseSimulator() {
  m_fp = new FileProcessor();
  masterStudent = new BST<Student*>();
  masterFaculty = new BST<Faculty*>();
}

// destructor
DatabaseSimulator::~DatabaseSimulator() {
  delete m_fp;
  delete masterFaculty;
  delete masterStudent;
}

// void DatabaseSimulator::populateDatabases() {
//   // check if student file exists
//   if (m_fp->getStudDatabase()->getRoot() != NULL) {
//     masterStudent = m_fp->getStudDatabase();
//   }
//   // check if faculty file exists
//   if (m_fp->getFacDatabase()->getRoot() != NULL) {
//     masterFaculty = m_fp->getFacDatabase();
//   }
// }
