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

/* This is the template class for a stack (GenStack). We made a template class because this
should be able to work for any data type. In this assignment we will use it for a char based stack
and an int based stack
*/
#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include "TemplateDLL.h"

template <class T>
class GenStack{
public:
  GenStack();
  ~GenStack();

  //core functions
  void push(T data);
  T pop();

  //aux functions
  T peek(); //AKA top
  bool isEmpty();
  bool isFull();
  T getSize();
  void print(bool link);

private:
  DoubleListNode<T> *top;

  //tracks the size of the stack
  T mSize;

  //stack is linked list based so we need to make a linked list
  TemplateDLL<T> *myList;

};

//default constructor that initializes the stack with the appropriate values
template <class T>
GenStack<T>::GenStack(){
  mSize = 0;
  myList = new TemplateDLL<T>();
  top = myList->front;
}

//default destructor
template <class T>
GenStack<T>::~GenStack(){
  delete myList;
}

/*
* @param T value that represents what value will be pushed to the stack
* This method pushes a value to the top of a the stack
*/
template <class T>
void GenStack<T>::push(T data){
  myList->insertFront(data);
  top = myList->front;
  mSize++;
}

/*
* @return T value that represents what was at the top of the stack
* This method returns the top value of a stack, and removes the top item from the stack
*/
template <class T>
T GenStack<T>::pop(){
  //check if empty
  T temp = top->data;
  if(isEmpty()){
    throw runtime_error("Stack empty can NOT pop!");
  }else{


    //leverage the removefront method from GenLinkedList since we are only adding and removing to the front
    myList->removeFront();
    top = myList->front;
    mSize--;

  }
  return temp;
}

/*
* @return T value that represents what was at the top of the stack
* This method returns the top value of a stack but does not remove the top item of the stack
*/
template <class T>
T GenStack<T>::peek(){

  if(isEmpty()){
    throw runtime_error("Stack empty can NOT peek!");
  }
  return top->data;
}

/*
* @return boolean that represents whether a stack is empty or not
* This method checks if a stack is empty or not
*/
template <class T>
bool GenStack<T>::isEmpty(){
  return (mSize == 0);
}

/*
* @return T value that represents the size of the stack
* This method is used to find the size of a stack
*/
template <class T>
T GenStack<T>::getSize(){
  return mSize;
}

template <class T>
void GenStack<T>::print(bool link){
  myList->printList(link);
}

#endif
