// Copyright 2026 Maksim

#include <vector>
#include "../ListNode_lib/ListNode.h"
#include "gtest/gtest.h"

TEST(ListNodeTest, TestDefaultConstructor) {
  ListNode<int> list;
  EXPECT_EQ(list.get_head(), nullptr);
  EXPECT_EQ(list.get_tail(), nullptr);
  EXPECT_EQ(list.size(), 0);
}

TEST(ListNodeTest, TestNodeConstructor) {
  Node<int> n1(nullptr, 5);

  EXPECT_EQ(n1.get_data(), 5);
  EXPECT_EQ(n1.get_next(), nullptr);
}

TEST(ListNodeTest, TestIsEmpty) {
  ListNode<int> list;
  EXPECT_TRUE(list.isEmpty());
  list.push_back(5);
  EXPECT_FALSE(list.isEmpty());
}

TEST(ListNodeTest, TestPushFront) {
  ListNode<int> list;
  list.push_front(5);
  EXPECT_EQ(list.get_head()->get_data(), 5);
  EXPECT_EQ(list.get_tail()->get_data(), 5);
  EXPECT_EQ(list.size(), 1);

  list.push_front(6);
  EXPECT_EQ(list.get_head()->get_data(), 6);
  EXPECT_EQ(list.get_tail()->get_data(), 5);
  EXPECT_EQ(list.size(), 2);

  list.push_front(56);

  EXPECT_EQ(list.get_head()->get_data(), 56);
  EXPECT_EQ(list.get_tail()->get_data(), 5);
  EXPECT_EQ(list.size(), 3);
}

TEST(ListNodeTest, TestPushBack) {
  ListNode<int> list;
  list.push_back(5);
  EXPECT_EQ(list.get_head()->get_data(), 5);
  EXPECT_EQ(list.get_tail()->get_data(), 5);
  EXPECT_EQ(list.size(), 1);

  list.push_back(11);
  EXPECT_EQ(list.get_head()->get_data(), 5);
  EXPECT_EQ(list.get_tail()->get_data(), 11);
  EXPECT_EQ(list.size(), 2);

  list.push_back(9999);

  EXPECT_EQ(list.get_head()->get_data(), 5);
  EXPECT_EQ(list.get_tail()->get_data(), 9999);
  EXPECT_EQ(list.size(), 3);
}

TEST(ListNodeTest, TestPopFront) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);

  EXPECT_EQ(list.pop_front(), 10);
  EXPECT_EQ(list.size(), 1);

  EXPECT_EQ(list.pop_front(), 20);
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

TEST(ListNodeTest, TestPopBack) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);

  EXPECT_EQ(list.pop_back(), 20);
  EXPECT_EQ(list.size(), 1);

  EXPECT_EQ(list.pop_back(), 10);
  EXPECT_TRUE(list.isEmpty());
}

TEST(ListNodeTest, TestInsertOnIndex) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(30);
  list.insert_ind(20, 1);

  EXPECT_EQ(list.size(), 3);

  EXPECT_EQ(list.get_head()->get_data(), 10);
  list.pop_front();

  EXPECT_EQ(list.get_head()->get_data(), 20);
  list.pop_front();

  EXPECT_EQ(list.get_head()->get_data(), 30);
  list.pop_front();
  EXPECT_TRUE(list.isEmpty());
}

TEST(ListNodeTest, TestInsertOnPtr) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(30);

  Node<int>* nd = list.get_head();

  list.insert(nd, 20);
  EXPECT_EQ(list.size(), 3);

  EXPECT_EQ(list.get_head()->get_data(), 10);
  list.pop_front();
  EXPECT_EQ(list.get_head()->get_data(), 20);
  list.pop_front();
  EXPECT_EQ(list.get_head()->get_data(), 30);
}

TEST(ListNodeTest, TestErase) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);
  list.push_back(50);

  EXPECT_EQ(list.erase(2), 30);
  EXPECT_EQ(list.erase(2), 40);
  EXPECT_EQ(list.erase(2), 50);
  EXPECT_EQ(list.size(), 2);

  EXPECT_EQ(list.get_head()->get_data(), 10);
  EXPECT_EQ(list.get_tail()->get_data(), 20);
}

TEST(ListNodeTest, TestFind) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  EXPECT_EQ(list.find(10)->get_data(), 10);
  EXPECT_EQ(list.find(20)->get_data(), 20);
  EXPECT_EQ(list.find(30)->get_data(), 30);
  EXPECT_EQ(list.find(50), nullptr);
}

TEST(ListNodeIteratorTest, TestIteratorIncrement) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  auto it = list.begin();
  EXPECT_EQ(*it, 10);
  auto& prefix_ref = ++it;
  EXPECT_EQ(*it, 20);
  EXPECT_EQ(&prefix_ref, &it);
  auto old_it = it++;
  EXPECT_EQ(*old_it, 20);
  EXPECT_EQ(*it, 30);
  ++it;
  EXPECT_EQ(it, list.end());
}

TEST(ListNodeIteratorTest, TestIteratorEquality) {
  ListNode<int> list;
  list.push_back(10);
  list.push_back(20);

  auto it1 = list.begin();
  auto it2 = list.begin();
  EXPECT_TRUE(it1 == it2);
  EXPECT_FALSE(it1 != it2);
  ++it2;
  EXPECT_FALSE(it1 == it2);
  EXPECT_TRUE(it1 != it2);
}

TEST(ListNodeIteratorTest, TestIteratorModifValue) {
  ListNode<int> list;
  list.push_back(10);

  auto it = list.begin();
  *it = 99;
  EXPECT_EQ(list.get_head()->get_data(), 99);
}

TEST(ListNodeIteratorTest, TestIteratorForLoop) {
  ListNode<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);

  std::vector<int> result;
  for (int value : list) {
    result.push_back(value);
  }

  EXPECT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
}
