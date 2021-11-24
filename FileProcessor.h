
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
#include <string>
#include "TemplateDLL.h"
#include "Student.h"
#include "Faculty.h"


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
  void rtrim(string &token);

};


#endif
