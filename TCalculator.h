#pragma once

#include <string>
#include "TStack.h"

using std::string;

class TCalculator {
	// поля

	string infix, postfix;			// инфиксная и постфиксная формы записи алгебраического выражения
	TStack<char> operation;			// стек, хранящий операции
	TStack<double> number;			// стек, хранящий операнды

	// методы

	int Priority(char op) const;										// приоритет операции
	bool Check(const string& str) const;								// проверка на корректность алгебраического выражения str
	void ClearStacks() { operation.Clear(); number.Clear(); }			// очистить стеки 
	void ToPostfix(void);												// найти postfix

public:
	TCalculator(const string& in);										// конструктор

	string GetInfix() const { return infix; }							// выдать значение infix
	string GetPostfix();												// выдать значение postfix

	double Calc(void);													// вычислить postfix
};