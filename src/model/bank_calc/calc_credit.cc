#include "calc_credit.h"

namespace s21 {

CalcCredit::CalcCredit()
    : amount_(0), percent_(0), period_(0), table_(nullptr) {}

CalcCredit::~CalcCredit() { DelTable(); }

CalcCredit::CalcCredit(const CalcCredit &other)
    : amount_(other.amount_), percent_(other.percent_), period_(other.period_) {
  AllocTable();
  CopyTable(other);
}

CalcCredit::CalcCredit(CalcCredit &&other)
    : amount_(other.amount_),
      percent_(other.percent_),
      period_(other.period_),
      table_(other.table_) {
  other.table_ = nullptr;
  other.amount_ = 0;
  other.period_ = 0;
  other.percent_ = 0;
}

CalcCredit CalcCredit::operator=(const CalcCredit &other) {
  if (this != &other) {
    DelTable();
    amount_ = other.amount_;
    period_ = other.period_;
    percent_ = other.percent_;
    AllocTable();
    CopyTable(other);
  }
  return *this;
}

CalcCredit &CalcCredit::operator=(CalcCredit &&other) {
  if (this != &other) {
    DelTable();
    amount_ = other.amount_;
    period_ = other.period_;
    percent_ = other.percent_;
    table_ = other.table_;

    other.table_ = nullptr;
    other.amount_ = 0;
    other.period_ = 0;
    other.percent_ = 0;
  }
  return *this;
}

void CalcCredit::CopyTable(const CalcCredit &other) {
  for (unsigned int i = 0; i < other.period_; i++) {
    for (unsigned int j = 0; j < kRemains + 1; j++) {
      table_[i][j] = other.table_[i][j];
    }
  }
}

void CalcCredit::AnnuityPaymentCalc(const double amount, const double percent,
                                    const double period, bool period_type) {
  SetCreditParam(amount, percent, period, period_type);
  AnnuityPayment();
}

void CalcCredit::DifferentiatedPaymentCalc(const double amount,
                                           const double percent,
                                           const double period,
                                           bool period_type) {
  SetCreditParam(amount, percent, period, period_type);
  DifferentiatedPayment();
}

double **CalcCredit::GetTablePayment() const noexcept { return table_; }

/// @param amount Взятая в кредит сумма
/// @param percent Ставка в процентах
/// @param period Количество месяцев
/// @param period_type 0 - месяцев 1 - лет
void CalcCredit::SetCreditParam(const double amount, const double percent,
                                const double period, bool period_type) {
  DelTable();
  amount_ = amount;
  percent_ = percent;
  period_ = period_type ? period * 12 : period;
  AllocTable();
}

/// @brief Подсчет одной выплаты
/// @return Ежемесячную выплату в банк
void CalcCredit::AnnuityPayment() const noexcept {
  double percent = percent_ / 1200;

  double payment = 0., amount = amount_;
  double quotient = percent * pow(1 + percent, (double)period_);
  quotient /= pow((1 + percent), period_) - 1;

  payment = amount_ * quotient;

  if (table_) {
    for (unsigned i = 0; amount >= 0 && i < period_; i++) {
      double percent_pay = amount * percent;
      amount -= payment - percent_pay;
      table_[i][kRow] = i + 1;
      table_[i][kAmountPayment] = payment;
      table_[i][kPayment] = payment - percent_pay;
      table_[i][kPercentPayment] = percent_pay;
      table_[i][kRemains] = amount;
    }
  }
}

/// @brief Подсчет всего кредитного периода
/// @return Последнюю выплату в банк
void CalcCredit::DifferentiatedPayment() const noexcept {
  double payment = 0., amount = amount_;
  double dif_body = 0., percent_body = 0.;
  double percent = percent_ / 1200;
  dif_body = amount_ / period_;
  if (table_) {
    for (unsigned i = 0; amount >= 0 && i < period_; i++) {
      percent_body = amount * percent;
      payment = dif_body + percent_body;
      amount = amount - dif_body;
      table_[i][kRow] = i + 1;
      table_[i][kAmountPayment] = payment;
      table_[i][kPayment] = dif_body;
      table_[i][kPercentPayment] = percent_body;
      table_[i][kRemains] = amount;
    }
  }
}

void CalcCredit::DelTable() {
  if (!table_) return;
  for (unsigned int i = 0; i < period_ && table_[i]; i++) {
    delete[] table_[i];
    table_[i] = nullptr;
  }
  if (table_) delete[] table_;
  table_ = nullptr;
}

void CalcCredit::AllocTable() {
  table_ = new double *[period_]();
  for (unsigned i = 0; i < period_; i++) {
    table_[i] = new double[kRemains + 1]();
  }
}

}  // namespace s21
