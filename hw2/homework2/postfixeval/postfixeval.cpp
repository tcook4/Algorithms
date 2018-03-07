/* Author: Tyler Cook
 * Date: March 7th, 2018
 * UNT CSCE 3110 - Homework 2
 * Description: This program evaluates expressions given in postfix format.
 */

#include "stack.hpp"

using namespace std;

int main()
{
    freopen("input_postfixEval.txt", "r", stdin);
    string s;
    int solution;
    int line_counter = 0;
    int temp1, temp2, temp3;

    while(cin >> solution)
    {
        cin >> s;
        Stack<int> stack;

        // Iterate through our expression
        for(int i=0; i<s.length(); ++i)
        {
            // Push operands to the stack
           if ((s[i]-48 >= 0) && (s[i]-48 <= 9))
           {
               stack.push(s[i]-48);
           }

           // If operator, pop operands and evaluate, and push result back on to stack
           else
           {
               switch(s[i])
               {
               case '+':
                   temp1 = stack.remove();
                   temp2 = stack.remove();
                   temp3 = temp2 + temp1;
                   stack.push(temp3);
                   break;

               case '-':
                   temp1 = stack.remove();
                   temp2 = stack.remove();
                   temp3 = temp2 - temp1;
                   stack.push(temp3);
                   break;

               case '*':
                   temp1 = stack.remove();
                   temp2 = stack.remove();
                   temp3 = temp2 * temp1;
                   stack.push(temp3);
                   break;

               case '/':
                   temp1 = stack.remove();
                   temp2 = stack.remove();
                   temp3 = temp2 / temp1;
                   stack.push(temp3);
                   break;

               case '^':
                   temp1 = stack.remove();
                   temp2 = stack.remove();
                   temp3 = temp2 ^ temp1;
                   stack.push(temp3);
                   break;
               }
           }
        }

        // Checking whether the value you calculated is correct ...
        int value = stack.top();

        if(solution == value)
        {
            cout << "line " << line_counter << ": OK [" << solution << " " << value << "]" << endl;
        }
        else
        {
            cout << "line " << line_counter << ": ERROR [" << solution << " " << value << "]" << endl;
        }
        line_counter++;
    }
}
