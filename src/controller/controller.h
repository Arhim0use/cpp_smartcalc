#ifndef CPP3__SRC__CONTROLLER__CONTROLLER_H
#define CPP3__SRC__CONTROLLER__CONTROLLER_H

#include "../model/since_calc/calc_model.h"

//! @brief Пространство имен учебных проектов школы программирован School 21
namespace s21 {

//! @brief Класс контроллер для доступа к вычислительной модели инженерного
//! калькулятора
class SmartCalcController {
 public:
  SmartCalcController();
  ~SmartCalcController();

  /**
   * @brief Доступ к статусу вычисляемого выражения
   * @return 0 - выражение верно и подсчитано; 1 - в выражении есть ошибка
   */
  bool GetStatus() const noexcept;

  /**
   * @brief Присвоение и валидация строки переменной
   * @param str Строка с воодимой переменной
   */
  void SetVarX(const std::string &str);

  /**
   * @brief Вычисление подсчитываемой строки
   * @param str Вычисляемая строка
   * @return Результат вычесления или 0 если выражение было с ошибкой
   */
  double Calculate(const std::string &str);

  /**
   * @brief Построение графика выражения
   * @param accuracy Количество отсраиваемых точек
   * @param start_pos Позиция-начало отрисовки графика
   * @param end_pos Позиция-конец отрисовки графика
   * @return Вектор из трех векторов с точками x, y и статусом если выражение
   * можно подсчитать
   */
  std::vector<std::vector<double>> GrafCalculation(const int accuracy,
                                                   const double start_pos,
                                                   const double end_pos);

  /**
   * @brief Построение графика выражения с задаваемой строкой
   * @param str Вычисляемая строка
   * @param accuracy Количество отсраиваемых точек
   * @param start_pos Позиция-начало отрисовки графика
   * @param end_pos Позиция-конец отрисовки графика
   * @return Вектор из трех векторов с точками x, y и статусом если выражение
   * можно подсчитать
   */
  std::vector<std::vector<double>> GrafCalculation(const std::string &str,
                                                   const int accuracy,
                                                   const double start_pos,
                                                   const double end_pos);

 private:
  SmartCalc controller_;
};

}  // namespace s21

#endif  // CPP3__SRC__CONTROLLER__CONTROLLER_H