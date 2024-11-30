//CSE 232 Homework 2
//Count all the "MSU" letters in an input
#include <iostream>
#include <cctype>

int main() {
    char ch;
    int count = 0;

    //std::cout << "Enter a string (End with a period): ";

    while (std::cin.get(ch) && ch != '.') {
        // Check if the character is M, S, or U (case-insensitive)
        if (std::toupper(ch) == 'M' || std::toupper(ch) == 'S' || std::toupper(ch) == 'U') {
            count++;
        }
    }

    std::cout << "The count of letters (\"MSU\") is " << count << "." << std::endl;

    return 0;
}


 //Add the sum of intergers in an input
#include <iostream>

int main() {
    int sum = 0;
    int x;

    std::cout << "Enter integers: ";

    while (std::cin >> x) {
        // Add the sum of entered integers
        sum += x;
    }

    std::cout << sum << std::endl;

    return 0;
}


 //Check which metric measurment is bigger
#include <iostream>
#include <sstream>
#include <string>

double convertToMeters(double distance, const std::string& unit) {
    if (unit == "mm") {
        return distance / 1000.0;
    }
    else if (unit == "cm") {
        return distance / 100.0;
    }
    else if (unit == "m") {
        return distance;
    }
    else if (unit == "km") {
        return distance * 1000.0;
    }
    else {
        // Default case (invalid unit), treat as meters
        return distance;
    }
}

int main() {
    std::string input;
    //std::cout << "Enter pairs of metric distances: ";

    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        double distance1, distance2;
        std::string unit1, unit2;

        // Read the pair of metric distances
        iss >> distance1 >> unit1 >> distance2 >> unit2;

        // Convert distances to meters for comparison
        double meters1 = convertToMeters(distance1, unit1);
        double meters2 = convertToMeters(distance2, unit2);

        // Check and print if the first distance is larger than the second
        if (meters1 > meters2) {
            std::cout << distance1 << unit1 << " is larger than " << distance2 << unit2 << std::endl;
        }
        else if (meters1 < meters2) {
            std::cout << distance1 << unit1 << " is smaller than " << distance2 << unit2 << std::endl;
        }
        else {
            std::cout << distance1 << unit1 << " is the same as " << distance2 << unit2 << std::endl;
        }
    }

    return 0;
}


 //Biggest difference between three numbers
#include <iostream>
#include <cstdlib>

int main() {
    int num1, num2, num3;

    //std::cout << "Enter three integers: ";

    while (std::cin >> num1 >> num2 >> num3) {
        // Calculate absolute differences
        int diff1 = std::abs(num1 - num2);
        int diff2 = std::abs(num1 - num3);
        int diff3 = std::abs(num2 - num3);

        // Find the smallest difference
        int minDiff = std::min({ diff1, diff2, diff3 });

        // Print the smallest difference
        std::cout << "The smallest diff of " << num1 << ", " << num2 << ", and " << num3 << " is " << minDiff << "." << std::endl;
    }

    return 0;
}


 //Stop loop if the char M, S, U are found in that order
// Example 3.6
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <iomanip>
using std::noskipws;
using std::setw;

int main() {
  char C;               // Input character
  int char_count = 0,   // Number of characters in input stream
      line_count = 0,   // Number of newlines
      white_count = 0,  // Number of whitespace characters
      digit_count = 0,  // Number of digits
      other_count = 0;  // Number of other characters
  int breakCounter = 0;

  cin >> noskipws;

  while (cin >> C && breakCounter < 3) {
    ++char_count;  // Increment overall character count
    switch (C) {   // Classify each character
      case '\n':   // Newline
        ++line_count;
        [[fallthrough]]; // Added to indicate that fallthrough is expected
      case ' ':  // White space (newline, blank or tab)
      case '\t':
        ++white_count;
        break;
      case '0':  // Decimal digit
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        ++digit_count;
        break;
      default:  // Other character
        if (C == 'M' && breakCounter == 0){
          breakCounter++;
        }
        else if (C == 'S' && breakCounter == 1){
          breakCounter++;
        }
        else if (C == 'U' && breakCounter == 2){
          breakCounter++;

        }
        else {
          breakCounter = 0;
        }
        ++other_count;
        break;
    }
  }

  cout << endl;
  cout << "Newlines:   " << setw(5) << line_count << endl;
  cout << "Whitespace: " << setw(5) << white_count << endl;
  cout << "Digits:     " << setw(5) << digit_count << endl;
  cout << "Other:      " << setw(5) << other_count << endl;
  cout << "Total:      " << setw(5) << char_count << endl;
  cout << endl;
}


//Important Code
#include <iostream>
#include <sstream>
#include <string>
int main() {
    std::string input;
    //std::cout << "Enter pairs of metric distances: ";

    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        double distance1, distance2;
        std::string unit1, unit2;

        // Read the pair of metric distances
        iss >> distance1 >> unit1 >> distance2 >> unit2;

        //Print the numbers
        std::cout << distance1 << unit1 << " and " << distance2 << unit2 << std::endl;

        return 0;
    }
}