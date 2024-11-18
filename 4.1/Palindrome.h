#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Palindrome {

    public:

        Palindrome(string sentance) : sentance(sentance){};
        bool isPalindrome() const;
        friend ostream& operator<< (ostream& out, const Palindrome& p);

    private:
        string sentance;
        string stripSentance() const;
};

string Palindrome::stripSentance() const {
    string clean = "";
    for (char c : sentance) {
        c = tolower(c);
        if (c >= 'a' && c <= 'z') {
            clean += c;
        }
    }
    return clean;
}

bool Palindrome::isPalindrome() const {
    string clean = stripSentance();
    stack<char> s;
    queue<char> q;

    for (char c: clean) {
        s.push(c);
        q.push(c);
    } 

    while (!s.empty()) {
        if (s.top() != q.front()) {
            return false;
        }
        s.pop();
        q.pop();
    } 
    return true;
}

ostream& operator<< (ostream& out, const Palindrome& p) {
    out << p.sentance << " is ";
    if (!p.isPalindrome()) {
        out << "not ";
    }
    out << "a palindrome";
    return out;
}