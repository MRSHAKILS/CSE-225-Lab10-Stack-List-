#include <iostream>
#include"stacktype.h"

using namespace std;


// Helper functions

bool is_operator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int apply_operator(int a, int b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        default: return 0;
    }
}

string infix_to_postfix(const string &infix) {
    StackType <char> s;
    string postfix = "";

    for (char ch : infix) {
        if (isdigit(ch)) {
            postfix += ch;
        } else if (is_operator(ch)) {
            while (!s.IsEmpty() && precedence(s.Top()) >= precedence(ch)) {
                postfix += s.Top();
                s.Pop();
            }
            s.Push(ch);
        } else if (ch == '(') {
            s.Push(ch);
        } else if (ch == ')') {
            while (!s.IsEmpty() && s.Top() != '(') {
                postfix += s.Top();
                s.Pop();
            }
            if (!s.IsEmpty() && s.Top() == '(') {
                s.Pop();
            }
        }
    }
    while (!s.IsEmpty()) {
        postfix += s.Top();
        s.Pop();
    }

    return postfix;
}

int evaluate_postfix(const string &postfix) {
    StackType<int> s;

    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.Push(ch - '0');
        } else if (is_operator(ch)) {
            int b = s.Top(); s.Pop();
            int a = s.Top(); s.Pop();
            s.Push(apply_operator(a, b, ch));
        }
    }

    return s.Top();
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);

    try {
        string postfix = infix_to_postfix(infix);
        int result = evaluate_postfix(postfix);
        cout << "Result: " << result << endl;
    } catch (const exception &e) {
        cout << "Invalid expression" << endl;
    }

    return 0;
}
