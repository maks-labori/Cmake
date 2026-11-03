// Copyright 2026 Maksim Tarasenko
#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Multistack {
 private:
  T* data_;
  int* R;
  int* L;
  int* tops_;
  size_t count;
 public:
  Multistack(size_t count_stack, size_t size) {
    data_ = new T[size];
    R = new int[count_stack];
    L = new int[count_stack];
    tops_ = new int[count_stack];
    count = 0;
    size_t part = (size / count_stack)+(size % count_stack != 0);
    for (size_t i = 0; i < count_stack; ++i) {
      tops_[i] = -1 + part*i;
      L[i] = part * i;
      R[i] = L[i] + part - 1;
    }
    R[count_stack - 1] = size - 1;
  }
  //~Multistack() { 
  //  if(R){delete[] R;
  //  delete[] L;
  //  delete[] tops_;
  //  delete[] data_;
  //}
  inline size_t get_count() { return count; }
  bool isEmpty() { return count == 0; }
  bool isEmpty(size_t number) { return tops_[number - 1] < L[number-1];}
  bool isFull(size_t number) { return tops_[number - 1] == R[number - 1]; }
  void push(size_t number, const T& elem) {
    if (isFull(number)) {
      throw std::logic_error("full this stack");
    }
    tops_[number - 1]++;
    data_[tops_[number - 1]] = elem;
    count++;
  }
  T pop(size_t number) {
    if (isEmpty(number)) {
      throw std::logic_error("empty this stack");
    }
    T elem = data_[tops_[number - 1]];
    tops_[number - 1]--;
    count--;
    return elem;
  }
  T& top(size_t number) { 
      if (isEmpty(number)) {
        throw std::logic_error("empty this stack");
    }
      return data_[tops_[number - 1]]; }
};