#include "tests_s21_containers.h"

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, InitializerConstructor) {
  s21::set<int> s{1, 2, 3, 4, 1};
  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2(s);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2(std::move(s));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
  EXPECT_TRUE(s.empty());
}

TEST(SetMoveAssignment, MovesElementsCorrectly) {
  s21::set<int> original{1, 2, 3};
  s21::set<int> moved;

  moved = std::move(original);

  EXPECT_EQ(moved.size(), 3);
  EXPECT_TRUE(moved.contains(1));
  EXPECT_TRUE(moved.contains(2));
  EXPECT_TRUE(moved.contains(3));

  EXPECT_EQ(original.size(), 0);
  EXPECT_TRUE(original.empty());
}

TEST(SetTest, BeginIterator) {
  s21::set<int> s{1, 2, 3};
  auto it = s.begin();
  EXPECT_EQ(*it, 1);
}

TEST(SetTest, EndIterator) {
  s21::set<int> s{1, 2, 3};
  auto it = s.end();
  --it;
  EXPECT_EQ(*it, 3);
}

TEST(SetTest, Empty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, Size) {
  s21::set<int> s{1, 2, 3};
  EXPECT_EQ(s.size(), 3);
}

TEST(SetTest, MaxSize) {
  s21::set<int> s;
  EXPECT_GT(s.max_size(), 0);
  EXPECT_GE(s.max_size(), s.size());
}

TEST(SetTest, Clear) {
  s21::set<int> s{1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
}

TEST(SetTest, InsertSuccess) {
  s21::set<int> s{1, 2, 3};
  auto res = s.insert(4);
  EXPECT_EQ(s.size(), 4);
  EXPECT_TRUE(s.contains(4));
  EXPECT_EQ(*res.first, 4);
  EXPECT_TRUE(res.second);
}

TEST(SetTest, InsertFailure) {
  s21::set<int> s{1, 2, 3};
  auto res = s.insert(3);
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(*res.first, 3);
  EXPECT_FALSE(res.second);
}

TEST(SetTest, Erase) {
  s21::set<int> s{1, 2, 3};
  auto it = s.begin();
  ++it;
  s.erase(it);
  EXPECT_EQ(s.size(), 2);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6, 7};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 4);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s1.contains(7));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{2, 3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
}

TEST(SetTest, Find) {
  s21::set<int> s1{1, 2, 3};
  auto res = s1.find(3);
  EXPECT_EQ(*res, 3);
}

TEST(SetTest, InsertMany) {
  s21::set<int> s1{1, 2, 3};
  auto res = s1.insert_many(3, 4, 5, 6, 7);
  EXPECT_EQ(*res[0].first, 3);
  EXPECT_FALSE(res[0].second);
  EXPECT_EQ(*res[1].first, 4);
  EXPECT_TRUE(res[1].second);
  EXPECT_EQ(*res[2].first, 5);
  EXPECT_TRUE(res[2].second);
  EXPECT_EQ(*res[3].first, 6);
  EXPECT_TRUE(res[3].second);
  EXPECT_EQ(*res[4].first, 7);
  EXPECT_TRUE(res[4].second);
}
