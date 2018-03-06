#include "stack.hpp"

using namespace std;

template<class T>
void Stack<T>::push(T c)
{
    topIndex++;
    arr[topIndex] = c;
}

template<class T>
T Stack<T>::top()
{
    return arr[topIndex];
}

template<class T>
void Stack<T>::pop()
{
    topIndex--;
}

template<class T>
int Stack<T>::size()
{
  return topIndex;
}

template<class T>
void Stack<T>::display()
{
    int i;
    for (i = topIndex; i >=0; i--)
    {
        cout << arr[i] << " ";
    }
}

template class Stack<char>;
template class Stack<int>;
