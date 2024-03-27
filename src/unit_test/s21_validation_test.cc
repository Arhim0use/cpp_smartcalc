#include "s21_smartcalc_test.h"

namespace s21{

void SmartCalcValidationTest::SetUp() {
  model = new s21::SmartCalc();
}

void SmartCalcValidationTest::TearDown() {
  delete model;
}


TEST_F(SmartCalcValidationTest, VoidLine) {
  std::string calc_line = "";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_1) {
  std::string calc_line = "x";


  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_2) {
  std::string calc_line = "x";

  
  std::string var_line = "-100e-2";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_3) {
  std::string calc_line = "x";

  
  std::string var_line = "12.33";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, VarLine_4) {
  std::string calc_line = "x";

  
  std::string var_line = "";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_1) {
  std::string calc_line = "3.14";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_2) {
  std::string calc_line = "3.14+256";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_3) {
  std::string calc_line = "256^(1/2)";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_4) {
  std::string calc_line = ".256*10";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_5) {
  std::string calc_line = "256./10";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyLine_6) {
  std::string calc_line = "1";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_1) {
  std::string calc_line = "sin(64)";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_2) {
  std::string calc_line = "sqrt(x)";
  std::string var_line = "10";
  model->SetVarX(var_line);

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyFuncLine_3) {
  std::string calc_line = "12.3%x";
  std::string var_line = "8";
  model->SetVarX(var_line);

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_1) {
  std::string calc_line = "-20";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_2) {
  std::string calc_line = "-20-10";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyUnariLine_3) {
  std::string calc_line = "-x";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyExpNotationLine_1) {
  std::string calc_line = "314E-2";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, EasyExpNotationLine_2) {
  std::string calc_line = "1.123e+12";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1)-sqrt(4))-1)/1)*2";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, HardLine_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcValidationTest, BrokenLineUnari_1) {
  std::string calc_line = "-/x";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineUnari_2) {
  std::string calc_line = "*16-9";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineExpNotation_1) {
  std::string calc_line = "1.1e-1.1+1";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineExpNotation_2) {
  std::string calc_line = "10e*1+2";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_1) {
  std::string calc_line = "asan(e)";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_2) {
  std::string calc_line = "12-hgf()";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineFunk_3) {
  std::string calc_line = "12-sin";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDot_1) {
  std::string calc_line = "12..4+3";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineParenthesis_1) {
  std::string calc_line = "(12.+3))";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_1) {
  std::string calc_line = "(12+)";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_2) {
  std::string calc_line = "-12-";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_3) {
  std::string calc_line = "100x0.1";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineOperator_4) {
  std::string calc_line = "100(0.1)";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDoesNotExist_1) {
  std::string calc_line = "!5";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcValidationTest, BrokenLineDoesNotExist_2) {
  std::string calc_line = "-";

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

} // namespace s21