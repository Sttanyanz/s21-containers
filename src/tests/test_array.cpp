#include "tests_s21_containers.h"

// Проверка конструктора по умолчанию
TEST(S21ArrayTest, DefaultConstructor) {
  s21::array<int, 3> arr;
  EXPECT_EQ(arr.size(), 3);
  for (size_t i = 0; i < arr.size(); ++i) EXPECT_EQ(arr[i], 0);
}

// Проверка конструктора initializer_list
TEST(S21ArrayTest, InitializerListConstructor) {
  ::s21::array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

// Проверка конструктора копирования
TEST(S21ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1{4, 5, 6};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(arr2[0], 4);
  EXPECT_EQ(arr2[1], 5);
  EXPECT_EQ(arr2[2], 6);
}

// Проверка конструктора перемещения
TEST(S21ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1{7, 8, 9};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2[0], 7);
  EXPECT_EQ(arr2[1], 8);
  EXPECT_EQ(arr2[2], 9);
}

// Проверка оператора присваивания перемещением
TEST(S21ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 3> arr1{1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

// Проверка метода at()
TEST(S21ArrayTest, AtMethod) {
  s21::array<int, 3> arr{3, 5, 7};
  EXPECT_EQ(arr.at(2), 7);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

// Проверка метода front() и back()
TEST(S21ArrayTest, FrontBackMethods) {
  s21::array<int, 3> arr{2, 4, 8};
  EXPECT_EQ(arr.front(), 2);
  EXPECT_EQ(arr.back(), 8);
}

// Проверка метода data()
TEST(S21ArrayTest, DataMethod) {
  s21::array<int, 3> arr{1, 2, 3};
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);
}

// Проверка методов begin() / end()
TEST(S21ArrayTest, IteratorMethods) {
  s21::array<int, 3> arr{11, 12, 13};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) sum += *it;
  EXPECT_EQ(sum, 36);
}

// Проверка empty(), size(), max_size()
TEST(S21ArrayTest, SizeMethods) {
  s21::array<int, 3> arr;
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr.max_size(), 3);
}

// Проверка fill()
TEST(S21ArrayTest, FillMethod) {
  s21::array<int, 3> arr;
  arr.fill(42);
  for (size_t i = 0; i < arr.size(); ++i) EXPECT_EQ(arr[i], 42);
}

// Проверка swap()
TEST(S21ArrayTest, SwapMethod) {
  s21::array<int, 3> arr1{1, 2, 3};
  s21::array<int, 3> arr2{4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

// Проверка InitializerList: больше элементов, чем размер
TEST(S21ArrayTest, InitializerListTooManyElements) {
  s21::array<int, 3> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);  // лишние элементы игнорируются
}

// InitializerList: меньше элементов
TEST(S21ArrayTest, InitializerListTooFewElements) {
  s21::array<int, 5> arr{42};
  EXPECT_EQ(arr[0], 42);
  for (size_t i = 1; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);  // хвост должен быть заполнен T{}
  }
}

// at(): успешный доступ
TEST(S21ArrayTest, AtMethodReturn) {
  s21::array<int, 2> arr{10, 20};
  EXPECT_EQ(arr.at(1), 20);  // проверяем ветку return
}
