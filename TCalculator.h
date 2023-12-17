#pragma once

#include "TStack.h"

using std::string;

template <class T>
class TCalculator {
	string infix, postfix;
	TStack<char> operation(TStack::Get_MAXMAXSIZE());
	TStack<double> number(TStack::Get_MAXMAXSIZE());

	int Priority(char op) const {
		int res;
		switch (op) {
		case '(': res = 0; break;
		case ')': res = 0; break;
		case '-': res = 1; break;
		case '+': res = 1; break;
		case '*': res = 2; break;
		case '/': res = 2; break;
		case '^': res = 3; break;
		}

		return res;
	}

	void ToPostfix(void);
public:
	TCalculator(const string& in);

	double Calc(void);
};

template <class T>
TCalculator<T>::TCalculator(const string& in) {
	infix = '(' + in + ')';

	ToPostfix();
}

template <class T>
void TCalculator<T>::ToPostfix(void) {
	operation.Clear();
}







