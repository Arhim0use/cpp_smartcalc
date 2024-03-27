#include "s21_smartcalc_test.h"

namespace s21{
void SmartCalcCalculationTest::SetUp() {
  model = new s21::SmartCalc();
}

void SmartCalcCalculationTest::TearDown() {
  delete model;
}

TEST_F(SmartCalcCalculationTest, VoidLine) {
  std::string calc_line = "";
  double expect = 0;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_1) {
  std::string calc_line = "x";
  double expect = 0;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_2) {
  std::string calc_line = "x";
  std::string var_line = "-100e-2";
  double expect = -100e-2;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_3) {
  std::string calc_line = "x";
  std::string var_line = "12.33";
  double expect = 12.33;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_4) {
  std::string calc_line = "x";
  std::string var_line = "";
  double expect = 0;
  double result = 0;

  model->SetVarX(var_line);
  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_1) {
  std::string calc_line = "3.14";
  double expect = 3.14;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_2) {
  std::string calc_line = "3.14+256";
  double expect = 3.14 + 256;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_3) {
  std::string calc_line = "256^(1/2)";
  double expect = pow(256., (1. / 2.));
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}


TEST_F(SmartCalcCalculationTest, EasyLine_4) {
  std::string calc_line = ".256*10";
  double expect = 0.256 * 10;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_5) {
  std::string calc_line = "256./10";
  double expect = 256. / 10;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_6) {
  std::string calc_line = "1";
  double expect = 1;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_1) {
  std::string calc_line = "sin(64)";
  double expect = sin(64);
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_2) {
  std::string calc_line = "sqrt(x)";
  std::string var_line = "100e-2";
  model->SetVarX(var_line);

  double x = 100e-2;
  double expect = sqrt(x);
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_3) {
  std::string calc_line = "x%2";
  std::string var_line = "100e+2";
  model->SetVarX(var_line);

  double x = 100e+2;
  double expect = fmod(x, 2);
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_1) {
  std::string calc_line = "-20";
  double expect = -20.;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_2) {
  std::string calc_line = "-20-10";
  double expect = -20 - 10;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_3) {
  std::string calc_line = "-x";
  std::string var_line = "100e+2";
  model->SetVarX(var_line);

  double x = 100e+2;
  double expect = -x;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyExpNotationLine) {
  std::string calc_line = "314E-2";
  double expect = 314E-2;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";
  double expect = -1.23 * 100. / sin(2.5) - (pow(2., (log(9)/10.)));
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1.)-sqrt(4.))-1)/10.)*2";
  std::string var_line = "100e+2";
  model->SetVarX(var_line);

  double x = 100e+2;
  double expect = -x + (sin(1.5 * (acos(1.) - sqrt(4.)) - 1.) / 10.) * 2;
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";
  double expect = -(1. + pow(4., -2.) - (-4. + -10. * -(1. / 2.) * 2.));
  double result = 0;

  result = model->ProcessAndCalculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, BrokenHardLine_1) {
  std::string calc_line = "-ln(sqrt((sin(10)^2)-(cos(10)^2)))";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(Status::kError, model->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenHardLine_2) {
  std::string calc_line = "100/(((911+89)/2/-500)/0)";
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(Status::kError, model->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenEasyLine_1) {
  std::string calc_line = "sqrt(-x)";
  std::string var_line = "100e-2";

  model->SetVarX(var_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(Status::kError, model->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenEasyLine_2) {
  std::string calc_line = "ln(-x)";
  std::string var_line = "0";

  model->SetVarX(var_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(Status::kError, model->GetStatus());
}

} // namespace s21