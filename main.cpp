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
#include <string>

int main(int argc, char **argv) {
  BST<int> *bst = new BST<int>();
  bst->insert(4);
  bst->insert(8);
  bst->insert(2);
  bst->insert(6);
  bst->insert(10);
  bst->printNodes();
  delete bst;
  return 0;
}
