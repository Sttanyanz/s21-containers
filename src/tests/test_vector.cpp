#include "tests_s21_containers.h"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, ConstructorWithSizeType) {
  s21::vector<int> v(25);
  EXPECT_EQ(v.size(), 25);
  EXPECT_EQ(v.capacity(), 25);
  EXPECT_NE(v.data(), nullptr);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v.data()[i], 0);
  }
}

TEST(VectorTest, ConstructorWithZeroSize) {
  s21::vector<int> v(0);

  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, CoopyConstructor) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int> v_cp(v);

  EXPECT_EQ(v_cp.size(), v.size());
  EXPECT_EQ(v_cp.capacity(), v.capacity());

  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v_cp.data()[i], v.data()[i]);
  }

  EXPECT_NE(v_cp.data(), v.data());
}

TEST(VectorTest, CoopyConstructorWithNNull) {
  s21::vector<int> v(0);
  s21::vector<int> v_cp(v);

  EXPECT_EQ(v_cp.data(), nullptr);
}

TEST(VectorTest, MoveConstructorWithMove) {
  s21::vector<int> v{1, 2, 3};
  s21::vector<int> v_cp(std::move(v));
  EXPECT_EQ(v_cp.size(), 3);
  EXPECT_EQ(v_cp.capacity(), 3);
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
  EXPECT_EQ(v.data(), nullptr);
}

TEST(VectorTest, Swap) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{1, 2, 3, 5, 6};
  size_t v1_size = v1.size();
  size_t v1_capacity = v1.capacity();
  auto *v1_arr = v1.data();
  size_t v2_size = v2.size();
  size_t v2_capacity = v2.capacity();
  auto *v2_arr = v2.data();

  v1.swap(v2);

  EXPECT_EQ(v1.size(), v2_size);
  EXPECT_EQ(v1.capacity(), v2_capacity);
  EXPECT_EQ(v1.data(), v2_arr);
  EXPECT_EQ(v2.size(), v1_size);
  EXPECT_EQ(v2.capacity(), v1_capacity);
  EXPECT_EQ(v2.data(), v1_arr);
}

TEST(VectorTest, CopyOperator) {
  s21::vector<int> v1{1, 2, 3};
  s21::vector<int> v2{1, 2, 3, 5, 6};
  v1 = v2;
  EXPECT_EQ(v1.size(), v2.size());
  EXPECT_EQ(v1.capacity(), v2.capacity());
  for (size_t i = 0; i < v2.size(); ++i) {
    EXPECT_EQ(v1.data()[i], v2.data()[i]);
  }

  EXPECT_NE(v1.data(), v2.data());
}

TEST(VectorTest, CopyOperatorTheSameOne) {
  s21::vector<int> v1{1, 2, 3};
  v1 = v1;
  EXPECT_EQ(v1.size(), v1.size());
  EXPECT_EQ(v1.capacity(), v1.capacity());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.data()[i], v1.data()[i]);
  }
}

TEST(VectorTest, MoveOperator) {
  s21::vector<int> v1{1, 2, 3};

  s21::vector<int> temp{1, 2, 3, 4, 5, 6};
  v1 = std::move(temp);

  EXPECT_EQ(v1.size(), 6);
  EXPECT_EQ(v1.capacity(), 6);
  int expected[] = {1, 2, 3, 4, 5, 6};
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v1.data()[i], expected[i]);
  }

  EXPECT_EQ(temp.size(), 0);
  EXPECT_EQ(temp.capacity(), 0);
  EXPECT_EQ(temp.data(), nullptr);
}

TEST(VectorTest, AtTest) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1.at(2), 3);
}

TEST(VectorTest, AtTestErr) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_THROW(v1.at(3), std::out_of_range);
}

TEST(VectorTest, OperatorAt) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1[2], 3);
}

TEST(VectorTest, Front) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1.front(), 1);
}

TEST(VectorTest, Back) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1.back(), 3);
}

TEST(VectorTest, Begin) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1.begin(), v1.data());
}

TEST(VectorTest, End) {
  s21::vector<int> v1{1, 2, 3};

  EXPECT_EQ(v1.end(), v1.data() + v1.size());
}

TEST(VectorTest, MaxSizeCompare) {
  s21::vector<int> v1;
  s21::vector<char> v2;

  EXPECT_GE(v2.max_size(), v1.max_size());
}

TEST(VectorTest, ReserveBiggerThanMaxSize) {
  s21::vector<int> v1;
  size_t reservation = v1.max_size() + 1;

  EXPECT_THROW(v1.reserve(reservation), std::length_error);
}

TEST(VectorTest, ReserveTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.reserve(4);
  EXPECT_EQ(v1.capacity(), 4);
}

TEST(VectorTest, ShrinkToFitBiggerThanCapacity) {
  s21::vector<int> v1{1, 2, 3};
  v1.reserve(10);
  v1.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), v1.size());
}

TEST(VectorTest, ShrinkToFitNoChange) {
  s21::vector<int> v1{1, 2, 3};
  v1.shrink_to_fit();
  EXPECT_EQ(v1.capacity(), v1.size());
}

TEST(VectorTest, ClearTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.clear();
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, InsertTestAtBegin) {
  s21::vector<int> v1{1, 2, 3};
  v1.insert(v1.data(), 5);
  EXPECT_EQ(v1[0], 5);
}

TEST(VectorTest, InsertTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.insert(v1.begin() + 2, 5);
  EXPECT_EQ(v1[2], 5);
}

TEST(VectorTest, EraseTestAtBegin) {
  s21::vector<int> v1{1, 2, 3};
  v1.erase(v1.begin());
  EXPECT_EQ(v1[0], 2);
}

TEST(VectorTest, EraseTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.erase(v1.begin() + 1);
  EXPECT_EQ(v1[1], 3);
}

TEST(VectorTest, PushBackTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.push_back(10);
  EXPECT_EQ(v1[3], 10);
}

TEST(VectorTest, PopBackTest) {
  s21::vector<int> v1{1, 2, 3};
  v1.pop_back();
  EXPECT_EQ(v1.size(), 2);
}

TEST(VectorTest, PopBackTestNull) {
  s21::vector<int> v1;
  v1.pop_back();
  EXPECT_EQ(v1.size(), 0);
}

TEST(VectorTest, InsertManyTest) {
  s21::vector<int> v1{1, 2, 3, 4};
  v1.insert_many(v1.begin() + 1, 2, 2, 2);
  EXPECT_EQ(v1.size(), 7);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 2);
  EXPECT_EQ(v1[3], 2);
  EXPECT_EQ(v1[4], 2);
  EXPECT_EQ(v1[5], 3);
  EXPECT_EQ(v1[6], 4);
}

TEST(VectorTest, InsertManyBackTest) {
  s21::vector<int> v1{1, 2, 3, 4};
  v1.insert_many_back(2, 2, 2, 2);
  EXPECT_EQ(v1.size(), 8);
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[1], 2);
  EXPECT_EQ(v1[2], 3);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 2);
  EXPECT_EQ(v1[5], 2);
  EXPECT_EQ(v1[6], 2);
  EXPECT_EQ(v1[7], 2);
}
