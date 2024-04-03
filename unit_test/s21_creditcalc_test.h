#ifndef CPP3__SRC__UNIT_TEST__S21_CREDITCALC_TEST_H
#define CPP3__SRC__UNIT_TEST__S21_CREDITCALC_TEST_H

#include <gtest/gtest.h>

#include "../src/controller/bank_calc_controller.h"
#include "../src/model/bank_calc/calc_credit.h"

namespace s21 {
const double kEps = 1e-02;

class CreditCalcTest : public testing::Test {
 protected:
  
  BankCalcController *calc_controller;
  CalcCredit *model;
  
  void SetUp();
  void TearDown();
};

}  // namespace s21

#endif  // CPP3__SRC__UNIT_TEST__S21_CREDITCALC_TEST_H