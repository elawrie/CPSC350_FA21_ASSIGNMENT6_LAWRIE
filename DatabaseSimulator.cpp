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
  m_fp = new FileProcessor();
  masterStudent = new BST<Student*>();
  masterFaculty = new BST<Faculty*>();
  // FIXME DELETE LATER: FOR TESTING
  Student *stud1 = new Student(2364909, "Evelyn Lawrie", "Sophomore", "Computer Science", 4.0, 1234);
  Student *stud2 = new Student(2378582, "Alex Rea", "Sophomore", "Computer Science", 4.0, 1234);
  Student *stud3 = new Student(3243432, "Joe Smith", "Junior", "Computer Engineering", 3.2, 4321);
  masterStudent->insert(stud1);
  masterStudent->insert(stud2);
  masterStudent->insert(stud3);
  Faculty *fac1 = new Faculty(1234, "Rene German", "Instructor", "Computer Science");
  Faculty *fac2 = new Faculty(4321, "Elizabeth Stevens", "Assistant Professor", "Computer Science");
  fac1->addAdvisee(2364909);
  fac1->addAdvisee(2378582);
  fac2->addAdvisee(3243432);
  masterFaculty->insert(fac1);
  masterFaculty->insert(fac2);
}

// destructor
DatabaseSimulator::~DatabaseSimulator() {
  delete m_fp;
  delete masterFaculty;
  delete masterStudent;
}

// void DatabaseSimulator::populateDatabases() {
//   // check if student file exists
//   if (m_fp->getStudDatabase()->getRoot() != NULL) {
//     masterStudent = m_fp->getStudDatabase();
//   }
//   // check if faculty file exists
//   if (m_fp->getFacDatabase()->getRoot() != NULL) {
//     masterFaculty = m_fp->getFacDatabase();
//   }
// }

/*
method to display the list of menu options
returns void
*/
void DatabaseSimulator::displayMenu() {
  cout << "Press '1' to print all students" << endl;
  cout << "Press '2' to print all faculty" << endl;
  cout << "Press '3' to print a specific student" << endl;
  cout << "Press '4' to print a specific faculty member" << endl;
  cout << "Press '5' to print a student's advisor" << endl;
  cout << "Press '6' to print a faculty members's advisees" << endl;
  cout << "Press '7' to add a new student" << endl;
  cout << "Press '8' to delete a student" << endl;
  cout << "Press '9' to add a new faculty member" << endl;
  cout << "Press '10' to delete a faculty member" << endl;
  cout << "Press '11' to change a student's advisor" << endl;
  cout << "Press '12' to remove a faculty member's advisee" << endl;
  cout << "Press '13' to rollback" << endl;
  cout << "Press '14' to exit" << endl;
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
    // FIXME: SHOULD WE CHECK IF A FACULTY IS IN THE OTHER DATABASE BEFORE SETTING A STUDENT'S INITIAL ADVISOR IN FILEPROCESSOR?
    // SHOULD I CHECK HERE IF THE ADVISOR EXISTS?
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
      // FIXME: SAME HERE, SHOULD WE CHECK IF EACH ADVISEE EXISTS BEFORE PRINTING OR HAS THIS ALREADY BEEN DONE?
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
  int id;
  string name;
  string level;
  string major;
  double gpa;
  int advisor;
  string buffer;
  cout << "Enter the student's ID number: ";
  cin >> id;
  cout << "Enter the student's name: ";
  cin >> name;
  // in case they input a first and last name
  cin >> buffer;
  name = name + " " + buffer;
  cout << "Enter the student's level: ";
  cin >> level;
  cout << "Enter the student's major: ";
  cin >> major;
  cout << "Enter the student's gpa: ";
  cin >> gpa;
  cout << "Enter the ID number of the student's advisor: ";
  cin >> advisor;
  // makes the user input a new faculty advisor ID number until it exists in the faculty database
  while (masterFaculty->find(advisor) == NULL) {
    cout << "Enter a valid ID number for the student's advisor: ";
    cin >> advisor;
  }
  Student *newStud = new Student(id, name, level, major, gpa, advisor);
  // update advisee list of faculty member
  Faculty *changedFac = masterFaculty->find(advisor);
  changedFac->addAdvisee(id);
  masterStudent->insert(newStud);
}

/*
method to delete a student given their ID
returns void
*/
void DatabaseSimulator::deleteStud(int id) {
  // find the student in the database
  Student *delStud = masterStudent->find(id);
  if (delStud != NULL) {
    Faculty *delFac = masterFaculty->find(delStud->getAdvisor());
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
  int id;
  string name;
  string level;
  string department;
  int advisee;
  string buffer;
  cout << "Enter the faculty member's ID number: ";
  cin >> id;
  cout << "Enter the faculty member's name: ";
  cin >> name;
  // in case they input a first and last name
  cin >> buffer;
  name = name + " " + buffer;
  cout << "Enter the faculty member's level: ";
  cin >> level;
  cin >> buffer;
  level = level + " " + buffer;
  cout << "Enter the faculty member's department: ";
  cin >> department;
  cin >> buffer;
  department = department + " " + buffer;
  Faculty *newFac = new Faculty(id, name, level, department);
  masterFaculty->insert(newFac);
  cout << "Enter 'a' to add advisees: ";
  cin >> buffer;
  while (buffer == "a") {
    cout << "Enter the ID number of the faculty member's advisee: ";
    cin >> advisee;
    // update advisor of student advisee
    cout << "FAC ID: " << newFac->getID() << endl;
    cout << "CONTAINS NEW FAC: " << masterFaculty->contains(newFac) << endl;
    changeAdvisor(advisee, newFac->getID(), false);
    cout << "Enter 'a' to add new advisee: ";
    cin >> buffer;
  }
}

/*
method to delete a faculty memeber by ID
returns void
*/
void DatabaseSimulator::deleteFac(int id) {
  // find the faculty member in the database
  Faculty *delFac = masterFaculty->find(id);
  if (delFac != NULL) {
    // traverse list of advisees
    DoubleListNode<int> *current = delFac->m_advisees->getFront();
    while (current != NULL) {
      // set advisor to default value for each advisee
      changeAdvisor(current->data, id, true);
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
void DatabaseSimulator::changeAdvisor(int studId, int facId, bool delFac) {
  // check to make sure they both exist in their respective databases
  Student *stud = masterStudent->find(studId);
  while (stud == NULL) {
    cout << "Enter a valid student ID: ";
    cin >> studId;
    stud = masterStudent->find(studId);
  }
  if (delFac) {
    stud->setAdvisor(0);
    // EITHER SET ADVISOR TO 0 OR PROMPT FOR NEW ADVISOR
  }
  else {
    Faculty *fac = masterFaculty->find(facId);
    while (fac == NULL) {
      cout << "Enter a valid faculty ID: ";
      cin >> facId;
      fac = masterFaculty->find(facId);
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
  // check to make sure they both exist in their respective databases
  Student *stud = masterStudent->find(studId);
  while (stud == NULL) {
    cout << "Enter a valid student ID: ";
    cin >> studId;
    stud = masterStudent->find(studId);
  }
  Faculty *fac = masterFaculty->find(facId);
  while (fac == NULL) {
    cout << "Enter a valid faculty ID: ";
    cin >> facId;
    fac = masterFaculty->find(facId);
  }
  // remove that student from their advisor's list of advisees
  fac->removeAdvisee(studId);
  // prompt for a new advisor for the student, only applicable outside the deleteStud method
  if (!delStud) {
    cout << "Enter a faculty ID for advisee's new advisor: ";
    cin >> newAdvisor;
    Faculty *newFac = masterFaculty->find(newAdvisor);
    while (newFac == NULL) {
      cout << "Enter a valid faculty ID: ";
      cin >> newAdvisor;
      fac = masterFaculty->find(newAdvisor);
    }
    stud->setAdvisor(newAdvisor);
  }
  else {
    stud->setAdvisor(0);
  }
}
