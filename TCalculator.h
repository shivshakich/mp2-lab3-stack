#pragma once

#include "TStack.h"

#include <string>

// считаем, что infix не должен содеражать пробелов

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

class TCalculator {
	string infix, postfix;			// инфиксная и постфиксная формы записи алгебраического выражения
	TStack<char> operation;			// стек, хранящий операции
	TStack<double> number;			// стек, хранящий операнды

	void ClearStacks() { operation.Clear(); number.Clear(); }		// очистить стеки 
	void ToPostfix(void);											// найти postfix
public:
	// конструктор
	TCalculator(const string& in) : infix(in), postfix(), operation(in.size()), number(in.size()) {}

	//int IsCorrect() const;												// проверка корректности this->infix

	string GetInfix() const { return infix; }							// выдать значение infix
	string GetPostfix() const { return postfix; }						// выдать значение postfix

	double Calc(void);													// вычислить postfix
};

void TCalculator::ToPostfix(void) {
	ClearStacks();
	postfix = "";

	//str, lengthStr;
	string str = "(" + infix + ")";
	int lengthStr = 2 + infix.length();

	for (int i = 0; i < lengthStr; ++i) {
		int prior = Priority(str[i]);

		if (str[i] == '(')											// когда '('
			operation.Push('(');

		else if (str[i] == ')') {									// когда ')'
			char c;
			while ((c = operation.Pop()) != '(')		
				postfix += c;
		}

		else if (prior > 0) {										// когда операция 
			char c;
			while (prior <= Priority(c = operation.Top())) {
				postfix += c;
				operation.Pop();
			}
		}

		else {														// когда операнд
			double n = std::stod(str.substr(i));
			string syr = std::to_string(n);
			i += syr.length() - 1;
			postfix += syr;
		}
	}
}

double TCalculator::Calc(void) {
	ClearStacks();
	ToPostfix();

	int lengthPostfix = postfix.length();

	for (int i = 0; i < lengthPostfix; ++i) {
		char c = postfix[i];

		if (Priority(c) > 0) {		// когда операция
			double x1, x2;
			x2 = number.Pop();
			x1 = number.Pop();

			switch (c) {
			case '+': x1 = x1 + x2; break;
			case '-': x1 = x1 - x2; break;
			case '*': x1 = x1 * x2; break;
			case '/': x1 = x1 / x2; break;
			case '^': x1 = pow(x1,x2); break;
			}

			number.Push(x1);
		}
		else {						// когда операнд
			double n = std::stod(postfix.substr(i));
			string syr = std::to_string(n);
			i += syr.length() - 1;
			number.Push(n);
		}
	}

	return number.Pop();
}