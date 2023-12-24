#include "pch.h"
#include "../TStack.h"

// конструктор преобразования типа

TEST(TStack, can_create_stack_with_positive_size) {
	ASSERT_NO_THROW(TStack<int> st(3));
}
 
TEST(TStack, cant_create_stack_with_null_size) {
	ASSERT_ANY_THROW(TStack<int> st(0));
}

TEST(TStack, cant_create_stack_with_negative_size) {
	ASSERT_ANY_THROW(TStack<int> st(-10));
}

TEST(TStack, created_with_default_constructor_stack_is_empty) {
	TStack<int> st(10);

	ASSERT_ANY_THROW(st.Pop());
}

// конструктор копирования

TEST(TStack, can_create_copy_stack) {
	int n = 100;
	
	TStack<double> st1(n);
	
	for (int i = 0; i < n; ++i)
		st1.Push(i);

	ASSERT_NO_THROW(TStack<double> st2(st1));
}

TEST(TStack, stack_and_created_copy_stack_equal) {
	int n = 100;

	TStack<double> st1(n);

	for (int i = 0; i < n; ++i)
		st1.Push(i);

	TStack<double> st2(st1);

	int result;

	for (int i = 0; i < n; ++i) {
		result = st1.Pop() == st2.Pop();

		if (result == false)
			break;
	}

	ASSERT_EQ(result, true);
}

// оператор присваивания

TEST(TStack, self_appropriation) {
	TStack<int> st(10);

	for (int i = 0; i < 10; ++i)
		st.Push(i);

	ASSERT_NO_THROW(st = st);
}

TEST(TStack, correct_use_of_operatorEQUAL) {
	TStack<int> a(100);
	TStack<int> b(100);

	for (int i = 0; i < 100; ++i)
		a.Push(i);

	b = a;

	bool result;

	for (int i = 0; i < 100; ++i) {
		result = a.Pop() == b.Pop();

		if (result == false)
			break;
	}

	ASSERT_EQ(result, true);
}

TEST(TStack, correct_use_of_operatorEQUAL_when_different_sizes) {
	TStack<int> a(100);
	TStack<int> b(10);

	for (int i = 0; i < 100; ++i)
		a.Push(i);

	b = a;

	bool result;

	for (int i = 0; i < 100; ++i) {
		result = a.Pop() == b.Pop();

		if (result == false)
			break;
	}

	ASSERT_EQ(result, true);
}

// Pop, Push, Top, Clear, Get_MaxSize

TEST(TStack, correct_pop_result) {
	TStack<int> st(10);
	st.Push(1234);

	ASSERT_EQ(1234, st.Pop());
}

TEST(TStack, cant_push_full_stack) {
	TStack<int> st(10);

	for (int i = 0; i < 10; ++i)
		st.Push(i);

	ASSERT_ANY_THROW(st.Push(5555));
}

TEST(TStack, correct_top_work) {
	TStack<int> st(1);
	st.Push(1234);

	ASSERT_NO_THROW(st.Top());
	ASSERT_NO_THROW(st.Top()); 
	ASSERT_NO_THROW(st.Top());

	ASSERT_EQ(st.Top(), 1234);

	ASSERT_NO_THROW(st.Pop());
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, correct_clear_work) {
	TStack<int> st(10);

	for (int i = 0; i < 10; ++i)
		st.Push(i);

	st.Clear();

	ASSERT_ANY_THROW(st.Pop());

	st.Push(1234);
	ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, get_correct_max_size) {
	TStack<int> st(10);

	ASSERT_EQ(st.Get_MaxSize(), 10);
}