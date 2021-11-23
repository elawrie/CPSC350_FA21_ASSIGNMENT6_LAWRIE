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
