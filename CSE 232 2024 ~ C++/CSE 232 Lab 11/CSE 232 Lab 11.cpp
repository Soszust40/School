#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <numeric>
#include <algorithm>

void PassOrFail(std::vector<std::pair<std::string, int>>& v);

void ShiftRange(std::vector<int>& v, int left, int right);

void generateFibonacci(std::vector<int>& fib, int n);

std::vector<int> Fibonacci(int n);

int BinaryToInt(const std::string& binary_str);



#include "Generic.hpp"


void PassOrFail(std::vector<std::pair<std::string, int>>& v) {
    auto failedStudents = std::partition(v.begin(), v.end(),
        [](const auto& pair) {
            return pair.second >= 600;
        });;

    std::sort(v.begin(), failedStudents, [](const auto& a, const auto& b) {
        return a.first < b.first;
        });
    std::sort(failedStudents, v.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
        });
}

void ShiftRange(std::vector<int>& v, int left, int right) {
    std::sort(v.begin(), v.end());
    auto leftSide = std::lower_bound(v.begin(), v.end(), left);
    auto rightRight = std::upper_bound(v.begin(), v.end(), right);

    std::rotate(leftSide, rightRight, v.end());
}

void generateFibonacci(std::vector<int>& fib, int n) {
    if (n <= 0) return;
    if (n == 1) return;
    generateFibonacci(fib, n - 1);
    fib[n - 1] = fib[n - 2] + fib[n - 3];
}

std::vector<int> Fibonacci(int n) {
    std::vector<int> fib(n, 1);
    std::iota(fib.begin() + 2, fib.end(), 2);

    generateFibonacci(fib, n);

    return fib;
}

int BinaryToInt(const std::string& binary_str) {
    return std::accumulate(binary_str.begin(), binary_str.end(), 0,
        [](int sum, char c) {
            return sum * 2 + (c - '0');
        });
}