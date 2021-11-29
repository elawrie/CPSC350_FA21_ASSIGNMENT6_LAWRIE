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
  // FIXME: PROGRESS UPDATE COMMENT
  // TESTED ALL THESE METHODS AND THEY WORK!
  // HAVE SOME QUESTIONS IN DATABASESIMULATOR.CPP
  DatabaseSimulator *ds = new DatabaseSimulator();
  // ALL OF THE COMMENTED METHODS WORK
  // ds->displayMenu();
  // ds->printAllStuds();
  // ds->printAllFacs();
  // ds->printStud(2364909);
  // ds->printStud(2);
  // ds->printFac(1234);
  // ds->printFac(3);
  // ds->printAdvisor(2378582);
  // ds->printAdvisor(1);
  // ds->printAdvisees(4321);
  // ds->printAdvisees(0);
  // ds->addStud();
  // ds->deleteStud(2364909);
  // ds->printAllStuds();
  // ds->printAllFacs();
  // TESTING THESE NEW METHODS
  // ds->addFac(); // DOESN"T WORK
  ds->printAllFacs();
  ds->printAllStuds();
  ds->deleteFac(1234); // DOESN"T WORK
  ds->printAllFacs();
  ds->printAllStuds();
  delete ds;
  return 0;
  /*
  QUESTIONS FOR RENE IN OH:
  - can you help me debug my addFac() method?
  - when a faculty/student gets deleted, should we prompt for a new advisee/advisor or make it null when needed?
  - when a student gets deleted, removeAdvisee gets called => should this only prompt for a new advisor for the student if not called from within deleteStud method?
  - when the user inputs specific fields for member variables of students and faculty, should we check to make sure they're putting in valid values?
  - should we trap the user in a while loop when seeing if they inputted a valid faculty member for an advisor when creating a new student? or let the student have no falculty member?
  */
}
