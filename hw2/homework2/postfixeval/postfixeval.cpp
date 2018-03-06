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
        // The input file is in the format "expected_solution postfix_expression"

        for(int i=0; i<s.length(); ++i)
        {
           if ((s[i]-48 >= 0) && (s[i]-48 <= 9))
           {
               stack.push(s[i]-48);
           }
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
