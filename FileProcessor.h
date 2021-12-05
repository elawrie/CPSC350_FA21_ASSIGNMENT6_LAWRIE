/*
Evelyn lawrie
2364909
lawrie@chapman.edu
CPSC 350-01
Assignment 6

/*


Alejandro Rea
2378582
area@chapman.edu
CPSC350-01
Assignment 6

*/

/* This is the header file for the FileProcessor class that outlines
the necessary functions and member variables to process a file. */

#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "TemplateDLL.h"
#include "TemplateBST.h"
#include "Student.h"
#include "Faculty.h"


using namespace std;


class FileProcessor{

public:

  //default constructor
  FileProcessor();
  //destructor
  ~FileProcessor();

  BST<Student*>* processStudentFile(string studentFile);
  BST<Faculty*>* processFacultyFile(string facultyFile);
  void serializeStudentBST(string outputFile, BST<Student*>* studentBST);
  void serializeFacultyBST(string outputFile, BST<Faculty*>* facultyBST);
  void ltrim(string &token);
  void rtrim(string &token);
  BST<Student*> *m_studentBST;
  BST<Faculty*> *m_facultyBST;

private:

  // BST<Student*> *m_studentBST;
  // BST<Faculty*> *m_facultyBST;

};


#endif
