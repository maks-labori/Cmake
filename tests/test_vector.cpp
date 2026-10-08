#include "gtest/gtest.h"
#include "vector.h"
TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_TRUE(v.isEmpty());
}

TEST(VectorTest, ConstructorWithSize) {
    Vector<int> v(5);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorTest, ConstructorWithArray) {
    int arr[] = { 1, 2, 3, 4, 5 };
    Vector<int> v(5, arr);
    EXPECT_EQ(v.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i], arr[i]);
    }
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<int> v{ 1, 2, 3, 4, 5 };
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1{ 1, 2, 3 };
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> v1{ 1, 2, 3 };
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v1.size(), 0u);
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushFront) {
    Vector<int> v;
    v.pushFront(1);
    v.pushFront(2);
    v.pushFront(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 1);
}

TEST(VectorTest, PushFrontMany) {
    Vector<int> v;
    int arr[] = { 1, 2, 3 };
    v.pushFrontMany(arr, 3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PushBackMany) {
    Vector<int> v;
    int arr[] = { 1, 2, 3 };
    v.pushBackMany(arr, 3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, PopBack) {
    Vector<int> v{ 1, 2, 3 };
    v.popBack();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, PopBackEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.popBack(), std::logic_error);
}

TEST(VectorTest, PopFront) {
    Vector<int> v{ 1, 2, 3 };
    v.popFront();
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, PopFrontEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.popFront(), std::logic_error);
}

TEST(VectorTest, Insert) {
    Vector<int> v{ 1, 2, 4, 5 };
    v.insert(3, 2);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(v[3], 4);
    EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, InsertAtBeginning) {
    Vector<int> v{ 2, 3 };
    v.insert(1, 0);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, InsertAtEnd) {
    Vector<int> v{ 1, 2 };
    v.insert(3, 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, InsertOutOfRange) {
    Vector<int> v{ 1, 2, 3 };
    EXPECT_THROW(v.insert(5, 10), std::out_of_range);
}

TEST(VectorTest, Erase) {
    Vector<int> v{ 1, 2, 3, 4, 5 };
    v.erase(2);
    EXPECT_EQ(v.size(), 4u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 4);
    EXPECT_EQ(v[3], 5);
}

TEST(VectorTest, EraseFirst) {
    Vector<int> v{ 1, 2, 3 };
    v.erase(0);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, EraseLast) {
    Vector<int> v{ 1, 2, 3 };
    v.erase(2);
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(v[1], 2);
}

TEST(VectorTest, EraseOutOfRange) {
    Vector<int> v{ 1, 2, 3 };
    EXPECT_THROW(v.erase(5), std::out_of_range);
}

TEST(VectorTest, Front) {
    Vector<int> v{ 1, 2, 3 };
    EXPECT_EQ(v.front(), 1);
}

TEST(VectorTest, Back) {
    Vector<int> v{ 1, 2, 3 };
    EXPECT_EQ(v.back(), 3);
}

TEST(VectorTest, FrontEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.front(), std::logic_error);
}

TEST(VectorTest, BackEmpty) {
    Vector<int> v;
    EXPECT_THROW(v.back(), std::logic_error);
}

TEST(VectorTest, ResizeSmaller) {
    Vector<int> v{ 1, 2, 3, 4, 5 };
    v.resize(3);
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, ResizeLarger) {
    Vector<int> v{ 1, 2, 3 };
    v.resize(5);
    EXPECT_EQ(v.size(), 5u);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, Clear) {
    Vector<int> v{ 1, 2, 3 };
    v.clear();
    EXPECT_EQ(v.size(), 0u);
    EXPECT_TRUE(v.isEmpty());
}

TEST(VectorTest, CopyAssignment) {
    Vector<int> v1{ 1, 2, 3 };
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v2[0], 1);
}

TEST(VectorTest, MoveAssignment) {
    Vector<int> v1{ 1, 2, 3 };
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3u);
    EXPECT_EQ(v1.size(), 0u);
}

TEST(VectorTest, EqualitySameContentDifferentLayout) {
    Vector<int> v1;
    v1.pushBack(1);
    v1.pushBack(2);

    Vector<int> v2;
    v2.pushFront(2);
    v2.pushFront(1);

    // Содержимое одинаковое: [1, 2]
    EXPECT_EQ(v1[0], v2[0]);
    EXPECT_EQ(v1[1], v2[1]);

    EXPECT_TRUE(v1 == v2);
}

TEST(VectorTest, Inequality) {
    Vector<int> v1{ 1, 2, 3 };
    Vector<int> v2{ 1, 2, 4 };
    EXPECT_FALSE(v1 == v2);
}

TEST(VectorTest, IteratorBasic) {
    Vector<int> v{ 1, 2, 3, 4, 5 };
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);
}

TEST(VectorTest, IteratorDecrement) {
    Vector<int> v{ 1, 2, 3 };
    auto it = v.end();
    --it;
    EXPECT_EQ(*it, 3);
    --it;
    EXPECT_EQ(*it, 2);
}

TEST(VectorTest, IteratorArithmetic) {
    Vector<int> v{ 10, 20, 30, 40, 50 };
    auto it = v.begin();
    it += 2;
    EXPECT_EQ(*it, 30);
    it -= 1;
    EXPECT_EQ(*it, 20);
}

TEST(VectorTest, EmptyVectorIterator_FAILS_DUE_TO_BUG) {
    Vector<int> v;
    // begin() и end() вызывают front() и back(), которые бросают исключение
    EXPECT_NO_THROW({
        auto b = v.begin();
        auto e = v.end();
        EXPECT_EQ(b, e);
        });
}

TEST(VectorTest, ConstIterator) {
    const Vector<int> v{ 1, 2, 3 };
    int sum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, ManyPushFrontAndBack) {
    Vector<int> v;
    for (int i = 0; i < 100; ++i) {
        if (i % 2 == 0) v.pushBack(i);
        else v.pushFront(i);
    }
    EXPECT_EQ(v.size(), 100u);
}

TEST(VectorTest, OutputOperator) {
    Vector<int> v{ 1, 2, 3 };
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "{1 2 3}\n");
}

TEST(VectorTest, InputOperator) {
    std::stringstream ss("10 20 30");
    Vector<int> v;
    ss >> v;
    EXPECT_EQ(v.size(), 3u);
    EXPECT_EQ(v[0], 10);
    EXPECT_EQ(v[2], 30);
}

