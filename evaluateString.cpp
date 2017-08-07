/*
Solve the arithmetic expression evaluation problem.
reference: http://www.geeksforgeeks.org/expression-evaluation/
           https://en.wikipedia.org/wiki/Shunting-yard_algorithm


input: an Infix Expression, operands are non-negative integers
output: result of evaluation of expression
*/

#include <iostream>
#include <stack>
#include <string>
#include <assert.h>
using namespace std;


// Returns true if 'op2' has higher or same precedence as 'op1',
// otherwise returns false.
bool hasPrecedence(char op1, char op2) {
    if (op2 == '(' || op2 == ')')
        return false;
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return false;
    else
        return true;
}

// A utility method to apply an operator 'op' on operands 'a' 
// and 'b'. Return the result.
int applyOp(char op, int b, int a) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        assert(b!=0);
        return a / b;
    }
    return 0;
}

int evaluate(string exp) {
    // Stack for numbers: 'values'
    stack<int> values;
    // Stack for Operators: 'ops'
    stack<char> ops;

    for (size_t i = 0; i < exp.size(); i++) {
        // Current token is a whitespace, skip it
        if (exp[i] == ' ') continue;

        // Current token is a number, push it to stack for numbers
        else if (exp[i] >= '0' && exp[i] <= '9') {
            string tmp = exp.substr(i);
            size_t offset;
            values.push(stoi(tmp, &offset));
            i += ( offset -1);
        }

        // Current token is an opening brace, push it to 'ops'
        else if (exp[i] == '(') ops.push(exp[i]);

        // Closing brace encountered, solve entire brace
        else if (exp[i] == ')') {
            while (ops.top() != '(') {
                int val1 = values.top(); values.pop();
                int val2 = values.top(); values.pop();
                values.push( applyOp(ops.top(), val1, val2) );
                ops.pop();
            }
            ops.pop();
        }

        // Current token is an operator.
        else if (exp[i] == '+' || exp[i] == '-' ||
                 exp[i] == '*' || exp[i] == '/') {
            // While top of 'ops' has same or greater precedence to current
            // token, which is an operator. Apply operator on top of 'ops'
            // to top two elements in values stack
            while (!ops.empty() && hasPrecedence(exp[i], ops.top())) {
                int val1 = values.top(); values.pop();
                int val2 = values.top(); values.pop();
                values.push( applyOp(ops.top(), val1, val2) );
                ops.pop();
            }
            // Push current token to 'ops'.
            ops.push(exp[i]);
        }
    }

    // Entire expression has been parsed at this point, apply remaining
    // ops to remaining values
    while (!ops.empty()) {
        int val1 = values.top(); values.pop();
        int val2 = values.top(); values.pop();
        values.push( applyOp(ops.top(), val1, val2) );
        ops.pop();
    }
    // Top of 'values' contains result, return it
    return values.top();
}


int main() {
    string s;
    cout<<"Please input an expression, press Enter to complete, press q to exit:"<<endl;
    while( getline(cin, s) && s.find('q')== string::npos) {
        cout<<s<<endl;
        cout<<evaluate(s)<<endl;
    }
    return 0;
}
