#include "Student.h"
#include <iostream>

Student::Student(){
  m_studentID = 0;
  m_name = "";
  m_levelField = "";
  m_major = "";
  m_gpa = 0;
  m_advisor = 0;
}

Student::Student(int id, string name, string level, string major, double gpa, int advisor){
  m_studentID = id;
  m_name = name;
  m_levelField = level;
  m_major = major;
  m_gpa = gpa;
  m_advisor = advisor;

}

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

string Student::printSerialized(){
  string serialized = to_string(m_studentID) + ", " + m_name + ", " + m_levelField + ", " + m_major + ", " + to_string(m_gpa) + ", " + to_string(m_advisor) + '\n';
  return serialized;
}

int Student::getID(){
  return m_studentID;
}

int Student::getAdvisor() {
  return m_advisor;
}

string Student::getName() {
  return m_name;
}

void Student::setAdvisor(int advisor) {
  m_advisor = advisor;
}

bool Student::operator <(const Student& s){
  if(this->m_studentID < s.m_studentID){
    return true;
  }
  return false;

}

bool Student::operator ==(const Student& s){
  if(this->m_studentID == s.m_studentID){
    return true;
  }
  return false;

}
