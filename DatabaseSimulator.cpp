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

// implementation file for the database simulation class

#include "DatabaseSimulator.h"
#include "TemplateDLL.h"
#include <iostream>

using namespace std;

// default constructor
DatabaseSimulator::DatabaseSimulator() {
  rollbackStack = new GenStack<RollbackObject*>();
  m_fp = new FileProcessor();
  masterStudent = new BST<Student*>();
  masterFaculty = new BST<Faculty*>();
  BST<Student*> *tempStuds = m_fp->processStudentFile("studentTable.txt");
  if (!tempStuds->isEmpty()) {
    masterStudent = tempStuds;
  }
  BST<Faculty*> *tempFacs = m_fp->processFacultyFile("facultyTable.txt");
  if (!tempFacs->isEmpty()) {
    masterFaculty = tempFacs;
  }
}

// destructor
DatabaseSimulator::~DatabaseSimulator() {}


/*
method to run the student database simulation
returns void
*/
void DatabaseSimulator::simulate() {
  string userInput;
  string id;
  int studId;
  int facId;
  string buffer;
  int rollbackCount = 0;
  bool didRollback;
  // validate BSTs from files
  cout << endl;
  if (validateBSTs(masterStudent->root) == false) {
    cout << "There is a mismatch of a student/faculty pair." << endl;
    return;
  }
  do {
    displayMenu();
    cin >> userInput;
    if (userInput == "1") {
      printAllStuds();
    }
    else if (userInput == "2") {
      printAllFacs();
    }
    else if (userInput == "3") {
      cout << "Enter the ID of the student to print: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        studId = stoi(id);
        printStud(studId);
      }
    }
    else if (userInput == "4") {
      cout << "Enter the ID of the faculty member to print: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        facId = stoi(id);
        printFac(facId);
      }
    }
    else if (userInput == "5") {
      cout << "Enter the ID of the student to print the advisor of: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        studId = stoi(id);
        printAdvisor(studId);
      }
    }
    else if (userInput == "6") {
      cout << "Enter the ID of the faculty member to print the advisees of: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        facId = stoi(id);
        printAdvisees(facId);
      }
    }
    else if (userInput == "7") {
      addStud();
      rollbackCount = 0;
    }
    else if (userInput == "8") {
      if (masterStudent->isEmpty()) {
        cout << "Student database empty: cannot delete" << endl;
        continue;
      }
      cout << "Enter the ID of the student to delete: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        studId = stoi(id);
        deleteStud(studId, false);
        rollbackCount = 0;
      }
    }
    else if (userInput == "9") {
      addFac();
      rollbackCount = 0;
    }
    else if (userInput == "10") {
      if (masterFaculty->isEmpty()) {
        cout << "Faculty database empty: cannot delete" << endl;
        continue;
      }
      cout << "Enter the ID of the faculty member to delete: ";
      getline(cin, buffer);
      getline(cin, id);
      if (validateID(id)) {
        facId = stoi(id);
        deleteFac(facId, false);
        rollbackCount = 0;
      }
    }
    else if (userInput == "11") {
      if (masterStudent->isEmpty() || masterStudent->isEmpty()) {
        cout << "Database empty: cannot change advisor" << endl;
        continue;
      }
      cout << "Enter the ID of the student: ";
      getline(cin, buffer);
      getline(cin, id);
      if (!validateID(id)) {
        continue;
      }
      studId = stoi(id);
      cout << "Enter the ID of the faculty member: ";
      getline(cin, id);
      if (validateID(id)) {
        facId = stoi(id);
        changeAdvisor(studId, facId, false, false);
      }
    }
    else if (userInput == "12") {
      if (masterStudent->isEmpty() || masterStudent->isEmpty()) {
        cout << "Database empty: cannot remove advisee" << endl;
        continue;
      }
      cout << "Enter the ID of the student: ";
      getline(cin, buffer);
      getline(cin, id);
      if (!validateID(id)) {
        continue;
      }
      studId = stoi(id);
      cout << "Enter the ID of the faculty member: ";
      getline(cin, id);
      if (validateID(id)) {
        facId = stoi(id);
        removeAdvisee(studId, facId, false);
      }

    }
    else if (userInput == "13") {
      if (rollbackCount > 5) {
        cout << "Cannot undo more actions: rollback limit has been reached" << endl;
        continue;
      }
      didRollback = rollback();
      if(didRollback){
        ++rollbackCount;
      }

    }
    else {
      if (userInput == "14") {
        m_fp->serializeStudentBST("studentTable.txt", masterStudent);
        m_fp->serializeFacultyBST("facultyTable.txt", masterFaculty);
        break;
      }
      cout << "Enter a valid option" << endl;
    }
    cout << endl;
  }
  while (userInput != "14");
}

/*
method to display the list of menu options
returns void
*/
void DatabaseSimulator::displayMenu() {
  cout << "Type '1' to print all students" << endl;
  cout << "Type '2' to print all faculty" << endl;
  cout << "Type '3' to print a specific student" << endl;
  cout << "Type '4' to print a specific faculty member" << endl;
  cout << "Type '5' to print a student's advisor" << endl;
  cout << "Type '6' to print a faculty members's advisees" << endl;
  cout << "Type '7' to add a new student" << endl;
  cout << "Type '8' to delete a student" << endl;
  cout << "Type '9' to add a new faculty member" << endl;
  cout << "Type '10' to delete a faculty member" << endl;
  cout << "Type '11' to change a student's advisor" << endl;
  cout << "Type '12' to remove a faculty member's advisee" << endl;
  cout << "Type '13' to rollback" << endl;
  cout << "Type '14' to exit" << endl;
}

/*
method to print all students in ascending order by ID
returns void
*/
void DatabaseSimulator::printAllStuds() {
  masterStudent->printNodes();
}

/*
method to print all faculty members in ascending order by ID
returns void
*/
void DatabaseSimulator::printAllFacs() {
  masterFaculty->printNodes();
}

/*
method to print a student given their ID
parameter is an int representing a student's ID
returns void
*/
void DatabaseSimulator::printStud(int id) {
  if (masterStudent->find(id) != NULL) {
    masterStudent->find(id)->print();
  }
  else {
    cout << "Student not found" << endl;
    cout << endl;
  }
}

/*
method to print a faculty member given their ID
parameter is an int representing a faculty member's ID
retuns void
*/
void DatabaseSimulator::printFac(int id) {
  if (masterFaculty->find(id) != NULL) {
    masterFaculty->find(id)->print();
  }
  else {
    cout << "Faculty member not found" << endl;
    cout << endl;
  }
}

/*
method to print the advisor of a given student by ID
parameter is an int representing a student's ID
returns void
*/
void DatabaseSimulator::printAdvisor(int id) {
  Student *stud = masterStudent->find(id);
  if (stud != NULL) {
    masterFaculty->find(stud->getAdvisor())->print();
  }
  else {
    cout << "Student not found" << endl;
    cout << endl;
  }
}

/*
method to print the advisees of a given faculty member by ID
parameter is an int representing a faculty member's ID
retuns void
*/
void DatabaseSimulator::printAdvisees(int id) {
  Faculty *fac = masterFaculty->find(id);
  if (fac != NULL) {
    DoubleListNode<int> *current = fac->m_advisees->getFront();
    while (current != NULL) {
      masterStudent->find(current->data)->print();
      current = current->next;
    }
  }
  else {
    cout << "Faculty member not found" << endl;
    cout << endl;
  }
}

/*
method to add a student into the student database
returns void
*/
void DatabaseSimulator::addStud() {
  int id = generateId(false);
  string name;
  string level;
  string major;
  double gpa;
  int advisor;
  string buffer;
  string idString;
  getline(cin, buffer);
  cout << "Enter the student's name: ";
  getline(cin, name);
  cout << "Enter the student's level: ";
  getline(cin, level);
  cout << "Enter the student's major: ";
  getline(cin, major);
  cout << "Enter the student's GPA: ";
  getline(cin, buffer);
  while (!validateGPA(buffer)) {
    cout << "Enter a valid GPA: ";
    getline(cin, buffer);
  }
  gpa = stof(buffer);
  while ((gpa < 1.0) || (gpa > 4.0)) {
    cout << "Enter a valid GPA: ";
    getline(cin, buffer);
    while (!validateGPA(buffer)) {
      cout << "Enter a valid GPA: ";
      getline(cin, buffer);
    }
    gpa = stof(buffer);
  }
  Student *newStud = new Student(id, name, level, major, gpa, 0);
  masterStudent->insert(newStud);
  if (!masterFaculty->isEmpty()) {
    cout << "Enter the ID number of the student's advisor: ";
    getline(cin, buffer);
    while (!validateID(buffer)) {
      cout << "Enter a valid ID: ";
      getline(cin, buffer);
    }
    advisor = stoi(buffer);
    // makes the user input a new faculty advisor ID number until it exists in the faculty database
    while (masterFaculty->find(advisor) == NULL) {
      cout << "Enter a valid ID number for the student's advisor: ";
      getline(cin, idString);
      advisor = stoi(idString);
      if (validateID(idString)) {
        advisor = stoi(idString);
      }
    }
    // update advisee list of faculty member
    changeAdvisor(id, advisor, false, false);
    RollbackObject *rollbackStudent = new RollbackObject("insert", "student", newStud, masterFaculty->find(advisor));
    //push a rollback object to the stack here with action as insert, tree type student, Student* as newStud, Faculty* as masterFaculty->find(advisor)
    rollbackStack->push(rollbackStudent);
  }
  else {
    RollbackObject *rollbackStudent = new RollbackObject("insert", "student", newStud, NULL);
    //push a rollback object to the stack here with action as insert, tree type student, Student* as newStud, Faculty* as masterFaculty->find(advisor)
    rollbackStack->push(rollbackStudent);
  }

}

/*
method to delete a student given their ID
returns void
*/
void DatabaseSimulator::deleteStud(int id, bool isRollback) {
  // find the student in the database
  Student *delStud = masterStudent->find(id);
  if (delStud != NULL) {
    Faculty *delFac = masterFaculty->find(delStud->getAdvisor());
    if(!isRollback){
      RollbackObject *rollbackStudent = new RollbackObject("delete", "student", delStud, delFac);
      //push a rollback object to the stack here with action as delete, tree type student, Student* as delStud, Faculty* as delFac
      rollbackStack->push(rollbackStudent);
    }
    if (delFac != NULL) {
      removeAdvisee(id, delFac->getID(), true);
    }

    masterStudent->deleteNode(delStud);
  }
  else {
    cout << "Enter a valid ID number of a student to delete" << endl;
  }
}

/*
method to add a faculty member into the faculty database
returns void
*/
void DatabaseSimulator::addFac() {
  int id = generateId(true);
  string name;
  string level;
  string department;
  int advisee;
  string buffer;
  string idString;
  getline(cin, buffer);
  cout << "Enter the faculty member's name: ";
  getline(cin, name);
  cout << "Enter the faculty member's level: ";
  getline(cin, level);
  cout << "Enter the faculty member's department: ";
  getline(cin, department);
  Faculty *newFac = new Faculty(id, name, level, department);
  masterFaculty->insert(newFac);

  cout << "Enter 'a' to add advisees (type any other key to exit): ";
  cin >> buffer;
  while (buffer == "a") {
    cout << "Enter the ID number of the faculty member's advisee: ";
    getline(cin, idString);
    getline(cin, idString);
    if (validateID(idString)) {
      advisee = stoi(idString);
    }
    else {
      continue;
    }
    // update advisor of student advisee
    changeAdvisor(advisee, newFac->getID(), false, false);
    cout << "Enter 'a' to add new advisee (type any other key to exit): ";
    cin >> buffer;
  }
    //push a rollback object to the stack here with action as insert, tree type faculty, Student* as NULL, Faculty* as newFac
    RollbackObject *rollbackFaculty = new RollbackObject("insert", "faculty", NULL, newFac);
    rollbackStack->push(rollbackFaculty);
    validateStudents(masterStudent->root, id);
}

/*
method to delete a faculty memeber by ID
returns void
*/
void DatabaseSimulator::deleteFac(int id, bool isRollback) {
  bool deletedFac;
  // find the faculty member in the database
  Faculty *delFac = masterFaculty->find(id);
  Faculty *delFacCopy = masterFaculty->find(id);

  if (delFac != NULL) {
    //push a rollback object to the stack here with action as delete, tree type faculty, Student* as NULL, Faculty* as delFac
    if(!isRollback){
      RollbackObject *rollbackFaculty = new RollbackObject("delete", "faculty", NULL, delFacCopy);
      rollbackStack->push(rollbackFaculty);
    }
    // traverse list of advisees
    if (!delFac->m_advisees->isEmpty()) {
      DoubleListNode<int> *current = delFac->m_advisees->getFront();
      while (current != NULL) {
        // set advisor to default value for each advisee
        if (isRollback) {
          changeAdvisor(current->data, id, true, true);
        }
        else {
          changeAdvisor(current->data, id, true, false);
        }
        current = current->next;
      }
    }
    deletedFac = masterFaculty->deleteNode(delFac);
  }
  else {
    cout << "Enter a valid ID number of a faculty member to delete" << endl;
  }
}

/*
method to change a student's advisor given both their IDs
returns void
*/
void DatabaseSimulator::changeAdvisor(int studId, int facId, bool delFac, bool isRollback) {
  int newId;
  string idString;
  string buffer2;
  // check to make sure they both exist in their respective databases
  Student *stud = masterStudent->find(studId);
  if (stud == NULL) {
    cout << "Student does not exist" << endl;
    return;
  }
  // check if the student and faculty are a real advisor/advisee pair
  if ((stud->getAdvisor() != facId) && (stud->getAdvisor() != 0)) {
    cout << "Not a valid pair of advisor and advisee or student already has an advisor" << endl;
    return;
  }
  string buffer;
  if (delFac) {
    if ((masterFaculty->root->left == NULL) && (masterFaculty->root->right == NULL)) {
      stud->setAdvisor(0);
    }
    else {
      cout << "Enter a new advisor for the student " << stud->getName() << ": ";
      if (isRollback) {
        getline(cin, buffer2);
      }
      getline(cin, idString);
      if (validateID(idString)) {
        stud->setAdvisor(0);
        newId = stoi(idString);
        changeAdvisor(studId, newId, false, false);
      }
      else {
        cout << "Invalid ID for the new faculty member" << endl;
      }
    }
  }
  else {
    if (stud->getAdvisor() != 0) {
      cout << "Student already has an advisor!" << endl;
      return;
    }
    Faculty *fac = masterFaculty->find(facId);
    if (fac == NULL) {
      cout << "Faculty member does not exist" << endl;

      return;
    }
    fac->addAdvisee(studId);
    stud->setAdvisor(facId);
  }

}

/*
method to remove an advisee from a faculty member given both their IDs
returns void
*/
void DatabaseSimulator::removeAdvisee(int studId, int facId, bool delStud) {
  int newAdvisor;
  string idString;
  string buffer;
  Faculty *newFac;
  // check to make sure they both exist in their respective databases
  Student *stud = masterStudent->find(studId);
  while (stud == NULL) {
    cout << "Enter a valid student ID: ";
    getline(cin, idString);
    if (validateID(idString)) {
      studId = stoi(idString);
      stud = masterStudent->find(studId);
    }
  }
  Faculty *fac = masterFaculty->find(facId);
  while (fac == NULL) {
    cout << "Enter a valid faculty ID: ";
    getline(cin, idString);
    if (validateID(idString)) {
      facId = stoi(idString);
      fac = masterFaculty->find(facId);
    }
  }
  // check if the student and faculty are a real advisor/advisee pair
  if (stud->getAdvisor() != facId) {
    cout << "Not a valid pair of advisor and advisee" << endl;
    return;
  }
  // remove that student from their advisor's list of advisees
  fac->removeAdvisee(studId);
  // prompt for a new advisor for the student, only applicable outside the deleteStud method
  if (!delStud) {
    cout << "Enter a faculty ID for advisee's new advisor: ";
    getline(cin, idString);
    if (validateID(idString)) {
      newAdvisor = stoi(idString);
      newFac = masterFaculty->find(newAdvisor);
    }
    while (newFac == NULL) {
      cout << "Enter a valid faculty ID: ";
      getline(cin, idString);
      if (validateID(idString)) {
        newAdvisor = stoi(idString);
        newFac = masterFaculty->find(newAdvisor);
      }
    }
    stud->setAdvisor(newAdvisor);
    masterFaculty->find(newAdvisor)->addAdvisee(stud->getID());
  }
  else {
    stud->setAdvisor(0);
  }
}

/*
method to allow the user to undo their most recent action
returns a boolean representing if the action was successfully undone
*/
bool DatabaseSimulator::rollback(){
  if(rollbackStack->isEmpty()){
    cout << "No action to undo" << endl;
    return false;
  }
  if(rollbackStack->peek()->getTreeType() == "student"){
    if(rollbackStack->peek()->getAction() == "insert"){
      deleteStud(rollbackStack->peek()->getStudent()->getID(), true);
      rollbackStack->pop();
    }
    else{
      rollbackStack->peek()->getFaculty()->addAdvisee(rollbackStack->peek()->getStudent()->getID());
      rollbackStack->peek()->getStudent()->setAdvisor(rollbackStack->peek()->getFaculty()->getID());
      masterStudent->insert(rollbackStack->peek()->getStudent());
      rollbackStack->pop();
    }

  }
  else if(rollbackStack->peek()->getTreeType() == "faculty"){
    if(rollbackStack->peek()->getAction() == "insert"){
      deleteFac(rollbackStack->peek()->getFaculty()->getID(), true);
      rollbackStack->pop();
    }
    else{
      DoubleListNode<int> *current = rollbackStack->peek()->getFaculty()->m_advisees->getFront();
      Student *currStud;
      Faculty *currAdvisor;
      while (current != NULL) {
        currStud = masterStudent->find(current->data);
        currAdvisor = masterFaculty->find(currStud->getAdvisor());
        currAdvisor->removeAdvisee(currStud->getID());
        currStud->setAdvisor(rollbackStack->peek()->getFaculty()->getID());
        current = current->next;
      }
      masterFaculty->insert(rollbackStack->peek()->getFaculty());
      rollbackStack->pop();
    }

  }
  return true;
}

/*
method to generate an ID of a student or faculty member randomly
parameter is a boolean representing the type of affiliate to create an ID for
returns an int representing the ID of the faculty or student
*/
int DatabaseSimulator::generateId(bool faculty) {
  srand(time(NULL));
  int id;
  if (faculty) {
    id = (rand() % 1000) + 1001;
    while (masterFaculty->find(id) != NULL) {
      id = (rand() % 1000) + 1;
    }
  }
  else {
    id = (rand() % 1000) + 1;
    while (masterStudent->find(id) != NULL) {
      id = (rand() % 1000) + 1;
    }
  }
  return id;
}

/*
method to check if an ID is numeric
parameter is a string representing the ID to check
returns a boolean representing if the string is numeric or not
*/
bool DatabaseSimulator::validateID(string id) {
  for (int i = 0; i < id.length() - 1; ++i) {
    if (!isdigit(id[i])) {
      cout << "Invalid input" << endl;
      return false;
    }
  }
  return true;
}

/*
method to check if a GPA input is valid
parameter is a string representing the GPA to check
returns a boolean representing if the GPA is valid or not
*/
bool DatabaseSimulator::validateGPA(string gpa) {
  for (int i = 0; i < gpa.length() - 1; ++i) {
    if (!isdigit(gpa[i]) && (gpa[i] != '.')) {
      cout << "Invalid input" << endl;
      return false;
    }
  }
  return true;
}

/*
method to validate the BSTs collected from input files
input is a node representing the starting node of the tree to check referential integrity for
returns a boolean representing if the trees uphold referential integrity
*/
bool DatabaseSimulator::validateBSTs(TreeNode<Student*> *node) {
  if (node == NULL) { // base case
    return true;
  }
  // traverse student tree
  validateBSTs(node->left);
  // check if each student's advisor exists in the faculty bst
  if(masterFaculty->find(node->key->getAdvisor()) == NULL){
    cout << "STUDENT IN ADVISOR DOESN'T EXIST: " << endl;
    masterFaculty->printNodes();
    masterStudent->printNodes();
    node->key->print();
    return false;
  }
  // check if each advisor has that student in their list of advisees
  if(masterFaculty->find(node->key->getAdvisor())->m_advisees->find(node->key->getID()) == -1){
    masterFaculty->printNodes();
    masterStudent->printNodes();
    cout << "STUDENT IN ADVISEE DOESN'T EXIST: " << endl;
    node->key->print();
    return false;
  }
  validateBSTs(node->right);


}


/*
method to check if any students are missing an advisor and assign the given ID as their advisor
parameters are the starting node to traverse the student BST and an int representing the faculty member's ID
returns void
*/
void DatabaseSimulator::validateStudents(TreeNode<Student*> *node, int facId) {
  if (node == NULL) { // base case
    return;
  }
  validateStudents(node->left, facId);
  if(node->key->getAdvisor() == 0){
    node->key->setAdvisor(facId);
    masterFaculty->find(facId)->addAdvisee(node->key->getID());
  }
  validateStudents(node->right, facId);
}
