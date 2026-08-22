#include "tests_s21_containers.h"

TEST(MapTest, DefaultConstructor) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m.at(1), "a");
  EXPECT_EQ(m.at(2), "b");
  EXPECT_EQ(m.at(3), "c");
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  s21::map<int, std::string> m1(m);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.at(1), "a");
  EXPECT_EQ(m1.at(2), "b");
  EXPECT_EQ(m1.at(3), "c");
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  s21::map<int, std::string> m1(std::move(m));
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.at(1), "a");
  EXPECT_EQ(m1.at(2), "b");
  EXPECT_EQ(m1.at(3), "c");
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, Operator) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  s21::map<int, std::string> m1;
  m1 = std::move(m);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.at(1), "a");
  EXPECT_EQ(m1.at(2), "b");
  EXPECT_EQ(m1.at(3), "c");
}

TEST(MapTest, Find) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto it = m.find(5);
  EXPECT_EQ(it, m.end());
}

TEST(MapTest, AtThrow) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  EXPECT_THROW(m.at(5), std::out_of_range);
}

TEST(MapTest, Brackets) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto data = m[1];
  EXPECT_EQ(data, "a");
}

TEST(MapTest, Brackets2) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto data = m[4];
  EXPECT_EQ(m[4], "");
}

TEST(MapTest, Begin) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto it = m.begin();
  EXPECT_EQ(it->first, 1);
  EXPECT_EQ(it->second, "a");
}

TEST(MapTest, Insert) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto res = m.insert({4, "d"});
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->first, 4);
  EXPECT_EQ(res.first->second, "d");
}

TEST(MapTest, Clear) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  m.clear();
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, InsertKeyValue) {
  s21::map<int, std::string> m;
  auto res = m.insert(1, "a");
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->first, 1);
  EXPECT_EQ(res.first->second, "a");

  auto res2 = m.insert(1, "b");
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(res2.first->second, "a");
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, std::string> m;
  auto res1 = m.insert_or_assign(1, "a");
  EXPECT_TRUE(res1.second);
  EXPECT_EQ(res1.first->second, "a");

  auto res2 = m.insert_or_assign(1, "b");
  EXPECT_FALSE(res2.second);
  EXPECT_EQ(res2.first->second, "b");
}

TEST(MapTest, Erase) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}, {3, "c"}};
  auto it = m.find(2);
  m.erase(it);
  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ(m.contains(2), false);
  EXPECT_EQ(m.contains(1), true);
  EXPECT_EQ(m.contains(3), true);
}

TEST(MapTest, Swap) {
  s21::map<int, std::string> m1{{1, "a"}, {2, "b"}};
  s21::map<int, std::string> m2{{3, "c"}, {4, "d"}};

  m1.swap(m2);

  EXPECT_EQ(m1.size(), 2);
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m1.contains(4));

  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m2.contains(1));
  EXPECT_TRUE(m2.contains(2));
}

TEST(MapTest, Merge) {
  s21::map<int, std::string> m1{{1, "a"}, {2, "b"}};
  s21::map<int, std::string> m2{{2, "bb"}, {3, "c"}, {4, "d"}};

  m1.merge(m2);

  EXPECT_EQ(m1.size(), 4);
  EXPECT_TRUE(m1.contains(1));
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m1.contains(3));
  EXPECT_TRUE(m1.contains(4));

  EXPECT_EQ(m2.size(), 1);
  EXPECT_TRUE(m2.contains(2));
}

TEST(MapTest, Contains) {
  s21::map<int, std::string> m{{1, "a"}, {2, "b"}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_FALSE(m.contains(3));
}

TEST(MapTest, InsertMany) {
  s21::map<int, std::string> m;
  auto results = m.insert_many(std::make_pair(1, "a"), std::make_pair(2, "b"),
                               std::make_pair(1, "c"));

  EXPECT_EQ(m.size(), 2);
  EXPECT_EQ(m.at(1), "a");
  EXPECT_EQ(m.at(2), "b");

  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_FALSE(results[2].second);
}
