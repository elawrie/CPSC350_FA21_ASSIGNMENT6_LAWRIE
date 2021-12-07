# CPSC350_FA21_ASSIGNMENT6_LAWRIE

# CPSC350_FA21_ASSIGNMENT2_REA



1)
Alejandro Rea
2378582
area@chapman.edu
CPSC350-01
Assignment 6

Evelyn Lawrie
2364909
lawrie@chapman.edu
CPSC 350-01
Assignment 6

2)
DatabaseSimulator.cpp
DatabaseSimulator.h
Faculty.cpp
Faculty.h
facultyTable.txt
FileProcessor.cpp
FileProcessor.h
main.cpp
Makefile
RollbackObject.cpp
RollbackObject.h
Student.cpp
Student.h
studentTable.txt
TemplateBST.h
TemplateDLL.h
TemplateStack.h

3)

All student information will be stored in studentTable.txt and all faculty information will be stored in facultyTable.txt. Both of these files start off blank.

IDs are randomly generated for both students and faculty.

For text files, keep the information in comma separated format, with the last item not having a comma.

When a faculty member gets created, it checks if any students needs an advisor and automatically assigns them to the new faculty.

If a student is created before any faculty members exist, their advisor will be set to 0.

4)

https://stackoverflow.com/questions/34170164/destructor-for-binary-search-tree Used for destructor.

https://www.tutorialspoint.com/cplusplus/relational_operators_overloading.htm Used this link to overload an operator.

https://www.cplusplus.com/reference/cctype/isprint/ Used for working with non-printable characters.

5)

Make all
./assignment6.out


1234, Rene German, Instructor, Computer Science, 2364909, 249
1437, josh, ta, cs, 937
4321, Elizabeth Stevens, Assistant Professor, Computer Science, 3243432
4444, Erik Linstead, Assistant Professor, Computer Science, 2378582, 2378459

249, erh, weg, eth, 4.000000, 1234
937, olivia, sophomore, cs, 4.000000, 1437
2364909, Evelyn Lawrie, Sophomore, Computer Science, 4.000000, 1234
2378459, Juan L, Freshman, Computer Science, 3.900000, 4444
2378582, Alex Rea, Sophomore, Computer Science, 4.000000, 4444
3243432, Joe Smith, Junior, Computer Engineering, 3.200000, 4321
