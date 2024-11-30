#pragma once

#include <iostream>
#include <vector>

// A Table of integer values.
class Table {
private:
	using row_t = std::vector<int>;  // Each row is a regular vector of int.
	std::vector<row_t> table_;       // Table is a vector of rows.
	size_t width_;                   // How wide is table_ (how many columns)?
	size_t height_;                  // How high is table_ (how many rows)?

public:
	// table will be width x height, default val is 0
	Table(size_t width, size_t height, int val = 0);

	// Pre-made member functions to access the width and height variables.
	size_t GetWidth() const { return width_; }
	size_t GetHeight() const { return height_; }

	// Function to print the tables's contents to a provided output stream.
	void PrintTable(std::ostream&) const;

	// range from low to high, seed has default of 0
	void FillRandom(int low, int high, int seed = 0);

	// Accessors to get and set values.
	bool SetValue(size_t col, size_t row, int val);
	int GetValue(size_t col, size_t row) const;
};


#include "Table.hpp"
#include <random>
#include <iostream>

Table::Table(size_t width, size_t height, int val) : width_(width), height_(height)
// PLACE A ':' HERE FOLLOWED BY ANY MEMBER VARIABLE INITIALIZIONS
{
	table_.resize(height);
	for (auto& row : table_) {
		row.resize(width, val);
	}
}

// WRITE THE DEFINITION FOR Table::PrintTable
void Table::PrintTable(std::ostream& os) const {
	for (const auto& row : table_) {
		for (const auto& cell : row) {
			os << cell << ", ";
		}
		os << std::endl;
	}
}

// WRITE THE DEFINITION FOR Table::FillRandom
void Table::FillRandom(int low, int high, int seed) {
	//Create Random Number
	std::mt19937 generator(seed);
	std::uniform_int_distribution<int> distribution(low, high);
	for (auto& row : table_) {
		for (auto& cell : row) {
			cell = distribution(generator);
		}
	}
}

// WRITE THE DEFINITION FOR Table::SetValue
bool Table::SetValue(size_t col, size_t row, int val) {
	if (col < width_ && row < height_) {
		table_[row][col] = val;
		return true;
	}
	//throw std::out_of_range("Too High of Set Value");
	return false;
}

// WRITE THE DEFINITION FOR Table::GetValue
int Table::GetValue(size_t col, size_t row) const {
	if (col < width_ && row < height_) {
		return table_[row][col];
	}
	throw std::out_of_range("Too High of Get Value");
}


#include <exception>
#include <iostream>
#include "Table.hpp"

int main() {
	std::cout << std::boolalpha;

	Table my_table(5, 5);
	std::cout << "Initial Table:\n";
	my_table.PrintTable(std::cout);
	std::cout << std::endl;

	my_table.FillRandom(1, 10);
	std::cout << "Random Table:\n";
	my_table.PrintTable(std::cout);
	std::cout << std::endl;

	bool result_bool = my_table.SetValue(100, 100, 100);
	std::cout << "Set illegal value (should return false). Result: " << result_bool << std::endl;
	std::cout << std::endl;

	int result_int = my_table.GetValue(3, 2);
	std::cout << "Value at 3,2: " << result_int << std::endl;
	try {
		result_int = my_table.GetValue(100, 100);
	}
	catch (std::out_of_range& e) {
		std::cout << "Correct - threw out-of-range exception!" << std::endl;
	}
	std::cout << std::endl;

	for (int i = 0; i < 5; i++) {
		result_bool = my_table.SetValue(i, i + 1, i * i);
		std::cout << "Set " << i << "," << (i + 1) << " to " << (i * i);
		if (!result_bool) std::cout << " (failed)";
		std::cout << "\n";
	}

	std::cout << "\nFinal Table:\n";
	my_table.PrintTable(std::cout);
	std::cout << std::endl;
}
