//CSE 232 Homework 6
//Sum by Index
#include <iostream>
#include <vector>

std::vector<int> SumByIndex(const std::vector<std::vector<int>>& input) {
    // Determine the size of the output vector based on the maximum subvector size
    size_t maxSubvectorSize = 0;
    for (const auto& subvector : input) {
        maxSubvectorSize = std::max(maxSubvectorSize, subvector.size());
    }

    // Initialize the output vector with zeros
    std::vector<int> result(maxSubvectorSize, 0);

    // Sum the elements from each subvector
    for (const auto& subvector : input) {
        for (size_t i = 0; i < subvector.size(); ++i) {
            result[i] += subvector[i];
        }
    }

    return result;
}


 //Repeat Twice
#include "header.hpp"

int Repeat(int num) {
    return num * 2;
}

std::string Repeat(char ch) {
    return std::string(2, ch);
}

std::string Repeat(const std::string& str) {
    return str + " " + str;
}


#ifndef header_H
#define header_H

#include <string>

int Repeat(int num);
std::string Repeat(char ch);
std::string Repeat(const std::string& str);

#endif


 //Seats and Organizing Vector
#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

struct Point {
    int x;
    int y;
};

int calculateValue(Point seat, const vector<Point>& superFans) {
    int stageDistance = 100 - seat.y * 5;
    int totalValue = stageDistance;

    for (const Point& fan : superFans) {
        int distance = abs(fan.x - seat.x) + abs(fan.y - seat.y);

        if (distance == 0)
            totalValue -= 60;
        else if (distance == 1)
            totalValue -= 40;
        else if (distance == 2)
            totalValue -= 20;
    }

    return totalValue;
}

vector<Point> parseSuperFans(const string& input) {
    vector<Point> superFans;
    stringstream ss(input);
    char discard;
    int x, y;

    while (ss >> discard >> x >> discard >> y >> discard) {
        superFans.push_back({x, y});
    }

    return superFans;
}

int main() {
    string superFansInput;

    vector<Point> superFans;
    while (getline(cin, superFansInput) && superFansInput != "done") {
        vector<Point> parsedFans = parseSuperFans(superFansInput);
        superFans.insert(superFans.end(), parsedFans.begin(), parsedFans.end());
    }

    const int rows = 10;
    const int cols = 20;

    for (int y = rows - 1; y >= 0; --y) {
        for (int x = 0; x < cols; ++x) {
            Point seat = {x, y};
            int value = calculateValue(seat, superFans);

            bool isSuperFanSeat = false;
            for (const Point& fan : superFans) {
                if (fan.x == seat.x && fan.y == seat.y) {
                    isSuperFanSeat = true;
                    break;
                }
            }

            if (isSuperFanSeat)
                cout << "   *";
            else {
              if (y == 0 && value == 100) cout << " " << value;
              else if (value < -10) cout << " " << value;
              else if (value < -99) cout << "" << value;
              else if (value < 10 && value >= 0) cout << "   " << value;
              else cout << "  " << value;
            }
            cout << ",";
        }
        cout << endl;
    }

    return 0;
}


 //Count Exceptions
#include <vector>
#include <string>
#include <stdexcept>
#include "name_checker.hpp"

std::vector<int> CountExceptions(const std::vector<std::string>& input) {
    int invalidArgumentCount = 0;
    int lengthErrorCount = 0;
    int outOfRangeCount = 0;

    for (const std::string& title : input) {
        try {
            CheckName(title);
        } catch (const std::invalid_argument& e) {
            // Catch and count invalid_argument exceptions
            invalidArgumentCount++;
        } catch (const std::length_error& e) {
            // Catch and count length_error exceptions
            lengthErrorCount++;
        } catch (const std::out_of_range& e) {
            // Catch and count out_of_range exceptions
            outOfRangeCount++;
        }
    }
    return {invalidArgumentCount, lengthErrorCount, outOfRangeCount};
}


 //Add Numbers in Vector
#include <iostream>
#include <vector>

int SumButScared(const std::vector<int>& input){
  int addedVector = 0;
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] % 13 == 0){
      throw std::invalid_argument("Multiple of 13");
    }
    addedVector += input[i];
  }
  return addedVector;
}
