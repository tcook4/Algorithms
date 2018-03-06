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


int main(){
    freopen("input_infix2postfix.txt", "r", stdin);
    string input;
    string solution;
    int line_counter = 0;
    char top;

    while(cin >> solution)
    {
        cin >> input;
        Stack<char> stack;
        string result;
        //The input file is in the format "expected_solution infix_expression", where expected_solution is the infix_expression in postfix format

        for(int i=0; i<input.length(); ++i)
        {
            if (isOperand(input[i]))
            {
                result+=input[i];
            }

            else
            {
                if (input[i] == '(')
                {
                    stack.push(input[i]);
                }
                else if (input[i] == ')')
                {
                    while (stack.top() != '(')
                    {
                        result+=stack.remove();
                    }

                    // Pop the '(' off the stack after we find it
                    stack.pop();
                }
                else if ((precedence(stack.top())) >= (precedence(input[i])))
                {
                    while (((precedence(stack.top())) >= (precedence(input[i]))) && (stack.size() >= 0))
                    {
                        result+=stack.remove();
                    }
                    stack.push(input[i]);
                }
                else
                {
                    stack.push(input[i]);
                }
            }


            // WRITE CODE HERE to store in 'result' the postfix transformation of 'input'
            cout << "result is now : " << result << endl;
        }
        while (stack.size() >= 0)
        {
            top = stack.top();
            result+=top;
            stack.pop();
        }

        // You need to do some extra stuff here to store in 'result' the postfix transformation of 'input'


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
