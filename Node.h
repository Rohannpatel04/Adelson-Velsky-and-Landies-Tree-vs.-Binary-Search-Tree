#ifndef NODE
#define NODE

using namespace std;
#include <iostream>

template <class T>
class Node {
 public:
  // Constructor and Destructor
  Node();
  Node(T data, int count, int h, Node<T> *leftPtr, Node<T> *rightPtr);
  ~Node();

  // Getters:

  // returns the data of the node
  T getNodeData() const;

  // returns the left child node
  Node<T> *getNodeLeft() const;

  // returns the right child node
  Node<T> *getNodeRight() const;

  // returns the the key of the node
  int getNodeKey() const;

  // get the couter
  int getCounter() const;

  // gets the height of a node
  int getNodeHeight() const;

  // Setters:

  // set count
  bool setCounter(int count);

  // Set the key of the node
  bool setNodeKey(double k);

  // Set the node data
  bool setNodeData(T d);

  // Sets the left child node
  bool setNodeLeft(Node<T> *leftPtr);

  // Sets the right child node
  bool setNodeRight(Node<T> *rightPtr);

  // sets the height of a node
  bool setNodeHeight(int h);

 private:
  // Pointer to the left child
  Node<T> *left;

  // Pointer to the right child
  Node<T> *right;

  // data within the node
  T data;

  // key of the node
  int key;

  // counter for dublicates
  int counter;

  int height;
};

#include "Node.cpp"

#endif  // NODE