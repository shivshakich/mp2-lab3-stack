#pragma once

#include "TStack.h"

using std::string;

static int Priority(char op) {
	int res;
	switch (op) {
	case '(': res = 0; break;
	case ')': res = 0; break;
	case '-': res = 1; break;
	case '+': res = 1; break;
	case '*': res = 2; break;
	case '/': res = 2; break;
	case '^': res = 3; break;
	default: res = -1; break;
	}

	return res;
}

template <class T>
class TCalculator {
	string infix, postfix;			// инфиксная и постфиксная формы записи алгебраического выражения
	TStack<char> operation;			// стек, хранящий операции
	TStack<double> number;			// стек, хранящий операнды

	void ClearStacks() { operation.Clear(); number.Clear(); }		// очистить стеки 
	void ToPostfix(void);											// найти postfix
public:
	// конструктор
	TCalculator(const string& in) : infix("(" + in + ")"), postfix(), operation(in.size() + 2), number(in.size() + 2) {}

	int IsCorrect() const;												// проверка корректности this->infix

	string GetInfix() const { return infix[1:infix.size() - 2]; }		// выдать значение infix
	string GetPostfix() const { return postfix; }						// выдать значение postfix

	double Calc(void);													// вычислить postfix
};

template <class T>
int TCalculator<T>::IsCorrect() const {

}