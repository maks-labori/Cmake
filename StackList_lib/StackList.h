// Copyright 2026 Maksim Tarasenko
#pragma once
#include "../ListNode_lib/ListNode.h"

#include <iostream>
#include <stdexcept>

template <class T>
class Stack {
private:
    ListNode<T> data_;
    size_t size_;

public:
    explicit Stack(size_t size);
    Stack(const Stack& other);
    ~Stack();
    void push(const T& value);
    T pop();
    inline size_t get_size()const noexcept {
        return size_;
    }
    inline T top() {
        if (is_empty()) {
            throw std::logic_error("empty");
        }
        return data_.get_head()->get_data();
    }
    inline bool is_empty()const noexcept {
        return data_.isEmpty();
    }
    inline bool is_full()const noexcept {
        return data_.size() == size_;
    }
};

template <typename T>
Stack<T>::Stack(size_t size) :size_(size) {}

template <typename T>
Stack<T>::Stack(const Stack& other) {
    size_ = other.size_;
    Node<T>* tmp = other.data_.get_head();
    for (size_t i = 0; i < other.data_.size(); ++i) {
        data_.push_front(tmp->get_data());
        tmp = tmp->next_;
    }
}

template <typename T>
Stack<T>::~Stack() {
    data_.~ListNode();
    size_ = 0;
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (is_full()) {
        throw std::logic_error("stack overflow");
    }
    data_.push_front(value);
}

template <typename T>
T Stack<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("empty");
    }
    return data_.pop_front();
}
