#include "s21_creditcalc_test.h"

namespace s21 {

void CreditCalcTest::SetUp() {
  calc_controller = new s21::BankCalcController();
  model = new s21::CalcCredit();
}

void CreditCalcTest::TearDown() {
  delete calc_controller;
  delete model;
}

TEST_F(CreditCalcTest, Annuity_1_mounth) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = false;

  calc_controller->AnnuityPaymentCalc(amount, percent, period, is_year);
  double **table = calc_controller->GetCreditResultTable();
  period = is_year ? period * 12 : period;
  float expect[period][5]{{0, 10083.33, 10000, 83.33, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Annuity_1_year) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;

  calc_controller->AnnuityPaymentCalc(amount, percent, period, is_year);
  double **table = calc_controller->GetCreditResultTable();

  period = is_year ? period * 12 : period;
  float expect[period][5] = {
      {0, 879.16, 795.83, 83.33, 9204.17}, {0, 879.16, 802.46, 76.70, 8401.71},
      {0, 879.16, 809.15, 70.01, 7592.57}, {0, 879.16, 815.89, 63.27, 6776.69},
      {0, 879.16, 822.69, 56.47, 5954.00}, {0, 879.16, 829.54, 49.62, 5124.46},
      {0, 879.16, 836.46, 42.70, 4288.00}, {0, 879.16, 843.43, 35.73, 3444.58},
      {0, 879.16, 850.45, 28.70, 2594.12}, {0, 879.16, 857.54, 21.62, 1736.58},
      {0, 879.16, 864.69, 14.47, 871.89},  {0, 879.16, 871.89, 7.27, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Differentiated_1_mounth) {
  double amount = 10000;
  double percent = 5;
  unsigned period = 1;
  bool is_year = false;

  calc_controller->DifferentiatedPaymentCalc(amount, percent, period, is_year);
  double **table = calc_controller->GetCreditResultTable();

  period = is_year ? period * 12 : period;
  float expect[period][5]{{0, 10041.67, 10000, 41.67, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Differentiated_1_year) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;

  calc_controller->DifferentiatedPaymentCalc(amount, percent, period, is_year);
  double **table = calc_controller->GetCreditResultTable();

  period = is_year ? period * 12 : period;
  float expect[period][5] = {
      {0, 916.67, 833.33, 83.33, 9166.67}, {0, 909.72, 833.33, 76.39, 8333.33},
      {0, 902.78, 833.33, 69.44, 7500.00}, {0, 895.83, 833.33, 62.50, 6666.67},
      {0, 888.89, 833.33, 55.56, 5833.33}, {0, 881.94, 833.33, 48.61, 5000.00},
      {0, 875.00, 833.33, 41.67, 4166.67}, {0, 868.06, 833.33, 34.72, 3333.33},
      {0, 861.11, 833.33, 27.78, 2500.00}, {0, 854.17, 833.33, 20.83, 1666.67},
      {0, 847.22, 833.33, 13.89, 833.33},  {0, 840.28, 833.33, 6.94, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Copy_constructor) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;

  model->DifferentiatedPaymentCalc(amount, percent, period, is_year);
  double **main_table = model->GetTablePayment();

  CalcCredit cp_model(*model);
  double **cp_table = cp_model.GetTablePayment();
  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(cp_table[i][1], main_table[i][1], kEps);
    EXPECT_NEAR(cp_table[i][2], main_table[i][2], kEps);
    EXPECT_NEAR(cp_table[i][3], main_table[i][3], kEps);
    EXPECT_NEAR(cp_table[i][4], main_table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Move_constructor) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;

  model->DifferentiatedPaymentCalc(amount, percent, period, is_year);

  CalcCredit mv_model(std::move(*model));
  double **mv_table = mv_model.GetTablePayment();

  period = is_year ? period * 12 : period;
  float expect[period][5] = {
      {0, 916.67, 833.33, 83.33, 9166.67}, {0, 909.72, 833.33, 76.39, 8333.33},
      {0, 902.78, 833.33, 69.44, 7500.00}, {0, 895.83, 833.33, 62.50, 6666.67},
      {0, 888.89, 833.33, 55.56, 5833.33}, {0, 881.94, 833.33, 48.61, 5000.00},
      {0, 875.00, 833.33, 41.67, 4166.67}, {0, 868.06, 833.33, 34.72, 3333.33},
      {0, 861.11, 833.33, 27.78, 2500.00}, {0, 854.17, 833.33, 20.83, 1666.67},
      {0, 847.22, 833.33, 13.89, 833.33},  {0, 840.28, 833.33, 6.94, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], mv_table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], mv_table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], mv_table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], mv_table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Copy_operator) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;
  CalcCredit cp_model;

  model->DifferentiatedPaymentCalc(amount, percent, period, is_year);
  double **main_table = model->GetTablePayment();

  cp_model = *model;
  double **cp_table = cp_model.GetTablePayment();
  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(cp_table[i][1], main_table[i][1], kEps);
    EXPECT_NEAR(cp_table[i][2], main_table[i][2], kEps);
    EXPECT_NEAR(cp_table[i][3], main_table[i][3], kEps);
    EXPECT_NEAR(cp_table[i][4], main_table[i][4], kEps);
  }
}

TEST_F(CreditCalcTest, Move_operator) {
  double amount = 10000;
  double percent = 10;
  unsigned period = 1;
  bool is_year = true;
  CalcCredit mv_model;
  model->DifferentiatedPaymentCalc(amount, percent, period, is_year);

  mv_model = std::move(*model);
  double **mv_table = mv_model.GetTablePayment();

  period = is_year ? period * 12 : period;
  float expect[period][5] = {
      {0, 916.67, 833.33, 83.33, 9166.67}, {0, 909.72, 833.33, 76.39, 8333.33},
      {0, 902.78, 833.33, 69.44, 7500.00}, {0, 895.83, 833.33, 62.50, 6666.67},
      {0, 888.89, 833.33, 55.56, 5833.33}, {0, 881.94, 833.33, 48.61, 5000.00},
      {0, 875.00, 833.33, 41.67, 4166.67}, {0, 868.06, 833.33, 34.72, 3333.33},
      {0, 861.11, 833.33, 27.78, 2500.00}, {0, 854.17, 833.33, 20.83, 1666.67},
      {0, 847.22, 833.33, 13.89, 833.33},  {0, 840.28, 833.33, 6.94, 0.00}};

  for (unsigned i = 0; i < period; i++) {
    EXPECT_NEAR(expect[i][1], mv_table[i][1], kEps);
    EXPECT_NEAR(expect[i][2], mv_table[i][2], kEps);
    EXPECT_NEAR(expect[i][3], mv_table[i][3], kEps);
    EXPECT_NEAR(expect[i][4], mv_table[i][4], kEps);
  }
}

}  // namespace s21
