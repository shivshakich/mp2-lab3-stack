#pragma once

#include <string>
#include "TStack.h"

using std::string;

class TCalculator {
	// ����

	string infix, postfix;			// ��������� � ����������� ����� ������ ��������������� ���������
	TStack<char> operation;			// ����, �������� ��������
	TStack<double> number;			// ����, �������� ��������

	// ������

	int Priority(char op) const;										// ��������� ��������
	bool Check(const string& str) const;								// �������� �� ������������ ��������������� ��������� str
	void ClearStacks() { operation.Clear(); number.Clear(); }			// �������� ����� 
	void ToPostfix(void);												// ����� postfix

public:
	TCalculator(const string& in);										// �����������

	string GetInfix() const { return infix; }							// ������ �������� infix
	string GetPostfix();												// ������ �������� postfix

	double Calc(void);													// ��������� postfix
};