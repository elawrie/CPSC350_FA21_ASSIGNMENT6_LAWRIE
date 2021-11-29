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
  // HAVE SOME QUESTIONS FOR ALEX IN FIXME COMMENTS DATABASESIMULATOR.CPP
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
  // ds->printAllFacs();
  // ds->printAllStuds();
  // ds->deleteFac(1234);
  // ds->printAllFacs();
  // ds->printAllStuds();
  // MINOR BUGS => EXPLAINED BELOW
  ds->printAllFacs();
  ds->printAllStuds();
  ds->addFac();
  ds->printAllFacs();
  ds->printAllStuds();
  delete ds;
  return 0;

  /*
  QUESTIONS FOR RENE IN OH:
  - can you help me debug my addFac() method if necessary? it works except when you add an advisee when the faculty's ID starts with a 0 => says the faculty ID is invalid

  - can we assume that the student/faculty names will always be two words? faculty level and department will also be two words? => else, is there a way to cin until a return character rather than whitespace?

  - when a faculty/student gets deleted, should we prompt for a new advisee/advisor or make it null when needed?

  - we should remove students from other advisee lists when they get added to a new advisee list, right? FIXME: IMPLEMENT THIS 

  - what do you mean by warning the user about referential integrity? which cases should we warn for, and is it okay if we just execute the commands and fix them ourselves?

  - when a student gets deleted, removeAdvisee gets called => should this only prompt for a new advisor for the student if not called from within deleteStud method?

  - when a faculty member is deleted, their advisees have an advisor ID of 0 => is this okay? should we prompt for a new advisor?

  - for inserting students/faculty, when the user inputs specific fields for member variables of students and faculty, should we check to make sure they're putting in valid values?

  - should we trap the user in a while loop when seeing if they inputted a valid faculty member for an advisor when creating a new student? or let the student have no falculty member?
  */
}
