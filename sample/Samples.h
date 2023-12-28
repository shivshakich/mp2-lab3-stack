#pragma once

#include <string>
#include <locale>
#include "../TCalculator.h"

using std::string;

void sample1(void);
void sample2(void);

void sample1(void) {
	setlocale(LC_CTYPE, "Russian");

	try {
		string a = "1 + 2 + 3";						double resA = 6.0;
		string b = "(1+2*3)*(4/5-6)";				double resB = -36.4;
		string c = "1(23";
		string d = "2*";

		// a

		TCalculator calcA(a);
		if (calcA.GetInfix() != a)
			throw "1.1";
		if (calcA.GetPostfix() != "1 2 + 3 +")
			throw "1.2";
		if (calcA.Calc() != resA)
			throw "1.3";

		// b

		TCalculator calcB(b);
		if (calcB.GetInfix() != b)
			throw "2.1";
		if (calcB.GetPostfix() != "1 2 3 * + 4 5 / 6 - *")
			throw "2.2";
		if (calcB.Calc() != resB)
			throw "2.3";
		else
			std::cout << b << " = " << resB << std::endl;

		// c, d

		char q;
		TCalculator* cal;

		std::cout << "¬ведите символ:" << std::endl;
		std::cin >> q;

		// не будет вызыватьс€ throw из-за переписанного конструктора
		switch (q) {
		case 'c': cal = new TCalculator(c); delete cal; break;
		case 'd': cal = new TCalculator(d); delete cal; break;
		}
	}
	catch (string exception) {
		std::cout << "EXCEPTION: " << exception << std::endl;
	}
	catch (char exception[]) {
		std::cout << "EXCEPTION: ";

		char c; int i = 0;
		while ((c = exception[i++]) != '\0')
			std::cout << c;
		std::cout << std::endl;
	}
}

void sample2(void) {
	string a = "(1 + 2 * 3) * (20 / 5 - 6)";
	string b = "2 * 3  4 * ";					// throw
	string c = "";								// throw
	string d = "23 * () 100";					// некорректна€ работа: должен вызыватьс€ throw, чего не происходит
	string e = "120 * 10 + 0.5 - 10^ 2";

	string str = e;

	TCalculator calc(str);
	double res = calc.Calc();
	std::cout << str << " = " << res << std::endl;

}