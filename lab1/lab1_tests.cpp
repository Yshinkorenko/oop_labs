#include "gtest/gtest.h"
#include "BitArray.h"

// Простые тесты
TEST(BitArrayTest, DefaultConstructor) {
    BitArray a;
    ASSERT_EQ(a.size(), 0);
    ASSERT_TRUE(a.empty());
}

TEST(BitArrayTest, ConstructorWithSize) {
    BitArray a(10);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.count(), 0);
    ASSERT_FALSE(a.empty());
}

TEST(BitArrayTest, ConstructorWithValue) {
    BitArray a(8, 0b10101010);
    ASSERT_EQ(a.size(), 8);
    ASSERT_EQ(a.count(), 4);
    ASSERT_EQ(a.to_string(), "10101010");
}

TEST(BitArrayTest, CopyConstructor) {
    BitArray a(8, 0b10101010);
    BitArray b(a);
    ASSERT_EQ(b.size(), 8);
    ASSERT_EQ(b.to_string(), "10101010");
}

// Тесты resize
TEST(BitArrayTest, ResizeSmaller) {
    BitArray a(10, 0b1111111111);
    a.resize(5);
    ASSERT_EQ(a.size(), 5);
    ASSERT_EQ(a.to_string(), "11111");
}

TEST(BitArrayTest, ResizeLargerWithZeros) {
    BitArray a(5, 0b11111);
    a.resize(10);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.to_string(), "0000011111");
}

TEST(BitArrayTest, ResizeLargerWithOnes) {
    BitArray a(5, 0b11111);
    a.resize(10, true);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.to_string(), "1111111111");
}

// Тесты set/reset
TEST(BitArrayTest, SetBit) {
    BitArray a(5);
    a.set(2);
    ASSERT_EQ(a.to_string(), "00100");
}

TEST(BitArrayTest, ResetBit) {
    BitArray a(5, 0b11111);
    a.reset(2);
    ASSERT_EQ(a.to_string(), "11011");
}

TEST(BitArrayTest, SetAll) {
    BitArray a(5);
    a.set();
    ASSERT_EQ(a.to_string(), "11111");
}

TEST(BitArrayTest, ResetAll) {
    BitArray a(5, 0b11111);
    a.reset();
    ASSERT_EQ(a.to_string(), "00000");
}

// Тесты any/none
TEST(BitArrayTest, AnyTrue) {
    BitArray a(5, 0b10000);
    ASSERT_TRUE(a.any());
}

TEST(BitArrayTest, AnyFalse) {
    BitArray a(5);
    ASSERT_FALSE(a.any());
}

TEST(BitArrayTest, NoneTrue) {
    BitArray a(5);
    ASSERT_TRUE(a.none());
}

TEST(BitArrayTest, NoneFalse) {
    BitArray a(5, 0b1);
    ASSERT_FALSE(a.none());
}

// Тесты push_back
TEST(BitArrayTest, PushBackTrue) {
    BitArray a(3, 0b101);
    a.push_back(true);
    ASSERT_EQ(a.to_string(), "1101");
}

TEST(BitArrayTest, PushBackFalse) {
    BitArray a(3, 0b101);
    a.push_back(false);
    ASSERT_EQ(a.to_string(), "0101");
}

// Тесты сдвигов
TEST(BitArrayTest, LeftShift) {
    BitArray a(8, 0b11001010);
    BitArray b = a << 3;
    ASSERT_EQ(b.to_string(), "01010000");
}

TEST(BitArrayTest, RightShift) {
    BitArray a(8, 0b11001010);
    BitArray b = a >> 3;
    ASSERT_EQ(b.to_string(), "00011001");
}

// Тесты побитовых операций
TEST(BitArrayTest, BitwiseAND) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b10101010);
    BitArray c = a & b;
    ASSERT_EQ(c.to_string(), "10001010");
}

TEST(BitArrayTest, BitwiseOR) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b10101010);
    BitArray c = a | b;
    ASSERT_EQ(c.to_string(), "11101010");
}

TEST(BitArrayTest, BitwiseXOR) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b10101010);
    BitArray c = a ^ b;
    ASSERT_EQ(c.to_string(), "01100000");
}

// Тесты сравнения
TEST(BitArrayTest, EqualityTrue) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b11001010);
    ASSERT_TRUE(a == b);
}

TEST(BitArrayTest, EqualityFalse) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b10101010);
    ASSERT_FALSE(a == b);
}

TEST(BitArrayTest, InequalityTrue) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b10101010);
    ASSERT_TRUE(a != b);
}

TEST(BitArrayTest, InequalityFalse) {
    BitArray a(8, 0b11001010);
    BitArray b(8, 0b11001010);
    ASSERT_FALSE(a != b);
}

// Тесты на инверсию
TEST(BitArrayTest, BitwiseNOT) {
    BitArray a(8, 0b11001010);
    BitArray b = ~a;
    ASSERT_EQ(b.to_string(), "00110101");
}

// Тесты для больших массивов
TEST(BitArrayTest, LargeArraySetAndCount) {
    int size = 100000;
    BitArray a(size);
    a.set();
    ASSERT_EQ(a.count(), size);
}

TEST(BitArrayTest, LargeArrayResetAndNone) {
    int size = 100000;
    BitArray a(size);
    a.reset();
    ASSERT_TRUE(a.none());
}

