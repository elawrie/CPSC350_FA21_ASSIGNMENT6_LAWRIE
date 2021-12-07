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

// this file defines and implements a binary search tree

#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

// class definition for tree node

template <class T>
class TreeNode {
  public:
    TreeNode(); // default constructor
    TreeNode(T key); // overloaded constructor
    virtual ~TreeNode(); // destructor
    T key; // key of each node to sort on
    TreeNode<T> *left; // node to the left of the current node
    TreeNode<T> *right; // node to the right of the current node

};

// implementation for tree node

// default constructor for tree node class
template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = NULL;
}

// overloaded constructor for tree node class
template <class T>
TreeNode<T>::TreeNode(T k) {
  left = NULL;
  right = NULL;
  key = k;
}

// destructor for the tree node class
template <class T>
TreeNode<T>::~TreeNode() {
  left = NULL;
  right = NULL;
}

// class definition for bst

template <class T>
class BST {
  public:
    BST(); // default constructor
    virtual ~BST(); // destructor
    void deleteTree(TreeNode<T> *node); // method to delete the tree
    void insert(T value); // method to insert a value into the tree
    bool contains(T value); // method to search the tree
    T find(int id); // method to search a tree and return the data at the number key
    bool deleteNode(T k); // method to delete a node from the tree
    bool isEmpty(); // method to check if the tree is empty
    T* getMin(); // method to get the minumum value in the tree
    T* getMax(); // method to get the maximum value in the tree
    TreeNode<T>* getSuccessor(TreeNode<T> *d); // method to get the successor from a node to delete
    void printNodes(); // method to print the nodes
    void recursivePrint(TreeNode<T> *node); // method to recursively print the nodes
    string serializedRecursivePrint(TreeNode<T> *node, string& treeString);
    string serializedPrintNodes(string& treeString);
    TreeNode<T> getRoot(); // returns the root of the tree
    TreeNode<T> *root; // root of the tree
  private:
    //TreeNode<T> *root; // root of the tree
};

// implementation for bst

// default constructor for the bst class
template <class T>
BST<T>::BST() {
  root = NULL;
}

// destructor for the bst class;
template <class T>
BST<T>::~BST() {
  deleteTree(root);
}

/*
method to return the root of the tree
returns a tree node representing the tree's root
*/
template <class T>
TreeNode<T> BST<T>::getRoot() {

  return root;
}

/*
method to delete the tree recursively
parameter is a node to delete
returns void
*/
template <class T>
void BST<T>::deleteTree(TreeNode<T> *node) {
  if (node != NULL) {
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
}

/*
method to recursively print the tree
parameter is a node to print
returns void
*/
template <class T>
void BST<T>::recursivePrint(TreeNode<T> *node) {
  if (node == NULL) { // base case
    return;
  }
  recursivePrint(node->left);
  node->key->print();
  recursivePrint(node->right);
}


/*
method to print the nodes in the tree
returns void
*/
template <class T>
void BST<T>::printNodes() {
  recursivePrint(root); // print entire tree by utilizing the recursivePrint method
}

/*
method to recursively access every node
parameter is a node to print
returns a string of all serialized nodes
*/
template <class T>
string BST<T>::serializedRecursivePrint(TreeNode<T> *node, string& treeString){
  if (node == NULL) { // base case
    return "";
  }
  serializedRecursivePrint(node->left, treeString);
  treeString += node->key->printSerialized();
  serializedRecursivePrint(node->right, treeString);
  return treeString;

}

/*
method to print the nodes in a serialized fashion
returns a string of all the nodes in serialized fashion
*/
template <class T>
string BST<T>::serializedPrintNodes(string& treeString) {
  return serializedRecursivePrint(root, treeString); // print entire tree by utilizing the recursivePrint method
}

/*
method to check if the tree is empty
returns a boolean representing if the tree is empty or not
*/
template <class T>
bool BST<T>::isEmpty() {
  return (root == NULL);
}

/*
method to return the minimum value in the tree
returns a generic type representing the minimum value in the tree
*/
template <class T>
T* BST<T>::getMin() {
  // go all the way to the left
  TreeNode<T> *current = root; // start at the root
  if (root == NULL) { // tree is empty
    return NULL;
  }
  while(current->left != NULL) {
    current = current->left;
  }
  // should now be at the left-most node
  return &(current->key); // or return current, returns a pointer to a tree node
}

/*
method to return the maximum value in the tree
returns a generic type representing the maximum value in the tree
*/
template <class T>
T* BST<T>::getMax() {
  // go all the way to the right
  TreeNode<T> *current = root; // start at the root
  if (root == NULL) { // tree is empty
    return NULL;
  }
  while(current->right != NULL) {
    current = current->right;
  }
  // should now be at the right-most node
  return &(current->key); // or return current, returns a pointer to a tree node
}

/*
method to insert a node in the bst
parameter is a generic type representing the value to insert into the bst
returns void
*/
template <class T>
void BST<T>::insert(T value) {
  TreeNode<T> *node = new TreeNode<T>(value); // create a new tree node to hold the value
  if (isEmpty()) {
    // tree was empty, root should be the new node
    root = node;
  }
  else {
    // tree was not empty
    // go left or right until we hit the insertion point
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    while (true) {
      // make comparisons and update current and parent
      parent = current;
      if (value->getID() < current->key->getID()) {
        // go left
        current = current->left;
        if (current == NULL) {
          // found the insertion point
          parent->left = node;
          break;
        }
      }
      else {
        // go right
        current = current->right;
        if (current == NULL) {
          // found the insertion point
          parent->right = node;
          break;
        }
      }
    }
  }
}

/*
method to search the tree and check if a value exists within it
parameter is a generic type representing the value to find in the tree
returns a boolean representing if that value is in the tree or not
*/
template <class T>
bool BST<T>::contains(T value) {
  if (isEmpty()) {
    return false;
  }
  else {
    // if tree is not empty, look for the value
    TreeNode<T> *current = root;
    while (current->key->getID() != value->getID()) {
      if (value->getID() < current->key->getID()) {
        current = current->left;
      }
      else {
        current = current->right;
      }
      if (current == NULL) {
        return false;
      }
    }
    return true;
  }
}

/*
method to search the tree for a value
parameter is an integer representing the id to find in the tree
returns a generic type pointer representing the value found in the tree
*/
template <class T>
T BST<T>::find(int id) {
  if (isEmpty()) {
    return NULL;
  }
  else {
    // if tree is not empty, look for the value
    TreeNode<T> *current = root;
    while (current->key->getID() != id) {
      if (id < current->key->getID()) {
        current = current->left;
      }
      else {
        current = current->right;
      }
      if (current == NULL) {
        return NULL;
      }
    }
    return current->key;
  }
}

/*
method to delete a node from the tree
parameter is a generic type representing the key to delete
returns boolean to see if the delete was successful or not
*/
template <class T>
bool BST<T>::deleteNode(T k) {
  if (isEmpty()) {
    // nothing to delete
    cout << "Tree is empty, can't delete!" << endl;
    return false;
  }
  if (!contains(k)) {
    // doesn't contain the value we want to delete
    cout << "Value doesn't exist, can't delete!" << endl;
    return false;
  }
  // now established that the key exists in the tree
  // need to make current and parent
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root; // do this since we may be deleting the root
  bool isLeft = true;
  // find the value so that we can set current and parent
  while (current->key->getID() != k->getID()) {
    parent = current; // parent must stay one above current
    if (k->getID() < current->key->getID()) {
      isLeft = true;
      current = current->left;
    }
    else {
      isLeft = false;
      current = current->right;
    }
    if (current == NULL) {
      return false; // value doesn't exist, shouldn't need this since we have search but this handles that if we don't want to search
    }
  }
  // if we make it outside the while loop, we found the node that needs to be deleted
  // check for three cases: node to delete has no children (leaf), one child, or two children
  // check for no children
  if (current->left == NULL && current->right == NULL) {
    if (current == root) {
      root = NULL;
    }
    // check for if node is coming down from the left or right of a parent (if it's a left or right child)
    if (isLeft) {
      parent->left = NULL;
    }
    else {
      parent->right = NULL;
    }
  }
  // check if the node to be deleted has one child
  // determine if that child is a left or right child
  else if (current->right == NULL) {
    // has at least one child (left), not a leaf since we checked for that above
    // node to be deleted has a left child (no right)
    // check three cases: if it's the root, a left child, or a right child
    if (current == root) {
      // if the node we're deleting is the root
      root = current->left;
    }
    else if (isLeft) {
      // if the node we're deleting is a left child
      parent->left = current->left;
    }
    else {
      // if the node we're deleting is right child
      parent->right = current->left;
    }
  }
  else if (current->left == NULL) {
    // has at least one child (right), not a leaf since we checked for that above
    // node to be deleted has a right child (no left)
    if (current == root) {
      // if the node we're deleting is the root
      root = current->right;
    }
    else if (isLeft) {
      // if the node we're deleting is a left child
      parent->left = current->right;
    }
    else {
      // if the node we're deleting is right child
      parent->right = current->right;
    }
  }
  else {
    // node to be deleted has two children
    TreeNode<T> *successor = getSuccessor(current);
    if (current == root) {
      root = successor;
    }
    else if (isLeft) {
      parent->left = successor;
    }
    else {
      parent->right = successor;
    }
    // successor's left child has to go to current's left child
    successor->left = current->left;
  }
  //return true;
}

/*
method to find the successor of the target node
parameter is a tree node of generic type representing the node to delete
returns a tree node representing the successor of the node to delete
*/
template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d) {
  // parameter d represents the node to be deleted
  // implementing successor as the smallest node greater than the node to delete
  TreeNode<T> *sp = d; // successor's parent
  TreeNode<T> *successor = d; // successor
  TreeNode<T> *current = d->right;

  while (current != NULL) {
    // updating pointers until you find the correct successor
    sp = successor;
    successor = current;
    current = current->left;
  }
  // if successor is descendant of a right child, we have to update pointers (would be false if the right child of d doesn't have a left child)
  if (successor != d->right) {
    sp->left = successor->right; // successor right = NULL
    successor->right = d->right; // this happens since successor is taking d's place
    // update the rest of the pointers in the deleteNode method
  }
  return successor;
}


#endif
