//CSE 232 Homework 8
//Pokemon Stats
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

struct Pokemon {
    std::string name;
    int stat; // Represents the general stat (HP, Speed, etc.)
};

int main() {
    std::string nameLine, statLine;
    std::getline(std::cin, nameLine);
    std::getline(std::cin, statLine);

    std::vector<Pokemon> pokemons;

    std::istringstream nameStream(nameLine.substr(5)); // Skip "Name:"
    std::istringstream statStream(statLine);

    std::string otherStat;
    std::getline(statStream, otherStat, ':'); // Get the text before the colon

    std::string nameToken, statToken;
    while (std::getline(nameStream, nameToken, ',') && std::getline(statStream, statToken, ',')) {
        pokemons.push_back({nameToken, std::stoi(statToken)});
    }

    std::cout << "Name," << otherStat << "," << std::endl;
    for (const auto& pokemon : pokemons) {
        std::cout << pokemon.name << "," << pokemon.stat << "," << std::endl;
    }

    auto maxStatPokemon = std::max_element(pokemons.begin(), pokemons.end(), [](const Pokemon& p1, const Pokemon& p2) {
        return p1.stat < p2.stat;
    });

    std::cout << "Max:" << std::endl;
    std::cout << maxStatPokemon->name << "," << maxStatPokemon->stat << "," << std::endl;

    return 0;
}



 //Traffic Program
#ifndef TRAFFIC_JAM_H
#define TRAFFIC_JAM_H

#include <vector>

bool AreRoadsBalanced(const std::vector<std::vector<bool>>& road_map);

#endif


#include "traffic_jam.h"

bool AreRoadsBalanced(const std::vector<std::vector<bool>>& road_map) {
    const int num_cities = road_map.size();

    // Initialize arrays to keep track of incoming and outgoing roads for each city
    std::vector<int> incoming(num_cities, 0);
    std::vector<int> outgoing(num_cities, 0);

    // Calculate incoming and outgoing roads for each city
    for (int i = 0; i < num_cities; ++i) {
        for (int j = 0; j < num_cities; ++j) {
            if (road_map[i][j]) {
                outgoing[i]++;
                incoming[j]++;
            }
        }
    }

    // Check if each city has the same number of incoming and outgoing roads
    for (int i = 0; i < num_cities; ++i) {
        if (incoming[i] != outgoing[i]) {
            return false;
        }
    }

    return true;
}


 //Print Code but stop after closing )
#ifndef Header_hpp
#define Header_hpp

#include <string>
#include <vector>

class LispExpression {
public:
    LispExpression(const std::string& expr);
    std::string PrettyPrint() const;

private:
    std::vector<std::string> tokens;
    void Tokenize(const std::string& expr);
    std::string Indent(int level) const;
};

#endif // LISPEXPRESSION_HPP


#include "header.hpp"
#include <sstream>
#include <iostream>

LispExpression::LispExpression(const std::string& expr) {
    Tokenize(expr);
}

void LispExpression::Tokenize(const std::string& expr) {
    std::istringstream iss(expr);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

std::string LispExpression::PrettyPrint() const {
    std::stringstream ss;
    int level = 0;
    bool stopPrinting = false;
    bool foundClosingParenthesis = false; // Flag to track if closing parenthesis is found
    bool reachedEndOfExpression = false; // Flag to track if end of expression is reached
    for (const auto& token : tokens) {
        if (stopPrinting) {
            break;
        }
        if (token == "(") {
            ss << Indent(level) << "(" << std::endl;
            level++;
        } else if (token == ")") {
            level--;
            if (level < 0) {
                stopPrinting = true;
                break; // Stop printing if more closing parentheses than opening ones
            }
            ss << Indent(level) << ")" << std::endl;
            foundClosingParenthesis = true; // Set the flag to true when closing parenthesis is found
        } else {
            ss << Indent(level) << token << std::endl;
        }

        // Check if reached end of expression after processing each token
        if (foundClosingParenthesis && level == 0) {
            reachedEndOfExpression = true;
        }

        // Stop printing if both closing parenthesis and end of expression are found
        if (foundClosingParenthesis && reachedEndOfExpression) {
            stopPrinting = true;
        }
    }
    return ss.str();
}

std::string LispExpression::Indent(int level) const {
    std::string indentation;
    for (int i = 0; i < level; ++i) {
        indentation += " ";
    }
    return indentation;
}


 //Price
#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>

class Price {
private:
    int dollars;
    int totalCents;
    int cents;

public:
    // Default constructor
    Price();

    // Converting constructor
    Price(double value);

    // Overloaded operators
    friend std::ostream& operator<<(std::ostream& os, const Price& price);
    friend Price operator+(const Price& lhs, const Price& rhs);
    friend Price& operator+=(Price& lhs, const Price& rhs);
    friend Price operator-(const Price& lhs, const Price& rhs);
    friend Price& operator-=(Price& lhs, const Price& rhs);
    friend std::istream& operator>>(std::istream& is, Price& price);
};

#endif

#include "header.hpp"
#include <cmath>

Price::Price() : dollars(0), cents(0) {}

Price::Price(double value) {
    dollars = static_cast<int>(value);
    totalCents = static_cast<int>(std::round(value * 100));
    cents = static_cast<int>(totalCents % 100);
}

std::ostream& operator<<(std::ostream& os, const Price& price) {
    os << "$" << price.dollars << ".";
    if (price.cents < 10)
        os << "0"; // add leading zero if necessary
    os << price.cents;
    return os;
}

Price operator+(const Price& lhs, const Price& rhs) {
    Price result;
    result.dollars = lhs.dollars + rhs.dollars;
    result.cents = lhs.cents + rhs.cents;
    if (result.cents >= 100) {
        result.dollars += result.cents / 100;
        result.cents %= 100;
    }
    return result;
}

Price& operator+=(Price& lhs, const Price& rhs) {
    lhs.dollars += rhs.dollars;
    lhs.cents += rhs.cents;
    if (lhs.cents >= 100) {
        lhs.dollars += lhs.cents / 100;
        lhs.cents %= 100;
    }
    return lhs;
}

Price operator-(const Price& lhs, const Price& rhs) {
    Price result;
    int total_cents_lhs = lhs.dollars * 100 + lhs.cents;
    int total_cents_rhs = rhs.dollars * 100 + rhs.cents;
    if (total_cents_lhs >= total_cents_rhs) {
        result.dollars = (total_cents_lhs - total_cents_rhs) / 100;
        result.cents = (total_cents_lhs - total_cents_rhs) % 100;
    } else {
        // Handle negative result by setting to zero
        result.dollars = 0;
        result.cents = 0;
    }
    return result;
}

Price& operator-=(Price& lhs, const Price& rhs) {
    int total_cents_lhs = lhs.dollars * 100 + lhs.cents;
    int total_cents_rhs = rhs.dollars * 100 + rhs.cents;
    if (total_cents_lhs >= total_cents_rhs) {
        lhs.dollars = (total_cents_lhs - total_cents_rhs) / 100;
        lhs.cents = (total_cents_lhs - total_cents_rhs) % 100;
    } else {
        // Handle negative result by setting to zero
        lhs.dollars = 0;
        lhs.cents = 0;
    }
    return lhs;
}

std::istream& operator>>(std::istream& is, Price& price) {
    char dollar_sign;
    is >> dollar_sign; // Read '$' sign
    is >> price.dollars;
    is.ignore(); // Ignore '.' separator
    is >> price.cents;
    return is;
}



 //Counter and adding
#ifndef header_hpp
#define header_hpp

#include <iostream>
#include <vector>
#include <string>

class Counter {
public:
  Counter();
  Counter(int initialValue);
  Counter(const Counter& other); // Copy Constructor
  Counter& operator=(const Counter& other); // Copy Assignment Operator
  int Value();
  Counter operator+(const Counter& other) const;
  friend std::ostream& operator<<(std::ostream& os, const Counter& counter);
  mutable std::vector<std::string> log_;

private:
  int value;
  int startValue;
};

#endif

#include "header.hpp"

Counter::Counter() : value(0), startValue(0) {
  log_.push_back("Default Constructor called.");
}

Counter::Counter(int initialValue) : value(initialValue), startValue(initialValue) {
  log_.push_back("Constructor called with a " + std::to_string(initialValue));
}

Counter::Counter(const Counter& other) : log_(other.log_), value(other.value), startValue(other.startValue) {
  log_.push_back("Copy Constructor called.");
}

Counter& Counter::operator=(const Counter& other) {
    if (this != &other) {
        value = other.value;
        startValue = other.startValue;
        log_ = other.log_;
        log_.push_back("= called.");
    }
    return *this;
}

int Counter::Value() {
  log_.push_back("Value called. Returned a " + std::to_string(value));
  return value--;
}

Counter Counter::operator+(const Counter& other) const {
  int sumInitialValue = startValue + other.startValue;
  int sumCurrentValue = value + other.value;

  Counter result(sumInitialValue);
  result.value = sumCurrentValue;

  result.log_.push_back("+ called.");
  return result;
}

std::ostream& operator<<(std::ostream& os, const Counter& counter) {
  os << "Counter(" << counter.startValue << ")@" << counter.value;
  counter.log_.push_back("<< called.");
  return os;
}

#include <iostream>
#include "header.hpp"

int main() {
    Counter c(6);
    std::cout << c.Value() << std::endl; // Prints 6
    std::cout << c.Value() << std::endl; // Prints 5
    return 0;
}
