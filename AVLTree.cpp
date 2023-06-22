
// Constructor and Destructor
template <class T>
AVLTree<T>::AVLTree() {
  root = NULL;
}

template <class T>
AVLTree<T>::~AVLTree() {
  emptyTree(root);
}

template <class T>
Node<T>* AVLTree<T>::newNode(int key, T value) {
  // New Node is created and the key and value is added to it

  Node<T>* newNode = new Node<T>(value, 1, 1, NULL, NULL);
  newNode->setNodeKey(key);

  if (root == NULL) {
    root = newNode;
  }

  return newNode;
}

template <class T>
Node<T>* AVLTree<T>::InsertHelper(Node<T>* root, int key, T value) {
  // Check if the root is null
  if (root == NULL) {
    return (newNode(key, value));
  }

  // check for duplicate
  if (key == root->getNodeKey()) {
    root->setCounter(root->getCounter() + 1);
    return root;
  }

  // Treverse left
  if (key < root->getNodeKey()) {
    root->setNodeLeft(InsertHelper(root->getNodeLeft(), key, value));
  }

  // Treverse right
  else {
    root->setNodeRight(InsertHelper(root->getNodeRight(), key, value));
  }

  // Update height
  root->setNodeHeight(
      max(GetHeight(root->getNodeLeft()), GetHeight(root->getNodeRight())));

  // get the balance factor
  int bf = getBalanceFactor(root);

  // Left Left Rotation
  if (bf > 1 && key < root->getNodeLeft()->getNodeKey()) {
    return RightRotation(root);
  }

  // Left Right Rotation
  if (bf > 1 && key > root->getNodeLeft()->getNodeKey()) {
    root->setNodeLeft(LeftRotation(root->getNodeLeft()));
    return RightRotation(root);
  }

  // Right Right Rotation
  if (bf < -1 && key < root->getNodeRight()->getNodeKey()) {
    return LeftRotation(root);
  }

  // Right Left Rotation
  if (bf < -1 && key < root->getNodeRight()->getNodeKey()) {
    root->setNodeRight(RightRotation(root->getNodeRight()));
    return LeftRotation(root);
  }

  return root;
}

// Inserts a new node in the correct location
template <class T>
bool AVLTree<T>::Insert(double key, T value) {
  InsertHelper(root, key, value);

  return true;
}

// Removes the node with a key matching the key being passed in
template <class T>
bool AVLTree<T>::Remove(double key) {
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
      // if there are dublicates
      if (current->getCounter() > 1) {
        current->setCounter(current->getCounter() - 1);
      }

      // if both the left and right of current are NULL
      else if (current->getNodeRight() == NULL &&
               current->getNodeLeft() == NULL) {
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

  // AVL formation:

  int bf = getBalanceFactor(previous);

  // If a right rotation needs to occur
  if (bf > 1 && key < previous->getNodeLeft()->getNodeKey()) {
    previous = RightRotation(previous);
  }

  // if a left rotation and then a right rotation needs to occur
  if (bf > 1 && key > previous->getNodeLeft()->getNodeKey()) {
    previous->setNodeLeft(LeftRotation(previous->getNodeLeft()));
    previous = RightRotation(previous);
  }

  // if a left rotation needs to occur
  if (bf < -1 && key > previous->getNodeRight()->getNodeKey()) {
    previous = LeftRotation(previous);
  }

  // if a right rotation and then a left rotation needs to occur
  if (bf < -1 && key < previous->getNodeRight()->getNodeKey()) {
    previous->setNodeRight(RightRotation(previous->getNodeRight()));
    previous = LeftRotation(previous);
  }
  return true;
}

// Finds a node which matches the key being passed in and returns it's data
template <class T>
T AVLTree<T>::Find(double key) {
  // if the root is null
  if (root == NULL) {
    return T();
  }

  // Pointer which points to the current node
  Node<T>* current = root;

  // While the the current key doesnt equal the key that needs to be removed
  // or the left and right child are NULL
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

// Returns the height of a node in the tree
template <class T>
int AVLTree<T>::GetHeight(Node<T>* n) {
  if (n == NULL) {
    return 0;
  }

  else {
    return n->getNodeHeight();
  }
}

// Returns the balance factor of a node
template <class T>
int AVLTree<T>::getBalanceFactor(Node<T>* n) {
  // check if the node is NULL
  if (n == NULL) {
    return 0;
  }

  return (GetHeight(n->getNodeLeft()) - GetHeight(n->getNodeRight()));
}

// Conducts left rotation
template <class T>
Node<T>* AVLTree<T>::LeftRotation(Node<T>* previous) {
  Node<T>* current = previous->getNodeRight();

  Node<T>* t = current->getNodeLeft();

  current->setNodeLeft(previous);
  previous->setNodeRight(t);

  previous->setNodeHeight(max(GetHeight(previous->getNodeLeft()),
                              GetHeight(previous->getNodeRight())) +
                          1);

  current->setNodeHeight(max(GetHeight(current->getNodeLeft()),
                             GetHeight(current->getNodeRight())) +
                         1);

  return current;
}

// Conducts right rotation
template <class T>
Node<T>* AVLTree<T>::RightRotation(Node<T>* previous) {
  Node<T>* current = previous->getNodeLeft();
  Node<T>* t = current->getNodeRight();

  current->setNodeRight(previous);
  previous->setNodeLeft(t);

  previous->setNodeHeight(max(GetHeight(previous->getNodeLeft()),
                              GetHeight(previous->getNodeRight())) +
                          1);

  current->setNodeHeight(max(GetHeight(current->getNodeLeft()),
                             GetHeight(current->getNodeRight())) +
                         1);

  return current;
}

template <class T>
void AVLTree<T>::printCall() {
  if (root == NULL) {
    cout << "No Nodes Found!" << endl;
  } else {
    print(root);
  }
}

template <class T>
void AVLTree<T>::print(Node<T>* ptr) {
  if (ptr == NULL) {
    return;
  } else {
    print(ptr->getNodeLeft());
    cout << ptr->getNodeKey() << endl;
    print(ptr->getNodeRight());
  }
}

template <class T>
void AVLTree<T>::emptyTree(Node<T>* node) {
  if (node == NULL) {
    root = NULL;
    return;
  }
  emptyTree(node->getNodeLeft());
  emptyTree(node->getNodeRight());
  delete node;
  node = NULL;
}
