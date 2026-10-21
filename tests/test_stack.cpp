// Copyright 2026 Maksim

#include "gtest/gtest.h"
#include "../StackMas_lib/stack.h"

TEST(TestStackMas , TestSizeConstructor) {
    Stack<int> stack(20);
    EXPECT_EQ(stack.get_size(), 20);
    EXPECT_EQ(stack.get_top(), -1);
}

TEST(TestStackMas , TestCopyConstructor) {
    Stack<int> stack(20);
    Stack<int> copy(stack);
    EXPECT_EQ(stack.get_size(), copy.get_size());
    EXPECT_EQ(stack.get_top(), copy.get_top());
}

TEST(TestStackMas , TestIsFull) {
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    EXPECT_TRUE(stack.is_full());
}

TEST(TestStackMas , TestIsEmpty) {
    Stack<int> stack(3);
    EXPECT_TRUE(stack.is_empty());
    stack.push(1);
    EXPECT_FALSE(stack.is_empty());
    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(TestStackMas , TesTop) {
    Stack<int> stack(3);
    EXPECT_THROW(stack.top(), std::logic_error);
    stack.push(1);
    EXPECT_EQ(stack.top(), 1);
    stack.push(50);
    EXPECT_EQ(stack.top(), 50);
}

TEST(TestStackMas , TestPop) {
    Stack<int> stack(30);
    EXPECT_THROW(stack.pop(),std::logic_error);
    stack.push(5);
    EXPECT_EQ(stack.pop(), 5);
    EXPECT_THROW(stack.pop(), std::logic_error);
    EXPECT_TRUE(stack.is_empty(), true);
}

TEST(TestStackMas , TestPush) {
    Stack<int> stack(20);
    int count = 0;
    while (!stack.is_full()) {
        stack.push(++count);
    }
    while (!stack.is_empty()) {
        EXPECT_EQ(stack.pop(), count--);
    }
}
