#include <iostream>
#include <stack>

using namespace std;

class BracketCheck;

ostream& operator<<(ostream &out, BracketCheck &check);

class BracketCheck {
    public:
        BracketCheck(string exp);
        bool isBalanced();
        int numBrackets();
        friend ostream& operator<<(ostream &out, BracketCheck &check);
    private:
        bool isBalancedVar;
        stack<char> pairs;
        int numBracketsVar = 0;
};

ostream& operator<< (ostream & out, BracketCheck & check) {
    if (check.isBalanced()) {
        out << "Balanced";
    } else {
        out << "Not Balanced";
    }
    return out;
}

BracketCheck::BracketCheck(string exp) {
    bool isBalancedLocally = true; // Set initial value to true
    for (const char c : exp) { // Loop through all characters in expression
        if (c == '(' || c == '[' || c == '{') { // If character is opening parenthesis
            pairs.push(c); // Add to the top of the stack
            continue;
        } 
        if (c == ')' || c == ']' || c == '}') {
            if (pairs.empty()) {
                isBalancedLocally = false;
                isBalancedVar = false;
                break;
            } else if (pairs.top() == '(' && c == ')') {
                pairs.pop();
                numBracketsVar++;
            } else if (pairs.top() == '[' && c == ']') {
                pairs.pop();
                numBracketsVar++;
            } else if (pairs.top() == '{' && c == '}') {
                pairs.pop();
                numBracketsVar++;
            } else {
                isBalancedLocally = false;
                isBalancedVar = false;
                break;
            }
        }
    }
    isBalancedVar = (pairs.empty() && isBalancedLocally);
}

bool BracketCheck::isBalanced() {
    return isBalancedVar;
}

int BracketCheck::numBrackets() {
    return numBracketsVar;
}