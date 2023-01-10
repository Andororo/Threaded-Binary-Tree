/**
 * @file tree.cpp
 * @brief implements all functions declared within tree.h to use and modify
 * threaded BST objects
 * @author Braxton Goss & Andrew Pham
 */
#include "tree.h"
#include "treeNode.h"
#include <iostream>

using namespace std;

// EMPTY CONSTRUCTOR //
Tree::Tree() {
  root = nullptr;
  numberOfNodes = 0;
}

// GIVEN N-SIZE CONSTRUCTOR //
Tree::Tree(int n) {
  this->numberOfNodes = n;
  if (n < 1) {
    return;
  } else {
    root = nullptr;
    int midpoint = (1 + n) / 2;
    root = insert(midpoint); // insert midpoint
    for (int i = 1; i <= n; i++) {
      if (i == midpoint) { // DO NOT INSERT MIDPOINT AGAIN
        continue;
      } else {
        root = insert(i); // insert rest of elements other than midpoint
      }
    }
  }
}

// COPY CONSTRUCTOR //
Tree::Tree(const Tree &otherTree) {
  this->numberOfNodes = otherTree.getNumberOfNodes();
  if (otherTree.numberOfNodes < 1) {
    return;
  } else {
    root = nullptr;
    int midpoint = (1 + otherTree.getNumberOfNodes()) / 2;
    root = insert(midpoint); // insert midpoint
    for (int i = 1; i <= otherTree.numberOfNodes; i++) {
      if (i == midpoint) { // DO NOT INSERT MIDPOINT AGAIN
        continue;
      } else {
        root = insert(i); // insert rest of elements other than midpoint
      }
    }
  }
}

// DECONSTRUCTOR //
Tree::~Tree() {
  makeEmpty(root);
  root = nullptr;
}

// return pointer to root node of tree
treeNode *Tree::getRoot() { return this->root; }

// return number of nodes in tree
int Tree::getNumberOfNodes() const { return this->numberOfNodes; }

// Insert a Node in Binary Threaded Tree
treeNode *Tree::insert(int data) {
  // Searching for a Node with given value
  treeNode *ptr = root;
  treeNode *par = nullptr; // Parent of key to be inserted
  while (ptr != nullptr) {

    par = ptr; // Update parent pointer

    // Moving on left subtree.
    if (data < ptr->data) {
      if (ptr->lthread == false)
        ptr = ptr->left;
      else
        break;
    }

    // Moving on right subtree.
    else {
      if (ptr->rthread == false)
        ptr = ptr->right;
      else
        break;
    }
  }

  // Create a new Node for the thread binary tree
  treeNode *temp = new treeNode(data);
  temp->lthread = true;
  temp->rthread = true;
  if (par == nullptr) {
    root = temp;
    temp->left = nullptr;
    temp->right = nullptr;
  } else if (data < par->data) {
    temp->left = par->left;
    temp->right = par;
    par->lthread = false;
    par->left = temp;
  } else {
    temp->left = par;
    temp->right = par->right;
    par->rthread = false;
    par->right = temp;
  }
  return root;
}

// Returns inorder successor using rthread
// (Used in inorder)
treeNode *Tree::inOrderSuccessor(treeNode *ptr) {
  // If rthread is set, we can quickly find
  if (ptr->rthread == true) {
    return ptr->right;
  }

  // Else return leftmost child of right subtree
  ptr = ptr->right;
  while (ptr->lthread == false) {
    ptr = ptr->left;
  }
  return ptr;
}

// Printing the threaded tree
void Tree::printInOrder(treeNode *root) {
  if (root == nullptr) {
    cout << "EMPTY TREE" << endl;
    return;
  }

  // Reach leftmost Node
  treeNode *ptr = root;
  while (ptr->lthread == false) {
    ptr = ptr->left;
  }

  // One by one print successors
  while (ptr != nullptr) {
    cout << ptr->data << " ";
    ptr = inOrderSuccessor(ptr);
  }
}

// find inOrderPredecessor
treeNode *Tree::inOrderPredecessor(treeNode *ptr) {
  if (ptr->lthread == true)
    return ptr->left;

  ptr = ptr->left;
  while (ptr->rthread == false)
    ptr = ptr->right;
  return ptr;
}
// helper function for removal if there are no children of removed root
treeNode *Tree::case1(treeNode *root, treeNode *parentPtr, treeNode *childPtr) {
  // If Node to be deleted is root
  if (parentPtr == nullptr)
    root = nullptr;

  // If Node to be deleted is left
  // of its parent
  else if (childPtr == parentPtr->left) {
    parentPtr->lthread = true;
    parentPtr->left = childPtr->left;
  } else {
    parentPtr->rthread = true;
    parentPtr->right = childPtr->right;
  }

  // Free memory and return new root
  delete childPtr;
  childPtr = nullptr;
  return root;
}
// helper function for removal when node to be removed has a single child (right
// or left)
treeNode *Tree::case2(treeNode *root, treeNode *parentPtr, treeNode *childPtr) {
  treeNode *child;

  // Initialize child Node to be deleted has
  // left child.
  if (childPtr->lthread == false)
    child = childPtr->left;

  // Node to be deleted has right child.
  else
    child = childPtr->right;

  // Node to be deleted is root Node.
  if (parentPtr == nullptr)
    root = child;

  // Node is left child of its parent.
  else if (childPtr == parentPtr->left)
    parentPtr->left = child;
  else
    parentPtr->right = child;

  // Find successor and predecessor
  treeNode *s = inOrderSuccessor(childPtr);
  treeNode *p = inOrderPredecessor(childPtr);

  // If ptr has left subtree.
  if (childPtr->lthread == false)
    p->right = s;

  // If ptr has right subtree.
  else {
    if (childPtr->rthread == false)
      s->left = p;
  }

  delete childPtr;
  childPtr = nullptr;
  return root;
}

// Helper function for removal when node to be removed has two child nodes
treeNode *Tree::case3(treeNode *root, treeNode *ptr) {
  // Find inorder successor and its parent.
  treeNode *parsucc = ptr;
  treeNode *succ = ptr->right;

  // Find leftmost child of successor
  while (succ->lthread == false) {
    parsucc = succ;
    succ = succ->left;
  }

  ptr->data = succ->data;

  if (succ->lthread == true && succ->rthread == true)
    root = case1(root, parsucc, succ);
  else
    root = case2(root, parsucc, succ);

  return root;
}

// Delete target from TBST given it's root, returns new root of BST.
treeNode *Tree::remove(treeNode *root, int target) {
  // Initialize parent as nullptr and
  // Node as root.
  treeNode *par = nullptr, *ptr = root;

  // Search key in BST
  // find Node and its a parent
  while (ptr != nullptr) {
    if (target == ptr->data) {
      break;
    }
    par = ptr;
    if (target < ptr->data) {
      if (ptr->lthread == false)
        ptr = ptr->left;
      else
        break;
    } else {
      if (ptr->rthread == false)
        ptr = ptr->right;
      else
        break;
    }
  }

  // Two Children
  if (ptr->lthread == false && ptr->rthread == false)
    root = case3(root, ptr);

  // Only Left Child
  else if (ptr->lthread == false)
    root = case2(root, par, ptr);

  // Only Right Child
  else if (ptr->rthread == false)
    root = case2(root, par, ptr);

  // No child
  else
    root = case1(root, par, ptr);

  return root;
}

// called from client to remove all even numbered nodes from tree
void Tree::removeEvens(int n) {
  for (int i = 2; i <= n; i += 2) {
    remove(root, i);
  }
}

void Tree::makeEmpty(treeNode *&root) {
  // iterate using post-order: L R N
  // delete each node as we iterate
  // Reach leftmost Node
  while (root->lthread == false) {
    root = root->left;
  }
  // One by one delete successors
  while (root != nullptr) {
    treeNode *nodeToDelete = root;
    root = inOrderSuccessor(root);
    delete nodeToDelete;
    nodeToDelete = nullptr;
  }
}
