#include "Student.h"
#include <iostream>

Student::Student(){
  m_studentID = 0;
  m_name = NULL;
  m_levelField = NULL;
  m_major = NULL;
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
