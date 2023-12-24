#include "pch.h"
#include "../TCalculator.h"

using std::string;

TEST(TCalculator, can_create_calculator_with_possitive_size_of_infix)
{
    string a = "1+2";
    ASSERT_NO_THROW(TCalculator<int>a);
}

TEST(TCalculator, can_get_infix_form_of_calculator)
{
    std::string a = "2+(3*5)";
    std::string b;
    TCalculator calc(a);
    ASSERT_NO_THROW(b = calc.get_infix());
    EXPECT_EQ(a, b);
}
TEST(TCalculator, can_set_infix_form_of_calculator)
{
    std::string a = "2+(3*5)";
    std::string b;
    TCalculator calc(a);
    ASSERT_NO_THROW(calc.set_infix(b));
    EXPECT_EQ(calc.get_infix(), b);
}
TEST(TCalculator, can_get_correct_postfix_form_of_calculator_if_the_number_of_brackets_is_correct)
{
    std::string a = "2+(3*5)";
    std::string b = "235*+";
    std::string c;
    TCalculator calc(a);
    ASSERT_NO_THROW(c = calc.get_postfix());
    EXPECT_EQ(c, b);
}
TEST(TCalculator, cant_get_correct_postfix_form_of_calculator_if_the_number_of_brackets_is_incorrect)
{
    std::string a = "2+((3*5)";
    std::string b = "235*+";
    std::string c;
    TCalculator calc(a);
    c = calc.get_postfix();
    EXPECT_NE(c, b);
}
TEST(TCalculator, check_expression_return_true_when_the_number_of_brackets_is_correct)
{
    std::string a = "2+(3*5)";


    TCalculator calc(a);
    bool check;
    ASSERT_NO_THROW(check = calc.CheckExpression());
    EXPECT_EQ(1, check);
}
TEST(TCalculator, check_expression_return_false_when_the_number_of_brackets_is_incorrect)
{
    std::string a = "2+((3*5)";


    TCalculator calc(a);
    bool check;
    ASSERT_NO_THROW(check = calc.CheckExpression());
    EXPECT_EQ(0, check);
}
TEST(TCalculator, can_calculat_if_the_number_of_brackets_is_correct)
{
    std::string a = "2+(3*5)";


    TCalculator calc(a);
    double check;
    ASSERT_NO_THROW(check = calc.CalcPostfix());
    EXPECT_EQ(17, check);
}

TEST(TCalculator, cant_calculat_if_the_number_of_brackets_is_incorrect)
{
    std::string a = "2+((3*5)";


    TCalculator calc(a);
    double check;
    ASSERT_ANY_THROW(check = calc.CalcPostfix());
    EXPECT_NE(17, check);
}