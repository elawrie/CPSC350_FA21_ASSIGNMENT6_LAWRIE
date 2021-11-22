/*
Evelyn lawrie
2364909
lawrie@chapman.edu
CPSC 350-01
Assignment 6

<<<<<<< HEAD
=======
/*

>>>>>>> 698b9f2127f18fc2de8b4235a206875381d49a09
Alejandro Rea
2378582
area@chapman.edu
CPSC350-01
<<<<<<< HEAD
Assignment 6
=======
Assignment 5

>>>>>>> 698b9f2127f18fc2de8b4235a206875381d49a09
*/

/* This is the header file for the FileProcessor class that outlines
the necessary functions and member variables to process a file. */

#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

<<<<<<< HEAD
#include <iostream>
#include <fstream>
#include "TemplateDLL.h"
#include "Student.h"
=======



#include <iostream>
#include <fstream>
#include <string>
#include "TemplateDLL.h"
#include "Student.h"
#include "Faculty.h"
>>>>>>> 698b9f2127f18fc2de8b4235a206875381d49a09


using namespace std;

<<<<<<< HEAD
=======

>>>>>>> 698b9f2127f18fc2de8b4235a206875381d49a09
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
