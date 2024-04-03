#include "bank_calc_controller.h"

namespace s21 {

void BankCalcController::AnnuityPaymentCalc(const double amount,
                                            const double percent,
                                            const double period,
                                            bool period_type) {
  credit.AnnuityPaymentCalc(amount, percent, period, period_type);
}

void BankCalcController::DifferentiatedPaymentCalc(const double amount,
                                                   const double percent,
                                                   const double period,
                                                   bool period_type) {
  credit.DifferentiatedPaymentCalc(amount, percent, period, period_type);
}

double **BankCalcController::GetCreditResultTable() const noexcept {
  return credit.GetTablePayment();
}

}  // namespace s21
