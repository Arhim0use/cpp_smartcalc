#include "s21_smartcalc_test.h"

namespace s21 {

void SmartCalcValidationTest::SetUp() {
  calc_controller = new s21::SmartCalcController();
}

void SmartCalcValidationTest::TearDown() { delete calc_controller; }

TEST_F(SmartCalcValidationTest, VoidLine) {
  std::string calc_line = "";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_1) {
  std::string calc_line = "x";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_2) {
  std::string calc_line = "x";

  std::string var_line = "-100e-2";
  calc_controller->SetVarX(var_line);

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_3) {
  std::string calc_line = "x";

  std::string var_line = "12.33";
  calc_controller->SetVarX(var_line);

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_4) {
  std::string calc_line = "x";

  std::string var_line = "";
  calc_controller->SetVarX(var_line);

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_1) {
  std::string calc_line = "3.14";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_2) {
  std::string calc_line = "3.14+256";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_3) {
  std::string calc_line = "256^(1/2)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_4) {
  std::string calc_line = ".256*10";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_5) {
  std::string calc_line = "256./10";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_6) {
  std::string calc_line = "1";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_1) {
  std::string calc_line = "sin(64)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_2) {
  std::string calc_line = "sqrt(x)";
  std::string var_line = "10";
  calc_controller->SetVarX(var_line);

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_3) {
  std::string calc_line = "12.3%x";
  std::string var_line = "8";
  calc_controller->SetVarX(var_line);

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_1) {
  std::string calc_line = "-20";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_2) {
  std::string calc_line = "-20-10";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_3) {
  std::string calc_line = "-x";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyExpNotationLine_1) {
  std::string calc_line = "314E-2";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyExpNotationLine_2) {
  std::string calc_line = "1.123e+12";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1)-sqrt(4))-1)/1)*2";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, BrokenLineUnari_1) {
  std::string calc_line = "-/x";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineUnari_2) {
  std::string calc_line = "*16-9";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineExpNotation_1) {
  std::string calc_line = "1.1e-1.1+1";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineExpNotation_2) {
  std::string calc_line = "10e*1+2";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_1) {
  std::string calc_line = "asan(e)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_2) {
  std::string calc_line = "12-hgf()";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_3) {
  std::string calc_line = "12-sin";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDot_1) {
  std::string calc_line = "12..4+3";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineParenthesis_1) {
  std::string calc_line = "(12.+3))";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_1) {
  std::string calc_line = "(12+)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_2) {
  std::string calc_line = "-12-";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_3) {
  std::string calc_line = "100x0.1";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_4) {
  std::string calc_line = "100(0.1)";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDoesNotExist_1) {
  std::string calc_line = "!5";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDoesNotExist_2) {
  std::string calc_line = "-";

  calc_controller->Calculate(calc_line);
  EXPECT_EQ(calc_controller->GetStatus(), Status::kError);
}

}  // namespace s21