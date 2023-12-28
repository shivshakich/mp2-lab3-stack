#include "TCalculator.h"

int main() {
	string a = "(1 + 2 * 3) * (20 / 5 - 6)";
	string b = "2 * 3  4 * ";
	string c = "";
	string d = "23 * () 100";
	TCalculator calc(d);
	double res = calc.Calc();

	return 0;
}