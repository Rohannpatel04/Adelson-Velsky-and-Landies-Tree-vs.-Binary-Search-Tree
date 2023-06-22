#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <iostream>
using namespace std;

#include "Node.h"

template <class T>
class BinarySearchTree {
 public:
  // Constructor and Destructor
  BinarySearchTree();
  ~BinarySearchTree();

  // Inserts a new node in the correct location
  bool Insert(double key, T value);

  // Removes the node with a key matching the key being passed in
  bool Remove(double key);

  // Finds a node which matches the key being passed in
  T Find(double key);

  // delete all the nodes in the tree
  void emptyTree(Node<T>* node);

  void printCall();
  void print(Node<T>* ptr);

 private:
  Node<T>* root;
};

#include "BinarySearchTree.cpp"
#endif  // BINARYSEARCHTREE