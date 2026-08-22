#include "tests_s21_containers.h"

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_EQ(q.size(), 0);
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, ConstructorInitializer) {
  s21::queue<int> q{1, 2, 3};
  EXPECT_EQ(q.size(), 3);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q{1, 2, 3};
  s21::queue<int> q_cp(q);

  EXPECT_EQ(q_cp.size(), q.size());

  while (!q.empty() && !q_cp.empty()) {
    EXPECT_EQ(q.front(), q_cp.front());
    q.pop();
    q_cp.pop();
  }

  EXPECT_TRUE(q.empty());
  EXPECT_TRUE(q_cp.empty());
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q{1, 2, 3};
  s21::queue<int> q_cp(std::move(q));

  EXPECT_EQ(q_cp.size(), 3);
  EXPECT_EQ(q_cp.front(), 1);
  EXPECT_EQ(q_cp.back(), 3);

  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, MoveOperator) {
  s21::queue<int> q{1, 2, 3};
  s21::queue<int> q_cp;
  q_cp = std::move(q);

  EXPECT_EQ(q_cp.size(), 3);
  EXPECT_EQ(q_cp.front(), 1);
  EXPECT_EQ(q_cp.back(), 3);

  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, FrontEmpty) {
  s21::queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
}

TEST(QueueTest, BackEmpty) {
  s21::queue<int> q;
  EXPECT_THROW(q.back(), std::out_of_range);
}

TEST(QueueTest, Push) {
  s21::queue<int> q{1, 2, 3};
  q.push(4);
  EXPECT_EQ(q.back(), 4);
}

TEST(QueueTest, PopEmpty) {
  s21::queue<int> q;
  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Swap) {
  s21::queue<int> q1{1, 2, 3, 4};
  s21::queue<int> q2{4, 5, 6};
  int q1_size = q1.size();
  int q1_front = q1.front();
  int q1_back = q1.back();
  int q2_size = q2.size();
  int q2_front = q2.front();
  int q2_back = q2.back();

  q1.swap(q2);
  EXPECT_EQ(q1.size(), q2_size);
  EXPECT_EQ(q1.front(), q2_front);
  EXPECT_EQ(q1.back(), q2_back);
  EXPECT_EQ(q2.size(), q1_size);
  EXPECT_EQ(q2.front(), q1_front);
  EXPECT_EQ(q2.back(), q1_back);
}
