#ifndef AVLTREE
#define AVLTREE

#include <iostream>
using namespace std;
#include <stack>

#include "Node.h"

template <class T>
class AVLTree {
 public:
  // Constructor and Destructor
  AVLTree();
  ~AVLTree();

  // Inserts a new node in the correct location
  bool Insert(double key, T value);

  // recursive insert
  Node<T>* InsertHelper(Node<T>* root, int key, T value);

  // creates a new node
  Node<T>* newNode(int key, T data);

  // Removes the node with a key matching the key being passed in
  bool Remove(double key);

  // Finds a node which matches the key being passed in and returns it's
  // data
  T Find(double key);

  // Returns the height of a node in the tree
  int GetHeight(Node<T>* root);

  // Returns the balance factor of a node
  int getBalanceFactor(Node<T>* n);

  // Conducts left rotation
  Node<T>* LeftRotation(Node<T>* previous);

  // Conducts right rotation
  Node<T>* RightRotation(Node<T>* previous);

  // delete all the nodes in the tree
  void emptyTree(Node<T>* node);

  void printCall();
  void print(Node<T>* ptr);

 private:
  Node<T>* root;
};
#include "AVLTree.cpp"
#endif  // AVLTree