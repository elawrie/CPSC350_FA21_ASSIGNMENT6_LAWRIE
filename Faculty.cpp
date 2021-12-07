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

#include "Faculty.h"
#include <iostream>

// implements faculty class

// default constructor
Faculty::Faculty(){
  m_facultyID = 0;
  m_name = "";
  m_levelField = "";
  m_department = "";
}

// overloaded constructor
Faculty::Faculty(int id, string name, string level, string department){
  m_facultyID = id;
  m_name = name;
  m_levelField = level;
  m_department = department;
  m_advisees = new TemplateDLL<int>();
}

/*
print method prints information about a faculty member
returns void
*/
void Faculty::print() {
  cout << "Faculty Member" << endl;
  cout << "Name: " << m_name << endl;
  cout << "ID: " << m_facultyID << endl;
  cout << "Level: " << m_levelField << endl;
  cout << "Department: " << m_department << endl;
  cout << "Advisees: ";
  printAdvisees();
  cout << endl;
}

/*
method to print all the advisees of a faculty member
returns void
*/
void Faculty::printAdvisees() {
  m_advisees->printList(false);
}

/*
method to print the faculty information in serialized format
returns void
*/
string Faculty::printSerialized(){
  string serializedAdvisees = m_advisees->serializedPrint();
  string serialized = to_string(m_facultyID) + ", " + m_name + ", " + m_levelField + ", " + m_department + ", " + serializedAdvisees + '\n';
  return serialized;
}

/*
method to add an advisee to the faculty member's list of advisees
returns void
*/
void Faculty::addAdvisee(int id) {
  if (m_advisees->find(id) == -1) {
    m_advisees->insertBack(id);
  }
}

/*
method to remove an advisee from the faculty member's list of advisees
returns void
*/
void Faculty::removeAdvisee(int id) {
  m_advisees->removeNode(id);
}

/*
accessor for the ID member variable
returns an integer representing the faculty member's ID
*/
int Faculty::getID() {
  return m_facultyID;
}

/*
overloaded operator for comparing faculty members by the less than operator
parameter is a faculty member to compare
returns a boolean representing if the current faculty is less than the parameter
*/
bool Faculty::operator <(const Faculty& f){
  if(this->m_facultyID < f.m_facultyID){
    return true;
  }
  return false;

}

/*
overloaded operator for comparing faculty members by the equality operator
parameter is a faculty member to compare
returns a boolean representing if the current faculty is equal to the parameter
*/
bool Faculty::operator ==(const Faculty& f){
  if(this->m_facultyID == f.m_facultyID){
    return true;
  }
  return false;

}
