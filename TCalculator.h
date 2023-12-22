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
	string infix, postfix;			// ��������� � ����������� ����� ������ ��������������� ���������
	TStack<char> operation;			// ����, �������� ��������
	TStack<double> number;			// ����, �������� ��������

	void ClearStacks() { operation.Clear(); number.Clear(); }		// �������� ����� 
	void ToPostfix(void);											// ����� postfix
public:
	// �����������
	TCalculator(const string& in) : infix("(" + in + ")"), postfix(), operation(in.size() + 2), number(in.size() + 2) {}

	int IsCorrect() const;												// �������� ������������ this->infix

	string GetInfix() const { return infix[1:infix.size() - 2]; }		// ������ �������� infix
	string GetPostfix() const { return postfix; }						// ������ �������� postfix

	double Calc(void);													// ��������� postfix
};

template <class T>
int TCalculator<T>::IsCorrect() const {

}