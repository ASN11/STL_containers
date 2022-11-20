#include <gtest/gtest.h>

#include "s21_queue.h"

namespace s21 {
TEST(Constructors, Default) {
  s21_queue<int> queue;
  EXPECT_EQ(queue.empty(), true);
}

TEST(Constructors, InitList) {
  s21_queue<int> queue = {1, 2, 3, 4, 5};
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 5);
  EXPECT_EQ(queue.size(), 5);
}

TEST(Constructors, Copy) {
  s21_queue<int> queue = {5, 3, 1, 9, 6, 7};
  s21_queue<int> second = queue;

  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Constructors, Move) {
  s21_queue<int> queue = {5, 3, 1, 9, 6, 7};
  s21_queue<int> second(std::move(queue));

  EXPECT_EQ(queue.size(), 0);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Constructors, OperatorMove) {
  s21_queue<int> queue = {5, 3, 1, 9, 6, 7};
  s21_queue<int> second;
  second = std::move(queue);

  EXPECT_EQ(queue.size(), 0);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);

  second = std::move(second);
  EXPECT_EQ(second.front(), 5);
  EXPECT_EQ(second.back(), 7);
  EXPECT_EQ(second.size(), 6);
}

TEST(Queue, ElementAccess) {
  s21_queue<int> queue = {111, 222, 333, 444, 555, 666};
  EXPECT_EQ(queue.front(), 111);
  EXPECT_EQ(queue.back(), 666);
  queue.pop();
  EXPECT_EQ(queue.front(), 222);
  queue.push(777);
  EXPECT_EQ(queue.back(), 777);
}

TEST(Queue, Capacity) {
  s21_queue<int> queue;
  EXPECT_EQ(queue.empty(), true);
  EXPECT_EQ(queue.size(), 0);
  queue.push(1);
  queue.push(2);
  EXPECT_EQ(queue.empty(), false);
  EXPECT_EQ(queue.size(), 2);
}

TEST(QueueModifiers, Push) {
  s21_queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  queue.push(4);
  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 4);
}

TEST(QueueModifiers, Pop) {
  s21_queue<int> queue;
  queue.push(11);
  queue.push(22);
  queue.push(33);
  queue.pop();
  queue.pop();
  EXPECT_EQ(queue.front(), 33);
  EXPECT_EQ(queue.back(), 33);

  queue.pop();
  EXPECT_ANY_THROW(queue.pop());
}

TEST(QueueModifiers, Swap) {
  s21_queue<int> queue = {10, 20, 30, 40};
  s21_queue<int> second = {1, 2, 3, 4, 5, 6, 7, 8};

  queue.swap(second);

  EXPECT_EQ(queue.front(), 1);
  EXPECT_EQ(queue.back(), 8);
  EXPECT_EQ(queue.size(), 8);

  EXPECT_EQ(second.front(), 10);
  EXPECT_EQ(second.back(), 40);
  EXPECT_EQ(second.size(), 4);
}

TEST(QueueModifiers, EmplaceBack) {
  s21_queue<int> queue = {10, 20, 30, 40};
  queue.emplace_back(1, 2, 3, 4, 5, 6, 7, 8);

  EXPECT_EQ(queue.front(), 10);
  EXPECT_EQ(queue.back(), 8);
  EXPECT_EQ(queue.size(), 12);
}
}  // namespace s21

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
