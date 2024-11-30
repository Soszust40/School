//CSE 232 Homework 4
//Random Math Functions
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int Triple(int value){
  return (value*3);
}

int Closest_Multiple_Of_13(int value){
  return (round(value/13.0) * 13);
}

int main() {
  int input;
  cin >> input;
  cout << (input*2);

  return 0;
}



 //Replace spelled out numbers with numbers
#include <iostream>
#include <string>
#include <cctype>
using std::string;
std::string toUpperCase(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}
void To_Digits(std::string& input) {
    string real_output = input;
    string output = input;
    output = toUpperCase(output);

    size_t pos = 0;

    while ((pos = output.find("ZERO", pos)) != std::string::npos) {
        output.replace(pos, 4, "0");
        real_output.replace(pos, 4, "0");
    }
    pos = 0;

    while ((pos = output.find("ONE", pos)) != std::string::npos) {
        output.replace(pos, 3, "1");
        real_output.replace(pos, 3, "1");
    }
    pos = 0;

    while ((pos = output.find("TWO", pos)) != std::string::npos) {
        output.replace(pos, 3, "2");
        real_output.replace(pos, 3, "2");
    }
    pos = 0;

    while ((pos = output.find("THREE", pos)) != std::string::npos) {
        output.replace(pos, 5, "3");
        real_output.replace(pos, 5, "3");
    }
    pos = 0;

    while ((pos = output.find("FOUR", pos)) != std::string::npos) {
        output.replace(pos, 4, "4");
        real_output.replace(pos, 4, "4");
    }
    pos = 0;

    while ((pos = output.find("FIVE", pos)) != std::string::npos) {
        output.replace(pos, 4, "5");
        real_output.replace(pos, 4, "5");

    }
    pos = 0;

    while ((pos = output.find("SIX", pos)) != std::string::npos) {
        output.replace(pos, 3, "6");
        real_output.replace(pos, 3, "6");
    }
    pos = 0;

    while ((pos = output.find("SEVEN", pos)) != std::string::npos) {
        output.replace(pos, 5, "7");
        real_output.replace(pos, 5, "7");
    }
    pos = 0;

    while ((pos = output.find("EIGHT", pos)) != std::string::npos) {
        output.replace(pos, 5, "8");
        real_output.replace(pos, 5, "8");
    }
    pos = 0;

    while ((pos = output.find("NINE", pos)) != std::string::npos) {
        output.replace(pos, 4, "9");
        real_output.replace(pos, 4, "9");
    }
    input = real_output;
}


 //Factorio
#include <iostream>

double Centrifuge(int& time, int& ore, double* u238) {
    int cycles = std::min(time / 12, ore / 10); // Calculate maximum number of cycles
    double u235 = 0.0;

    // Perform cycles
    for (int i = 0; i < cycles; ++i) {
        ore -= 10;    // Consume 10 uranium ore per cycle
        time -= 12;   // Consume 12 units of time per cycle
        u235 += 0.007;  // Generate 0.007 units of enriched U235 per cycle
        *u238 += 0.993;  // Generate 0.993 units of depleted U238 per cycle
    }

    // Return the amount of U235 generated
    return u235;
}


 //Count if the letter at index is same as other words
#include <iostream>
#include <string>

std::string SharedLetters(std::string const & str1, std::string const str2, std::string const * const str3) {
    std::string result;
    int max_length = std::max({str1.length(), str2.length(), str3->length()});

    std::string padded_str1 = str1 + std::string(max_length - str1.length(), '0');
    std::string padded_str2 = str2 + std::string(max_length - str2.length(), '0');
    std::string padded_str3 = *str3 + std::string(max_length - str3->length(), '0');

    for (int i = 0; i < max_length; ++i) {
        int count = 0;
        if (padded_str1.at(i) == padded_str2.at(i) && padded_str1.at(i) != '0') count++;
        if (padded_str1.at(i) == padded_str3.at(i) && padded_str1.at(i) != '0') count++;
        if (padded_str2.at(i) == padded_str3.at(i) && padded_str2.at(i) != '0') count++;
        result += std::to_string(count) + ",";
    }

    return result;
}

int main() {
    std::string a, b, c;
    std::cin >> a >> b >> c;

    std::string result = SharedLetters(a, b, &c);
    std::cout << result << std::endl;

    return 0;
}



 //Find letter sandwiched by others
#include <iostream>
#include <string>

char * Sandwich(std::string & line, char * bread_ptr) {
    // Iterate through the string, starting from the second character
    for (int i = 1; i < static_cast<int>(line.length()) - 1; ++i) {
        // Check if the character before and after matches bread_ptr
        if (line[i - 1] == *bread_ptr && line[i + 1] == *bread_ptr) {
            // Return a pointer to the character at index i
            return &line[i];
        }
    }
    // Return nullptr if no sandwich is found
    return nullptr;
}

int main() {
    std::string line = "Char is a character";
    char bread = 'a';
    char * filling_ptr = Sandwich(line, &bread);
    std::cout << *filling_ptr << std::endl; // Should be r
}



 //Convert temp to different temp unit with different class
#include <iostream>

class Temperature {
private:
    double temperature;

public:
    // Constructor
    Temperature(double temp, char unit) {
        // Convert temperature to Celsius for internal representation
        if (unit == 'C')
            temperature = temp;
        else if (unit == 'F')
            temperature = (temp - 32.0) * 5.0 / 9.0;
        else if (unit == 'K')
            temperature = temp - 273.15;
        else if (unit == 'R')
            temperature = (temp - 491.67) * 5.0 / 9.0;
        else {
            std::cerr << "Invalid unit. Defaulting to Celsius." << std::endl;
            temperature = temp;
        }
    }

    // Methods to convert temperature to different units
    double AsCelsius() const {
        return temperature;
    }

    double AsFahrenheit() const {
        return temperature * 9.0 / 5.0 + 32.0;
    }

    double AsKelvin() const {
        return temperature + 273.15;
    }

    double AsRankine() const {
        return (temperature + 273.15) * 9.0 / 5.0;
    }
};

#include <iostream>
#include "temperature.cpp" // LAter you will be taught better ways to include files

int main() {
  Temperature t(13, 'C'); // 13.0 degrees C
  std::cout << t.AsKelvin() << std::endl; // Should return 286.15 as that is the temp in Kelvin.
}
