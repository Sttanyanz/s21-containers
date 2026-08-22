#include "tests_s21_containers.h"

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}
TEST(MultisetTest, MoveAssignment) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2;
  ms2 = std::move(ms1);

  EXPECT_TRUE(ms1.empty());
  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms{1, 2, 2, 3};
  EXPECT_EQ(ms.size(), 4);
  EXPECT_TRUE(ms.contains(1));
  EXPECT_TRUE(ms.contains(2));
  EXPECT_TRUE(ms.contains(3));
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1{1, 2, 3};
  s21::multiset<int> ms2(ms1);

  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1{1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));

  EXPECT_EQ(ms2.size(), 3);
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(MultisetTest, InsertAndCount) {
  s21::multiset<int> ms;
  ms.insert(5);
  ms.insert(5);
  ms.insert(7);

  EXPECT_EQ(ms.size(), 3);
  EXPECT_EQ(ms.count(5), 2);
  EXPECT_EQ(ms.count(7), 1);
  EXPECT_EQ(ms.count(10), 0u);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> ms{1, 2, 2, 3};
  auto it = ms.find(2);
  ms.erase(it);

  EXPECT_EQ(ms.size(), 3);
  EXPECT_EQ(ms.count(2), 1);
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> ms{1, 2, 3};
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> a{1, 2};
  s21::multiset<int> b{3, 4, 5};

  a.swap(b);

  EXPECT_EQ(a.size(), 3);
  EXPECT_EQ(b.size(), 2);
  EXPECT_TRUE(a.contains(3));
  EXPECT_TRUE(b.contains(1));
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> a{1, 2};
  s21::multiset<int> b{2, 3};

  a.merge(b);

  EXPECT_EQ(a.size(), 4);
  EXPECT_EQ(b.size(), 0);
  EXPECT_EQ(a.count(2), 2);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> ms{10, 20, 30};
  auto it = ms.find(20);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 20);
}

TEST(MultisetTest, Contains) {
  s21::multiset<int> ms{1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(100));
}

TEST(MultisetTest, EqualRange) {
  s21::multiset<int> ms{1, 2, 2, 3};
  auto range = ms.equal_range(2);

  int count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    EXPECT_EQ(*it, 2);
    count++;
  }
  EXPECT_EQ(count, 2);
}

TEST(MultisetTest, LowerBoundUpperBound) {
  s21::multiset<int> ms{1, 2, 3, 4};

  auto lb = ms.lower_bound(2);
  auto ub = ms.upper_bound(2);

  EXPECT_EQ(*lb, 2);
  EXPECT_EQ(*ub, 3);
}
