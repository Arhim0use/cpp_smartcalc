#include "s21_smartcalc_test.h"

namespace s21{

void SmartCalcTest::SetUp() {
  model = new s21::SmartCalc();
}

void SmartCalcTest::TearDown() {
  delete model;
}


TEST_F(SmartCalcTest, void_line) {
  std::string calc_line = "";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, x_line) {
  std::string calc_line = "x";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_1) {
  std::string calc_line = "3.14";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_2) {
  std::string calc_line = "3.14+256";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_3) {
  std::string calc_line = "256^(1/2)";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_4) {
  std::string calc_line = ".256*10";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_5) {
  std::string calc_line = "256./10";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_line_6) {
  std::string calc_line = "1";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_func_line_1) {
  std::string calc_line = "sin(64)";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_func_line_2) {
  std::string calc_line = "sqrt(x)";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_unary_line_1) {
  std::string calc_line = "-20";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_unary_line_2) {
  std::string calc_line = "-20-10";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_unary_line_3) {
  std::string calc_line = "-x";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_exp_notation_line_1) {
  std::string calc_line = "314E-2";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, easy_exp_notation_line_2) {
  std::string calc_line = "1.123e+12";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, hard_line_1) {
  std::string calc_line = "-1.23*100/sin(2.5)-(2^(ln(9)/10))";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, hard_line_2) {
  std::string calc_line = "-x+(sin(1.5*(acos(1)-sqrt(4))-1)/1)*2";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, hard_line_3) {
  std::string calc_line = "-(1+4^-2-(-4+-10*-(1/2)*2))";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, hard_line_4) {
  std::string calc_line = "-ln(sqrt((sin(10)^2)-(cos(10)^2)))";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kOk);
}

TEST_F(SmartCalcTest, broken_line_1) {
  std::string calc_line = "-/x";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_2) {
  std::string calc_line = "1.1e-1.1+1";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_3) {
  std::string calc_line = "asan(e)";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_4) {
  std::string calc_line = "12..4+3";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_5) {
  std::string calc_line = "(12.+3))";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_6) {
  std::string calc_line = "(12+)";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_7) {
  std::string calc_line = "-12-";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_8) {
  std::string calc_line = "12-hgf";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_9) {
  std::string calc_line = "!5";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_10) {
  std::string calc_line = "*16-9";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

TEST_F(SmartCalcTest, broken_line_11) {
  std::string calc_line = "-";
  model->SetCalcLine(calc_line);
  model->IsValidString(calc_line);
  EXPECT_EQ(model->GetStatus(), Status::kError);
}

} // namespace s21