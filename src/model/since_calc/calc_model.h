#ifndef CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H
#define CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H

#include <list>
#include <string>
#include <iostream>

namespace s21 {
const size_t kmax_size = 256;

struct Token {
  Token() : value(0), type(0) {};
  ~Token() = default;
  double value;
  short int type;
};

enum Status { kOk, kError };

class SmartCalc {

  public:
    SmartCalc() : var_x_(""), calcus_line_(""), token_line_(std::list<struct Token>()), status_(kOk) {};
    ~SmartCalc() = default;
    
    void SetVarX(const std::string &str) { var_x_ = str; }
    void SetCalcLine(const std::string &str) { calcus_line_ = str; }

    bool IsDot(const char symbol) const noexcept;
    bool IsDigit(const char symbol) const noexcept;
    bool IsLetter(const char symbol) const noexcept;
    bool IsOperator(const char symbol) const noexcept;
    bool IsParenthesis(const char symbol) const noexcept;

    bool IsFunc(const std::string &str) const noexcept;
    bool IsValidVarX(const std::string &str) const noexcept;
    bool IsValidNum(std::string::const_iterator it, std::string::const_iterator it_end) const noexcept;
    bool IsValidExpNotation(std::string::const_iterator it, std::string::const_iterator it_end) const noexcept;
    bool IsValidOperator(const std::string &str, int at_pos) const;

    bool IsValidString(const std::string &str) const;
  private:
    double db_var_x;
    std::string var_x_;
    std::string calcus_line_;
    std::list<struct Token> token_line_;
    enum Status status_;
};

}  // namespace s21

#endif  // CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H