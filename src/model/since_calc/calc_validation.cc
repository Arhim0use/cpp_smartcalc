#include "calc_model.h"

namespace s21 {
  bool SmartCalc::IsDigit(const char symbol) const noexcept {
    return  (symbol >= '0' && symbol <= '9');
  }
  
  bool SmartCalc::IsLetter(const char symbol) const noexcept {
    return (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'); 
  }
  
  bool SmartCalc::IsFunc(const std::string &str) const noexcept {
    std::string function[11] = {"mod",  "sin",  "cos",  "tan", "asin",
                        "acos", "atan", "sqrt", "log", "ln"};
    bool result = false;
    for(int i = 0; i < 11 && !result ; i++){
      result = str == function[i];
    }
    return result;
  }
  
  bool SmartCalc::IsOperator(const char symbol) const noexcept {
    return (symbol == '+' || symbol == '-' || symbol == '*' 
      || symbol == '/' || symbol == '^'); 
  }
  
  bool SmartCalc::IsParenthesis(const char symbol) const noexcept {
    return (symbol == '(' || symbol == ')'); 
  }
  
  bool SmartCalc::IsDot(const char symbol) const noexcept {
    return symbol == '.'; 
  }

  void SmartCalc::IsValidVarX(const std::string &str) noexcept {
    IsValidNum(str);
  }

  void SmartCalc::IsValidNum(const std::string &str)  noexcept {
    size_t size = std::distance(str.begin(), str.end());
    if (!size) {
      status_ = kOk; 
      return;
    }
    if (size > kmax_size) {
      status_ = kError; 
      return;
    }
    if (size == 1 && IsDot(*str.begin())) {
      status_ = kError; 
      return;
    }
    if (size == 1 && (*str.begin() == 'X' || *str.begin() == 'x')) {
      status_ = kOk; 
      return;
    }

    int count_dot = 0;
    for(auto it = str.begin(); it != str.end() && status_ == kOk && !IsOperator(*it); ++it){
      if (IsLetter(*it)) {
        if (*it == 'e' || *it == 'E'){ 
          IsValidExpNotation(it, str.end()); 
          break;
        } else {
          status_ = kError;
        }
      }
      if (IsDot(*it)) {
        count_dot++;
        if (count_dot > 1) status_ = kError;
      };
    }

  }

  void SmartCalc::IsValidExpNotation(std::string::const_iterator it, std::string::const_iterator it_end)  noexcept {
    // 1.1234e-11;
    size_t size = std::distance(it, it_end);
    if (size <= 1) {
      status_ = kError; 
      return;
    }
    
    int count_operator = 0;
    auto cp_it = ++it;

    for(; cp_it != it_end && count_operator < 2 && status_ == kOk; ++cp_it){
      if (IsOperator(*cp_it)) {
        if (*cp_it != '+' && *cp_it !=  '-') {
          status_ = kError;
        } else {
          count_operator++;
        }
      }
      if (IsLetter(*cp_it)) status_ = kError;
      if (IsDot(*cp_it)) status_ = kError;
    } 
  }

  void SmartCalc::IsValidOperator(const std::string &str, int at_pos) {
    /* valid -asin  -(   ((  (0  (-  ))  )-  )\0 -- +- *- /- ^- */
    auto it = str.begin() + at_pos;
    if (str[at_pos] == ')' && it == (str.end() - 1)) {
      status_ = kOk;
    } else if (IsOperator(str[at_pos]) && it == (str.end() - 1)) { 
      status_ = kError;
    } else if (IsOperator(str[at_pos])) { 
      IsValidUnari(str[at_pos + 1]);
    } else if (str[at_pos] == '(' && (str[at_pos + 1] == '(' || 
                str[at_pos + 1] == '-' || IsLetter(str[at_pos + 1]) || IsDigit(str[at_pos + 1]))) {
      status_ = kOk;
    } else if (str[at_pos] == ')' && (str[at_pos + 1] == ')' || IsOperator(str[at_pos + 1]))) {
      status_ = kOk;
    } else {
      status_ = kError;
    }
  
  }

  void SmartCalc::IsValidUnari(const char second) noexcept {
    /* valid -asin  -(  (0  (-  -- +- *- /- ^-     */
    if (second == '-' || IsLetter(second) || IsDigit(second) || second == '(') {
      status_ = kOk;
    } else if (IsOperator(second) || second == ')') {
      status_ = kError;
    } 
  }

} // namespace s21