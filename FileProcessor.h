/*
Evelyn Lawrie
2364909
lawrie@chapman.edu
CPSC 350-01
Assignment 6


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

  BST<Student*>* processStudentFile(string studentFile); //reads in all the information from a text file to form a student* based BST according to that info
  BST<Faculty*>* processFacultyFile(string facultyFile); //reads in all the information from a text file to form a faculty* based BST according to that info
  void serializeStudentBST(string outputFile, BST<Student*>* studentBST); // writes the student BST in serialized format to a file
  void serializeFacultyBST(string outputFile, BST<Faculty*>* facultyBST); // writes the faculty BST in serialized format to a file
  void ltrim(string &token); //removes extra whitespace before a token
  bool validateID(string id); //checks if the ID of a student/advisor is a valid number
  BST<Student*> *m_studentBST; //Student* based BST that contains info from studentTable
  BST<Faculty*> *m_facultyBST; //Faculty* based BST that contains info from facultyTable


};


#endif
