
/*

Alejandro Rea
2378582
area@chapman.edu
CPSC350-01
Assignment 5

*/

/* This is the header file for the FileProcessor class that outlines
the necessary functions and member variables to process a file. */

#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H




#include <iostream>
#include <fstream>
#include "TemplateDLL.h"
#include "Student.h"


using namespace std;


class FileProcessor{

public:

  //default constructor
  FileProcessor();
  //destructor
  ~FileProcessor();

  void processStudentFile(string studentFile);
  void processFacultyFile(string facultyFile);
  void ltrim(string &token);
  void ltrim(string &token);

};


#endif
