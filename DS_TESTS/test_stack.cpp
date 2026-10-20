// Copyright 2026 Maksim

#include <gtest/gtest.h>
#include <string>
#include "../Algorithms/skobki.h"

TEST(TestSkobki,TestOnTrueExample) {
    std::string input = "{(())()[()()]}";
    bool flag = check_breckets(input);
    EXPECT_EQ(flag, true);
}
TEST(TestSkobki, TestOnFalseExample) {
    std::string input = "{(())()[()(]}";
    bool flag = check_breckets(input);
    EXPECT_EQ(flag, false);
}
TEST(TestSkobki, TestWithStackEmpty) {
    std::string input = "}}{(())()[()()]}";
    bool flag = check_breckets(input);
    EXPECT_EQ(flag, false);
}
