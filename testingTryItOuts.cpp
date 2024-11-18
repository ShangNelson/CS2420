#include <iostream>
#include <stack>
#include <queue>
using namespace std;

bool isPalindrome(string word, int first, int last ){
	if (first == last || first+1 == last) {
        return true;
    }
    if (word[first] != word[last]) {
        return false;
    }
    isPalindrome(word, first+1, last-1);
    return true;
}
//Facilitate Recursive method call
bool isPalindrome(string word){
    return isPalindrome(word, 0, word.length()-1);
}
int main(){
    string words[] = {"madam", "palindrome", "racecar"};
    for(int i = 0; i < 3; i++){
       cout << words[i] << ": " << (isPalindrome(words[i]) ? "Palindrome\n": "Not\n" );
    }
    return 0;
}


