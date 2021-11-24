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

#include "TemplateBST.h"
#include "DatabaseSimulator.h"
#include <string>

int main(int argc, char **argv) {
  DatabaseSimulator *ds = new DatabaseSimulator();
  FileProcessor *processor = new FileProcessor();
  processor->processStudentFile("student.txt");
  //ds->simulate();
  return 0;
}
