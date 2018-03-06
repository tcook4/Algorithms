#include "stack.hpp"

using namespace std;

// Auxiliary method, you probably find it useful
// Operands are all lower case and upper case characters
bool isOperand(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Auxiliary method, you probably find it useful
int precedence(char c)
{
    if(c == '+' || c == '-')
    {
        return 0;
    }
    if(c == '*' || c == '/')
    {
        return 1;
    }
    if(c == '^')
    {
        return 2;
    }
    return -1;
}


int main()
{
    freopen("input_infix2postfix.txt", "r", stdin);
    string input;
    string solution;
    int line_counter = 0;

    while(cin >> solution)
    {
        cin >> input;
        Stack<char> stack;
        string result;

        // Iterate through our expression
        for(int i=0; i<input.length(); ++i)
        {
            // If the character is an operand, append it to the result
            if (isOperand(input[i]))
            {
                result+=input[i];
            }

            // Operators get pushed to the stack
            else
            {
                // If we find an open parenthesis, push it to the stack
                if (input[i] == '(')
                {
                    stack.push(input[i]);
                }

                // If we find a closing parenthesis, pop the stack until we find the partner
                else if (input[i] == ')')
                {
                    while (stack.top() != '(')
                    {
                        result+=stack.remove();
                    }

                    // Pop the '(' off the stack after we find it
                    stack.pop();
                }

                // Pop operators with higher precidence before pushing
                else if ((precedence(stack.top())) >= (precedence(input[i])))
                {
                    while (((precedence(stack.top())) >= (precedence(input[i]))) && (stack.size() >= 0))
                    {
                        result+=stack.remove();
                    }
                    stack.push(input[i]);
                }

                // Otherwise, push the operator
                else
                {
                    stack.push(input[i]);
                }
            }
        }

        // Finish by popping all remaining operators
        while (stack.size() >= 0)
        {
            result+=stack.remove();
        }

        // Checking whether the result you got is correct
        if(solution == result)
        {
            cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
        }
        else
        {
            cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
        }
        line_counter++;
    }
}
