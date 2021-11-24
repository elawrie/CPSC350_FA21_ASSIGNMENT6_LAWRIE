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

// file defines the database simulation class

#ifndef DATABASESIMULATOR_H
#define DATABASESIMULATOR_H

#include "Student.h"
#include "Faculty.h"
#include "TemplateBST.h"
#include "FileProcessor.h"

class DatabaseSimulator {
  public:
    DatabaseSimulator(); // default constructor
    ~DatabaseSimulator(); // overloaded constructor
    void populateDatabases(); // method to populate the initial databases
    void displayMenu(); // method to display the list of menu options
    void printAllStuds(); // method to print all students in ascending order by ID
    void printAllFacs(); // method to print all faculty in ascneding order by ID
    void printStud(int id); // method to print a student given their ID
    void printFac(int id); // method to print a faculty member given their ID
    void printAdvisor(int id); // method to print the advisor of a given student by ID
    void printAdvisees(int id); // method to print the advisees of a given faculty member by ID
    void addStud(); // method to add a student
    void deleteStud(int id); // method to delete a student given their ID
    void addFac(); // method to add a faculty member
    void deleteFac(int id); // method to delete a faculty memeber by ID
    void changeAdvisor(int studId, int facId); // method to change a student's advisor given both their IDs
    void removeAdvisee(int studId, int facId); // method to remove an advisee from a faculty member given both their IDs
    void rollback(); // method to reverse up to the last five commands
  private:
    FileProcessor *m_fp;
    BST<Student*> *m_studDatabase;
    BST<Faculty*> *m_facDatabase;
};




#endif
