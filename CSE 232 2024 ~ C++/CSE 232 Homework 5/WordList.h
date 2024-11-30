#pragma once
#ifndef WordList_H
#define WordList_H

#include <string>

bool AtListPosition(const std::string& wordList, const std::string& word, size_t position);

size_t FindInList(const std::string& wordList, const std::string& word, size_t startPos);

std::string GetFirstInList(const std::string& wordList, std::string* word1, std::string* word2);

size_t CountInList(const std::string& wordList, const std::string& word);

#endif // WordList_H
