/**
 * @file tree.h
 * @brief outlines all of the functions needed to create and modify a threaded
 * BST
 * @author Braxton Goss & Andrew Pham
 */

#ifndef TREE_H
#define TREE_H

#include "treeNode.h"
#include <iostream>

using namespace std;

class Tree {
public:
  //-------------------------------------------------------
  //       Constructor and Destructor Section
  //------------------------------------------------------
  Tree();
  Tree(int n);
  Tree(const Tree &otherTree);
  ~Tree();
  //------------------------------------------------------
  //       Tree Implentation Method Section
  //------------------------------------------------------
  /**
   * @brief insert 1 to n value into threaded binary tree
   * @pre given a valid value of n
   * @post insert the data into into the threaded binary tree
   * @param data- data from userinput  
   */
  treeNode *insert(int data);

  /**
   * @brief find the left most child of the right tree
   * @pre created a valid threaded binary tree
   * @post Returns inorder successor data using rthread
   * @param ptr- pointer to the node that being traverse
   */
  treeNode *inOrderSuccessor(treeNode *ptr);

  /**
   * @brief given the binary tree print it inorder
   * @pre valid input of binary tree
   * @post print the node values to the console inOrder
   * @param root- pointer to the root
   */
  void printInOrder(treeNode *root);

  /**
   * @brief find the inOrder Predecessor of each nodes
   * @pre valid input  of the binary tree
   * @post return the data of the Predecessor
   * @param ptr- pointer tothe node that being  traverse
   */
  treeNode *inOrderPredecessor(treeNode *ptr);

  /**
   * @brief helper function for removal if there are no children of removed root
   * @pre root is initalized and not nullptr, found to be the one removed
   * @post root is removed and surrounding nodes are modified
   * @param root - root of the tree node is being removed from
   * @param parentPtr - pointer to the previous parent node of childPtr
   * @param childPtr - pointer to the node to be removed
   */
  treeNode *case1(treeNode *root, treeNode *parentPtr, treeNode *childPtr);

  /**
   * @brief helper function for removal when node to be removed has a single
   * child (right or left)
   * @pre root is initialized and not nullptr, remove function found the node
   * being removed
   * @post node is removed and surrounding nodes are modified
   * @param root - root of the tree node is being removed from
   * @param parentPtr - pointer to the node that is being deleted
   * @param childPtr - single child of the node to be deleted
   */
  treeNode *case2(treeNode *root, treeNode *parentPtr, treeNode *childPtr);

  /**
   * @brief helper function for removal if node to be removed has two children
   * @pre root is initialized and not nullptr, ptr points to the node to be
   * removed
   * @post node is removed and surrounding nodes are modified
   * @param root - root of the tree node is being removed from
   * @param ptr - pointer to the node to be removed
   */
  treeNode *case3(treeNode *root, treeNode *ptr);

  /**
   * @brief Removes a node with a data that matches a given number
   * @pre valid input
   * @post remove the node from tree and return new root to binary tree
   * @param root- points to the root value
   * @param target- removes the target value
   */
  treeNode *remove(treeNode *root, int target);

  /**
   * @brief Removes a node with a data that matches a given number
   * @pre valid input
   * @post remove the node from tree and return new root to binary tree
   * @param n- input value from the user from 1 to n...
   */
  void removeEvens(int n);

  /**
   * @brief clear all nodes and its descendants
   * @pre created valid threaded binary tree
   * @post call in the destructor to release all dynamic allocated memory
   * @param root- pass by pointer reference to dellocate memory 
   */
  void makeEmpty(treeNode *&root);
  //------------------------------------------------------
  //        Node Getters Implentation Method Section
  //------------------------------------------------------
  /**
   * @brief getter function for the root node
   * @pre valid input for the binary tree
   * @post return root node
   * @param none
   */
  treeNode *getRoot();

  /**
   * @brief getter function for the number of nodes
   * @pre valid input for the binary tree
   * @post return node amounts
   * @param none
   */
  int getNumberOfNodes() const;

private:
  treeNode *root;    // pointer to the root node
  int numberOfNodes; // Integer to the number of nodes being created
};// end threadedBST.h
#endif