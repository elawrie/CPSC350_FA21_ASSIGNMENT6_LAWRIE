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

#include "FileProcessor.h"

FileProcessor::FileProcessor(){

  m_studentBST = new BST<Student*>();
  m_facultyBST = new BST<Faculty*>();

}

FileProcessor::~FileProcessor(){

}

BST<Student*>* FileProcessor::processStudentFile(string fileInput){
  fstream reader;

  //testing the writing stuff
  string serializedTree = "";

  reader.open(fileInput, ios::in);

  if(reader.is_open()){
    string line;
    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisorID;
    string value; //the content (value) we are to assign to a member variable
    string delimiter = ","; //what separates our member variables in a line
    size_t index; // index the delimiter was found
    int infoCounter;
    Student *studentToAdd;


    while(getline(reader, line)){
      cout << "Inside big while loop and our line is " << line << endl;
      index = 0;
      infoCounter = 0;
      studentToAdd = NULL;
      while((index != -1)){
        index = line.find(delimiter);
        cout << index << " is index where delimiter was found" <<endl;
        value = line.substr(0,index);
        ltrim(value);
        if(infoCounter == 0){
          id = stoi(value);
        }
        if(infoCounter == 1){
          name = value;
        }
        if(infoCounter == 2){
          level = value;
        }
        if(infoCounter == 3){
          major = value;
        }
        if(infoCounter == 4){
          gpa = stod(value);
        }
        if(infoCounter == 5){
          advisorID = stoi(value);
          studentToAdd = new Student(id, name, level, major, gpa, advisorID);
          m_studentBST->insert(studentToAdd);
          //studentToAdd->print();
          cout << "IN infocounter equals 5" << endl;
        }
        cout << "TOKEN:" << "[" << value << "]" << endl;
        line.erase(0, index + delimiter.length());
        cout << "REST OF THE LINE IS:" << line << endl;

        cout << "line length: " << line.length() << endl;
        infoCounter++;
      }

    }


  }

  cout << "BEFORE PRINTING STUDENT BST" << endl;
  cout << m_studentBST->serializedPrintNodes(serializedTree);
  cout << "AFTER PRINTING STUDENT BST" << endl;
  return m_studentBST;
}

BST<Faculty*>* FileProcessor::processFacultyFile(string fileInput){
  fstream reader;

  //testing the writing stuff
  string serializedTree = "";

  reader.open(fileInput, ios::in);

  if(reader.is_open()){
    string line;
    int id;
    string name;
    string level;
    string department;
    string value; //the content (value) we are to assign to a member variable
    string delimiter = ","; //what separates our member variables in a line
    size_t index; // index the delimiter was found
    int infoCounter; // this should reach 4 and then anything after that will be added to a list
    Faculty *facultyToAdd; //node of a student tree

    while(getline(reader, line)){
      cout << "Inside big while loop and our line is " << line << endl;
      index = 0;
      infoCounter = 0;
      facultyToAdd = NULL;
      while((index != -1)){
        index = line.find(delimiter);
        cout << index << " is index where delimiter was found" <<endl;
        value = line.substr(0,index);
        ltrim(value);
        if(infoCounter == 0){
          id = stoi(value);
        }
        if(infoCounter == 1){
          name = value;
        }
        if(infoCounter == 2){
          level = value;
        }
        if(infoCounter == 3){
          department = value;
        }
        if(infoCounter == 4){
          facultyToAdd = new Faculty(id, name, level, department);
        }
        if(infoCounter >= 4){
          if(!validateID(value)){
            break;
          }
          facultyToAdd->addAdvisee(stoi(value));
          // if(line.length() < 4){
          //   facultyToAdd->addAdvisee(stoi(value));
          //   cout << "THIS IS USING THE PRINT SERIALIZED METHOD: " << facultyToAdd->printSerialized();
          //   //facultyToAdd->m_advisees->printList(false);
          //   cout << endl;
          //   m_facultyBST->insert(facultyToAdd);
          //   //facultyToAdd->print();
          //   break;
          // }
          // else{
          //   cout << "ADDING TO ADVISEES LIST" << endl;
          // }

        }
        cout << "TOKEN:" << value << endl;
        line.erase(0, index + delimiter.length());
        cout << "REST OF THE LINE IS:" << line << endl;
        cout << "LENGTH OF THE REST OF THE LINE: " << line.length() << endl;
        infoCounter++;

      }

      m_facultyBST->insert(facultyToAdd);

    }

  }

  cout << "BEFORE PRINTING FACULTY BST" << endl;
  cout << m_facultyBST->serializedPrintNodes(serializedTree);
  cout << "AFTER PRINTING FACULTY BST" << endl;

  return m_facultyBST;
}

void FileProcessor::serializeStudentBST(string outputFileStudent, BST<Student*>* studentBST){
  string serializedStudentTree = "";
  fstream writer;
  writer.open(outputFileStudent, ios::out);
  writer << studentBST->serializedPrintNodes(serializedStudentTree);
  writer.close();


}

void FileProcessor::serializeFacultyBST(string outputFileFaculty, BST<Faculty*>* facultyBST){
  string serializedFacultyTree = "";
  fstream writer;
  writer.open(outputFileFaculty, ios::out);
  writer << facultyBST->serializedPrintNodes(serializedFacultyTree);
  writer.close();

}

void FileProcessor::ltrim(string &token){
  bool characterFound = false;
  while(characterFound == false){
    if(token[0] != ' '){
      characterFound = true;
    }
    else{
      token.erase(0, 1);
    }
  }
}

void FileProcessor::rtrim(string &token){
  bool characterFound = false;
  for(int i = token.size() - 1; characterFound == true; i--){
    if(token[i] != ' '){
      characterFound = true;
    }else{
      token.erase(i-1,1);
    }
  }
}

bool FileProcessor::validateID(string id) {
  for (int i = 0; i < id.length() - 1; ++i) {
    if (!isprint(id[i])) {
      return false;
    }
  }
  return true;
}

// every time u insert store a delete
// every time u delete store an insert
//
// pointer to a student
// pointer to a faculty
