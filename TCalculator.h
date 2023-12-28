#pragma once

#include <string>
#include "TStack.h"

using std::string;

// ¬ј∆Ќќ!	не работает с числами < 0 (которые имеют '-' в начале)
//			некорректна€ работа в таких случа€х, как "23 * () 100"
//			не учытиваютс€ случаи, когда вместо пробела используют tab

class TCalculator {
	// пол€

	string infix, postfix;			// инфиксна€ и постфиксна€ формы записи алгебраического выражени€
	TStack<char> operation;			// стек, хран€щий операции
	TStack<double> number;			// стек, хран€щий операнды

	// методы

	int Priority(char op) const;										// приоритет операции
	bool Check(const string& str) const;								// проверка на корректность алгебраического выражени€ str
	bool IsCorrect() const;												// проверка infix на символы, на чередуемость операндов и операций, 
																		// на отсутсвие пар скобок, которые ничего не содержат
	void ClearStacks() { operation.Clear(); number.Clear(); }			// очистить стеки 
	void ToPostfix(void);												// найти postfix

public:
	TCalculator(const string& in);										// конструктор

	string GetInfix() const { return infix; }							// выдать значение infix
	string GetPostfix();												// выдать значение postfix

	double Calc(void);													// вычислить postfix
};

// –≈јЋ»«ј÷»я

bool TCalculator::IsCorrect() const {
	bool res = false;

	const int OPERAND = 0;
	const int OPERATION = 1;

	int lastType = OPERATION;

	const size_t lengthInfix = infix.length();

	for (int i = 0; i < lengthInfix; ++i) {
		char c = infix[i];

		if (c == ' ' || c == '(' || c == ')') 
			continue;

		if ('0' <= c && c <= '9') {	// операнд
			res = true;

			if (lastType == OPERAND) {		// two operands are not separated by an operation
				res = false;
				break;
			}

			size_t lengthNum;
			std::stod(infix.substr(i), &lengthNum);
			i += lengthNum - 1;

			lastType = OPERAND;
		}
		else if (Priority(c) > 0) {																						// операци€
			if (lastType == OPERATION) {
				res = false;
				break;
			}

			lastType = OPERATION;
		}
		else {																											// недопустимый символ
			res = false;
			break;
		}
	}

	return res;
}

string TCalculator::GetPostfix(void) {
	if (postfix == "")
		ToPostfix();

	try {
		Calc();
	}
	catch (string exc) {
		throw "GetPostfix, invalid postfix";
	}

	return postfix;
}

bool TCalculator::Check(const string& str) const {
	bool res = true;

	if (!IsCorrect())
		return false;

	try {
		TCalculator calc(str);
		calc.Calc();
	}
	catch (string exc) {
		res = false;
	}

	return res;
}

int TCalculator::Priority(char op) const {
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

TCalculator::TCalculator(const string& in) : operation(in.size() + 1), number(in.size() + 1), infix(in), postfix("") {}

void TCalculator::ToPostfix(void) {
	ClearStacks();
	postfix = "";

	if (!IsCorrect())
		throw "ToPostfix, IsCorrect";

	//str, lengthStr;
	string str = "(" + infix + ")";
	int lengthStr = str.length();

	for (int i = 0; i < lengthStr; ++i) {
		char c = str[i];
		int prior = Priority(c);

		if (c == ' ')
			continue;

		else if (c == '(')											// когда '('
			operation.Push('(');

		else if (c == ')') {																	// когда ')'
			char k;
			while ((k = operation.Top()) != '(') {
				postfix = postfix + k + " ";
				operation.Pop();
			}
			operation.Pop();
		}

		else if (prior > 0) {																	// когда операци€ 
			char tmp;
			while (prior <= Priority(tmp = operation.Top())) {
				postfix = postfix + tmp + " ";
				operation.Pop();
			}
			operation.Push(c);
		}

		else if ('0' <= c && c <= '9') {	// когда операнд
			size_t lengthN;
			std::stod(str.substr(i), &lengthN);
			string sub = str.substr(i, lengthN);

			postfix += sub + " ";
			i += lengthN - 1;
		}

		else 																					// когда что-то другое
			throw "ToPostfix, unknown litera";
	}

	if (postfix == "")						// ни чисел, ни операций
		throw "ToPostfix, get incorrect infix";

	postfix.pop_back();
}

double TCalculator::Calc(void) {
	ClearStacks();

	if (postfix == "")
		ToPostfix();

	int lengthPostfix = postfix.length();

	for (int i = 0; i < lengthPostfix; ++i) {
		char c = postfix[i];

		if (c == ' ')
			continue;

		if ('0' <= c && c <= '9') {			// когда операнд
			size_t lengthN;
			double n = std::stod(postfix.substr(i), &lengthN);
			number.Push(n);
			i += lengthN - 1;
		}
		else {																													// когда операци€
			double x1, x2;

			if (number.IsEmpty())
				throw "Calc, attempting to access an empty stack (first try)";
			x2 = number.Pop();
			if (number.IsEmpty())
				throw "Calc, attempting to access an empty stack (second try)";
			x1 = number.Pop();

			switch (c) {
			case '+': x1 = x1 + x2; break;
			case '-': x1 = x1 - x2; break;
			case '*': x1 = x1 * x2; break;
			case '/': x1 = x1 / x2; break;
			case '^': x1 = pow(x1, x2); break;
			default:
				throw "Calc, unknown operation"; break;
			}

			number.Push(x1);
		}
	}

	double res = number.Pop();

	if (!number.IsEmpty())
		throw "Calc, wrong postfix";

	return res;
}