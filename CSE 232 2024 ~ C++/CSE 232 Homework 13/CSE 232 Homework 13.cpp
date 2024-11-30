//CSE 232 Homework 13
//Write a function, named "center", that takes two const_iterators denoting a range in a std::list of ints.
//Your function should return the int that is at the center/middle of that range.
#ifndef center_hpp
#define center_hpp

#include <list>

int center(const std::list<int>::const_iterator& begin, const std::list<int>::const_iterator& end);

#endif



#include "header.hpp"
#include <iostream>
#include <list>
#include <cassert>

int center(const std::list<int>::const_iterator& begin, const std::list<int>::const_iterator& end) {
    // Base case: if there's only one element, return it
    if (std::next(begin) == end) {
        return *begin;
    }

    // Recursive case: move both iterators towards each other
    return center(std::next(begin), std::prev(end));
}
int main() {

	std::list<int> my_list = { 1, 4, 5 };
	int result = center(my_list.cbegin(), my_list.cend());
	std::cout << result << std::endl;
	assert(result == 4);


	return 0;
}


//StackLinked
#pragma once
#include <iostream>

class Node {
public:
    char letter;
    Node* down;
    Node(char c) : letter(c), down(nullptr) {}
};

class Stack {
private:
    Node* top_ = nullptr;

public:
    Stack() = default;
    void push(char c);
    char top();
    void pop();
    bool isEmpty();
    void clear();
    friend std::ostream& operator<<(std::ostream& os, Stack const& s);
    ~Stack();
    Stack& operator=(Stack other);
    Stack(Stack const& other);
};

#include "header.hpp"

void Stack::push(char c) {
    Node* new_top = new Node(c);
    new_top->down = top_;
    top_ = new_top;
}

char Stack::top() {
    return top_->letter;
}

void Stack::pop() {
    Node* new_top = top_->down;
    delete top_;
    top_ = new_top;
}

bool Stack::isEmpty() {
    return top_ == nullptr;
}

void Stack::clear() {
    while (top_ != nullptr) {
        Node* next = top_->down;
        delete top_;
        top_ = next;
    }
}

std::ostream& operator<<(std::ostream& os, Stack const& s) {
    Node* current = s.top_;
    while (current != nullptr) {
        os << current->letter;
        os << ",";
        current = current->down;
    }
    return os;
}

Stack::Stack(Stack const& other) {
    Node* other_current = other.top_;
    Node* this_previous = nullptr;
    while (other_current != nullptr) {
        Node* new_node = new Node(other_current->letter);
        if (this_previous == nullptr) {
            this->top_ = new_node;
        }
        else {
            this_previous->down = new_node;
        }
        this_previous = new_node;
        other_current = other_current->down;
    }
}

Stack& Stack::operator=(Stack other) {
    std::swap(top_, other.top_);
    return *this;
}

Stack::~Stack() {
    clear();
}

#include "header.hpp"

#include <iostream>
#include <list>
#include <cassert>

int main() {

    Stack s;
    s.push('a');
    assert(s.top() == 'a');
    s.pop();

    return 0;
}


//Sorting: Bubble, Insertion, quicksort
#pragma once
#include <vector>

void bubble_sort(std::vector<int> vec);
void quicksort_sort(std::vector<int> vec);
void insertion_sort(std::vector<int> vec);



#include <iostream>
#include <vector>
#include <iterator>
#include "sort.h"

//Function to Print
void print_vector(const std::vector<int>& vec) {
    for (std::vector<int>::size_type i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

//Function to check if already Sorted
bool is_sorted(const std::vector<int>& vec) {
    for (std::vector<int>::size_type i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

// Bubble Sort
void bubble_sort(std::vector<int> vec) {
    print_vector(vec);
    if (is_sorted(vec)) {
        return;
    }

    bool swapped;
    int n = vec.size();
    do {
        swapped = false;
        for (int i = 1; i < n; ++i) {
            if (vec[i - 1] > vec[i]) {
                std::swap(vec[i - 1], vec[i]);
                print_vector(vec);
                swapped = true;
            }
        }
    } while (swapped);
}

// Insertion Sort
void swap(std::vector<int>& vec, int i, int j) {
    if (i == j) {
        return;
    }
    int temp = vec[i];
    vec[i] = vec[j];
    vec[j] = temp;
    print_vector(vec);
}

void insertion_sort(std::vector<int> vec) {
    print_vector(vec);
    int i{ 1 };
    while (i < static_cast<int>(vec.size())) {
        int j{ i };
        while (j > 0 && (vec.at(j - 1) > vec.at(j))) {
            swap(vec, j, j - 1);
            --j;
        }
        ++i;
    }
}

// Quicksort
int partition(std::vector<int>& vec, int lo, int hi) {
    int pivot{ vec.at(hi) };
    int i{ lo };
    for (int j{ lo }; j <= hi - 1; ++j) {
        if (vec.at(j) <= pivot) {
            swap(vec, i, j);
            ++i;
        }
    }
    swap(vec, i, hi);
    return i;
}

void quicksort_sort(std::vector<int>& vec, int lo, int hi) {
    if (lo >= hi || lo < 0) {
        return;
    }
    int p = partition(vec, lo, hi);
    quicksort_sort(vec, lo, p - 1);
    quicksort_sort(vec, p + 1, hi);
}

void quicksort_sort(std::vector<int> vec) {
    print_vector(vec);
    quicksort_sort(vec, 0, vec.size() - 1);

}


#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "sort.h"


int main() {
    // read a line from std::cin
    std::string line;
    getline(std::cin, line);

    // get whitespace-separated integers from line into an int vector
    std::istringstream iss(line);
    std::vector<int> values(std::istream_iterator<int>(iss), {});

    std::cout << "Bubble Sort" << std::endl;
    bubble_sort(values);

    std::cout << "Insertion Sort" << std::endl;
    insertion_sort(values);

    std::cout << "Quicksort Sort" << std::endl;
    quicksort_sort(values);

    return 0;
}


//Write a function called Flip that takes an pointer to a Node.
//Flip doesn’t return anything, instead it changes the data member named on from true to false, or false to true.
// Please note that Node objects have a data member named next that is a pointer to the next Node. Be sure to also flip those nodes.
//Node.hpp
#pragma once

struct Node {
    bool on = false;
    Node* next = nullptr;
};



#ifndef header_hpp
#define header_hpp

#include "Node.hpp"

void Flip(Node* head);

#endif



#include "header.hpp"
#include "Node.hpp"
#include <iostream>
int main() {

    Node* n1 = new Node;
    std::cout << (*n1).on << std::endl;
    Flip(n1);
    std::cout << (*n1).on << std::endl;

    return 0;
}

#include "header.hpp"
#include "Node.hpp"

void Flip(Node* head) {
    // Traverse the linked list
    Node* current = head;
    while (current != nullptr) {
        // Flip the 'on' member
        current->on = !current->on;
        // Move to the next node
        current = current->next;
    }
}