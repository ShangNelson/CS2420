#include <iostream>
#include "BracketCheck.h"

using namespace std;

bool check(string , string , bool );
bool checkVal(string, string, int);

int main()
{
    check ("Easy", "()", true);
    check ("Not Matched", "(}", false);
    check ("Mixed but valid", "({}[])", true);
    check ("Too Many Closing", "({}[])]", false);
    check ("Not Matched", "({)(})", false);
    check ("Too Many Opening", "{()", false);
    check ("Code", "if (num == 7) { cout << num; }", true);
    check ("Bad Code", "if (num == 7)  cout << num; }", false);
    checkVal ("Correct Bracket Count 1", "({[]})", 3);
    checkVal ("Correct Bracket Count 2", "if (this) then (that)", 2);
    checkVal ("Correct Bracket Count 3", "({)})", 0);
    checkVal ("Correct Bracket Count 4", "ThisHappenes()", 1);


    return 0;
}

bool check(string name, string expression, bool shouldBe){
    BracketCheck b(expression);
    if(shouldBe == b.isBalanced()){
        cout << "Passed: " << name << endl;
        return true;
    }
    else{
        cout << "Failed: " << name << " " << b << endl;
    }

    return false;
}

bool checkVal(string name, string expression, int count){
    BracketCheck b(expression);
    if(count == b.numBrackets()){
        cout << "Passed: " << name << endl;
        return true;
    }
    else{
        cout << "Failed: " << name << " " << b.numBrackets() << endl;
    }

    return false;
}

