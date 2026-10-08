#include "gtest/gtest.h"
#include "memdata.h"

TEST(MemDataTest, DefaultConstructor) {
    MemData<int> m;
    EXPECT_EQ(m.capacity(), MEM_STEP);
    EXPECT_NE(m.data(), nullptr);
}

TEST(MemDataTest, ConstructorWithSize) {
    MemData<int> m(10);
    EXPECT_GE(m.capacity(), 10u);
    EXPECT_NE(m.data(), nullptr);
}

TEST(MemDataTest, ConstructorWithData) {
    int arr[] = { 1, 2, 3, 4, 5 };
    MemData<int> m(5, arr);
    EXPECT_GE(m.capacity(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(m[i], arr[i]);
    }
}

TEST(MemDataTest, InitializerListConstructor) {
    MemData<int> m{ 1, 2, 3, 4, 5 };
    EXPECT_GE(m.capacity(), 5u);
    EXPECT_EQ(m[0], 1);
    EXPECT_EQ(m[4], 5);
}

TEST(MemDataTest, MoveConstructor) {
    MemData<int> m1(10);
    m1[0] = 42;
    int* ptr = m1.data();

    MemData<int> m2(std::move(m1));
    EXPECT_EQ(m2.data(), ptr);
    EXPECT_EQ(m2[0], 42);
    EXPECT_EQ(m1.data(), nullptr);
    EXPECT_EQ(m1.capacity(), 0u);
}

TEST(MemDataTest, MoveAssignment) {
    MemData<int> m1(10);
    m1[0] = 42;
    MemData<int> m2;

    m2 = std::move(m1);
    EXPECT_EQ(m2[0], 42);
    EXPECT_EQ(m1.data(), nullptr);
}

TEST(MemDataTest, OperatorIndex) {
    MemData<int> m(5);
    for (size_t i = 0; i < 5; ++i) {
        m[i] = static_cast<int>(i * 10);
    }
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(m[i], static_cast<int>(i * 10));
    }
}

TEST(MemDataTest, allocateRawIncreasesCapacity) {
    MemData<int> m(5);
    size_t old_cap = m.capacity();
    m.allocateRaw(100);
    EXPECT_GE(m.capacity(), 100u);
}

TEST(MemDataTest, Clear) {
    MemData<int> m(10);
    m.clear();
    EXPECT_EQ(m.capacity(), 0u);
    EXPECT_EQ(m.data(), nullptr);
}

TEST(MemDataTest, CalculateCapacity) {
    // Должно округлять вверх до кратного MEM_STEP
    MemData<int> temp;
    EXPECT_EQ(temp.calculateCapacity_(1), MEM_STEP);
    EXPECT_EQ(temp.calculateCapacity_(MEM_STEP), MEM_STEP * 2);
    EXPECT_EQ(temp.calculateCapacity_(MEM_STEP + 1), MEM_STEP * 2);
}

TEST(MemDataTest, ShiftRight) {
    MemData<int> m(10);
    for (size_t i = 0; i < 5; ++i) m[i] = static_cast<int>(i);

    m.shiftRight(1, 3); // сдвигает элементы [1,2,3] вправо на 1

    EXPECT_EQ(m[0], 0);
    EXPECT_EQ(m[2], 1); // было m[1]
    EXPECT_EQ(m[3], 2); // было m[2]
    EXPECT_EQ(m[4], 3); // было m[3]
}

TEST(MemDataTest, ShiftLeft) {
    MemData<int> m(10);
    for (size_t i = 0; i < 6; ++i) m[i] = static_cast<int>(i);

    m.shiftLeft(1, 3); // сдвигает элементы [2,3,4] влево на 1

    EXPECT_EQ(m[0], 0);
    EXPECT_EQ(m[1], 2); // было m[2]
    EXPECT_EQ(m[2], 3); // было m[3]
    EXPECT_EQ(m[3], 4); // было m[4]
}
