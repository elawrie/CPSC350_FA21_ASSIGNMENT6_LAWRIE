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

//This is the main file where the simulation is executed

#include "TemplateBST.h"
#include "DatabaseSimulator.h"
#include <string>

int main(int argc, char **argv) {
  DatabaseSimulator *ds = new DatabaseSimulator();
  ds->simulate();
  delete ds;
  return 0;
}
