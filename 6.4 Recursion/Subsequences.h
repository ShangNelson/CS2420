#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Subsequences;
ostream& operator<<(ostream&,vector<string>&);

class Subsequences {
    public: 
        Subsequences(string word) : word(word) {};
        bool isSubsequence(string sub, bool isSub);
        vector<string> getSubsequentWords();
        friend ostream& operator<<(ostream&, vector<string>&);
    private: 
        bool isSubsequence(string sub, string remainingWord);
        string word;
};

/**
 * @brief Generates a vector of subsequent words from a dictionary file.
 * 
 * This function reads words from the "dictionary.txt" file and filters
 * out those that are subsequences according to the isSubsequence function.
 * The resulting vector contains words that meet the specified criteria.
 *
 * @return A vector of subsequent words.
 */
vector<string> Subsequences::getSubsequentWords() {
    vector<string> allWords;
    string line;
    ifstream dictionary("dictionary.txt");
    if (dictionary.is_open()) {
        while (getline(dictionary,line)) {
            if (isSubsequence(line, false)) {
                allWords.push_back(line);
            }
        }
        dictionary.close();
    }
    return allWords;
}

/**
 * @brief Checks if one string is a subsequence of another.
 * 
 * This function determines if one string is a subsequence of another.
 * If 'isSub' is true, it checks if 'sub' is a subsequence of 'word';
 * otherwise, it checks if 'word' is a subsequence of 'sub'.
 *
 * @param sub The potential subsequence.
 * @param isSub If true, checks if 'sub' is a subsequence of 'word'; 
 *              otherwise, checks if 'word' is a subsequence of 'sub'.
 * @return True if the condition is met, false otherwise.
 */
bool Subsequences::isSubsequence(string sub, bool isSub) {
    if (isSub) {
        return isSubsequence(sub, word);
    } else {
        return isSubsequence(word, sub);
    }
}


/**
 * @brief Recursive function to check if one string is a subsequence of another.
 * 
 * This function recursively checks if 'sub' is a subsequence of 'remainingWord'.
 * It returns true if 'sub' is a subsequence, and false otherwise.
 *
 * @param sub The potential subsequence.
 * @param remainingWord The remaining portion of the word to check against.
 * @return True if 'sub' is a subsequence of 'remainingWord', false otherwise.
 */
bool Subsequences::isSubsequence(string sub, string remainingWord) {
    if (sub.length() <= 0) {
        return true;
    }
    if (remainingWord.length() <= 0 && sub.length() > 0) {
        return false;
    }
    //cout << sub << ": " << remainingWord << endl;
    if (tolower(sub[0]) == tolower(remainingWord[0])) {
        return isSubsequence(sub.substr(1), remainingWord.substr(1));
    } else {
        return isSubsequence(sub, remainingWord.substr(1));
    }
}

/**
 * @brief Overloaded output stream operator for vector<string>.
 * 
 * Outputs the elements of the vector<string> separated by "; ".
 *
 * @param out The output stream.
 * @param vec The vector<string> to output.
 * @return The output stream after printing the vector's elements.
 */
ostream& operator<<(ostream&out, vector<string>&vec) {
    for (string s : vec) {
        out << s << "; ";
    }
    return out;
}