#include "maxheap.hpp"
#include <stdio.h>
#include <iostream>

MaxHeap::MaxHeap() {}
MaxHeap::~MaxHeap() {}

/*
ALL YOUR CODE GOES HERE
The methods below either
  - don't do anything at all, or
  - return 0 just so that the code compiles

You have to implement every method in this class
 */

int MaxHeap::size() { 
  return 0;
}

int MaxHeap::left(int parent) {
  return 0;
}

int MaxHeap::right(int parent) {
  return 0;
}

int MaxHeap::parent(int child) {
  return 0;
}

void MaxHeap::insert(int element) {
  
}

int MaxHeap::deleteMax() {
  return 0;
}

void MaxHeap::display() {
  vector<int>::iterator it;
  cout << "MaxHeap:- ";
  for(it=arr.begin(); it!=arr.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void MaxHeap::percolateUp(int index) {

}

void MaxHeap::percolateDown(int index) {

}

void MaxHeap::buildHeap(vector<int> A,int n) {

}

void MaxHeap::heapsort(vector<int>& A,int n) {

}
