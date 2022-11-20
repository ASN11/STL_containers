#include <gtest/gtest.h>

#include <set>

#include "s21_multiset.h"

TEST(multiset, 1) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26, 1, 1, 20, 20, 20};
  std::multiset<double> vc = {-3, 1,  -5, 42, 2,  -6, 8,
                              20, 26, 1,  1,  20, 20, 20};

  ASSERT_EQ(*v.begin(), *vc.begin());
  ASSERT_EQ(v.empty(), vc.empty());
  ASSERT_EQ(v.size(), vc.size());
  ASSERT_EQ(v.max_size(), vc.max_size());
}

TEST(multiset, 2) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26, 1, 1, 20, 20, 20};
  std::multiset<double> vc = {-3, 1,  -5, 42, 2,  -6, 8,
                              20, 26, 1,  1,  20, 20, 20};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset, 3) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  v.clear();
  vc.clear();
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset, 4) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  std::multiset<double> vc = {2,  -3, 20, -5, 1, -6, 8, 42,
                              26, 1,  1,  1,  8, 8,  8};
  v.insert(15);
  vc.insert(15);
  v.erase(v.begin());
  vc.erase(vc.begin());
  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset, 5) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::multiset<double> v1 = {100, 200, 300, 400, 500};
  std::multiset<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset, 6) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::set<double> v1 = {100, 200, 300, 400, 500};
  s21::set<double> vc = {-3, 1,  -5,  42,  2,   -6,  8,
                         20, 26, 100, 200, 300, 400, 500};
  v.merge(v1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(multiset, 7) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::multiset<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(*v.find(20), *vc.find(20));
}

TEST(multiset, 8) {
  s21::multiset<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(v.contains(100), false);
}

TEST(multiset, 9) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.lower_bound(8);
  --x;
  ASSERT_EQ(*x, 2);
}

TEST(multiset, 10) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.upper_bound(8);
  --x;
  ASSERT_EQ(*x, 8);
}

TEST(multiset, 11) {
  s21::multiset<double> v = {2, -3, 20, -5, 1, -6, 8, 42, 26, 1, 1, 1, 8, 8, 8};
  auto x = v.equal_range(8);
  ASSERT_EQ(*x.first, 8);
  ASSERT_EQ(*x.second, 20);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
