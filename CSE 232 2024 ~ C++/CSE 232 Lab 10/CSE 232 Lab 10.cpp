#include<iostream>
#include<sstream>
#include<stdexcept>
#include<string>
#include <algorithm>

#include "singlelink.hpp"

SingleLink::SingleLink() : head_(nullptr), tail_(nullptr) {}

SingleLink::SingleLink(int dat) {
    head_ = new Node(dat);
    tail_ = head_;
}

void SingleLink::append_back(int dat) {
    Node* newNode = new Node(dat);
    if (head_ == nullptr) {
        head_ = newNode;
        tail_ = newNode;
    }
    else {
        tail_->next_ = newNode;
        tail_ = newNode;
    }
}

std::ostream& operator<<(std::ostream& out, const SingleLink& s) {
    Node* current = s.head_;
    while (current != nullptr) {
        out << current->data_;
        if (current->next_) {
            out << ", ";

        }
        current = current->next_;
    }
    return out;
}

bool SingleLink::del(int val) {
    // Edge cases:
    // 1. List is empty
    // 2. Node to be deleted is the head node
    // 3. Node to be deleted is the tail node
    // 4. Node to be deleted is in the middle of the list

    Node* current = head_;
    Node* prev = nullptr;

    // Search for the node with the given value
    while (current != nullptr && current->data_ != val) {
        prev = current;
        current = current->next_;
    }

    // Node with given value not found
    if (current == nullptr)
        return false;

    // If the node to be deleted is the head node
    if (current == head_) {
        head_ = head_->next_;
        delete current;
        // If there was only one node
        if (head_ == nullptr)
            tail_ = nullptr;
        return true;
    }

    // If the node to be deleted is the tail node
    if (current == tail_) {
        tail_ = prev;
        prev->next_ = nullptr;
        delete current;
        return true;
    }

    // Node to be deleted is in the middle
    prev->next_ = current->next_;
    delete current;
    return true;
}

Node& SingleLink::operator[](size_t index) {
    Node* current = head_;
    size_t count = 0;

    // Traverse the list until reaching the desired index or end of list
    while (current != nullptr && count < index) {
        current = current->next_;
        count++;
    }

    if (current == nullptr)
        throw std::out_of_range("Index out of range");

    return *current;
}

SingleLink::~SingleLink() {
    Node* current = head_;
    while (current != nullptr) {
        Node* next = current->next_;
        delete current;
        current = next;
    }
}

SingleLink::SingleLink(const SingleLink& other) : head_(nullptr), tail_(nullptr) {
    // Copy constructor
    Node* current = other.head_;
    while (current != nullptr) {
        append_back(current->data_);
        current = current->next_;
    }
}

SingleLink& SingleLink::operator=(SingleLink other) {
    // Assignment operator
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    return *this;
}

int main() {
    SingleLink s;
    s.append_back(3);
    s.append_back(4);
    std::cout << "Two Items: " << s << std::endl;

    SingleLink s2(10);
    s2.append_back(3);
    s2.append_back(4);
    std::cout << "Three Items: " << s2 << std::endl;

    s2.del(3);
    std::cout << "Removed 3: " << s2 << std::endl;


    SingleLink s3(56);
    s3.append_back(73);
    s3.append_back(345);
    s3.append_back(1);
    s3.append_back(15);
    std::cout << "Indexing 0: " << s3[0].data_ << std::endl;
    std::cout << "Indexing 1: " << s3[1].data_ << std::endl;
    std::cout << "Indexing 2: " << s3[2].data_ << std::endl;
    std::cout << "Indexing 3: " << s3[3].data_ << std::endl;
    std::cout << "Indexing 4: " << s3[4].data_ << std::endl;
}