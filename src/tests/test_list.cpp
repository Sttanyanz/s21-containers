#include "tests_s21_containers.h"

TEST(ListTest, DefaultConstructor) {
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, ParameterizedConstructor) {
  s21::list<int> l(5);
  EXPECT_FALSE(l.empty());
  EXPECT_EQ(l.size(), 5);
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> l{1, 2, 3, 4, 5};
  EXPECT_EQ(l.size(), 5);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 5);
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> copy(original);

  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.front(), copy.front());
  EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> moved(std::move(original));

  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(ListTest, CopyAssignment) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> copy;
  copy = original;

  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.front(), copy.front());
  EXPECT_EQ(original.back(), copy.back());
}

TEST(ListTest, MoveAssignment) {
  s21::list<int> original{1, 2, 3};
  s21::list<int> moved;
  moved = std::move(original);

  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.front(), 1);
  EXPECT_EQ(moved.back(), 3);
  EXPECT_TRUE(original.empty());
}

TEST(ListTest, FrontAndBack) {
  s21::list<int> l{10, 20, 30};
  EXPECT_EQ(l.front(), 10);
  EXPECT_EQ(l.back(), 30);
}

TEST(ListTest, Iterators) {
  s21::list<int> l{1, 2, 3};

  auto it = l.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, l.end());
}

TEST(ListTest, ConstIterators) {
  const s21::list<int> l{1, 2, 3};

  auto it = l.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, PushBack) {
  s21::list<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);

  EXPECT_EQ(l.size(), 3);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, PushFront) {
  s21::list<int> l;
  l.push_front(3);
  l.push_front(2);
  l.push_front(1);

  EXPECT_EQ(l.size(), 3);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 3);
}

TEST(ListTest, PopBack) {
  s21::list<int> l{1, 2, 3};
  l.pop_back();

  EXPECT_EQ(l.size(), 2);
  EXPECT_EQ(l.back(), 2);
}

TEST(ListTest, PopFront) {
  s21::list<int> l{1, 2, 3};
  l.pop_front();

  EXPECT_EQ(l.size(), 2);
  EXPECT_EQ(l.front(), 2);
}

TEST(ListTest, Insert) {
  s21::list<int> l{1, 3, 4};
  auto it = l.begin();
  ++it;  // points to 3

  auto new_it = l.insert(it, 2);

  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*new_it, 2);

  // Check order: 1, 2, 3, 4
  auto check_it = l.begin();
  EXPECT_EQ(*check_it++, 1);
  EXPECT_EQ(*check_it++, 2);
  EXPECT_EQ(*check_it++, 3);
  EXPECT_EQ(*check_it++, 4);
}

TEST(ListTest, Erase) {
  s21::list<int> l{1, 2, 3, 4};
  auto it = l.begin();
  ++it;  // points to 2

  l.erase(it);

  EXPECT_EQ(l.size(), 3);

  // Check order: 1, 3, 4
  auto check_it = l.begin();
  EXPECT_EQ(*check_it++, 1);
  EXPECT_EQ(*check_it++, 3);
  EXPECT_EQ(*check_it++, 4);
}

TEST(ListTest, Clear) {
  s21::list<int> l{1, 2, 3};
  l.clear();

  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0);
}

TEST(ListTest, Swap) {
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2{4, 5, 6, 7};

  l1.swap(l2);

  EXPECT_EQ(l1.size(), 4);
  EXPECT_EQ(l2.size(), 3);
  EXPECT_EQ(l1.front(), 4);
  EXPECT_EQ(l2.front(), 1);
}

TEST(ListTest, Reverse) {
  s21::list<int> l{1, 2, 3, 4, 5};
  l.reverse();

  EXPECT_EQ(l.front(), 5);
  EXPECT_EQ(l.back(), 1);

  // Check order: 5, 4, 3, 2, 1
  auto it = l.begin();
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 1);
}

TEST(ListTest, Unique) {
  s21::list<int> l{1, 1, 2, 3, 3, 3, 4, 5, 5};
  l.unique();

  EXPECT_EQ(l.size(), 5);

  // Check order: 1, 2, 3, 4, 5
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
}

TEST(ListTest, Sort) {
  s21::list<int> l{5, 3, 1, 4, 2};
  l.sort();

  // Check order: 1, 2, 3, 4, 5
  auto it = l.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
}

TEST(ListTest, Merge) {
  s21::list<int> l1{1, 3, 5};
  s21::list<int> l2{2, 4, 6};

  l1.merge(l2);

  EXPECT_EQ(l1.size(), 6);
  EXPECT_TRUE(l2.empty());

  // Check order: 1, 2, 3, 4, 5, 6
  auto it = l1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
  EXPECT_EQ(*it++, 6);
}

TEST(ListTest, Splice) {
  s21::list<int> l1{1, 4, 5};
  s21::list<int> l2{2, 3};

  auto pos = l1.begin();
  ++pos;  // points to 4

  l1.splice(pos, l2);

  EXPECT_EQ(l1.size(), 5);
  EXPECT_TRUE(l2.empty());

  // Check order: 1, 2, 3, 4, 5
  auto it = l1.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it++, 2);
  EXPECT_EQ(*it++, 3);
  EXPECT_EQ(*it++, 4);
  EXPECT_EQ(*it++, 5);
}

TEST(ListTest, EqualityOperator) {
  s21::list<int> l1{1, 2, 3};
  s21::list<int> l2{1, 2, 3};
  s21::list<int> l3{1, 2, 4};

  EXPECT_TRUE(l1 == l2);
  EXPECT_FALSE(l1 == l3);
}

TEST(ListTest, MaxSize) {
  s21::list<int> l;
  EXPECT_GT(l.max_size(), 0);
}

TEST(ListTest, InsertMany) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  int args[] = {10, 20, 30};
  s21::list<int> expected_list{1, 2, 10, 20, 30, 3, 4, 5};

  auto it = actual_list.insert_many(++(++actual_list.begin()), args[0], args[1],
                                    args[2]);

  EXPECT_EQ(++(++actual_list.begin()), it);
  EXPECT_EQ(expected_list, actual_list);
}

TEST(ListTest, InsertManyNoArgs) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  s21::list<int> expected_list(actual_list);

  auto it = actual_list.insert_many(++(++actual_list.begin()));

  EXPECT_EQ(++(++actual_list.begin()), it);
  EXPECT_EQ(expected_list, actual_list);
}

TEST(ListTest, InsertManyFront) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  int args[] = {10, 20, 30};
  s21::list<int> expected_list{10, 20, 30, 1, 2, 3, 4, 5};

  actual_list.insert_many_front(args[0], args[1], args[2]);

  EXPECT_EQ(expected_list, actual_list);
}

TEST(ListTest, InsertManyFrontNoArgs) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  s21::list<int> expected_list(actual_list);

  actual_list.insert_many_front();

  EXPECT_EQ(expected_list, actual_list);
}

TEST(ListTest, InsertManyBack) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  int args[] = {10, 20, 30};
  s21::list<int> expected_list{1, 2, 3, 4, 5, 10, 20, 30};

  actual_list.insert_many_back(args[0], args[1], args[2]);

  EXPECT_EQ(expected_list, actual_list);
}

TEST(ListTest, InsertManyBackNoArgs) {
  s21::list<int> actual_list{1, 2, 3, 4, 5};
  s21::list<int> expected_list(actual_list);

  actual_list.insert_many_back();

  EXPECT_EQ(expected_list, actual_list);
}

//------------------------------------------------------------------------------------

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> st = {1, 2, 3, 4, 5};
  EXPECT_EQ(st.size(), 5);
  EXPECT_EQ(st.top(), 5);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2(st1);

  EXPECT_EQ(st1.size(), st2.size());
  EXPECT_EQ(st1.top(), st2.top());

  st1.pop();
  EXPECT_NE(st1.top(), st2.top());
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2(std::move(st1));

  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);
  EXPECT_TRUE(st1.empty());
}

TEST(StackTest, PushAndTop) {
  s21::stack<int> st;
  st.push(10);
  EXPECT_EQ(st.top(), 10);

  st.push(20);
  EXPECT_EQ(st.top(), 20);

  st.push(30);
  EXPECT_EQ(st.top(), 30);
}

TEST(StackTest, Pop) {
  s21::stack<int> st = {1, 2, 3};

  EXPECT_EQ(st.top(), 3);
  st.pop();
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_TRUE(st.empty());
}

TEST(StackTest, EmptyAndSize) {
  s21::stack<int> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);

  st.push(1);
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), 1);

  st.pop();
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);
}

TEST(StackTest, Swap) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2 = {4, 5, 6, 7};

  size_t size1 = st1.size();
  size_t size2 = st2.size();
  int top1 = st1.top();
  int top2 = st2.top();

  st1.swap(st2);

  EXPECT_EQ(st1.size(), size2);
  EXPECT_EQ(st2.size(), size1);
  EXPECT_EQ(st1.top(), top2);
  EXPECT_EQ(st2.top(), top1);
}

TEST(StackTest, AssignmentOperator) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2;

  st2 = st1;
  EXPECT_EQ(st1.size(), st2.size());
  EXPECT_EQ(st1.top(), st2.top());
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> st1 = {1, 2, 3};
  s21::stack<int> st2;

  st2 = std::move(st1);
  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);
  EXPECT_TRUE(st1.empty());
}

TEST(StackTest, ExceptionOnEmptyPop) {
  s21::stack<int> st;
  EXPECT_THROW(st.pop(), std::out_of_range);
}

TEST(StackTest, InsertManyBack) {
  s21::stack<int> actual_stack{1, 2, 3, 4, 5};
  int args[] = {10, 20, 30};
  s21::stack<int> expected_stack{1, 2, 3, 4, 5, 10, 20, 30};

  actual_stack.insert_many_back(args[0], args[1], args[2]);

  ASSERT_EQ(expected_stack.size(), actual_stack.size());

  while (!actual_stack.empty()) {
    EXPECT_EQ(expected_stack.top(), actual_stack.top());
    expected_stack.pop(), actual_stack.pop();
  }
}

TEST(StackTest, InsertManyBackNoArgs) {
  s21::stack<int> actual_stack{1, 2, 3, 4, 5};
  s21::stack<int> expected_stack(actual_stack);

  actual_stack.insert_many_back();

  ASSERT_EQ(expected_stack.size(), actual_stack.size());

  while (!actual_stack.empty()) {
    EXPECT_EQ(expected_stack.top(), actual_stack.top());
    expected_stack.pop(), actual_stack.pop();
  }
}
