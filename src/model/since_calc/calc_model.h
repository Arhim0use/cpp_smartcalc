#ifndef CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H
#define CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H

#include <math.h>

#include <array>
#include <iostream>
#include <list>
#include <string>
#include <vector>

//! @brief Пространство имен учебных проектов школы программирования School 21
namespace s21 {
const size_t kmax_size = 256;

//! @brief Перечисление всех принемаемых токенов выражения
enum Type {        // priority
  kNumber,         // = 0,  // 1
  kVariable,       // = 1,  // 1
  kPlus,           // = 2,  // 3
  kMinus,          // = 3,  // 3
  kMul,            // = 4,  // 4
  kDiv,            // = 5,  // 4
  kPow,            // = 6,  // 5
  kMod,            // = 7,  // 4
  kSin,            // = 8,  // 6
  kCos,            // = 9,  // 6
  kTan,            // = 10, // 6
  kAsin,           // = 11, // 6
  kAcos,           // = 12, // 6
  kAtan,           // = 13, // 6
  kSqrt,           // = 14, // 6
  kLog,            // = 15, // 6
  kLn,             // = 16, // 6
  kL_parenthesis,  // = 17, // 2
  kR_parenthesis,  // = 18  // 2
  kUnary,          // = 19  // 6
};

enum Status { kOk, kError };

//! @brief   Модель калькулятора которая производит валидацию, парсинг и подсчет
//! матиматического выражения
class SmartCalc {
 public:
  SmartCalc();
  ~SmartCalc();

  /**
   * @brief Доступ к статусу вычисляемого выражения
   * @return 0 - выражение верно и подсчитано; 1 - в выражении есть ошибка
   */
  int GetStatus() const noexcept;
  /**
   * @brief Присвоение и валидация строки переменной
   * @param str Строка с воодимой переменной
   */
  void SetVarX(const std::string &str);
  /**
   * @brief Проверка и вычисление подсчитываемой строки
   * @param str Вычисляемая строка
   * @return Результат вычесления или 0 если выражение было с ошибкой
   */
  double ProcessAndCalculate(const std::string &str);

  /**
   * @brief Построение графика выражения
   * @param accuracy Количество отсраиваемых точек
   * @param start_pos Позиция-начало отрисовки графика
   * @param end_pos Позиция-конец отрисовки графика
   * @return Вектор из трех векторов с точками x, y и статусом если выражение
   * можно подсчитать
   */
  std::vector<std::vector<double>> GrafCalculation(const unsigned int accuracy,
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
                                                   const unsigned int accuracy,
                                                   double start_pos,
                                                   double end_pos);

 private:
  double db_var_x_;
  std::string calcus_line_;
  std::list<std::pair<double, short int>> token_line_pair;
  enum Status status_;

  bool IsDot(const char symbol) const noexcept;
  bool IsDigit(const char symbol) const noexcept;
  bool IsLetter(const char symbol) const noexcept;
  bool IsOperator(const char symbol) const noexcept;
  bool IsParenthesis(const char symbol) const noexcept;

  void IsValidUnari(const char second) noexcept;
  void IsValidNum(const std::string &str) noexcept;
  void IsValidNum(const std::string &str, bool x_str) noexcept;
  void IsValidVarX(const std::string &str) noexcept;
  void IsValidOperator(const std::string &str, int at_pos);
  void IsValidExpNotation(std::string::const_iterator it,
                          std::string::const_iterator it_end) noexcept;
  std::string ToLower(const std::string &str) noexcept;
  void IsValidString(const std::string &str);
  double SetVar(const std::string &str, double variable);

  bool IsFunc(const std::string &str);

  int GetType(const char ch) const;
  void ParseFirstUnari(std::string::const_iterator *it, const char ch);
  void ParseOperator(const std::string &str, int at_pos);
  void ParseParenthesis(const char ch, int *count_parthensis);
  void ParseNum(const std::string &str);
  void ParseToken(const std::string &str, const std::string &token,
                  std::string::const_iterator it);

  void ShuntingYard();
  void PushCloseParenthesis(std::pair<double, short> &token,
                            std::list<std::pair<double, short>> &stack,
                            std::list<std::pair<double, short>> &qu);
  void PushOperator(
      int &priority, std::list<std::pair<double, short>> &stack,
      std::list<std::pair<double, short>> &qu,
      std::reverse_iterator<std::list<std::pair<double, short>>::iterator> &it);

  int GetPriority(const int token_type) const noexcept;
  double FuncWork(double val_1, double val_2, int type) const;
  double Calculation(std::list<std::pair<double, short>> token_list);
  void GrafCalculation(std::vector<std::vector<double>> &graf,
                       const unsigned int accuracy, const double start_pos,
                       const double end_pos);
};

}  // namespace s21

#endif  // CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H