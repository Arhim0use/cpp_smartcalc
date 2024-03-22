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
enum type {
                               // priority
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
  
};

enum Status { kOk, kError };

class SmartCalc {

  public:
    SmartCalc() : /* var_x_(""), */ calcus_line_(""), token_line_(std::list<struct Token>()), status_(kOk) {};
    ~SmartCalc() = default;
    
    void SetVarX(const std::string &str) { 
      IsValidVarX(str);
      if (!str.size()) { 
        db_var_x_ = 0; 
      } else if (status_ == Status::kOk) {
        db_var_x_ = std::stod(str);
      }
    }

    void SetCalcLine(const std::string &str) { calcus_line_ = str; }

    enum Status GetStatus() const noexcept { return status_; }

    bool IsDot(const char symbol) const noexcept;
    bool IsDigit(const char symbol) const noexcept;
    bool IsLetter(const char symbol) const noexcept;
    bool IsOperator(const char symbol) const noexcept;
    bool IsParenthesis(const char symbol) const noexcept;

    bool IsFunc(const std::string &str) const noexcept;
    void IsValidVarX(const std::string &str) noexcept;
    void IsValidUnari(const char second)  noexcept;
    void IsValidNum(const std::string &str) noexcept;
    void IsValidExpNotation(std::string::const_iterator it, std::string::const_iterator it_end) noexcept;
    void IsValidOperator(const std::string &str, int at_pos) ;

    void PushFirstUnari(std::string::const_iterator *it, const char ch);
    void PushUnari(const std::string &str);
    void PushParenthesis(const char ch, int *count_parthensis);
    void PushNum(const std::string &str);
    void PushFunk(const std::string &str);

    void IsValidString(const std::string &str);
  private:
    double db_var_x_;
    // std::string var_x_;
    std::string calcus_line_;
    std::list<struct Token> token_line_;
    std::list<std::pair<double, short int>> token_line_pair;
    enum Status status_;
};

void PrintRLisr(std::list<std::pair<double, short int>> &l);

}  // namespace s21

#endif  // CPP3__SRC__MODEL__SINCE_CALC__CALC_MODEL_H