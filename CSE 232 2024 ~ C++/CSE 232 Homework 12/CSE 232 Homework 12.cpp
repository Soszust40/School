//CSE 232 Homework 12
//Write a function named SumOfOdd that takes two iterators denoting a range (much like almost all if the algorithm functions) in a vector of ints.
//The function should return the sum of the odd integers in this range.
//
//Write a function named MakeComplex that a std::valarray of std::complex<int>.
//For any number that doesn’t have an imaginary component, replace it with the square root of negative one.

#ifndef header_hpp
#define header_hpp

#include <vector>
#include <numeric>
#include <complex>
#include <valarray>
#include <algorithm>
#include <iostream>
#include <iterator>

template<typename InputIt>
int SumOfOdd(InputIt first, InputIt last);

template<typename ComplexArray>
void MakeComplexHelper(ComplexArray& arr);

template<typename ComplexArray>
void MakeComplex(ComplexArray& arr);

#endif


#include "header.hpp"

template<typename InputIt>
int SumOfOdd(InputIt first, InputIt last) {
  return std::accumulate(first, last, 0, [](int sum, int val) {
      return sum + (val % 2 != 0 ? val : 0);
  });
}

template<typename ComplexArray, typename Iterator>
void MakeComplexHelper(ComplexArray& arr, Iterator it, size_t size) {
    if (size > 0) {
        if ((*it).imag() == 0) {
            (*it) = std::complex<int>(0, 1); // Replace with sqrt(-1)
        }
        MakeComplexHelper(arr, ++it, size - 1);
    }
}

template<typename ComplexArray>
void MakeComplex(ComplexArray& arr) {
    MakeComplexHelper(arr, std::begin(arr), arr.size());
}

int main() {
    std::vector<int> const numbers = {1, 2, 3, 4, 5, 6, 8, 5, 2, 2, 5, 101};
    std::cout << SumOfOdd(numbers.cbegin(), numbers.cend()) << std::endl;
    std::cout << SumOfOdd(numbers.begin(), numbers.end()) << std::endl;

  std::valarray<std::complex<int>> complex_numbers = {{{1, 2}, {3, 0}, {0, 7}, {-45, -68}}};
  MakeComplex(complex_numbers);
  std::ranges::copy(complex_numbers, std::ostream_iterator<std::complex<int>>(std::cout, " "));
  // (1,2) (0,1) (0,7) (-45,-68)

}


 //Match and Find Random Number Seed
#include <iostream>
#include <random>
#include <vector>
#include <sstream>

int main() {
    std::string inputString;
    std::getline(std::cin, inputString);

    std::vector<int> input;
    std::istringstream iss(inputString);
    std::string token;
    while (iss >> token) {
        for (size_t i = 0; i < token.length(); i += 2) {
            std::string pair = token.substr(i, 2);
            int num = std::stoi(pair);
            input.push_back(num);
        }
    }

    for (int s = 0; s <= 1000; ++s) {
        std::mt19937_64 rng(s);
        std::uniform_int_distribution<int> distribution(10, 99);
        std::vector<int> generated(10);
        for (int i = 0; i < 10; ++i)
            generated[i] = distribution(rng);

        if (generated == input) {
            std::cout << "Seed: " << s << std::endl;
            std::mt19937_64 rng(s);
            for (int i = 0; i < 20; ++i)
               std::cout << distribution(rng) << " ";

            return 0;
        }
    }

    std::cout << "Seed not found!" << std::endl;
    return 1;
}


//The function should return a vector of ints representing the sampled population.
//The function should use std::mt19937_64 to generate random indices using the provided seed.

#pragma once

#include <vector>
#include <cstdint>

std::vector<int> SampleWithReplacement(std::vector<int> const & population, int n, std::uint64_t seed);


#include "header.hpp"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
#include <sstream>
#include <ranges>

std::vector<int> SampleWithReplacement(std::vector<int> const & population, int n, uint64_t seed) {
    // Create a random number generator with the provided seed
    std::mt19937_64 rng(seed);

    // Initialize a vector to store the sampled population
    std::vector<int> sampled_population;

    // Sample with replacement
    for (int i = 0; i < n; ++i) {
        // Generate a random index
        std::uniform_int_distribution<int> dist(0, population.size() - 1);
        int random_index = dist(rng);

        // Add the sampled element to the result
        sampled_population.push_back(population[random_index]);
    }

    return sampled_population;
}

int main() {
    std::vector<int> const population = {1, 2, 3, 4, 5, 5, 5, 5, 5, 5};
    std::vector<int> sample = SampleWithReplacement(population, 20, 123);
  std::ranges::copy(sample, std::ostream_iterator<int>(std::cout, " "));
  // 4 5 5 5 2 2 5 3 5 5 3 5 1 5 5 5 5 5 4 5

}