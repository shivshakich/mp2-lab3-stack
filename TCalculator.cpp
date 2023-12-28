#include "TCalculator.h"

string TCalculator::GetPostfix(void) {
	if (postfix == "")
		ToPostfix();

	return postfix;
}

bool TCalculator::Check(const string& str) const {
	bool res = true;

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

TCalculator::TCalculator(const string& in) : operation(in.size()), number(in.size()), infix(in), postfix("") {}

void TCalculator::ToPostfix(void) {
	ClearStacks();
	postfix = "";

	//str, lengthStr;
	string str = "(" + infix + ")";
	int lengthStr = str.length();

	for (int i = 0; i < lengthStr; ++i) {
		int prior = Priority(str[i]);

		if (str[i] == ' ')
			continue;

		else if (str[i] == '(')											// когда '('
			operation.Push('(');

		else if (str[i] == ')') {										// когда ')'
			char c;
			while ((c = operation.Top()) != '(') {
				postfix += c + " ";
				operation.Pop();
			}
		}

		else if (prior > 0) {											// когда операция 
			while (prior <= Priority(operation.Top())) {
				postfix += operation.Top() + " ";
				operation.Pop();
			}
			operation.Push(str[i]);
		}

		else {															// когда операнд или что-то другое
			string sub = str.substr(i);

			postfix += sub + " ";
			i += sub.length() - 1;
		}
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

		// пытаемся прочесть подстроку (от i индекса до последнего) как число

		size_t lengthN;
		double n = std::stod(postfix.substr(i), &lengthN);

		// обрабатываем два случая : когда операнд и когда операция

		if (lengthN > 0) {									// когда операнд
			number.Push(n);
			i += lengthN - 1;
		}
		else {												// когда операция
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