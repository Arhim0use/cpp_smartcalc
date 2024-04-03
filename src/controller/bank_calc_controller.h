#ifndef CPP3__SRC__CONTROLLER__BANK_CALC_CONTROLLER_H
#define CPP3__SRC__CONTROLLER__BANK_CALC_CONTROLLER_H

#include "../model/bank_calc/calc_credit.h"

//! @brief Пространство имен учебных проектов школы программирован School 21
namespace s21 {

//! @brief Класс контроллер для доступа к вычислительной модели кредитного
//! калькулятора
class BankCalcController {
 public:
  BankCalcController() = default;
  ~BankCalcController() = default;

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
      (месяц, сумма единоразовой выплаты, тело долга, процент долга, остаток
    долга)
   */
  double **GetCreditResultTable() const noexcept;

 private:
  CalcCredit credit;
};

}  // namespace s21

#endif  // CPP3__SRC__MODEL__BANK_CALC__BANK_CALC_H