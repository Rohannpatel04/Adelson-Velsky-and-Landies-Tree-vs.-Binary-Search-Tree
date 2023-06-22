// Constructor and Destructor

template <class T>
BinarySearchTree<T>::BinarySearchTree() {
  root = NULL;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
  emptyTree(root);
}

// Inserts a new node in the correct location
template <class T>
bool BinarySearchTree<T>::Insert(double key, T value) {
  // New Node is created and the key and value is added to it
  Node<T>* newNode = new Node<T>(value, 1, 0, NULL, NULL);
  newNode->setNodeKey(key);

  // Check if the root is null
  if (!root) {
    root = newNode;
    return true;
  }

  // Pointer which points to the past node
  Node<T>* previous = NULL;
  // Pointer which points to the current node
  Node<T>* current = root;

  // While the current is not null
  while (current != NULL) {
    // if the key is less than the root traverse through the left side
    if (key < current->getNodeKey()) {
      previous = current;
      current = current->getNodeLeft();
    }

    // if the key is larger than the root traverse through the right side
    else if (key > current->getNodeKey()) {
      previous = current;
      current = current->getNodeRight();
    }

    else {
      break;
    }
  }

  // if the previous key is less than the key that is being added
  if (previous->getNodeKey() < key) {
    // Inserting the new node on the right side of the parent
    previous->setNodeRight(newNode);
  }

  // if the previous key is greater than the key that is being added
  else if (previous->getNodeKey() > key) {
    // Inserting the new node on the left side of the parent
    previous->setNodeLeft(newNode);
  }

  else {
    current->setCounter(current->getCounter() + 1);

    delete newNode;
    newNode = NULL;
  }

  return true;
}

// Removes the node with a key matching the key being passed in
template <class T>
bool BinarySearchTree<T>::Remove(double key) {
  // check if the tree is empty
  if (root == NULL) {
    return false;
  }

  // Check if we only have 1 node in the tree
  if (root->getNodeLeft() == NULL && root->getNodeRight() == NULL) {
    if (root->getNodeKey() == key) {
      delete root;
      root = NULL;
      return true;
    }
  }

  // Pointer which points to the past node
  Node<T>* previous = NULL;
  // Pointer which points to the current node
  Node<T>* current = root;

  // While the current is not null
  while (current != NULL) {
    // if the key is less than the root traverse through the left side
    if (key < current->getNodeKey()) {
      previous = current;
      current = current->getNodeLeft();
    }

    // if the key is larger than the root traverse through the right side
    else if (key > current->getNodeKey()) {
      previous = current;
      current = current->getNodeRight();
    }

    else {
      // if both the left and right of current are NULL
      if (current->getNodeRight() == NULL && current->getNodeLeft() == NULL) {
        if (previous->getNodeKey() > current->getNodeKey()) {
          previous->setNodeLeft(NULL);
        }

        else {
          previous->setNodeRight(NULL);
        }

        // Delete Node
        delete current;
        current = NULL;
      }

      // if the left or right child of the current is not NULL
      else if (current->getNodeRight() == NULL ||
               current->getNodeLeft() == NULL) {
        // if previous key is greater than current key we reset the left
        if (previous->getNodeKey() > current->getNodeKey()) {
          //  if left is not null
          if (current->getNodeLeft() != NULL) {
            //  Connect previous left with current left
            previous->setNodeLeft(current->getNodeLeft());
          }
          // else right is not null
          else {
            // Connect previous left with right
            previous->setNodeLeft(current->getNodeRight());
          }
        }

        // if previous key is less than current key we reset the right
        if (previous->getNodeKey() < current->getNodeKey()) {
          //  if right is not null
          if (current->getNodeRight() != NULL) {
            //  Connect previous right with current left
            previous->setNodeRight(current->getNodeRight());
          }
          // else left is not null
          else {
            // connect previous right with left
            previous->setNodeRight(current->getNodeLeft());
          }
        }
        // delete the node
        delete current;
        current = NULL;
      }

      // if the left and right child of the current is not null
      else {
        Node<T>* temp = current->getNodeLeft();
        Node<T>* prev = NULL;

        // Iterate through the right side untill temp is NULL
        while (temp->getNodeRight() != NULL) {
          prev = temp;
          temp = temp->getNodeRight();
        }

        // if the previous is not null
        if (prev != NULL) {
          // we set the previous right to temps left
          prev->setNodeRight(temp->getNodeLeft());
        }

        // if we did not iterate through the right
        else {
          // set the current to the temp left
          current->setNodeLeft(temp->getNodeLeft());
        }

        // swap node data that needs to be deleted with temp
        current->setNodeData(temp->getNodeData());
        current->setNodeKey(temp->getNodeKey());

        // delete temp
        delete temp;
        temp = NULL;

        // exit while loop
        break;
      }
      return true;
    }
  }
  return false;
}

// Finds a node which matches the key being passed in
template <class T>
T BinarySearchTree<T>::Find(double key) {
  // if the root is null
  if (root == NULL) {

    return T();
  }

  // Pointer which points to the current node
  Node<T>* current = root;

  // While the the current key doesnt equal the key that needs to be removed

  // the left and right child are NULL
  while (current != NULL) {
    // if the key is less than the root traverse through the left side
    if (key < current->getNodeKey()) {
      current = current->getNodeLeft();
    }

    // if the key is larger than the root traverse through the right side
    else if (key > current->getNodeKey()) {
      current = current->getNodeRight();
    }

    // if the current key equals the key that is being passed in
    else {
      // Return the current data
      return current->getNodeData();
    }
  }
  return T();
}

template <class T>
void BinarySearchTree<T>::printCall() {
  if (root == NULL) {
    cout << "No Node Found!" << endl;
  } else {
    print(root);
  }
}

template <class T>
void BinarySearchTree<T>::print(Node<T>* ptr) {
  if (ptr == NULL) {
    return;
  } else {
    print(ptr->getNodeLeft());
    // cout << ptr->getNodeKey() << endl;
    print(ptr->getNodeRight());
  }
}

template <class T>
void BinarySearchTree<T>::emptyTree(Node<T>* node) {
  if (node == NULL) {
    root = NULL;
    return;
  }
  emptyTree(node->getNodeLeft());
  emptyTree(node->getNodeRight());
  delete node;
  node = NULL;
}
