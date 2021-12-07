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

// implements file processor class

#include "FileProcessor.h"

FileProcessor::FileProcessor(){

  m_studentBST = new BST<Student*>();
  m_facultyBST = new BST<Faculty*>();

}

FileProcessor::~FileProcessor(){
  delete m_studentBST;
  delete m_facultyBST;
}


/*
method to read in the information of the text file containing student information
returns a BST that has all of the students information
*/
BST<Student*>* FileProcessor::processStudentFile(string fileInput){
  fstream reader;

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
      index = 0;
      infoCounter = 0;
      studentToAdd = NULL;
      while((index != -1)){
        index = line.find(delimiter);
        value = line.substr(0,index);
        ltrim(value);
        // if(!validateID(value)){
        //   getline(reader, line);
        //   if(reader.eof()){
        //     cout << "end of file" << endl;
        //     return m_studentBST;
        //   }
        //   cout << "VALUE: " << value << endl;
        //   cout << "File contains bad input" << endl;
        //   exit(0);
        // }
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
        }
        line.erase(0, index + delimiter.length());
        infoCounter++;
      }

    }


  }

  return m_studentBST;
}


/*
method to read in the information of the text file containing faculty information
returns a BST that has the information of faculty members
*/
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
      index = 0;
      infoCounter = 0;
      facultyToAdd = NULL;
      while((index != -1)){
        index = line.find(delimiter);
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

          if(value.length() > 0){
            facultyToAdd->addAdvisee(stoi(value));
          }

        }
        line.erase(0, index + delimiter.length());
        infoCounter++;

      }

      m_facultyBST->insert(facultyToAdd);

    }

  }

  return m_facultyBST;
}

/*
method to write all of the information of a BST in serailized format to masterStudent file
returns void
*/
void FileProcessor::serializeStudentBST(string outputFileStudent, BST<Student*>* studentBST){
  string serializedStudentTree = "";
  fstream writer;
  writer.open(outputFileStudent, ios::out);
  writer << studentBST->serializedPrintNodes(serializedStudentTree);
  writer.close();


}

/*
method to write all of the information of a BST in serailized format to masterFaculty file
returns void
*/
void FileProcessor::serializeFacultyBST(string outputFileFaculty, BST<Faculty*>* facultyBST){
  string serializedFacultyTree = "";
  fstream writer;
  writer.open(outputFileFaculty, ios::out);
  writer << facultyBST->serializedPrintNodes(serializedFacultyTree);
  writer.close();

}

/*
method to remove extra whitespace before our token value
returns void
*/
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


/*
method to check if the ID value of a student or advisor is a valid value
returns boolean indicating if the string contains a non printable character
*/
bool FileProcessor::validateID(string id) {
  for (int i = 0; i < id.length(); ++i) {
    if (!isprint(id[i])) {
      return false;
    }
  }
  return true;
}
