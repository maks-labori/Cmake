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
  size_t size;
  size_t stacks;

 public:
  Multistack(size_t count_stack, size_t _size) {
    size = _size;
    stacks = count_stack;
    data_ = new T[_size];
    R = new int[count_stack];
    L = new int[count_stack];
    tops_ = new int[count_stack];
    count = 0;
    size_t part = (_size / count_stack) + (_size % count_stack != 0);
    for (size_t i = 0; i < count_stack; ++i) {
      tops_[i] = -1 + part * i;
      L[i] = part * i;
      R[i] = L[i] + part - 1;
    }
    R[count_stack - 1] = _size - 1;
  }
  ~Multistack() {
    delete[] R;
    delete[] L;
    delete[] tops_;
    delete[] data_;
  }
  void Repack() {
    std::vector<int> L_ptrs;
    std::vector<int> R_ptrs;
    int cnt = 0;
    L_ptrs.push_back(0);
    while (true) {
      if (R[cnt] == size - 1) {
        R_ptrs.push_back(R[cnt]);
        break;
      }
      int top = tops_[cnt];
      int elem_count = (top - L[cnt] + 1);
      int part = (elem_count == 0)
                     ? 1
                     : elem_count + 1 +
                           static_cast<int>(
                               static_cast<double>(size - count - 1) / stacks);
      if (part > (size - stacks + 1)) {
        throw std::logic_error("stack is full");
      }
      R_ptrs.push_back(L_ptrs[cnt] + part - 1);
      L_ptrs.push_back(R_ptrs[cnt] + 1);
      cnt++;
    }
    for (int i = cnt; i >= 0; --i) {
      for (int j = tops_[i]; j > L[i] - 1; --j) {
        int new_index = j - L[i] + L_ptrs[i];
        data_[new_index] = data_[j];
      }
      tops_[i] = tops_[i] - L[i] + L_ptrs[i];
    }
    for (int i = 0; i < cnt + 1; ++i) {
      L[i] = L_ptrs[i];
      R[i] = R_ptrs[i];
    }
  }
  inline size_t get_count() { return count; }
  bool isEmpty() { return count == 0; }
  bool isEmpty(size_t number) { return tops_[number - 1] < L[number - 1]; }
  bool isFull(size_t number) { return tops_[number - 1] == R[number - 1]; }
  void push(size_t number, const T& elem) {
    if (isFull(number)) {
      Repack();
      if (isFull(number)) {
        throw std::logic_error("full this stack");
      }
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
    return data_[tops_[number - 1]];
  }
};
