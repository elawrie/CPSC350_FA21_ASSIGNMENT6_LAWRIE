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
  // DatabaseSimulator *ds = new DatabaseSimulator();
  // FileProcessor *processor = new FileProcessor();
  // processor->processStudentFile("student.txt");
  Student *stud1 = new Student(2364909, "Evelyn Lawrie", "Sophomore", "Computer Science", 4.0, 1234);
  Student *stud2 = new Student(2378582, "Alex Rea", "Sophomore", "Computer Science", 4.0, 1234);
  Student *stud3 = new Student(3243432, "Joe Smith", "Junior", "Computer Engineering", 3.2, 4321);
  // stud->print();
  // Faculty *fac = new Faculty(1234, "Rene German", "Associate Professor", "Computer Science");
  // fac->addAdvisee(2364909);
  // fac->addAdvisee(2378582);
  // fac->print();
  //ds->simulate();
  BST<Student*> *bst = new BST<Student*>();
  bst->insert(stud1);
  bst->insert(stud2);
  bst->insert(stud3);
  cout << "FOUND: ";
  bst->find(2364909)->print();
  cout << endl;
  delete bst;
  return 0;
}
