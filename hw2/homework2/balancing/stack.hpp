//#include <bits/stdc++.h>
#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>

#define MAXSIZE 100000

using namespace std;

template<class T>

class Stack
{
private:
    T arr[MAXSIZE]; // the actual stack
    int topIndex;   // index of the top element

public:
    Stack(){topIndex = -1;}  // consructor
    ~Stack(){}               // destructor
    void push(T c);          // push c to the list
    T top();                 // return the top element in the stack
    void pop();              // remove the top element in the stack
    int size();              // returns the size of the stack
    void display();          // display the stack in stdout
    inline T remove(){       // returns the top of the stack and removes it
        topIndex--;
        return arr[topIndex+1];}
};
