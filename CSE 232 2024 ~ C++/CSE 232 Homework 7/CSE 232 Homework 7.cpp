//CSE 232 Homework 7
//Writing a class
#include "Penultimate.hpp"

Penultimate::Penultimate(const std::string& initialString) : previousString(initialString) {}

std::string Penultimate::push_back(const std::string& newString) {
    std::string temp = previousString;
    previousString = newString;
    return temp;
}



#ifndef PENULTIMATE_HPP
#define PENULTIMATE_HPP

#include <string>

class Penultimate {
public:
    Penultimate(const std::string& initialString);
    std::string push_back(const std::string& newString);

private:
    std::string previousString;
};

#endif // PENULTIMATE_HPP


#include "Penultimate.hpp"
#include <string>
#include <cassert>

int main() {
  Penultimate p("first");
  std::string s = p.push_back("second"); // s is "first"
  assert(s == "first");
  p.push_back("Third"); // returns "second"
  s = p.push_back("last"); // returns "Third"
  assert(s == "Third");
}


 // Forget first time value is inputted
#ifndef FORGETFULVECTOR_HPP
#define FORGETFULVECTOR_HPP

#include <vector>

class ForgetfulVector {
public:
    ForgetfulVector();
    void push_back(int value);
    int at(size_t index) const;
    size_t size() const;

private:
    std::vector<int> data;
    std::vector<int> forgottenValues;
};

#endif



#include "ForgetfulVector.hpp"
#include <algorithm>

ForgetfulVector::ForgetfulVector() {}

void ForgetfulVector::push_back(int value) {
    if (std::find(data.begin(), data.end(), value) == data.end()) {
        // If the value is not already present in the data
        data.push_back(value);
    } else {
        // If the value is already present, but not in forgottenValues
        forgottenValues.push_back(value);
    }
}

int ForgetfulVector::at(size_t index) const {
    return forgottenValues.at(index);
}

size_t ForgetfulVector::size() const {
    return forgottenValues.size();
}



 //Checks if syntax is correct
#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>

bool myLinter(std::istream& input) {
    std::string line;
    std::stack<char> brackets;

    while (std::getline(input, line)) {
        // Trim leading whitespaces
        size_t startPos = line.find_first_not_of(" \t");
        if (startPos == std::string::npos)
            continue; // Empty line

        // Check if the line starts with 'S'
        if (line[startPos] != 'S')
            return false;

        // Check if the line ends with a valid character
        char lastChar = line.back();
        if (lastChar != ';' && lastChar != '{' && lastChar != '}' && lastChar != '(' && lastChar != ')')
            return false;

        // Count brackets and parentheses
        for (char c : line) {
            if (c == '{' || c == '(') {
                brackets.push(c);
            } else if (c == '}' || c == ')') {
                if (brackets.empty())
                    return false;
                char top = brackets.top();
                if ((c == '}' && top != '{') || (c == ')' && top != '('))
                    return false;
                brackets.pop();
            }
        }
    }

    // Check if there are unmatched brackets or parentheses
    return brackets.empty();
}

int main() {
    if (myLinter(std::cin))
        std::cout << "Code is valid.\n";
    else
        std::cout << "Code is invalid.\n";
    return 0;
}



 //Wordle Game
#include <iostream>
#include <string>
#include <vector>

bool checkGuess(const std::string& guess, const std::string& secretWord, std::string& result) {
    if (guess.size() != secretWord.size())
        return false;

    result = "";
    for (size_t i = 0; i < secretWord.size(); ++i) {
        if (guess[i] == secretWord[i]) {
            result += secretWord[i];
        } else if (secretWord.find(guess[i]) != std::string::npos) {
            result += '?';
        } else {
            result += '.';
        }
    }
    return result == secretWord;
}

int main() {
    std::cout << "Give me a secret word: " << std::endl;
    std::string secretWord;
    std::cin >> secretWord;

    std::vector<std::string> guesses;
    std::string guess;

    std::cout << "Give me a guess: " << std::endl;
    for (int i = 0; i < 6; ++i) {
        if (!(std::cin >> guess)) {
            std::cout << "You Lose." << std::endl;
            return 0;
        }
        guesses.push_back(guess);

        std::string result;
        if (checkGuess(guess, secretWord, result)) {
            std::cout << result << std::endl;
            std::cout << "You Win!" << std::endl;
            return 0;
        } else {
            std::cout << result << std::endl;
        }
        if (i < 5)
          std::cout << "Give me a guess: " << std::endl;
    }

    std::cout << "You Lose." << std::endl;
    return 0;
}
