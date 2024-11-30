//CSE 232 Homeowrk 9
//ArrayToVector
#ifndef header_hpp
#define header_hpp

#include <vector>

template <typename T>
std::vector<T> ArrayToVector(T* arr, size_t size) {
    std::vector<T> result;
    for (size_t i = 0; i < size; ++i) {
        result.push_back(arr[i]);
    }
    delete[] arr;
    return result;
}

#endif


// DIDN'T NEED THE FILE (.cpp File)


// Note: This file is not tested by the autograder
#include <iostream>
#include <vector>
#include <cassert>
#include "header.hpp"

int main() {

  std::vector<int> const expected = {1, 45, -84, 0, 3, 2, 0};

    int * source = new int[expected.size()];
  for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
    source[i] = expected.at(i);
  }

  std::vector<int> const result = ArrayToVector(source, expected.size());

  assert(result.size() == expected.size());

  for (int i = 0; i < static_cast<int>(expected.size()); ++i) {
    assert(result.at(i) == expected.at(i));
  }
  assert(result == expected);

    return 0;
}


 //Copy Numbers until hit negative
#ifndef header_hpp
#define header_hpp

void CopyStockPrices(const double* source, double* destination);

#endif


#include <cstddef>

void CopyStockPrices(const double* source, double* destination) {
    // Copy valid stock prices until a negative value is encountered
    while (*source >= 0.0) {
        *destination = *source;
        ++source;
        ++destination;
    }
    // Copy the terminating negative value
    *destination = *source;
}



#include <iostream>
#include "header.hpp"

int main() {
    int size = 7;
    double source[] = {10.5, 7, 14, 0, 67, -4, 13};
    double destination[size] = {};
    CopyStockPrices(source, destination);
    for (int i = 0; i < size; ++i) {
        std::cout << destination[i] << std::endl;
    }
    return 0;
}


 //Copy Numbers based on size of array set by first value
#ifndef header_hpp
#define header_hpp

void CopyStockPrices(const double* source, double* destination);

#endif


#include <cstddef>

void CopyStockPrices(const double* source, double* destination) {
    for (int i = 0; i < source[0]; ++i) {
        *destination = *source;
        ++destination;
        ++source;
    }
  *destination = *source;
}



#include <iostream>
#include "header.hpp"

int main() {
    int size = 7;
    double source[] = {3, 1, 2, 3, 67, -4, 13};
    double destination[size] = {};
    CopyStockPrices(source, destination);
    for (int i = 0; i < size; ++i) {
        std::cout << destination[i] << std::endl;
    }
    return 0;
}


 //Fix Memory Leak
#pragma once

int SumOf5(int * array);


#include "header.hpp"

int SumOf5(int * array) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += array[i];
    }
  delete[] array; //ADDED LINE
    return sum;
}


#include <iostream>
#include "header.hpp"
int main() {
    int * array = new int[5];
    array[0] = 1;
    array[0] = 1;
    array[0] = 1;
    array[0] = 2;
    array[0] = 4;
    int result = SumOf5(array);
    std::cout << result << std::endl;
}


 //Every Other Value is Pushed Back
#ifndef header_hpp
#define header_hpp

#include <iostream>
#include <vector>
#include <sstream>

template <typename T>
class EveryOther {
private:
    std::vector<T> data_;
    bool addNext_; // Flag to track whether to add the next element

public:
    // Default constructor
    EveryOther() : addNext_(true) {}

    // Constructor with initializer list
    EveryOther(std::initializer_list<T> initList) : addNext_(true) {
        for (const auto& item : initList) {
            if (addNext_) {
                data_.push_back(item);
            }
            addNext_ = !addNext_; // Toggle the flag
        }
    }

    // Add an element to the end (only every other call does something)
    void push_back(const T& value) {
        if (addNext_) {
            data_.push_back(value);
        }
        addNext_ = !addNext_; // Toggle the flag
    }

    // Get the size of the container
    size_t size() const {
        return data_.size();
    }

  // Overload operator<< for printing
  friend std::ostream& operator<<(std::ostream& os, const EveryOther& eo) {
    os << "EveryOther(";
    for (size_t i = 0; i < eo.size(); ++i) {
        os << eo.data_[i];
        os << ", ";
    }
    os << ")";
    return os;
  }
};

#endif
