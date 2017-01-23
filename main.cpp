/***************************************************************************************************************\
*
*                                        Binary Search Tree Program
*                                        Documented and written by
*                                              Mathew Jackson
*                                                 (c)2016
*
*           DESCRIPTION:
*
*                    BST is a program that will take a value and insert it into a tree structure depending is it is
*                    greater than or less than the parent node. Duplicate values are not allowed.
*
*           Disclaimer:
*
*                    -9999 is not to be used as a root value. I chose this to terminate the entire program
*
*           FILES:
*                   main.cpp - contains the general main function
*                   generalFunctions.h - contains the interface functionality for the program
*                   bstClass.h - this contains the 2 classes for the BST and the node
*
*           Functionality:
*
*                INSERT - Insert a node as a leaf
*                DELETE - Delete a given value from the tree. Depending on how the tree is assigned, it will used
*                         a helper function called findPredecessor() or findSuccessor().
*                SEARCH - Search for a given value within the tree. The program will notify you if this value is
*                         found.
*                FIND DEPTH - This will give the general depth of the node that the user searches for
*                FIND COST - This uses an interface module that will create an array for all of the leaf nodes
*                            and then traverse the tree to find the leaf nodes, adding the values as it goes.
*                            It will then place the path values in another array to be compared for the highest
*                            path.
*                IS BALANCED - A function to determine if the balance factor of any node is above 2. If it is
*                              it will report that the tree is unbalanced. If not, it will report that the tree
*                              is balanced.
*                PRINT TREE - This function will print the entire tree in a descending order.
*
*
*
/****************************************************************************************************************/
#include <iostream>
#include "bstClass.h"
#include "generalFunctions.h"

using namespace std;

int main()
{
    while(userInterface() != 0);
    return 0;
}

