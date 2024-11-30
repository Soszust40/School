//CSE 232 Homework 11
//No loops
#ifndef header_hpp
#define header_hpp

#include <vector>
#include <string>

void SortByUppercase(std::vector<std::string>& words);
int SumOfOdd(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end);
std::string DoubleToPercentString(const std::vector<double>& doubles);

#endif


#include "header.hpp"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cassert>

void SortByUppercase(std::vector<std::string>& words) {
    std::stable_sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        std::string upper_a, upper_b;
        std::copy_if(a.begin(), a.end(), std::back_inserter(upper_a), ::isupper);
        std::copy_if(b.begin(), b.end(), std::back_inserter(upper_b), ::isupper);
        return upper_a < upper_b;
    });
}

int SumOfOdd(std::vector<int>::const_iterator begin, std::vector<int>::const_iterator end) {
    return std::accumulate(begin, end, 0, [](int sum, int num) {
        return sum + (num % 2 == 1 ? num : 0);
    });
}

std::string DoubleToPercentString(const std::vector<double>& doubles) {
    std::ostringstream oss;
    std::transform(doubles.begin(), doubles.end(), std::ostream_iterator<std::string>(oss, " "),
                   [](double d) {
                       int percent = static_cast<int>(d * 100);
                       return std::to_string(percent) + "%";
                   });
    return oss.str();
}

int main() {
    std::vector<std::string> words = {"wolf", "BanAna", "caRRot", "AprIcots", "BEets", "chiCkPeas", "orAngEs", "apple", "CAT", "dOG"};
    std::vector<std::string> expected = {"wolf", "apple", "orAngEs", "AprIcots", "BanAna", "BEets", "CAT", "chiCkPeas", "dOG", "caRRot"};
    SortByUppercase(words);
    assert(words == expected);

    std::vector<int> const numbers = {1, 2, 3, 4, 5, 6, 8, 5, 2, 2, 5, 101};
    assert(SumOfOdd(numbers.cbegin(), numbers.cend()) == 120);
    assert(SumOfOdd(numbers.begin() + 1, numbers.end() - 1) == 18);

    std::vector<double> const doubles = {1, 2, 100, 200, 12.3456, 4787, 0.123};
    assert(DoubleToPercentString(doubles) == "100% 200% 10000% 20000% 1234% 478700% 12% ");

    return 0;
}


 //Only use loops
#include <string>
#include <vector>

int Func(int a)
{
    std::vector<int> b(a);

    // Fill vector b with values from 12 to 12 + a
    for (int i = 0; i < a; ++i) {
        b[i] = 12 + i;
    }

    std::vector<int> c(b.size());

    // Reverse vector b and store it in vector c
    for (size_t i = 0; i < b.size(); ++i) {
        c[i] = b[b.size() - 1 - i];
    }

    // Perform the transformation
    for (size_t i = 0; i < b.size(); ++i) {
        b[i] = 2 * b[i] + c[i];
    }

    int count = 0;

    // Count the elements in vector b which contain '2' in their string representation
    for (size_t i = 2; i < b.size() - 2; ++i) {
        if (std::to_string(b[i]).find("2") != std::string::npos) {
            count++;
        }
    }

    return count;
}



//You need to write a function, named "MaxVector", that takes 2 arguments.
//Both of these arguments are vectors.
//The function should return a vector of a size equal to the longer of the two arguments.
//The returned vector will have the larger of the two elements from the arguments for each position.

#ifndef header_hpp
#define header_hpp

#include <vector>
#include <algorithm>
#include <string>

template<typename T>
std::vector<T> MaxVector(const std::vector<T>& vec1, const std::vector<T>& vec2) {
  size_t max_size = std::max(vec1.size(), vec2.size());
  std::vector<T> result(max_size);

  auto shorter_vec_size = std::min(vec1.size(), vec2.size());

  // Use std::transform to find maximum elements
  std::transform(vec1.begin(), vec1.begin() + shorter_vec_size, vec2.begin(), result.begin(),
                  [](const T& a, const T& b) { return std::max(a, b); });

  // Copy remaining elements from the longer vector
  const auto& longer_vec = (vec1.size() < vec2.size()) ? vec2 : vec1;
  std::copy(longer_vec.begin() + shorter_vec_size, longer_vec.end(), result.begin() + shorter_vec_size);

  return result;
}

#endif

