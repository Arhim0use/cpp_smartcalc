#include "s21_smartcalc_test.h"

namespace s21{

TEST_F(SmartCalcTest, CalcVoidLine) {
  std::string calc_line = "";
  double expect = 0;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcVarLine_1) {
  std::string calc_line = "x";
  double expect = 0;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcVarLine_2) {
  std::string calc_line = "x";
  std::string var_line = "-100e-2";
  double expect = -100e-2;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcVarLine_3) {
  std::string calc_line = "x";
  std::string var_line = "12.33";
  double expect = 12.33;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcVarLine_4) {
  std::string calc_line = "x";
  std::string var_line = "";
  double expect = 0;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcEasyLine_1) {
  std::string calc_line = "3.14";
  double expect = 3.14;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcEasyLine_2) {
  std::string calc_line = "3.14+256";
  double expect = 3.14 + 256;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcTest, CalcEasyLine_3) {
  std::string calc_line = "256^(1/2)";
  double expect = pow(256., (1. / 2.));
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

} // namespace s21