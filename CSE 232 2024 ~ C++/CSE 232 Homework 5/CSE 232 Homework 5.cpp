#include <iostream>
#include <string>
#include <cctype>
#include "WordList.h"

// Function to check if a word appears at a specific position in a word list
// Only returns true if the word is found exactly at the specified position and is not a substring of a longer word
bool AtListPosition(const std::string& wordList, const std::string& word, size_t position) {
    // Check if the word fits in the word list starting from the given position
    if (position + word.size() <= wordList.size()) {
        // Compare the substring of wordList starting from the given position with the word
        if (wordList.substr(position, word.size()) == word) {
            // Check if it's a whole word match (i.e., not a substring)
            if ((position == 0 || !std::isalnum(wordList[position - 1])) &&
                (position + word.size() == wordList.size() || !std::isalnum(wordList[position + word.size()]))) {
                return true; // Return true if it's a whole word match
            }
        }
    }
    return false;
}

// Function to find the first occurrence of a word in a word list starting at position 0
size_t FindInList(const std::string& wordList, const std::string& word, size_t startPos = 0) {
    for (size_t i = startPos; i < wordList.size(); ++i) {
        if (AtListPosition(wordList, word, i))
            return i;
    }
    return std::string::npos;
}

// Function to determine which of two words appears first in a word list
// Also returns "N/A" if neither word is found in the word list
std::string GetFirstInList(const std::string& wordList, std::string* word1, std::string* word2) {
    size_t pos1 = FindInList(wordList, *word1); // Find position of word1
    size_t pos2 = FindInList(wordList, *word2); // Find position of word2
    if (pos1 == std::string::npos && pos2 == std::string::npos)
        return "N/A"; // Return "N/A" if neither word is found
    else if (pos1 == std::string::npos)
        return *word2; // Return word2 if word1 is not found
    else if (pos2 == std::string::npos)
        return *word1; // Return word1 if word2 is not found
    else
        return (pos1 < pos2) ? *word1 : *word2; // Return the word that appears first in the list
}

// Function to count the number of times a word appears in a word list
size_t CountInList(const std::string& wordList, const std::string& word) {
    size_t count = 0;
    size_t pos = 0;
    while ((pos = FindInList(wordList, word, pos)) != std::string::npos) {
        // Ensure it's a whole word match
        if ((pos == 0 || !std::isalnum(wordList[pos - 1])) &&
            (pos + word.size() == wordList.size() || !std::isalnum(wordList[pos + word.size()]))) {
            count++; // Increment count if it's a whole word match
            pos += word.size(); // Move past the current match to avoid infinite loop
        }
        else {
            pos++;
        }
    }
    return count;
}



int main() {
    // Read the keywords from input
    std::string keyword1, keyword2;
    std::cin >> keyword1 >> keyword2;

    std::string wordList;
    // Read each word list and process it
    while (std::cin >> wordList) {
        // Count occurrences of keyword1 and keyword2 in the word list
        size_t count1 = CountInList(wordList, keyword1);
        size_t count2 = CountInList(wordList, keyword2);
        // Determine which keyword appears first in the word list
        std::cout << GetFirstInList(wordList, &keyword1, &keyword2) << " " << count1 << " " << count2 << std::endl;
    }

    return 0;
}