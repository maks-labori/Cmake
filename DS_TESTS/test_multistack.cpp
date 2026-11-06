// Copyright 2026 Maksim

#include <gtest/gtest.h>

#include "../multistack_lib/multistack.h"

TEST(Testmultistack, TestPush) {
  Multistack<int> multistack(3, 14);
  multistack.push(1, 3);
  EXPECT_EQ(multistack.get_count(), 1);

  multistack.push(1, 7);
  multistack.push(3, 4);
  multistack.push(3, 9);
  multistack.push(3, 8);
  multistack.push(3, 4);
  EXPECT_EQ(multistack.get_count(), 6);
  multistack.pop(1);
  multistack.push(1, 4);
  EXPECT_EQ(multistack.top(1), 4);
  EXPECT_THROW(multistack.top(2), std::logic_error);
  EXPECT_EQ(multistack.top(3), 4);
  multistack.push(2, 6);
  EXPECT_EQ(multistack.top(2), 6);
  EXPECT_EQ(multistack.get_count(), 7);
}

TEST(Testmultistack, TestEmpty) {
  Multistack<int> multistack(3, 14);
  EXPECT_TRUE(multistack.isEmpty());
  multistack.push(1, 3);
  EXPECT_FALSE(multistack.isEmpty(1));
  EXPECT_TRUE(multistack.isEmpty(2));
  EXPECT_TRUE(multistack.isEmpty(3));
}

TEST(Testmultistack, TestTop) {
  Multistack<int> multistack(3, 14);
  multistack.push(1, 10);
  EXPECT_EQ(multistack.top(1), 10);
  multistack.push(1, 20);
  EXPECT_EQ(multistack.top(1), 20);
  multistack.pop(1);
  EXPECT_EQ(multistack.top(1), 10);
  multistack.push(2, 30);
  EXPECT_EQ(multistack.top(2), 30);
  EXPECT_THROW(multistack.top(3), std::logic_error);
  multistack.push(3, 40);
  EXPECT_EQ(multistack.top(3), 40);
}

TEST(Testmultistack, TestPop) {
  Multistack<int> multistack(3, 14);

  multistack.push(2, 100);
  multistack.push(2, 200);

  EXPECT_EQ(multistack.pop(2), 200);
  EXPECT_EQ(multistack.top(2), 100);

  EXPECT_EQ(multistack.pop(2), 100);
  EXPECT_THROW(multistack.pop(2), std::logic_error);
}

TEST(Testmultistack, TestRepackShiftRight) {
  Multistack<int> multistack(3, 14);
  for (int i = 0; i < 12; ++i) {
    EXPECT_NO_THROW(multistack.push(1, (i + 1) * 100));
  }
  EXPECT_THROW(multistack.push(1, 99), std::logic_error);
}

TEST(Testmultistack, TestRepackShiftLeft) {
  Multistack<int> multistack2(3, 15);
  for (int i = 0; i < 13; ++i) {
    EXPECT_NO_THROW(multistack2.push(3, (i + 1) * 100));
  }
  EXPECT_THROW(multistack2.push(3, 99), std::logic_error);
}

TEST(Testmultistack, TestRepackInternalStack) {
  Multistack<int> multistack(3, 14);
  for (int i = 0; i < 12; ++i) {
    EXPECT_NO_THROW(multistack.push(2, (i + 1) * 100));
  }
  EXPECT_THROW(multistack.push(2, 99), std::logic_error);
}
