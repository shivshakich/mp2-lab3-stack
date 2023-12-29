#include "pch.h"
#include "../Stack-on-list.h"

// конструктор по умолчанию

TEST(TStackOnList, can_create_stack_with_default_constructor) {
	ASSERT_NO_THROW(TStackOnList<int> st);
}

TEST(TStackOnList, created_stack_with_default_constructor_is_empty) {
	TStackOnList<int> st;

	ASSERT_ANY_THROW(st.Pop());
}

// конструктор преобразования типа

TEST(TStackOnList, can_create_stack_with_conversion_constructor_and_value) {
	ASSERT_NO_THROW(TStackOnList<int> st(1234));
}

TEST(TStackOnList, created_stack_with_conversion_constructor_and_value_has_one_node) {
	TStackOnList<int> st(1234);

	ASSERT_NO_THROW(st.Pop());
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStackOnList, can_create_stack_on_list_with_conversion_constructor_and_stack_on_vector) {
	TStackOnList<int> ts(10);

	for (int i = 0; i < 10; ++i)
		ts.Push(i);

	ASSERT_NO_THROW(TStackOnList<int> st(ts));
}

TEST(TStackOnList, stack_on_vector_and_its_copied_stack_on_list_with_conversion_constructor_are_equivalent) {
	TStackOnList<int> ts(10);

	for (int i = 0; i < 10; ++i)
		ts.Push(i);

	TStackOnList<int> st(ts);

	ASSERT_EQ(ts.GetCount(), st.GetCount());
	
	for (int i = 0; i < 10; ++i) {
		bool res = ts.Pop() == st.Pop();

		ASSERT_EQ(res, true);
	}
}

// конструктор копирования

TEST(TStackOnList, can_create_stack_using_copy_constructor) {
	int n = 100;

	TStackOnList<double> st1(n);

	for (int i = 0; i < n; ++i)
		st1.Push(i);

	ASSERT_NO_THROW(TStackOnList<double> st2(st1));
}

TEST(TStackOnList, stack_and_created_stack_using_copy_constructor_are_equal) {
	int n = 100;

	TStackOnList<double> st1(n);

	for (int i = 0; i < n; ++i)
		st1.Push(i);

	TStackOnList<double> st2(st1);

	int result;

	for (int i = 0; i < n; ++i) {
		result = st1.Pop() == st2.Pop();

		if (result == false)
			break;
	}

	ASSERT_EQ(result, true);
}

// оператор присваивания

TEST(TStackOnList, self_appropriation) {
	TStackOnList<int> st(10);

	for (int i = 0; i < 10; ++i)
		st.Push(i);

	ASSERT_NO_THROW(st = st);
}

TEST(TStackOnList, correct_use_of_operatorEQUAL) {
	TStackOnList<int> a(1234);
	TStackOnList<int> b(1234);

	for (int i = 0; i < 99; ++i)
		a.Push(i);

	//TStackOnList<int> c(a);
	b = a;

	bool result;

	for (int i = 0; i < 100; ++i) {
		result = a.Pop() == b.Pop();

		if (result == false)
			break;
	}

	ASSERT_EQ(result, true);
}

TEST(TStackOnList, correct_use_of_operatorEQUAL_when_use_various_constructors) {
	TStackOnList<int> a(100);
	TStackOnList<int> b(a);

	for (int i = 0; i < 99; ++i)
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

TEST(TStackOnList, correct_pop_result) {
	TStackOnList<int> st(10);
	st.Push(1234);

	ASSERT_EQ(1234, st.Pop());
}

TEST(TStackOnList, correct_top_work) {
	TStackOnList<int> st;
	st.Push(1234);

	ASSERT_NO_THROW(st.Top());
	ASSERT_NO_THROW(st.Top());
	ASSERT_NO_THROW(st.Top());

	ASSERT_EQ(st.Top(), 1234);

	ASSERT_NO_THROW(st.Pop());
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStackOnList, correct_clear_work) {
	TStackOnList<int> st;

	for (int i = 0; i < 10; ++i)
		st.Push(i);

	st.Clear();

	ASSERT_ANY_THROW(st.Pop());
	ASSERT_EQ(st.IsEmpty(), true);
}