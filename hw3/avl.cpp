#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

void insert( const int & info, AvlNode * & root );
void remove( const int & info, AvlNode * & root );
void print(AvlNode *root, int level, int type);
void print(AvlNode *root);
void balance(AvlNode *&root);
AvlNode *rightRotate(AvlNode *&root);
AvlNode *leftRotate(AvlNode *&root);
AvlNode *rightLeftRotate(AvlNode *&root);
AvlNode *leftRightRotate(AvlNode *&root);
int getBalance(AvlNode*&root);
void updateHeight(AvlNode *& root);
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



/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert(const int & info, AvlNode * & root)
{
    if (root == nullptr)
    {
        root = new AvlNode (info, nullptr, nullptr);
        updateHeight(root);
    }

    else if (info < root->element)
    {
        insert(info, root->left);
        updateHeight(root);
        balance(root);
    }

    else
    {
        insert(info, root->right);
        updateHeight(root);
        balance(root);
    }
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int & info, AvlNode * & root )
{
    AvlNode *temp;

    if (root == NULL)
    {
        return;
    }

    if (info < root->element)
    {
        remove(info, root->left);
    }
    else if (info > root->element)
    {
        remove(info, root->right);
    }
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete(root);
            root = NULL;
        }
        else if (root->left == NULL)
        {
            AvlNode *temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            AvlNode *temp = root;
            root = root->left;
            delete temp;
        }
        // case 4: two children
        else
        {
            AvlNode *temp = findMin(root->right);
            root->element = temp->element;
            remove(root->element, root->right); // delete the duplicate node
        }
    }
}


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

// refactor
void balance(AvlNode *&root)
{
    int difference = getBalance(root);

    if (difference > 1)
    {
        if (getBalance(root->left) > 0)
        {
            root = rightRotate(root);
        }

        else
        {
            root = leftRightRotate(root);
        }

    }

    else if(difference < -1)
    {
        if (getBalance(root->right) < 0)
        {
            root = leftRotate(root);
        }

        else
        {
            root = rightLeftRotate(root);
        }
    }
}


AvlNode *rightRotate(AvlNode *&root)
{
    AvlNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;

    updateHeight(root);
    return temp;
}

AvlNode *leftRotate(AvlNode *&root)
{
    AvlNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;

    updateHeight(root);
    return temp;
}

AvlNode *rightLeftRotate(AvlNode *&root)
{
    AvlNode *temp = root->right;
    root->right = rightRotate(temp);
    return leftRotate(root);
}

AvlNode *leftRightRotate(AvlNode *&root)
{
    AvlNode *temp = root->left;
    root->left = leftRotate(temp);
    return rightRotate(root);
}

// Get the balance property of a tree
int getBalance(AvlNode *&root)
{
    int lHeight = 0;
    int rHeight = 0;

    if (root == NULL)
    {
        return 0;
    }

    if (root->left != NULL)
    {
        lHeight =  root->left->height;
    }

    if (root->right != NULL)
    {
        rHeight = root->right->height;
    }

    return lHeight - rHeight;
}

// Update the height of an AvlNode
void updateHeight(AvlNode *&root)
{
    int lHeight = 0;
    int rHeight = 0;
    int larger;

    if (root->left != NULL)
    {
        lHeight = root->left->height;
    }

    if (root->right != NULL)
    {
        rHeight =root->right->height;
    }

    larger = max(lHeight, rHeight);

    root->height = larger + 1;
}

// Find the minumum value of a subtree
AvlNode *findMin(AvlNode *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->left != NULL)
    {
        return findMin(root->left);
    }

    return root;
}

