#pragma once

#include "TStack.h"

#include <string>

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

bool Check(const string& str) {
	int num = 0, op = 0;
	int lengthStr = str.size();

	int nBracket = 0;		// ���������� ������

	for (int i = 0; i < lengthStr; ++i)
	{
		int prior = Priority(str[i]);

		if (str[i] == '(')								// ����� (
			++nBracket;
		else if (str[i] == ')')							// ����� )
		{
			if (nBracket < 1)
				throw "Check, str == ')'";

			--nBracket;
		}
		else if (prior > 0)								// ����� �������� 
			++op;
		else
			++num;
	}

	if (nBracket != 0)
		throw "Check, nBracket != 0";
	else if (num != (op + 1))
		throw "Check, num != (op + 1)";

	return true;
}

class TCalculator {
	string infix, postfix;			// ��������� � ����������� ����� ������ ��������������� ���������
	TStack<char> operation;			// ����, �������� ��������
	TStack<double> number;			// ����, �������� ��������

	void ClearStacks() { operation.Clear(); number.Clear(); }		// �������� ����� 
	void ToPostfix(void);											// ����� postfix

public:
	// �����������
	TCalculator(const string& in);

	//int IsCorrect() const;												// �������� ������������ this->infix

	string GetInfix() const { return infix; }							// ������ �������� infix
	string GetPostfix() const { return postfix; }						// ������ �������� postfix

	double Calc(void);													// ��������� postfix
};

TCalculator::TCalculator(const string& in) : operation(in.size()), number(in.size()) {
	bool isCorrect = Check(in);

	if (!isCorrect)
		throw "TCalculator(string), incorrect input";

	infix = in;

	postfix = "";
	ToPostfix();
}

void TCalculator::ToPostfix(void) {
	ClearStacks();
	postfix = "";

	//str, lengthStr;
	string str = "(" + infix + ")";
	int lengthStr = 2 + infix.length();

	for (int i = 0; i < lengthStr; ++i) {
		int prior = Priority(str[i]);

		if (str[i] == '(')											// ����� '('
			operation.Push('(');

		else if (str[i] == ')') {									// ����� ')'
			char c;
			while ((c = operation.Pop()) != '(')		
				postfix += c;
		}

		else if (prior > 0) {										// ����� �������� 
			char c;
			while (prior <= Priority(c = operation.Pop())) {
				postfix += c;
			}
		}

		else {														// ����� �������
			size_t n;	// ���-�� �������� �����
			std::stod(str.substr(i), &n);

			string sub = str.substr(i, n);
			postfix += sub;
			i += n - 1;
		}
	}

	bool a = true;
}

double TCalculator::Calc(void) {
	ClearStacks();
	ToPostfix();

	int lengthPostfix = postfix.length();

	for (int i = 0; i < lengthPostfix; ++i) {
		char c = postfix[i];

		if (Priority(c) > 0) {		// ����� ��������
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
		else {						// ����� �������
			double n = std::stod(postfix.substr(i));
			string syr = std::to_string(n);
			i += syr.length() - 1;
			number.Push(n);
		}
	}

	return number.Pop();
}