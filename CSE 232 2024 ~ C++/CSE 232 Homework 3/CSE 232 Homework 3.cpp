//CSE 232 Homework 3
//Add the sum of Additive Root
#include <iostream>

int calculatePairedAdditiveRoot(int num) {
    while (num >= 100) {
        int sum = 0;

        while (num > 0) {
            sum += num % 100; // Add the pair of digits
            num /= 100; // Move to the next pair of digits
        }
        num = sum;
    }
    return num;
}

int main() {
    int num;

    while (std::cin >> num) {
        int pairedAdditiveRoot = calculatePairedAdditiveRoot(num);
        std::cout << pairedAdditiveRoot << std::endl;
    }

    return 0;
}



 //Print '_' if the char is below the char before it
#include <iostream>

int main() {
    char prevChar = '\n'; // Initialize to newline character

    //std::cout << "Enter a string (terminate with EOF or Ctrl+D): ";

    char currentChar;
    while (std::cin.get(currentChar)) {
        // Output newline character and the first character of each line
        if (currentChar == '\n' || prevChar == 0) {
            std::cout.put(currentChar);
        }
        // Output characters whose ASCII values are strictly larger than the character before it
        else if (currentChar > prevChar) {
            std::cout.put(currentChar);
        }
        // Replace characters equal or less than their predecessor with an underscore
        else {
            std::cout.put('_');
        }

        prevChar = currentChar;
    }

    return 0;
}


 //Print first charcter of each word
#include <iostream>
#include <cctype>

int main() {
    //std::cout << "Enter a string: ";

    char prevChar = ' '; // Initialize to a non-alphabetic character

    char currentChar;
    while (std::cin.get(currentChar)) {
        if (isalpha(currentChar) && !isalpha(prevChar)) {
            // Print the first letter of each word
            std::cout.put(currentChar);
        }

        prevChar = currentChar;
    }

    return 0;
}


 //Times Tables
#include <iostream>

void printMultiplicationTable(int startRow, int endRow, int startCol, int endCol) {
    for (int i = startRow; i <= endRow; ++i) {
        for (int j = startCol; j <= endCol; ++j) {
            std::cout << i << "*" << j << "=" << (i * j);
            if (j < endCol) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    int startRow, endRow, startCol, endCol;

    // Input ranges
    std::cin >> startCol >> endCol;
    std::cin >> startRow >> endRow;

    // Print multiplication table within the specified range
    printMultiplicationTable(startRow, endRow, startCol, endCol);

    return 0;
}


 //Print words that have more than five letters in the word
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

int main() {
    std::vector<std::string> lines;

    // Read input lines
    std::string line;
    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    // Filter and print words with length 5 or greater
    for (const auto& line : lines) {
        std::istringstream iss(line);
        std::vector<std::string> words(std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{});

        for (const auto& word : words) {
            if (word.length() >= 5) {
                std::cout << word << " ";
            }
        }
        std::cout << std::endl;  // Preserve the newline character
    }

    return 0;
}

