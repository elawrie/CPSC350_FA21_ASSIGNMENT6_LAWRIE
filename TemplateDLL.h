/*

Alejandro Rea
2378582
area@chapman.edu
CPSC350-01
Assignment 6

*/


/* This is the template class for a node for a doubly linked list. It is a template class
because the node should be able to have data of any type.
*/
#ifndef GEN_DOUBLE_LINKEDLIST_H
#define GEN_DOUBLE_LINKEDLIST_H

#include <iostream>
#include <exception>

using namespace std;

//node class for a doubly linked list
template <class T>
class DoubleListNode{
public:
  DoubleListNode();
  DoubleListNode(T data);
  ~DoubleListNode();
  DoubleListNode<T> *next; //points to next node
  DoubleListNode<T> *prev; //points to previous node
  T data;
};

//default constructor
template <class T>
DoubleListNode<T>::DoubleListNode(){}

//overloaded constructor that takes in a T value to assign to the data of a new node
template <class T>
DoubleListNode<T>::DoubleListNode(T d){
  data = d;
  next = NULL;
  prev = NULL;
}

//default destructor
template <class T>
DoubleListNode<T>::~DoubleListNode(){
  prev = NULL;
  next = NULL;
}

/* This is the template class for a doubly linked list. I made a template class because this
should be able to work for any data type. This assignment calls for the use of a doubly linked list
that stores ints and chars
*/
template <class T>
class TemplateDLL{
public:
  DoubleListNode<T> *front;
  DoubleListNode<T> *back;
  int size;
public:
  TemplateDLL();
  virtual ~TemplateDLL();

  //core methods
  void insertFront(T d);
  void insertBack(T d);
  void insertAfter(T key, T d);
  T removeFront();
  T removeBack();
  T removeNode(T value);

  //aux methods
  int find(T value);
  bool isEmpty();
  bool printLink;
  int getSize();
  void printList(bool PrintLink);
  void printReverseList(bool PrintLink);
  string serializedPrint();
  void sort();
  DoubleListNode<T>* getFront();
};

//default constructor
template <class T>
TemplateDLL<T>::TemplateDLL(){
  front = NULL;
  back = NULL;
  size = 0;
}

//default destructor
template <class T>
TemplateDLL<T>::~TemplateDLL(){
  //keeps track of the next node
  DoubleListNode<T> *nextNode = NULL;
  //keeps track of the current node
  DoubleListNode<T> *currNode = front;
  //traveses until the list in empty
  while(currNode != NULL){
    nextNode = currNode->next;
    delete currNode;
    currNode = nextNode;

  }
}

/*
getFront method returns the node at the front of the list
returns a double list node pointer of a generic type
*/
template <class T>
DoubleListNode<T>* TemplateDLL<T>::getFront() {
  return front;
}

/*
* @param T value that represents what value will be inserted as a new front node of the list
* This method inserts a node at the front of the list with a specified value d
*/
template <class T>
void TemplateDLL<T>::insertFront(T d){
  DoubleListNode<T> *node = new DoubleListNode<T>(d);
  if(isEmpty()){
    back = node;
  }else{
    //not empty ListNode
    node->next = front; // updating the pointers of the old front
    front->prev = node;
  }
  front = node; //assigns the new node to be the front
  ++size;
}

/*
* @param d that represents what value will be inserted as a new back node of the list
* This method inserts a node at the back of the list with a specified value d
*/
template <class T>
void TemplateDLL<T>::insertBack(T d){
  DoubleListNode<T> *node = new DoubleListNode<T>(d);
  if(isEmpty()){
    front = node;
  }
  else{
    //not empty
    node->prev = back; // update pointers of the old back
    back->next = node;
  }
  back = node; //assign the new node to be the back
  ++size; //increase the size of the list
}

/*
* @param d that represents what value will be inserted as a new back node of the list
* This method inserts a node at the back of the list with a specified value d
*/
template <class T>
void TemplateDLL<T>::insertAfter(T key, T d){
  DoubleListNode<T> *node = new DoubleListNode<T>(d);
  DoubleListNode<T> *currNode = front;

  while(currNode->data != key){
    currNode = currNode->next;
    if(currNode == NULL){
      break;
    }
  }

  if(isEmpty()){
    front = node;
    back = node;
  }
  else if(currNode == back){
    insertBack(node->data);
  }
  else{
    DoubleListNode<T> *sucNode = currNode->next;
    node->next = sucNode;
    node->prev = currNode;
    currNode->next = node;
    sucNode->prev = node;
  }

  size++;
}

/*
* @return T value that represents data was at the front before being removed
* This method removes a node that was at the front of the list
*/
template <class T>
T TemplateDLL<T>::removeFront(){
  if(isEmpty()){ //checking if the list was empty
    throw runtime_error("Empty list so you can't remove!");
  }
  DoubleListNode<T> *temp = front; // temporary node to track front



  if(front->next == NULL){ //happens to be first and last
    back = NULL;
  }
  else{
    //we have more than 1 ListNode, list size is > 1
    front->next->prev = NULL; // updating pointer of second item in list
  }
  front = front->next; // updating the front to be the successor of original front
  T tempData = temp->data; //tracks the data of original front because this is what will be returned
  temp->next = NULL; //nullifies the next pointer so we can garbage collect
  --size;
  delete temp;
  return tempData;

}

/*
* @return T value that represents data was at the back before being removed
* This method removes a node that was at the back of the list
*/
template <class T>
T TemplateDLL<T>::removeBack(){
  if(isEmpty()){
    throw runtime_error("The list is empty!");
  }

  DoubleListNode<T> *temp = back;

  if(back->prev == NULL){ //happens to be first and last
    back = NULL;
  }
  else{
    back->prev->next = NULL; // nullifying the successor of term before back
  }
  back = back->prev; // updating the back to be the predecessor of original back
  T tempData = temp->data; //tracks the data of original back because this is what will be returned
  temp->prev = NULL; //nullifies the prev pointer so we can garbage collect
  --size;
  delete temp;

  return tempData;
}

/*
* @param T value that is the desired key
* @return T value that represents position of found item
* This method finds a node given a specified key
*/
template <class T>
int TemplateDLL<T>::find(T value){
  int pos = -1;
  DoubleListNode<T> *curr = front; //to keep track of where we are in the list

  //while loop to traverse the whole list
  while(curr != NULL){
    ++pos; //increase our index by one every iteration
    if(curr->data == value){//condition where the node's data matches the key
      break;
    }
    curr = curr->next;//move on to next node in the list
  }
  if(curr == NULL){ // case where the item was never found
    pos = -1;
  }
  return pos;
}

/*
* @param T value that is the desired key to remove
* @return T value that represents position of found item
* This method finds a node given a specified key
*/
template <class T>
T TemplateDLL<T>::removeNode(T value){
  if(isEmpty()){
    throw runtime_error("List is empty, can not remove");
  }
  DoubleListNode<T> *curr = front; //curr node to keep track of location in list

  while(curr != NULL){
    //++pos; //increase our index by one every iteration
    if(curr->data == value){//condition where the node's data matches the key
      break;
    }
    curr = curr->next;//move on to next node in the list
  }

  if(curr == NULL){
    throw runtime_error("did not find value");
  }
  //we found the node, and now curr is in the correct position
  if(curr != front && curr != back){
    //case where the found node is not the front or back
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  if(curr == front){ //case where desired node is the front
    return removeFront();
    // front = curr->next;
    // front->prev = NULL;
  }
  if(curr == back){ //case where desired node is the back
    return removeBack();
    // back = curr->prev;
    // back->next = NULL;
  }
  curr->next = NULL; //null out the prev and next pointers of node we will remove
  curr->prev = NULL;

  T temp = curr->data;
  delete curr;
  --size;
  return temp;

}

/*
* @return T value that represents list size
* This method returns the size of the list
*/
template <class T>
int TemplateDLL<T>::getSize(){
  return size;
}

/*
* @return bool that indicates if list is full or not
* This method returns if the list is empty or not
*/
template <class T>
bool TemplateDLL<T>::isEmpty(){
  return (size==0);
}

/*
* This method will sort the TemplateDLL in ascending order
*/
template <class T>
void TemplateDLL<T>::sort(){
  bool sorted = false;
  DoubleListNode<T> *curr = front;
  while(!sorted){
    sorted = true;
    curr = front;
    while(curr->next != NULL){
      if(curr->next->data < curr->data){
        sorted = false;
        T tempData = curr->data;
        curr->data = curr->next->data;
        curr->next->data = tempData;
      }
      curr = curr->next;
    }
  }
}


/*
* @param bool printlink to see if we print the linkage of nodes
* This method prints out the nodes and their values of an entire list
*/
template <class T>
void TemplateDLL<T>::printList(bool printLink){
    DoubleListNode<T> *curr = front;
    while(curr != 0){

      if(curr == front){
        cout << "{FRONT}: ";
      }
      else if(curr == back){
        cout << "{REAR}: ";
      }
      if(printLink){
        cout << "[ PREV: "<< curr->prev << " || " << curr->data << " || NEXT: "<< curr->next << " ] ";
      }
      else{
        cout << "[ " << curr->data << " ] ";
      }
      curr = curr->next;
      if(curr != 0){
        cout << " ==> ";
      }
    }
    cout << endl;
}

template <class T>
void TemplateDLL<T>::printReverseList(bool printLink){
    DoubleListNode<T> *curr = back;
    while(curr != 0){

      if(curr == back){
        cout << "{FRONT}: ";
      }
      else if(curr == front){
        cout << "{REAR}: ";
      }
      if(printLink){
        cout << "[ PREV: "<< curr->next << " || " << curr->data << " || NEXT: "<< curr->prev << " ] ";
      }
      else{
        cout << "[ " << curr->data << " ] ";
      }
      curr = curr->prev;
      if(curr != 0){
        cout << " ==> ";
      }
    }
    cout << endl;
}

template <class T>
string TemplateDLL<T>::serializedPrint(){
  string serializedList = "";
  DoubleListNode<T> *curr = front;
  while(curr != NULL){
    if(curr->next == NULL){
      serializedList += to_string(curr->data);
    }else{
      serializedList += to_string(curr->data) + ", ";
    }
    curr = curr->next;
  }
  return serializedList;
}



#endif
