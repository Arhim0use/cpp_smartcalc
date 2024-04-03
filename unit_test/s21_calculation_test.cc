#include "s21_smartcalc_test.h"

namespace s21 {
void SmartCalcCalculationTest::SetUp() {
  calc_controller = new s21::SmartCalcController();
}

void SmartCalcCalculationTest::TearDown() { delete calc_controller; }

TEST_F(SmartCalcCalculationTest, VoidLine) {
  std::string calc_line = "";
  double expect = 0;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_1) {
  std::string calc_line = "x";
  double expect = 0;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_2) {
  std::string calc_line = "x";
  std::string var_line = "-100e-2";
  double expect = -100e-2;
  double result = 0;

  calc_controller->SetVarX(var_line);
  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_3) {
  std::string calc_line = "x";
  std::string var_line = "12.33";
  double expect = 12.33;
  double result = 0;

  calc_controller->SetVarX(var_line);
  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, VarLine_4) {
  std::string calc_line = "x";
  std::string var_line = "";
  double expect = 1;
  double result = 0;

  calc_controller->SetVarX(var_line);
  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_1) {
  std::string calc_line = "3.140";
  double expect = 3.140;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_2) {
  std::string calc_line = "3.14+256";
  double expect = 3.14 + 256;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_3) {
  std::string calc_line = "256^(1/2)";
  double expect = pow(256., (1. / 2.));
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_4) {
  std::string calc_line = ".256*10";
  double expect = 0.256 * 10;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_5) {
  std::string calc_line = "256./10";
  double expect = 256. / 10;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyLine_6) {
  std::string calc_line = "1";
  double expect = 1;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_1) {
  std::string calc_line = "sin(64)";
  double expect = sin(64);
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_2) {
  std::string calc_line = "sqrt(x)";
  std::string var_line = "100e-2";
  calc_controller->SetVarX(var_line);

  double x = 100e-2;
  double expect = sqrt(x);
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_3) {
  std::string calc_line = "x%2";
  std::string var_line = "100e+2";
  calc_controller->SetVarX(var_line);

  double x = 100e+2;
  double expect = fmod(x, 2);
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_4) {
  std::string calc_line = "(x^2)-2";
  std::string var_line = "1e+1";
  calc_controller->SetVarX(var_line);

  double x = 1e+1;
  double expect = pow(x, 2) - 2;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyFuncLine_5) {
  std::string calc_line = "-x^2-2";
  std::string var_line = "1e+1";
  calc_controller->SetVarX(var_line);

  double x = 1e+1;
  double expect = pow(-x, 2) - 2;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_1) {
  std::string calc_line = "-20";
  double expect = -20.;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_2) {
  std::string calc_line = "-20-10";
  double expect = -20 - 10;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyUnariLine_3) {
  std::string calc_line = "-x";
  std::string var_line = "100e+2";
  calc_controller->SetVarX(var_line);

  double x = 100e+2;
  double expect = -x;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, EasyExpNotationLine) {
  std::string calc_line = "314E-2";
  double expect = 314E-2;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";
  double expect = -1.23 * 100. / sin(2.5) - (pow(2., (log(9) / 10.)));
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1.)-sqrt(4.))-1)/10.)*2";
  std::string var_line = "100e+2";
  calc_controller->SetVarX(var_line);

  double x = 100e+2;
  double expect = -x + (sin(1.5 * (acos(1.) - sqrt(4.)) - 1.) / 10.) * 2;
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, HardLine_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";
  double expect = -(1. + pow(4., -2.) - (-4. + -10. * -(1. / 2.) * 2.));
  double result = 0;

  result = calc_controller->Calculate(calc_line);
  EXPECT_FLOAT_EQ(expect, result);
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_1) {
  std::string calc_line = "-(x^2)";
  double x = 0;
  double expect = -pow(x, 2.);
  double result = 0;
  double x_min = -2;
  double x_max = 2;
  int accuracy = 5;

  result = calc_controller->Calculate(calc_line);
  auto res_vector = calc_controller->GrafCalculation(accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min, -1, 0, 1, x_max};
  std::vector<double> expect_y = {-4, -1, 0, -1, -4};

  EXPECT_FLOAT_EQ(expect, result);
  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  EXPECT_EQ(res_vector.at(0).size(), res_vector.at(1).size());
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_2) {
  std::string calc_line = "tan(x)";
  double x = 0;
  double expect = tan(x);
  double result = 0;
  double x_min = 0;
  double x_max = 4;
  int accuracy = 5;

  result = calc_controller->Calculate(calc_line);
  auto res_vector = calc_controller->GrafCalculation(accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min, 1, 2, 3, x_max};
  std::vector<double> expect_y = {0., 1.55740772, -2.18503986, -0.14254654,
                                  1.15782128};

  EXPECT_FLOAT_EQ(expect, result);
  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_3) {
  std::string calc_line = "atan(x)";

  double x_min = -3;
  double x_max = 0;
  int accuracy = 5;

  auto res_vector =
      calc_controller->GrafCalculation(calc_line, accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min, -2.25, -1.5, -0.75, x_max};
  std::vector<double> expect_y = {-1.24904577, -1.15257200, -0.98279372,
                                  -0.64350111, 0};

  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_4) {
  std::string calc_line = "(x)%3.";

  double x_min = -4.;
  double x_max = -3.;
  int accuracy = 5;

  auto res_vector =
      calc_controller->GrafCalculation(calc_line, accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min, -3.75, -3.5, -3.25, x_max};
  std::vector<double> expect_y = {-1, -0.75, -0.5, -0.25, 0.};

  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_5) {
  std::string calc_line = "ln(x)";

  double x_min = -2;
  double x_max = 5;
  int accuracy = 7;

  auto res_vector =
      calc_controller->GrafCalculation(calc_line, accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min,      -0.83333333, 0.33333333,
                                  1.50000000, 2.66666667,  3.83333333,
                                  x_max};
  std::vector<double> expect_y = {0.0,       0.0,       -1.0986123, 0.4054651,
                                  0.9808293, 1.3437347, 1.6094379};

  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, CalcGrafArray_6) {
  std::string calc_line = "asin(x)";

  double x_min = -2;
  double x_max = 1;
  int accuracy = 6;

  auto res_vector =
      calc_controller->GrafCalculation(calc_line, accuracy, x_min, x_max);
  std::vector<double> expect_x = {x_min,      -1.4000000, -0.8000000,
                                  -0.2000000, 0.4000000,  x_max};
  std::vector<double> expect_y = {0.0,        0.0,       -0.9272952,
                                  -0.2013579, 0.4115168, 1.5707963};

  EXPECT_EQ(res_vector.at(0).size(), accuracy);
  for (size_t i = 0; i < res_vector.at(0).size(); i++) {
    EXPECT_FLOAT_EQ(expect_x[i], res_vector.at(0)[i]);
    EXPECT_FLOAT_EQ(expect_y[i], res_vector.at(1)[i]);
  }
}

TEST_F(SmartCalcCalculationTest, BrokenHardLine_1) {
  std::string calc_line = "-ln(sqrt((sin(10)^2)-(cos(10)^2)))";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(Status::kError, calc_controller->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenHardLine_2) {
  std::string calc_line = "100/(((911+89)/2/-500)/0)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(Status::kError, calc_controller->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenEasyLine_1) {
  std::string calc_line = "sqrt(-x)";
  std::string var_line = "100e-2";

  calc_controller->SetVarX(var_line);
  calc_controller->Calculate(calc_line);
  EXPECT_EQ(Status::kError, calc_controller->GetStatus());
}

TEST_F(SmartCalcCalculationTest, BrokenEasyLine_2) {
  std::string calc_line = "ln(-x)";
  std::string var_line = "0";

  calc_controller->SetVarX(var_line);
  calc_controller->Calculate(calc_line);
  EXPECT_EQ(Status::kError, calc_controller->GetStatus());
}

}  // namespace s21