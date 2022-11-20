#include <gtest/gtest.h>

#include <set>

#include "s21_set.h"

TEST(set, 1) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::set<double> v1 = v;
  std::set<double> vc1 = vc;

  ASSERT_EQ(*v1.begin(), *vc1.begin());
  ASSERT_EQ(v1.empty(), vc1.empty());
  ASSERT_EQ(v1.size(), vc1.size());
  ASSERT_EQ(v1.max_size(), vc1.max_size());
}

TEST(set, 2) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(set, 3) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  v.clear();
  vc.clear();
  auto x = v.begin();
  auto y = vc.begin();

  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(set, 4) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
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

TEST(set, 5) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  s21::set<double> v1 = {100, 200, 300, 400, 500};
  std::set<double> vc1 = {100, 200, 300, 400, 500};
  v.swap(v1);
  vc.swap(vc1);

  auto x = v.begin();
  auto y = vc.begin();
  for (; x != v.end(); ++x, ++y) {
    ASSERT_EQ(*x, *y);
  }
}

TEST(set, 6) {
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

TEST(set, 7) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> vc = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(*v.find(20), *vc.find(20));
}

TEST(set, 8) {
  s21::set<double> v = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  ASSERT_EQ(v.contains(100), false);
}

TEST(set, 9) {
  s21::set<double> s = {-3, 1, -5, 42, 2, -6, 8, 20, 26};
  std::set<double> o = {-3, 1, -5, 42, 2, -6, 8, 20, 26};

  auto r = s.emplace(100, 200, 42, 400);

  auto pr1 = o.emplace(100);
  auto pr2 = o.emplace(200);
  auto pr3 = o.emplace(42);
  auto pr4 = o.emplace(400);

  EXPECT_EQ(*(r[0].first), *(pr1.first));
  EXPECT_EQ(r[0].second, pr1.second);

  EXPECT_EQ(*(r[1].first), *(pr2.first));
  EXPECT_EQ(r[1].second, pr2.second);

  EXPECT_EQ(*(r[2].first), *(pr3.first));
  EXPECT_EQ(r[2].second, pr3.second);

  EXPECT_EQ(*(r[3].first), *(pr4.first));
  EXPECT_EQ(r[3].second, pr4.second);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
