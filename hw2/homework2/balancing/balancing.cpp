/* Author: Tyler Cook
 * Date: March 7th, 2018
 * UNT CSCE 3110 - Homework 2
 * Description: This program detectes parenthesis "()", brackets "[]" and braces "{}", and
 * indicates weather the expression given is balanced or not.
 */

#include "stack.hpp"

using namespace std;

int main()
{
    FILE * fpTest;

    fpTest = freopen("input_balanced.txt", "r", stdin);
    if (fpTest == NULL)
    {
        cout << "filefiail\n";
    }
    string s,r;
    int line_counter;

    while(cin >> r)
    {
        cin>>s;
        Stack<char> stack;
        bool isBalanced = true;
        bool solution;
        char top;

        if(r[0] == 'Y' || r[0] == 'y')
        {
            solution = true;
        }
        else
        {
            solution = false;
        }

        // If we find an open bracket, parenthesis or brace, push it to the stack
        // If we find a closing bracket, parenthesis or brace, comapre it to the top if the stack
        // Pop the stack if we have a match, else, the expression is unbalanced
        for(int i=0; i<s.length(); ++i)
        {
            if ((s[i] == '(') || (s[i] == '[') || (s[i] == '{'))
            {
                stack.push(s[i]);
            }
            else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
            {
                top = stack.top();

                if (s[i] == ')' && top == '(')
                {
                    stack.pop();
                }
                else if (s[i] == ']' && top == '[')
                {
                    stack.pop();
                }
                else if (s[i] == '}' && top == '{')
                {
                    stack.pop();
                }
                else
                {
                    isBalanced = false;
                    break;
                }
            }
        }


        // checking if you stored in isBalanced the correct value
        if(isBalanced == solution)
        {
            cout << "line " << line_counter << ": OK [" << solution << " " << isBalanced << "]" << endl;
        }
        else
        {
            cout << "line " << line_counter << ": ERROR [" << solution << " " << isBalanced << "]" << endl;
        }
        line_counter++;
    }
}

