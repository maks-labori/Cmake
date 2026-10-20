#pragma once
#include <iostream>
#include <stdexcept>
template <class T>
class Stack {
private:
    T* data_;
    size_t size_;
    int top_;

public:
    Stack(size_t size);
    Stack(const Stack& other);
    ~Stack();
    void push(const T& value);
    T pop();
    inline T& top() {
        if (is_empty()) {
            throw std::logic_error("empty");
        }
        return data_[top_];
    }
    inline bool is_empty()const noexcept {
        return(top_ == -1);
    }
    inline bool is_full()const noexcept {
        return (top_ == (size_ - 1));
    }
};

template <typename T>
Stack<T>::Stack(size_t size) {
    data_ = new T[size];
    top_ = -1;
    size_ = size;
}

template <typename T>
Stack<T>::Stack(const Stack& other) {
    data_ = new T[other.size_];
    top_ = other.size_ - 1;
    size_ = other.size_;
    for (size_t i = 0;i < other.size_;++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T>
Stack<T>::~Stack() {
    if (data_) {
        delete[] data_;
    }
    data_ = nullptr;
    top_ = -1;
    size_ = 0;
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (is_full()) { throw std::logic_error("stack overflow"); }
    data_[++top_] = value;
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("empty");
    }
    return data_[top_--];
}