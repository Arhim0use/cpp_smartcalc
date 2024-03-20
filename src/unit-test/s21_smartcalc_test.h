#ifndef CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H
#define CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H

#include <gtest/gtest.h>



namespace s21 {
class SmartCalcTest : public testing::Test {
 protected:
  std::map<int, std::string>* std_map;

  void SetUp();
  void TearDown();
};
}  // namespace s21

#endif  // CPP3__SRC__UNIT_TEST__S21_SMARTCALC_TEST_H