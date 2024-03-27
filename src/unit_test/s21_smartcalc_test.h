#ifndef CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H
#define CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H

#include <gtest/gtest.h>

#include "../model/since_calc/calc_model.h"

namespace s21 {
class SmartCalcValidationTest : public testing::Test {
 protected:
  std::string* calc_line;
  SmartCalc *model;

  void SetUp();
  void TearDown();
};

class SmartCalcCalculationTest : public testing::Test {
 protected:
  std::string* calc_line;
  SmartCalc *model;

  void SetUp();
  void TearDown();
};
}  // namespace s21

#endif  // CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H