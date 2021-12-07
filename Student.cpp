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

// implements student class

#include "Student.h"
#include <iostream>

//default constructor
Student::Student(){
  m_studentID = 0;
  m_name = "";
  m_levelField = "";
  m_major = "";
  m_gpa = 0;
  m_advisor = 0;
}

//overloaded constructor
Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_studentID = id;
  m_name = name;
  m_levelField = level;
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;

}

/*
print method prints information about a student
returns void
*/
void Student::print() {
  cout << "Student" << endl;
  cout << "Name: " << m_name << endl;
  cout << "ID: " << m_studentID << endl;
  cout << "Level: " << m_levelField << endl;
  cout << "Major: " << m_major << endl;
  cout << "GPA: " << m_gpa << endl;
  cout << "Advisor: " << m_advisor << endl;
  cout << endl;
}

/*
method to print the student's information in serialized format
returns void
*/
string Student::printSerialized(){
  string serialized = to_string(m_studentID) + ", " + m_name + ", " + m_levelField + ", " + m_major + ", " + to_string(m_gpa) + ", " + to_string(m_advisor) + '\n';
  return serialized;
}

/*
accessor for the ID member variable
returns an integer representing the student's ID
*/
int Student::getID(){
  return m_studentID;
}

/*
accessor for the advisor member variable
returns an integer representing the faculty member's ID associated with this student
*/
int Student::getAdvisor() {
  return m_advisor;
}

/*
accessor for the name member variable
returns a string representing the student's name
*/
string Student::getName() {
  return m_name;
}

/*
mutator for the advisor member variable
returns void
*/
void Student::setAdvisor(int advisor) {
  m_advisor = advisor;
}

/*
overloaded operator for comparing students by the less than operator
parameter is a student to compare
returns a boolean representing if the current student is less than the parameter
*/
bool Student::operator <(const Student& s){
  if(this->m_studentID < s.m_studentID){
    return true;
  }
  return false;

}

/*
overloaded operator for comparing students by the equality operator
parameter is a student to compare
returns a boolean representing if the current student is equal to the parameter
*/
bool Student::operator ==(const Student& s){
  if(this->m_studentID == s.m_studentID){
    return true;
  }
  return false;

}
