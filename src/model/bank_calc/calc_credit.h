#ifndef CPP3__SRC__MODEL__BANK_CALC__CREDIT_CALC_H
#define CPP3__SRC__MODEL__BANK_CALC__CREDIT_CALC_H

#include <math.h>

#include <stdexcept>

//! @brief Пространство имен учебных проектов школы программирован School 21
namespace s21 {

//! @brief Модель банковского калькулятора для рассчета платежей по аннуитентным
//! и дифференциированным кредитам
class CalcCredit {
  /// @brief Перечисление столбцов вычисляемой таблицы кредитных выплат
  enum table {
    kRow,
    kAmountPayment,  // Сумма платежа
    kPayment,        // Платеж по основному долгу
    kPercentPayment,  // Проценты долга от суммы платежа
    kRemains,         // Остаток всего платежа
  };

 public:
  CalcCredit();
  CalcCredit(const CalcCredit &other);
  CalcCredit(CalcCredit &&other);
  ~CalcCredit();

  CalcCredit operator=(const CalcCredit &other);
  CalcCredit &operator=(CalcCredit &&other);

  /**
   * @brief Рассчет аннуитентных патежей
   * @param amount Сумма взятая в долг
   * @param percent Годовая кредитная ставка
   * @param period Срок на который Берется кредит
   * @param period_type Тип периода 1 - год 0 - месяц
   */
  void AnnuityPaymentCalc(const double amount, const double percent,
                          const double period, bool period_type);

  /**
   * @brief Рассчет дифферециированных патежей
   * @param amount Сумма взятая в долг
   * @param percent Годовая кредитная ставка
   * @param period Срок на который Берется кредит
   * @param period_type Тип периода 1 - год 0 - месяц
   */
  void DifferentiatedPaymentCalc(const double amount, const double percent,
                                 const double period, bool period_type);

  /**
    * @brief Доступ рассчетным данным
    * @return Двумерный массив размером срок кредита на 5 столбцов \
  (месяц, сумма единоразовой выплаты, тело долга, процент долга, остаток долга)
   */
  double **GetTablePayment() const noexcept;

 private:
  double amount_;
  double percent_;
  unsigned int period_;
  double **table_;

  void DelTable();
  void AllocTable();
  void CopyTable(const CalcCredit &other);

  void SetCreditParam(const double amount, const double percent,
                      const double period, bool period_type);
  void AnnuityPayment() const noexcept;
  void DifferentiatedPayment() const noexcept;
};

}  // namespace s21

#endif  // CPP3__SRC__MODEL__BANK_CALC__CREDIT_CALC_H
