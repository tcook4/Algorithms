#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

void insert(const int &info, AvlNode *&root);

void remove(const int & info, AvlNode * & root);

int getBalance(AvlNode *n);

int height(AvlNode *n);

AvlNode* rightRotate(AvlNode *y);

AvlNode* leftRotate(AvlNode x);

void print(AvlNode *root, int level, int type);

void print(AvlNode *root);


// Main method - do not change
int main(int argc, const char * argv[])
{
    AvlNode *root = NULL;
    std::string filename = argv[1];
    freopen(filename.c_str(), "r", stdin);
    std::string input;
    int data;

    while(std::cin >> input)
    {
        if (input == "insert")
        {
            std::cin>>data;
            insert(data, root);
        }

        else if(input == "delete")
        {
            std::cin>>data;
            remove(data, root);
        }

        else if(input == "print")
        {
            print(root);
            std::cout << "\n";
        }

        else
        {
            std::cout<<"Data not consistent in file";
            break;
        }
    }
    return 0;
}

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

void remove(const int & info, AvlNode * & root)
{
    std::cout << "Code for deleting " << info << " goes here" << endl;
}

int getBalance(AvlNode *n)
{
    if (n != NULL)
    {
        return (height(n->left) - height(n->right));
    }
    return 0;
}


int height(AvlNode *n)
{
    if (n != NULL)
    {
        return n->height;
    }
    return 0;
}


void insert(const int & info, AvlNode * & root)
{
    if (root == nullptr)
    {
        root = new AvlNode(info, nullptr, nullptr);
    }

    // If item is smaller than element, insert left
    else if (root->element < info)
    {
        insert(info, root->left);
    }

    // Else, insert right
    else
    {
        insert(info, root->right);
    }

    // Update the height of our node
    root->height = max(height(root->left), height(root->right)) + 1;


    // Get balance property
    int balance = getBalance(root);


    // Left rotate
    if (balance > 1 && info < root->left->element)
    {
        return rightRotate(root);
    }

    // Right rotate
    if (balance < -1 && info > root->right->element)
    {
        return leftRotate(root);
    }

    // Left Right rotate
    if (balance > 1 && data > root->left->element)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left rotate
    if (balance < -1 && data < root->right->element)
    {
        root->right = rightRotate(root->right);
        return leftRotate(node);
    }

    return node;
}

AvlNode *rightRotate(AvlNode *y)
{
    AvlNode* left = y->left;
    AvlNode* node2 = left->right;

    left->right = y;
    y->left = node2;

    left->height = max(height(left->left), height(left->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return left;
}

AvlNode *leftRotate(AvlNode *x)
{
    AvlNode *right = x->right;
    AvlNode *T2 = right->left;

    right->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    right->height = max(height(right->left), height(right->right)) + 1;

    return right;
}
