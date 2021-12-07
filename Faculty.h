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

// defines faculty class

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "TemplateDLL.h"

using namespace std;

class Faculty{
public:
  Faculty(); // default constructor
  Faculty(int id, string name, string level, string department); // overloaded constructor
  ~Faculty(); // destructor
  void print(); // print information about the faculty member
  void printAdvisees(); // print advisees of the faculty member
  string printSerialized(); // print faculty member information in serialized format
  void addAdvisee(int id); // method to add a student as an advisee by ID number
  void removeAdvisee(int id); // method to remove a student as an advisee by ID number
  bool operator<(const Faculty& f); // overloaded operator <
  bool operator==(const Faculty& f); // overloaded operator ==
  int getID(); // accessor for ID
  TemplateDLL<int> *m_advisees; // list of advisees
private:
  int m_facultyID; // int representing ID
  string m_name; // string representing name
  string m_levelField; // string representing level
  string m_department; // string representing department




};

#endif
