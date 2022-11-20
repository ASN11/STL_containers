#include <gtest/gtest.h>

#include "s21_stack.h"

namespace s21 {
TEST(Constructors, Default) {
  s21_stack<double> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.top());
}

TEST(Constructors, InitList) {
  s21_stack<double> stack = {1.23, 23.3, 3.13, 99.999, 55.55};
  EXPECT_EQ(stack.top(), 55.55);
  EXPECT_EQ(stack.size(), 5);
}

TEST(Constructors, Copy) {
  s21_stack<int> stack = {9, 7, 5, 3, 1, 4, 8};
  s21_stack<int> second = stack;

  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Constructors, Move) {
  s21_stack<int> stack = {9, 7, 5, 3, 1, 4, 8};
  s21_stack<int> second(std::move(stack));

  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.top());
  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Constructors, OperatorMove) {
  s21_stack<int> stack = {9, 7, 5, 3, 1, 4, 8};
  s21_stack<int> second;
  second = std::move(stack);

  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.top());
  EXPECT_EQ(second.top(), 8);
  EXPECT_EQ(second.size(), 7);
}

TEST(Stack, ElementAccess) {
  s21_stack<int> stack = {9, 7, 5, 3, 1, 4, 8};
  EXPECT_EQ(stack.top(), 8);
}

TEST(Stack, Capacity) {
  s21_stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_EQ(stack.empty(), true);
  stack.push(11);
  stack.push(22);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.empty(), false);
}

TEST(StackModifiers, Push) {
  s21_stack<int> stack;
  EXPECT_ANY_THROW(stack.top());
  stack.push(11);
  EXPECT_EQ(stack.top(), 11);
  stack.push(22);
  EXPECT_EQ(stack.top(), 22);
}

TEST(StackModifiers, Pop) {
  s21_stack<int> stack;
  EXPECT_ANY_THROW(stack.pop());
  stack.push(11);
  stack.push(22);
  EXPECT_EQ(stack.top(), 22);
  stack.pop();
  EXPECT_EQ(stack.top(), 11);
}

TEST(StackModifiers, Swap) {
  s21_stack<int> stack = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_stack<int> second = {16, 32, 64, 96};
  stack.swap(second);

  EXPECT_EQ(stack.size(), 4);
  EXPECT_EQ(stack.top(), 96);
  EXPECT_EQ(second.size(), 10);
  EXPECT_EQ(second.top(), 10);
}

TEST(StackModifiers, EmplaceFront) {
  s21_stack<int> stack = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  stack.emplace_front(16, 32, 64, 96);

  EXPECT_EQ(stack.size(), 14);
  EXPECT_EQ(stack.top(), 96);
}

}  // namespace s21

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
