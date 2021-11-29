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
    Student *studentToAdd; //node of a student tree
    string value; //the content (value) we are to assign to a member variable
    string delimiter = ","; //what separates our member variables in a line
    size_t index; // index the delimiter was found
    int infoCounter = 0;

    while(getline(reader, line)){
      cout << "Inside big while loop and our line is " << line << endl;
      index = 0;
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
        }
        cout << "TOKEN:" << "[" << value << "]" << endl;
        line.erase(0, index + delimiter.length());
        cout << "REST OF THE LINE IS: " << line << endl;

        cout << "line length: " << line.length() << endl;
        infoCounter++;
      }
      studentToAdd = new Student(id, name, level, major, gpa, advisorID);
    }

  }
}

// void FileProcessor::processFacultyFile(string fileInput){
//   fstream reader;
//
//   reader.open(fileInput, ios::in);
//
//   if(reader.is_open()){
//     string line;
//     int id;
//     string name;
//     string level;
//     string department;
//     // TemplateDLL<int> *adviseesList = new TemplateDLL<int>();
//     Faculty *facultyToAdd; //node of a student tree
//     string value; //the content (value) we are to assign to a member variable
//     string delimiter = ","; //what separates our member variables in a line
//     size_t index; // index the delimiter was found
//     int infoCounter; // this should reach 4 and then anything after that will be added to a list
//
//     while(getline(reader, line)){
//       cout << "Inside big while loop and our line is " << line << endl;
//       index = 0;
//       infoCounter = 0;
//       while((index != -1)){
//         infoCounter++;
//         index = line.find(delimiter);
//         cout << index << " is index where delimiter was found" <<endl;
//         value = line.substr(0,index);
//         ltrim(value);
//         if(infoCounter == 0){
//           id = stoi(value);
//         }
//         if(infoCounter == 1){
//           name = value;
//         }
//         if(infoCounter == 2){
//           level = value;
//         }
//         if(infoCounter == 3){
//           department = value;
//         }
//           if(infoCounter == 4){
//             // create faculty member
//             faculty->addAdvisee(stoi(value));
//           }
//           if (infoCounter > 4) {
//             if (isprint((char)value) == 0) {
//               faculty->print()
//               break;
//             }
//             else {
//               faculty->addAdvisee(stoi(value));
//             }
//         }
//         cout << "TOKEN: " << value << endl;
//         line.erase(0, index + delimiter.length());
//         cout << "REST OF THE LINE IS: " << line << endl;
//         cout << "std npos: " << std::string::npos << endl;
//
//       }
//
//     }
//
//   }
// }

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
