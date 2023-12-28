#include "pch.h"
#include "../TCalculator.h"

using std::string;

/*TEST(TCalculator, bababa_bebebe) {
    TCalculator tc("1+2+3");
    string a = tc.GetPostfix();
    string b = tc.GetInfix();

    ASSERT_NO_THROW(int a = 10);
}*/

TEST(TCalculator, can_create_calculator_with_possitive_size_of_infix)
{
    string a = "1+2";
    ASSERT_NO_THROW(TCalculator tc("1+2"));
    ASSERT_NO_THROW(TCalculator tc(a));
}

TEST(TCalculator, can_get_infix_form_of_calculator)
{
    string a = "2+(3*5)";
    string b;
    TCalculator calc(a);
    ASSERT_NO_THROW(b = calc.GetInfix());
    EXPECT_EQ(a, b);
}

TEST(TCalculator, can_get_correct_postfix_form_of_calculator_if_the_number_of_brackets_is_correct)
{
    string a = "(1+2*3)*(4/5-6)";
    string b = "1 2 3 * + 4 5 / 6 - *";

    TCalculator calc(a);
    string c = calc.GetPostfix();

    ASSERT_EQ(b, c);
}

TEST(TCalculator, can_calculate_without_brackets)
{
    double result;
    string a = "1+8";      // == 9

    TCalculator calc(a);

    ASSERT_NO_THROW(result = calc.Calc());
    ASSERT_EQ(result, 9);

    TCalculator calc1("1 + 8 * 9");         // == 73
    ASSERT_NO_THROW(result = calc1.Calc());
    ASSERT_EQ(result, 73.0);
}

TEST(TCalculator, can_calculate_if_the_number_of_brackets_is_correct)
{
    string a = "(1+2*3)*(20/5-6)";      // == -14

    TCalculator calc(a);

    double result;
    ASSERT_NO_THROW(result = calc.Calc());
    ASSERT_EQ(calc.Calc(), -14.0);
}

TEST(TCalculator, cant_calculat_if_the_number_of_brackets_is_incorrect)
{
    std::string a = "2+((3*5)";


    TCalculator calc(a);
    double result = 0.0;
    ASSERT_ANY_THROW(result = calc.Calc());
    EXPECT_NE(17.0, result);
}
