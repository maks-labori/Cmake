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

//TEST(Testmultistack, Test) {
//
//}
//
//TEST(Testmultistack, Test) {
//
//}
//
//TEST(Testmultistack, Test) {
//
//}

