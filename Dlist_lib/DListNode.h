// Copyright 2026 Maksim
#pragma once

#include <iostream>

template <typename T>
struct DNode {
    T data_;
    DNode<T>* next_;
    DNode<T>* prev_;
    explicit DNode(
        DNode<T>* next = nullptr,
        DNode<T>* prev = nullptr,
        const T& val = T())
        : data_(val), next_(next), prev_(prev) {
    }
    DNode(const DNode<T>& other) = default;
    DNode(DNode<T>&& other) = default;
    T get_data() const noexcept { return data_; }
    DNode<T>* get_next() const noexcept { return next_; }
    DNode<T>* get_prev() const noexcept { return prev_; }
};

template <typename T>
class ListDNode {
 private:
    DNode<T>* head_;
    DNode<T>* tail_;
    size_t size_;

 public:
    ListDNode() : head_(nullptr), tail_(nullptr), size_(0) {}
    ~ListDNode() {
        while (head_ != nullptr) {
            DNode<T>* tmp = head_->next_;
            delete head_;
            head_ = tmp;
        }
    }
    inline size_t size() const noexcept { return size_; }
    DNode<T>* get_head() const noexcept { return head_; }
    DNode<T>* get_tail() const noexcept { return tail_; }
    void push_front(const T& value) noexcept;
    void push_back(const T& value) noexcept;
    DNode<T>* insert_ind(const T& value, size_t index);
    void insert(DNode<T>* elem, const T& value) noexcept;
    T pop_front();
    T pop_back();
    T erase(size_t index);
    DNode<T>* find(const T& elem) const noexcept;
    inline bool isEmpty() const noexcept { return size_ == 0; }

    template <typename Type, typename DNodeType>
    class Iterator {
     private:
        DNodeType* current_;
        DNodeType* prev_node;

     public:
        explicit Iterator(DNodeType* current = nullptr, DNodeType* prev = nullptr) :
            current_(current), prev_node(prev) {}
        Iterator(const Iterator& other) :
            current_(other.current_), prev_node(other.prev_node) {}
        Iterator<Type, DNodeType>& operator++() {
            current_ = current_->next_;
            if (current_) {
                prev_node = current_->prev_;
            }else {
                prev_node = nullptr;
            }
            return (*this);
        }
        Iterator<Type, DNodeType> operator++(int) {
            Iterator<Type, DNodeType> tmp = (*this);
            ++(*this);
            return tmp;
        }
        Type& operator*() { return (current_->data_); }
        DNodeType* operator->() { return current_; }
        Iterator<Type, DNodeType>& operator=
            (const Iterator<Type, DNodeType>& it) {
            current_ = it.current_;
            prev_node = it.prev_node;
            return (*this);
        }
        Iterator<Type, DNodeType>& operator+=(size_t offset) {
            for (size_t i = 0; i < offset; ++i) {
                current_ = current_->next_;
                if (current_) {
                    prev_node = current_->prev_;
                }else {
                    prev_node = nullptr;
                }
            }
            return (*this);
        }

        Iterator<Type, DNodeType> operator+(size_t offset) {
            Iterator<Type, DNodeType> tmp(current_, prev_node);
            tmp += offset;
            return tmp;
        }

        bool operator==(const Iterator<Type, DNodeType>& it) const noexcept {
            return (current_ == it.current_);
        }
        bool operator!=(const Iterator<Type, DNodeType>& it) const noexcept {
            return !((*this) == it);
        }
        Iterator<Type, DNodeType>& operator--() {
            current_ = prev_node;
            if (current_) {
                prev_node = current_->prev_;
            }
            return (*this);
        }
        Iterator<Type, DNodeType> operator--(int) {
            Iterator<Type, DNodeType> tmp = (*this);
            --(*this);
            return tmp;
        }
        Iterator<Type, DNodeType>& operator-=(size_t offset) {
            for (size_t i = 0; i < offset; ++i) {
                current_ = prev_node;
                if (current_) {
                    prev_node = current_->prev_;
                }
            }
            return (*this);
        }

        Iterator<Type, DNodeType> operator-(size_t offset) {
            Iterator<Type, DNodeType> tmp(current_, prev_node);
            tmp -= offset;
            return tmp;
        }
    };

    typedef Iterator<T, DNode<T>> iterator;
    typedef Iterator<const T, const DNode<T>> const_iterator;

    const_iterator cbegin() const noexcept {
        return const_iterator(head_, nullptr);
    }
    const_iterator cend() const noexcept {
        return const_iterator(tail_->next_, tail_);
    }
    iterator begin() noexcept {
        return iterator(head_, nullptr);
    }
    iterator end() noexcept {
        return iterator(tail_->next_, tail_);
    }
    const_iterator begin()const noexcept {
        return const_iterator(head_, nullptr);
    }
    const_iterator end()const noexcept {
        return const_iterator(tail_->next_, tail_);
    }
};

template <typename T>
void ListDNode<T>::push_front(const T& value) noexcept {
    DNode<T>* tmp = new DNode<T>(head_, nullptr, value);
    if (isEmpty()) {
        tail_ = tmp;
    }else {
        head_->prev_ = tmp;
    }
    head_ = tmp;
    size_++;
}

template <typename T>
void ListDNode<T>::push_back(const T& value) noexcept {
    DNode<T>* tmp = new DNode<T>(nullptr, tail_, value);
    if (isEmpty()) {
        head_ = tmp;
    }else {
        tail_->next_ = tmp;
    }
    tail_ = tmp;
    size_++;
}

template <typename T>
DNode<T>* ListDNode<T>::insert_ind(const T& value, size_t index) {
    if (index >= size_) {
        throw std::out_of_range("out of range");
    }else if (isEmpty() || index == 0) {
        push_front(value);
        return head_;
    }else if (index == size_) {
        push_back(value);
        return tail_;
    }else {
        DNode<T>* current = head_;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next_;
        }
        DNode<T>* tmp = new DNode<T>(current->next_, current, value);
        current->next_->prev_ = tmp;
        current->next_ = tmp;
        size_++;
        return tmp;
    }
}

template <typename T>
void ListDNode<T>::insert(DNode<T>* elem, const T& value) noexcept {
    DNode<T>* tmp = new DNode<T>(elem->next_, elem, value);
    if (elem->next_ == nullptr) {
        tail_ = tmp;
    }
    elem->next_->prev_ = tmp;
    elem->next_ = tmp;
    size_++;
}

template <typename T>
T ListDNode<T>::pop_front() {
    if (isEmpty()) {
        throw std::logic_error("empty");
    }
    DNode<T>* tmp = head_->next_;
    if (tmp == nullptr) {
        tail_ = nullptr;
    }else {
        tmp->prev_ = nullptr;
    }
    T res = head_->data_;
    delete head_;
    head_ = tmp;
    size_--;
    return res;
}

template <typename T>
T ListDNode<T>::pop_back() {
    if (isEmpty()) {
        throw std::logic_error("empty");
    }
    if (size_ == 1) {
        return pop_front();
    }
    DNode<T>* current = tail_->prev_;
    current->next_ = nullptr;
    T res = tail_->data_;
    delete tail_;
    tail_ = current;
    size_--;
    return res;
}

template <typename T>
T ListDNode<T>::erase(size_t index) {
    if (isEmpty()) {
        throw std::logic_error("empty");
    }
    if (index > size_ - 1) {
        throw std::out_of_range("out of range");
    }
    if (index == 0) {
        return (pop_front());
    }
    if (index == size_ - 1) {
        return (pop_back());
    }
    DNode<T>* current = head_;
    for (size_t i = 0; i < index - 1; ++i) {
        current = current->next_;
    }
    DNode<T>* tmp = current->next_;
    T res = tmp->data_;
    current->next_ = tmp->next_;
    tmp->next_->prev_ = current;
    delete tmp;
    size_--;
    return res;
}

template <typename T>
DNode<T>* ListDNode<T>::find(const T& elem) const noexcept {
    if (isEmpty()) {
        return nullptr;
    }
    DNode<T>* current = head_;
    while (current->next_) {
        if (elem == current->data_) {
            return current;
        }
        current = current->next_;
    }
    return (elem == current->data_) ? current : nullptr;
}
