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

}

FileProcessor::~FileProcessor(){

}

void FileProcessor::processStudentFile(string fileInput){
  fstream reader;

  reader.open(fileInput, ios::in);

  if(reader.is_open()){
    string line;
    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisorID;
    Student *studentNode; //node of a student tree
    string value; //the content (value) we are to assign to a member variable
    string delimiter = ","; //what separates our member variables in a line
    size_t index; // index the delimiter was found

    while(getline(reader, line)){
      cout << "Inside big while loop and our line is " << line << endl;
      index = 0;
      while((index != -1)){
        index = line.find(delimiter);
        cout << index << " is index where delimiter was found" <<endl;
        value = line.substr(0,index);
        cout << "TOKEN:" << "[" << value << "]" << endl;
        line.erase(0, index + delimiter.length());
        cout << "REST OF THE LINE IS: " << line << endl;

        cout << "line length: " << line.length() << endl;
      }

    }

  }
}

void FileProcessor::processFacultyFile(string fileInput){
  fstream reader;

  reader.open(fileInput, ios::in);

  if(reader.is_open()){
    string line;
    int id;
    string name;
    string level;
    string department;
    double gpa;
    int advisorID;
    DoubleListNode<Student*> *studentNode; //node of a student tree
    string value; //the content (value) we are to assign to a member variable
    string delimiter = ","; //what separates our member variables in a line
    size_t index; // index the delimiter was found
    int infoCounter; // this should reach 4 and then anything after that will be added to a list

    while(getline(reader, line)){
      cout << "Inside big while loop and our line is " << line << endl;
      index = 0;
      infoCounter = 0;
      while((index != -1)){
        infoCounter++;
        index = line.find(delimiter);
        cout << index << " is index where delimiter was found" <<endl;
        value = line.substr(0,index);
        cout << "TOKEN: " << value << endl;
        line.erase(0, index + delimiter.length());
        cout << "REST OF THE LINE IS: " << line << endl;
        cout << "std npos: " << std::string::npos << endl;
        if(infoCounter > 4){
          //add every item after this point to list of advisees
        }

      }

    }

  }
}

void FileProcessor::ltrim(string &token){

}
