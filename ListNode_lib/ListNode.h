// Copyright 2026 Maksim
#pragma once

#include <iostream>

template <typename T>
struct Node {
  T data_;
  Node* next_;
  explicit Node(const T& val, Node* next = nullptr)
      : data_(val), next_(next) {};
  Node(const Node& other) = default;
  Node(Node&& other) = default;
};

template <typename T>
class ListNode {
 private:
  Node<T>* head_;
  Node<T>* tail_;
  size_t size_;

 public:
  ListNode() : head_(nullptr), tail_(nullptr), size_(0) {}
  ~ListNode() {
    while (head_ != nullptr) {
      Node<T>* tmp = head_->next;
      delete head_;
      head_ = tmp;
    }
  }
  inline size_t size() const noexcept { return size_; }
  void push_front(const T& value) noexcept;
  void push_back(const T& value) noexcept;
  Node<T>* insert(const T& value, size_t index);
  void insert(const T& value, const Node<T>* elem) noexcept;
  T pop_front();
  T pop_back();
  T erase(size_t index);
  Node<T>* find(const T& elem) const noexcept;
  inline bool isEmpty() const noexcept { return size_ == 0; }

  template <class Type>
  class Iterator {
   private:
    Node<Type>* current_;

   public:
    explicit Iterator(Node<Type>* current = nullptr) : current_(current) {}
    Iterator(const Iterator& other) : current_(other.current_) {}
    Iterator<Type>& operator++() {
      current_ = current_->next_;
      return (*this);
    }
    Iterator<Type> operator++(int) { return Iterator<Type>(current_->next_); }
    Node<Type>& operator*() { return (*current_); }
    Node<Type>* operator->() { return current_; }
    const Node<Type>& operator*() const { return (*current_); }
    Iterator<Type>& operator=(const Iterator<Type>& it) {
      current_ = it.current_;
      return (*this);
    }
    Iterator<Type>& operator+=(size_t offset) {
      for (size_t i = 0; i < offset; ++i) {
        current_ = current_->next_;
      }
      return (*this);
    }

    Iterator<Type> operator+(size_t offset) {
      Iterator<Type> tmp(current_);
      tmp += offset;
      return tmp;
    }

    bool operator==(const Iterator<Type>& it) const noexcept {
      return (*current_ == *it.current_);
    }
    bool operator!=(const Iterator<Type>& it) const noexcept {
      return !((*this) == it);
    }
  };

  template <class Type>
  class Iterator;
  typedef Iterator<T> iterator;

  template <class Type>
  class Iterator;
  typedef Iterator<const T> const_iterator;

  const_iterator cbegin() const noexcept { return const_iterator(head_); }
  const_iterator cend() const noexcept { return const_iterator(tail_); }
  iterator begin() noexcept { return iterator(head_); }
  iterator end() noexcept { return iterator(tail_); }
};
template <typename T>
void ListNode<T>::push_front(const T& value) noexcept {
  Node<T>* tmp = new Node<T>(value, head_);
  head_ = tmp;
  if (isEmpty()) {
    tail_ = tmp;
  }
  size_++;
}

template <typename T>
void ListNode<T>::push_back(const T& value) noexcept {
  Node<T>* tmp = new Node<T>(value);
  if (isEmpty()) {
    head_ = tmp;
  } else {
    tail_->next_ = tmp;
  }
  tail_ = tmp;
  size_++;
}

template <typename T>
Node<T>* ListNode<T>::insert(const T& value, size_t index) {
  if (index >= size_) {
    throw std::out_of_range("out of range");
  } else if (isEmpty() || index == 0) {
    push_front(value);
    return head_;
  } else if (index == size_ - 1) {
    push_back(value);
    return tail_;
  } else {
    Node<T>* current = head_;
    for (size_t i = 0; i < index - 1; ++i) {
      current = current->next_;
    }
    Node<T>* tmp = new Node<T>(value, current->next_);
    current->next_ = tmp;
    size++;
    return tmp;
  }
}

template <typename T>
void ListNode<T>::insert(const T& value, const Node<T>* elem) noexcept {
  Node<T>* tmp = new Node<T>(value, elem->next_);
  if (elem->next_ == nullptr) {
    tail_ = tmp;
  }
  elem->next_ = tmp;
  size_++;
}

template <typename T>
T ListNode<T>::pop_front() {
  if (isEmpty()) {
    throw std::logic_error("empty");
  }
  Node<T> tmp = head_->next_;
  if (tmp == nullptr) {
    tail_ = nullptr;
  }
  T res = head_->data_;
  delete head_;
  head_ = tmp;
  size_--;
  return res;
}

template <typename T>
T ListNode<T>::pop_back() {
  if (isEmpty()) {
    throw std::logic_error("empty");
  }
  Node<T>* current = head_;
  for (size_t i = 0; i < size_ - 1; ++i) {
    current = current->next_;
  }
  current->next_ = nullptr;
  T res = tail_->data_;
  delete tail_;
  tail_ = current;
  size_--;
  return res;
}

template <typename T>
T ListNode<T>::erase(size_t index) {
  if (isEmpty()) {
    throw std::logic_error("empty");
  }
  if (index > size_ - 1) {
    throw std::out_of_range("out of range");
  }
  if (index == 0) {
    return (pop_front(index));
  }
  if (index == size_ - 1) {
    return (push_back(index));
  }
  Node<T>* current = head_;
  for (size_t i = 0; i < index - 2; ++i) {
    current = current->next_;
  }
  Node<T>* tmp = current->next_;
  T res = tmp->data_;
  current->next_ = tmp->next_;
  delete tmp;
  size_--;
  return res;
}

template <typename T>
Node<T>* ListNode<T>::find(const T& elem) const noexcept {
  if (isEmpty()) {
    return nullptr;
  }
  Node<T> current = head_;
  while (current) {
    if (elem == current.data_) {
      return current;
    }
    current = current.next_;
  }
  return nullptr;
}
