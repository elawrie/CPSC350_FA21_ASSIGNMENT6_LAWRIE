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

// implementation file for the database simulation class

#include "DatabaseSimulator.h"
#include "TemplateDLL.h"
#include <iostream>

using namespace std;

// default constructor
DatabaseSimulator::DatabaseSimulator() {
  rollbackStack = new GenStack<RollbackObject*>();
  m_fp = new FileProcessor();
  masterStudent = new BST<Student*>(); // m_fp->processStudentFile();
  masterFaculty = new BST<Faculty*>(); // m_fp->processFacultyFile();
  masterStudent = m_fp->processStudentFile("studentTable.txt"); // m_fp->processStudentFile();
  masterFaculty = m_fp->processFacultyFile("facultyTable.txt"); // m_fp->processFacultyFile();


  //FIXME DELETE LATER: FOR TESTING
  // Student *stud1 = new Student(2364909, "Evelyn Lawrie", "Sophomore", "Computer Science", 4.0, 1234);
  // Student *stud2 = new Student(2378582, "Alex Rea", "Sophomore", "Computer Science", 4.0, 0);
  // Student *stud3 = new Student(3243432, "Joe Smith", "Junior", "Computer Engineering", 3.2, 4321);
  // masterStudent->insert(stud1);
  // masterStudent->insert(stud2);
  // masterStudent->insert(stud3);
  // Faculty *fac1 = new Faculty(1234, "Rene German", "Instructor", "Computer Science");
  // Faculty *fac2 = new Faculty(4321, "Elizabeth Stevens", "Assistant Professor", "Computer Science");
  // fac1->addAdvisee(2364909);
  // // fac1->addAdvisee(2378582);
  // fac2->addAdvisee(3243432);
  // masterFaculty->insert(fac1);
  // masterFaculty->insert(fac2);
}

// destructor
DatabaseSimulator::~DatabaseSimulator() {
  delete m_fp;
  delete masterFaculty;
  delete masterStudent;
}


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
  cout << "MASTER STUDENT ROOT: ";
  masterStudent->root->key->print();
  cout << endl;
  if (validateBSTs(masterStudent->root) == false) {
    cout << "There is a mismatch of a student/faculty pair." << endl;
    return;
  }
  do {
    cout << endl << "ROLLBACK COUNT: " << rollbackCount << endl;
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
  }
  while (userInput != "14");
  // m_fp->serializeStudentBST();
  // m_fp->serializeFacultyBST();
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
  cout << "BUFFER: " << buffer << endl;
  while (!validateGPA(buffer)) {
    cout << "Enter a valid GPA: ";
    getline(cin, buffer);
  }
  cout << "GOT INITIAL GPA" << endl;
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
  Student *newStud = new Student(id, name, level, major, gpa, 0);
  masterStudent->insert(newStud);
  // update advisee list of faculty member
  changeAdvisor(id, advisor, false, false);
  RollbackObject *rollbackStudent = new RollbackObject("insert", "student", newStud, masterFaculty->find(advisor));
  //push a rollback object to the stack here with action as insert, tree type student, Student* as newStud, Faculty* as masterFaculty->find(advisor)
  rollbackStack->push(rollbackStudent);

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
    removeAdvisee(id, delFac->getID(), true);

    if (masterStudent->deleteNode(delStud) == true) {
      // FIXME: DELETE THIS PRINT OUT STATEMENT
      cout << "Deleted student!" << endl;
    }
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
  cout << "FAC ID: " << newFac->getID() << "." << endl;
  cout << "CONTAINS NEW FAC: " << masterFaculty->contains(newFac) << endl;
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
    cout << "FAC ID: " << newFac->getID() << "." << endl;
    cout << "CONTAINS NEW FAC: " << masterFaculty->contains(newFac) << endl;
    changeAdvisor(advisee, newFac->getID(), false, false);
    cout << "Enter 'a' to add new advisee (type any other key to exit): ";
    cin >> buffer;

    //push a rollback object to the stack here with action as insert, tree type faculty, Student* as NULL, Faculty* as newFac
    RollbackObject *rollbackFaculty = new RollbackObject("insert", "faculty", NULL, newFac);
    rollbackStack->push(rollbackFaculty);

  }
}

/*
method to delete a faculty memeber by ID
returns void
*/
void DatabaseSimulator::deleteFac(int id, bool isRollback) {
  // find the faculty member in the database
  Faculty *delFac = masterFaculty->find(id);
  Faculty *delFacCopy = masterFaculty->find(id);

  if (delFac != NULL) {
    //push a rollback object to the stack here with action as delete, tree type faculty, Student* as NULL, Faculty* as delFacCopy
    if(!isRollback){
      RollbackObject *rollbackFaculty = new RollbackObject("delete", "faculty", NULL, delFacCopy);
      rollbackStack->push(rollbackFaculty);
    }
    // traverse list of advisees
    DoubleListNode<int> *current = delFac->m_advisees->getFront();
    while (current != NULL) {
      // set advisor to default value for each advisee
      // cout << "FACULTY ID " << id <<
      if (isRollback) {
        changeAdvisor(current->data, id, true, true);
      }
      else {
        changeAdvisor(current->data, id, true, false);
      }
      current = current->next;
    }
    if (masterFaculty->deleteNode(delFac) == true) {
      // FIXME: DELETE THIS PRINT OUT STATEMENT
      cout << "Deleted faculty member!" << endl;
    }
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
  cout << "FAC ID: " << facId << "." << endl;
  // check to make sure they both exist in their respective databases
  Student *stud = masterStudent->find(studId);
  cout << "STUD: " << stud << endl;
  // stud->print();
  if (stud == NULL) {
    cout << "Student does not exist" << endl;
    return;
    // cout << "Enter a valid student ID: ";
    // cin >> studId;
    // stud = masterStudent->find(studId);
  }
  // check if the student and faculty are a real advisor/advisee pair
  if ((stud->getAdvisor() != facId) && (stud->getAdvisor() != 0)) {
    cout << "Not a valid pair of advisor and advisee or student already has an advisor" << endl;
    return;
  }
  string buffer;
  if (delFac) {
    cout << "Enter a new advisor for the student " << stud->getName() << ": ";
    if (isRollback) {
      cout << "HERE" << endl;
      getline(cin, buffer2);
      cout << "BUFFER: " << buffer2 << endl;
    }
    getline(cin, idString);
    cout << "ID STRING: " << idString << endl;
    if (validateID(idString)) {
      stud->setAdvisor(0);
      newId = stoi(idString);
      changeAdvisor(studId, newId, false, false);
    }
    else {
      cout << "Invalid ID for the new faculty member" << endl;
    }
  }
  else {
    if (stud->getAdvisor() != 0) {
      cout << "Student already has an advisor!" << endl;
      return;
    }
    Faculty *fac = masterFaculty->find(facId);
    // either issue with find or insert
    cout << "FAC: " << fac << endl;
    //fac->print();
    if (fac == NULL) {
      cout << "Faculty member does not exist" << endl;

      return;
    }
    cout << "CONTAINS NEW FAC in method: " << masterFaculty->contains(fac) << endl;
    cout << "NEW FACULTY: " << endl;
    fac->print();
    masterFaculty->printNodes();
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
  cout << "BEFORE FINDING STUDENT" << endl;
  masterStudent->printNodes();
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

bool DatabaseSimulator::rollback(){

  if(rollbackStack->isEmpty()){
    cout << "No action to undo!" << endl;
    return false;
  }
  // TODO: CHECK IF STACK EMPTY AND RETURN IF TRUE
  cout << "stack is this: " << endl;
  rollbackStack->print(false);
  if(rollbackStack->peek()->getTreeType() == "student"){
    if(rollbackStack->peek()->getAction() == "insert"){
      deleteStud(rollbackStack->peek()->getStudent()->getID(), true);
      cout << "GOT PAST THE DELTESTUD" << endl;
      rollbackStack->pop();
    }
    else{
      rollbackStack->peek()->getStudent()->print();
      rollbackStack->peek()->getFaculty()->addAdvisee(rollbackStack->peek()->getStudent()->getID());
      rollbackStack->peek()->getStudent()->setAdvisor(rollbackStack->peek()->getFaculty()->getID());
      masterStudent->insert(rollbackStack->peek()->getStudent());

      //addStud(rollbackStack->peek()->getStudent()->getID());
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
  cout << "stack is now this: " << endl;
  rollbackStack->print(false);
  return true;
}

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

bool DatabaseSimulator::validateID(string id) {
  for (int i = 0; i < id.length() - 1; ++i) {
    if (!isdigit(id[i])) {
      cout << "Invalid input" << endl;
      return false;
    }
  }
  return true;
}

bool DatabaseSimulator::validateGPA(string gpa) {
  for (int i = 0; i < gpa.length() - 1; ++i) {
    if (!isdigit(gpa[i]) && (gpa[i] != '.')) {
      cout << "Invalid input" << endl;
      return false;
    }
  }
  return true;
}

bool DatabaseSimulator::validateBSTs(TreeNode<Student*> *node) {

  if (node == NULL) { // base case
    return true;
  }
  validateBSTs(node->left);
  if(masterFaculty->find(node->key->getAdvisor()) == NULL){
    return false;
  }
  if(masterFaculty->find(node->key->getAdvisor())->m_advisees->find(node->key->getID()) == -1){
    return false;
  }
  validateBSTs(node->right);

  //return true;
  // traverse student tree
  // check if each student's advisor exists in the faculty bst
  // check if each advisor has that student in their list of advisees
}
