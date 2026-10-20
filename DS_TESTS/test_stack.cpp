#include <gtest/gtest.h>
#include "../Algorithms/skobki.cpp"

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