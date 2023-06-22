// Constructor and Destructor

template <class T>
Node<T>::Node() {}

template <class T>
Node<T>::Node(T data, int count, int h, Node<T> *leftPtr, Node<T> *rightPtr) {
  data = data;
  counter = count;
  height = h;
  left = leftPtr;
  right = rightPtr;
}

template <class T>
Node<T>::~Node() {}

// Getters:

// returns the data of the node
template <class T>
T Node<T>::getNodeData() const {
  return data;
}

// returns the left child node
template <class T>
Node<T> *Node<T>::getNodeLeft() const {
  return left;
}

// returns the right child node
template <class T>
Node<T> *Node<T>::getNodeRight() const {
  return right;
}

// returns the the key of the node
template <class T>
int Node<T>::getNodeKey() const {
  return key;
}

// get the couter
template <class T>
int Node<T>::getCounter() const {
  return counter;
}

// gets the height of a node
template <class T>
int Node<T>::getNodeHeight() const {
  return height;
}

// Setters:

// set count
template <class T>
bool Node<T>::setCounter(int count) {
  counter = count;
  return true;
}

// Sets the nodes key
template <class T>
bool Node<T>::setNodeKey(double k) {
  key = k;
  return true;
}

// Set the node data
template <class T>
bool Node<T>::setNodeData(T d) {
  data = d;
  return true;
}

// Sets the left child node
template <class T>
bool Node<T>::setNodeLeft(Node<T> *leftPtr) {
  left = leftPtr;
  return true;
}

// Sets the right child node
template <class T>
bool Node<T>::setNodeRight(Node<T> *rightPtr) {
  right = rightPtr;
  return true;
}

// set nodes height
template <class T>
bool Node<T>::setNodeHeight(int h) {
  height = h;

  return true;
}
