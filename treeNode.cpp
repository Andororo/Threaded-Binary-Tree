/**
 * @file treeNode.cpp
 * @brief implements all of the functions defined in treeNode.h for use within
 * tree objects
 * @author Braxton Goss & Andrew Pham
 */

#include "treeNode.h"

// empty constructor
treeNode::treeNode() {
  this->data = 0;
  this->left = nullptr;
  this->right = nullptr;
  this->lthread = false;
  this->rthread = false;
}

// data constructor -- rest is nullptr or false
treeNode::treeNode(int i) {
  this->data = i;
  this->left = nullptr;  // To point to left treeNode
  this->right = nullptr; // To point to right treeNode
  this->lthread = false; // To check presence of left thread
  this->rthread = false; // to check presence of right thread
}

// full constructor
treeNode::treeNode(int data, treeNode *left, treeNode *right, bool lthread,
                   bool rthread) {
  this->data = data;
  this->left = left;
  this->right = right;
  this->lthread = lthread;
  this->rthread = rthread;
}

// destructor (blank but declaration required due to default constructor
// declaration)
treeNode::~treeNode() {}
