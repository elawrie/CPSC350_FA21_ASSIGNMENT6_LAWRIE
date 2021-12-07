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

// defines student class

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

using namespace std;

class Student{
public:

  //default constructor
  Student();

  //overloaded constructor
  Student(int id, string name, string level, string major, double gpa, int advisor); //

  // destructor
  ~Student();
  void print(); // prints out the information of a student
  string printSerialized(); // print student information in serialized format
  bool operator<(const Student& s); // overloaded operator <
  bool operator==(const Student& s); // overloaded operator ==
  int getAdvisor(); // accessor for the advisor member variable
  void setAdvisor(int advisor); // mutator for the advisor member variable (allows to change advisor)
  int getID(); // accessor for the ID member variable
  string getName(); //accessor for the student's name

private:
  int m_studentID; //member variable for a student's ID
  string m_name; //member variable for a student's name
  string m_levelField; // member variable for a student's level field
  string m_major; // member variable for a student's major
  double m_gpa; //member variable for a student's gpa
  int m_advisor; // member variable for a student's advisor




};

#endif
