#include "s21_smartcalc_test.h"

namespace s21{

void SmartCalcTest::SetUp() {
  model = new s21::SmartCalc();
}

void SmartCalcTest::TearDown() {
  delete model;
}


TEST_F(SmartCalcTest, VoidLine) {
  std::string calc_line = "";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, VarLine_1) {
  std::string calc_line = "x";
  // model->SetCalcLine(calc_line);

  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, VarLine_2) {
  std::string calc_line = "x";
  // model->SetCalcLine(calc_line);
  
  std::string var_line = "-100e-2";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, VarLine_3) {
  std::string calc_line = "x";
  // model->SetCalcLine(calc_line);
  
  std::string var_line = "12.33";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, VarLine_4) {
  std::string calc_line = "x";
  // model->SetCalcLine(calc_line);
  
  std::string var_line = "";
  model->SetVarX(var_line);
  
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_1) {
  std::string calc_line = "3.14";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_2) {
  std::string calc_line = "3.14+256";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_3) {
  std::string calc_line = "256^(1/2)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_4) {
  std::string calc_line = ".256*10";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_5) {
  std::string calc_line = "256./10";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyLine_6) {
  std::string calc_line = "1";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyFuncLine_1) {
  std::string calc_line = "sin(64)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyFuncLine_2) {
  std::string calc_line = "sqrt(x)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyFuncLine_3) {
  std::string calc_line = "x%x";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyUnariLine_1) {
  std::string calc_line = "-20";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyUnariLine_2) {
  std::string calc_line = "-20-10";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyUnariLine_3) {
  std::string calc_line = "-x";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyExpNotationLine_1) {
  std::string calc_line = "314E-2";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, EasyExpNotationLine_2) {
  std::string calc_line = "1.123e+12";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, HardLine_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, HardLine_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1)-sqrt(4))-1)/1)*2";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, HardLine_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, HardLine_4) {
  std::string calc_line = "-ln(sqrt((sin(10)^2)-(cos(10)^2)))";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, BrokenLineUnari_1) {
  std::string calc_line = "-/x";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineUnari_2) {
  std::string calc_line = "*16-9";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineExpNotation_1) {
  std::string calc_line = "1.1e-1.1+1";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineExpNotation_2) {
  std::string calc_line = "10e*1+2";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineFunk_1) {
  std::string calc_line = "asan(e)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineFunk_2) {
  std::string calc_line = "12-hgf()";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineFunk_3) {
  std::string calc_line = "12-sin";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineDot_1) {
  std::string calc_line = "12..4+3";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineParenthesis_1) {
  std::string calc_line = "(12.+3))";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineOperator_1) {
  std::string calc_line = "(12+)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineOperator_2) {
  std::string calc_line = "-12-";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineOperator_3) {
  std::string calc_line = "100x0.1";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineOperator_4) {
  std::string calc_line = "100(0.1)";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineDoesNotExist_1) {
  std::string calc_line = "!5";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, BrokenLineDoesNotExist_2) {
  std::string calc_line = "-";
  // model->SetCalcLine(calc_line);
  model->ProcessAndCalculate(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

} // namespace s21