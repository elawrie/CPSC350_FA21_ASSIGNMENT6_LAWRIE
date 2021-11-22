// with template classes, you can put the class definition and implementation all in the same file

#ifndef BST_H
#define BST_H
#include <iostream>

using namespace std;

// class definition for tree node
template <class T>
class TreeNode {
  public:
    TreeNode();
    TreeNode(T key); // key is what we sort on (for this tree, the key is the value)
    virtual ~TreeNode(); // if you inherit it, you can override the implementation of the destructor
    T key;
    TreeNode<T> *left; // need the brackets with T for template classes
    TreeNode<T> *right;

};

// implementation for tree node
template <class T>
TreeNode<T>::TreeNode() {
  left = NULL;
  right = NULL;
  key = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T k) {
  left = NULL;
  right = NULL;
  key = k;
}

template <class T>
TreeNode<T>::~TreeNode {
  left = NULL;
  right = NULL;
}

// class definition for bst
template <class T>
class BST {
  public:
    BST();
    virtual ~BST();
    void insert(T value);
    bool contains(T value); // search
    bool deleteNode(T k);
    bool isEmpty()
    T* getMin();
    T* getMax();
    TreeNode<T>* getSuccessor(TreeNode<T> *d); // d represents the node we're going to delete
    void printNodes();
    void recursivePrint(TreeNode<T> *node);
  private:
    TreeNode<T> *root; // only need to know the root of the tree
};

// implementation for bst
template <class T>
BST<T>::BST() {
  root = NULL;
}

template <class T>
BST<T>::~BST() {
  // build character and do research
}

template <class T>
void BST<T>::recursivePrint(TreeNode<T> *node) {
  if (node == NULL) { // base case
    return;
  }
  // this is an preorder traversal (postorder has the print after the function calls and inorder has it in between the left and right calls)
  // this prints all the way to the left and then all the way to the right
  // think of the activation records on the stack every time you make the call
  // once the left most node is null, it returns and pops off all the left calls and then looks at all the right calls and does the same for right
  cout << node->key << endl;
  recursivePrint(node->left);
  recursivePrint(node->right);
}

template <class T>
void BST<T>::printNodes() {
  recursivePrint(root); // print entire tree by utilizing the recursivePrint method
}

template <class T>
bool BST<T>::isEmpty() {
  return (root == NULL);
}

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

// ALWAYS INSERT AT A LEAF
template <class T>
void BST<T>::insert(T value) {
  TreeNode<T> *node = new TreeNode<T>(value); // create a new tree node to hold the value, key is value in our example
  if (isEmpty()) {
    // tree was empty, root should be the new node
    root = node;
  }
  else {
    // tree was not empty
    // go left or right until we hit the insertion point
    TreeNode<T> *current = root;
    TreeNode<T> *parent = NULL;
    while (true) { // or while current != NULL or whatever
      // make comparisons and update current and parent
      parent = current;
      if (value < current->key) {
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

// easy to modify if you want it to return something else other than a boolean
template <class T>
bool BST<T>::contains(T value) {
  if (isEmpty()) {
    return false;
  }
  else {
    // if tree is not empty, look for the value
    // keep track of where we are
    TreeNode<T> *current = root;
    while (current->key != value) {
      if (value < current->key) {
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

// return bool to see if the delete was successful or not
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
  // we've now established that the key exists in the tree
  // need to make current and parent
  TreeNode<T> *current = root;
  TreeNode<T> *parent = root; // do this since we may be deleting the root
  bool isLeft = true;
  // find the value so that we can set current and parent
  while (current ->key != k) {
    parent = current; // parent must stay one above current
    if (k < current->key) {
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
      root == NULL;
    }
    // check for if node is coming down from the left or right of a parent (if it's a left or right child)
    if (isLeft) {
      parent->left = NULL
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
}

template <class T>
TreeNode<T>* BST::getSuccessor(TreeNode<T> *d) {
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
