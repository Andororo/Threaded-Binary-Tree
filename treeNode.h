/**
 * @file treeNode.h
 * @brief outlines all of the functions and private data members for a treeNode
 * to be used within tree object
 * @author Braxton Goss & Andrew Pham
 */
#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <iostream>
using namespace std;

class Tree;

class treeNode {
public:
  /**
   * @brief constructs an empty node with no data, no children, and no threads
   * present
   * @pre declared in client class
   * @post initialized with nothing in it
   */
  treeNode();

  /**
   * @brief constructs a node with only the data, there are no children and no
   * threads
   * @pre data passed is an integer
   * @post treeNode is initialized with only data present
   * @param data - integer for node to hold
   */
  explicit treeNode(int data);

  /**
   * @brief constructs a full node with data, left and right children (can be
   * null though), left and right threads true or false
   * @pre all 5 parameters passed are of the correct type
   * @post node is constructed
   * @param data - integer for node to hold
   * @param left - pointer to the left child
   * @param right - pointer to the right child
   * @param lthread, rthread - presence of predecessor and successor
   * respectively
   */
  treeNode(int data, treeNode *left, treeNode *right, bool lthread,
           bool rthread);

  /**
   * @brief destructor for treeNode
   * @pre node is allocating memory
   * @post node is removed from memory and cleared up
   */
  ~treeNode();

  int data;        // data portion for integer storage
  treeNode *left;  // Pointer to the left child
  treeNode *right; // Pointer to the right child
  bool lthread;    // Denotes if left pointer points to predecessor
  bool rthread;    // Denotes if right pointer point to successor
};                 // end treeNode.h
#endif