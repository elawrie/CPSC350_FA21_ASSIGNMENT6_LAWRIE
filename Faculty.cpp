#include "Faculty.h"
#include <iostream>

Faculty::Faculty(){
  m_facultyID = 0;
  m_name = "";
  m_levelField = "";
  m_department = "";
}

Faculty::Faculty(int id, string name, string level, string department){
  m_facultyID = id;
  m_name = name;
  m_levelField = level;
  m_department = department;
  m_advisees = new TemplateDLL<int>();
}

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

void Faculty::printAdvisees() {
  m_advisees->printList(false);
}

void Faculty::addAdvisee(int id) {
  m_advisees->insertBack(id);
}

int Faculty::getID() {
  return m_facultyID;
}

bool Faculty::operator <(const Faculty& f){
  if(this->m_facultyID < f.m_facultyID){
    return true;
  }
  return false;

}

bool Faculty::operator ==(const Faculty& f){
  if(this->m_facultyID == f.m_facultyID){
    return true;
  }
  return false;

}
