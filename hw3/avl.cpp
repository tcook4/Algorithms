/* Author: Tyler Cook
 * Date: March 19, 2018
 * UNT CSCE 3110 - Homework 3
 * Description: This program is an implementation of AVL trees. The program contains methods to balance, rotate,
 * and print trees as given by a file with written operations and values.
 */

#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

void insert(const int &info, AvlNode *&root);
void remove(const int &info, AvlNode *&root);
void print(AvlNode *root, int level, int type);
void print(AvlNode *root);
void balance(AvlNode *&root);
AvlNode *rightRotate(AvlNode *&root);
AvlNode *leftRotate(AvlNode *&root);
AvlNode *rightLeftRotate(AvlNode *&root);
AvlNode *leftRightRotate(AvlNode *&root);
int getBalance(AvlNode *&root);
void updateHeight(AvlNode *&root);
AvlNode *findMin(AvlNode *root);

/*
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
    AvlNode *root = NULL;
    std::string filename = argv[1];
    freopen(filename.c_str(), "r", stdin);
    std::string input;
    int data;
    while(std::cin >> input){
        if (input == "insert"){
            std::cin>>data;
            insert(data, root);
        } else if(input == "delete"){
            std::cin>>data;
            remove(data, root);
        } else if(input == "print"){
            print(root);
            std::cout << "\n";
        } else{
            std::cout<<"Data not consistent in file";
            break;
        }
    }
    return 0;
}
/*
 * END main method
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
    if (root == NULL) {
        return;
    }
    if (type == IS_ROOT) {
        std::cout << root -> element << "\n";
    } else {
        for (int i = 1; i < level; i++) {
            std::cout << "| ";
        }
        if (type == IS_LEFT) {
            std::cout << "|l_" << root -> element << "\n";
        } else {
            std::cout << "|r_" << root -> element << "\n";
        }
    }
    if (root -> left != NULL) {
        print(root -> left, level + 1, IS_LEFT);
    }
    if (root -> right != NULL) {
        print(root -> right, level + 1, IS_RIGHT);
    }
}
void print(AvlNode *root) {
    print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */

// Begin edited methods
// Insert a value to the tree
void insert(const int & info, AvlNode * & root)
{
    // If node is null, add it here
    if (root == nullptr)
    {
        root = new AvlNode (info, nullptr, nullptr);
        updateHeight(root);
    }

    // If value is smaller than our current, add it to the left and rebalance
    else if (info < root->element)
    {
        insert(info, root->left);
        updateHeight(root);
        balance(root);
    }

    // If value is larger than our current, add it to the right and rebalance
    else
    {
        insert(info, root->right);
        updateHeight(root);
        balance(root);
    }
}

// Remove a value from the tree
void remove(const int & info, AvlNode * & root)
{
    // If we're here, the value does not exist
    if (root == NULL)
    {
        return;
    }

    // If value is smaller than current, look to the left
    if (info < root->element)
    {
        remove(info, root->left);
        balance(root);
    }
    // If value is larger than current, look to the right
    else if (info > root->element)
    {
        remove(info, root->right);
        balance(root);
    }

    // Otherwise, we're at our value
    // Swap with a node then delete
    else
    {
        AvlNode *temp;

        // No children - we can just delete
        if (root->left == NULL && root->right == NULL)
        {
            delete(root);
            root = NULL;
        }

        // Prefer to swap with the larger value
        else if (root->left == NULL)
        {
            temp = root;
            root = root->right;
            delete temp;
        }

        // Otherwise, swap with the left
        else if (root->right == NULL)
        {
            temp = root;
            root = root->left;
            delete temp;
        }

        // Else, we have two children
        else
        {
            // Find the smaller of the right child
            temp = findMin(root->right);

            // Swap values and remove the old
            root->element = temp->element;
            remove(root->element, root->right);
        }
    }
}

// Rebalance a tree
void balance(AvlNode *&root)
{
    // Find the height difference of the tree
    int difference = getBalance(root);

    // If difference is greater than one left side is 'heavier'
    if (difference > 1)
    {
        // If our left side is still balanced, we did a left-left insert, and only need single rotation
        if (getBalance(root->left) > 0)
        {
            root = rightRotate(root);
        }
        else // We inserted left-right
        {
            root = leftRightRotate(root);
        }
    }

    // Otherwise, our right side is heavier
    else if(difference < -1)
    {
        // If our right side is still balanced, we did a right-right insert, and only need single rotation
        if (getBalance(root->right) < 0)
        {
            root = leftRotate(root);
        }
        else // We inserted right-left, need to double rotate
        {
            root = rightLeftRotate(root);
        }
    }
}

// Single rotate a node to the right
AvlNode *rightRotate(AvlNode *&root)
{
    AvlNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;

    // Update the height of this node and return
    updateHeight(root);
    return temp;
}

// Single rotate a node to the left
AvlNode *leftRotate(AvlNode *&root)
{
    AvlNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;

    // Update the height of this node and return
    updateHeight(root);
    return temp;
}

// Double rotate right-left
AvlNode *rightLeftRotate(AvlNode *&root)
{
    AvlNode *temp = root->right;
    root->right = rightRotate(temp);
    return leftRotate(root);
}

// Double rotate left-right
AvlNode *leftRightRotate(AvlNode *&root)
{
    AvlNode *temp = root->left;
    root->left = leftRotate(temp);
    return rightRotate(root);
}

// Get the AVL balance property of a tree
int getBalance(AvlNode *&root)
{
    int left = 0;
    int right = 0;

    // Set the heights for each child
    if (root == NULL)
    {
        return 0;
    }
    if (root->left != NULL)
    {
        left = root->left->height;
    }
    if (root->right != NULL)
    {
        right = root->right->height;
    }

    // Return height difference between left and right
    return left - right;
}

// Update the height of a node
void updateHeight(AvlNode *&root)
{
    // Check for null
    if (root == NULL)
    {
        return;
    }

    // Create spots for our values
    int left = 0;
    int right = 0;
    int larger;

    // Set our values
    if (root->left != NULL)
    {
        left = root->left->height;
    }
    if (root->right != NULL)
    {
        right = root->right->height;
    }

    // Find the larger of the two heights and set this node to that value +1
    larger = max(left, right);
    root->height = larger + 1;
}

// Find the minumum value of a subtree
AvlNode *findMin(AvlNode *root)
{
    // We shouldn't find null here
    if (root == NULL)
    {
        return NULL;
    }

    // Left subtree should always be smaller
    if (root->left != NULL)
    {
        return findMin(root->left);
    }
    // Otherwise, return this node
    return root;
}

