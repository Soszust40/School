//CSE 232 Homework 10
//Iterators
#include <vector>
#include <cassert>
#include <iostream>

std::vector<int>::const_iterator FindSmallestIndexRange(
    std::vector<int> const & data, int begin_pos, int end_pos) {
    std::vector<int>::const_iterator iter = data.cbegin() + begin_pos;
    std::vector<int>::const_iterator iter_smallest = iter;
    while (iter < data.cend() && iter <=  data.cbegin() + end_pos) {
        if (*iter < *iter_smallest) {
            iter_smallest = iter;
        }
        ++iter;
    }
    return iter_smallest;
}


using c_iter = std::vector<int>::const_iterator;
int main() {
    std::vector<int> data = {6, 1, 5, 4, 3, 2, 1};
    c_iter iter_smallest = FindSmallestIndexRange(data, 2, 5);
    std::cout << *iter_smallest << std::endl;
    assert(*iter_smallest == 2);
    data.at(5) = 7;
    std::cout << *iter_smallest << std::endl;
    assert(*iter_smallest == 2);
}


#pragma once

#include <vector>

std::vector<int>::const_iterator FindSmallestIndexRange(
    std::vector<int> const & data, int begin_pos, int end_pos);

template <typename Iterator>
void DoubleIteratorRange(Iterator begin, Iterator end) {
  for (Iterator iter = begin; iter != end; ++iter) {
    *iter *= 2;
  }
}



 //Replace Bad Words
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <cctype>
#include <set>
#include <iterator>
#include <algorithm>

std::string MakeLowercase(std::string str) { // Intentional Copy
    std::transform(str.begin(), str.end(), str.begin(),
        [](char c){return std::tolower(c);}
    );
    return str;
}

std::set<std::string> ReplacementCensor(std::istream & is, std::ostream & os, std::map<std::string, std::string> const & bad_to_good) {
    std::map<std::string, std::string> bad_lowercase_to_good;
    for (auto [bad, good]: bad_to_good) {
        std::string bad_lower = MakeLowercase(bad);
        bad_lowercase_to_good[bad_lower] = good;
    }

    // From https://stackoverflow.com/questions/3203452/how-to-read-entire-stream-into-a-stdstring
    std::string input_string(std::istreambuf_iterator<char>(is), {});

    std::set<std::string> words_replaced;
    for (auto const & [bad, good]: bad_lowercase_to_good) {
        std::string input_string_lowercase = MakeLowercase(input_string);
        for (std::string::size_type pos = input_string_lowercase.find(bad);
            pos != std::string::npos; pos = input_string_lowercase.find(bad)) {
            std::string bad_word_found = input_string.substr(pos, bad.length());
            words_replaced.insert(bad_word_found);
            input_string.replace(pos, bad.length(), good);
            input_string_lowercase = MakeLowercase(input_string);
        }
    }

    os << input_string;
    return words_replaced;
}


#pragma once

#include <map>
#include <set>
#include <string>
#include <iostream>

std::set<std::string> ReplacementCensor(std::istream & is, std::ostream & os, std::map<std::string, std::string> const & bad_to_good);


 //Reverse a Stack
#ifndef header_hpp
#define header_hpp

#include <stack>

template <typename T>
std::stack<T> reverse_stack(const std::stack<T>& input_stack) {
    std::stack<T> reversed_stack;

    // Copy elements from input_stack to reversed_stack
    std::stack<T> temp_stack = input_stack;
    while (!temp_stack.empty()) {
        reversed_stack.push(temp_stack.top());
        temp_stack.pop();
    }

    return reversed_stack;
}

#endif

