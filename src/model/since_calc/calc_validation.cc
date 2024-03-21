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

  bool SmartCalc::IsValidVarX(const std::string &str) const noexcept {
    return str.size() == 0 || IsValidNum(std::begin(str), std::end(str));
  }

  bool SmartCalc::IsValidNum(std::string::const_iterator it, std::string::const_iterator it_end) const noexcept{
    size_t size = std::distance(it, it_end);
    if (!size) return false;
    if (size > kmax_size) return false;
    if (size == 1 && IsDot(*it)) return false;

    int count_dot = 0;
    bool result = true;
    for(auto cp_it = it; cp_it != it_end && result && !IsOperator(*cp_it); ++cp_it){
      if (IsLetter(*cp_it)) {
        if (*cp_it == 'e' || *cp_it == 'E'){
          result = IsValidExpNotation(cp_it, it_end); // добавить рес флаг
          break;
        } else {
          result = false;
        }
      }
      if (IsDot(*cp_it)) {
        count_dot++;
        if (count_dot > 1) result = false;
      };
    }

    return count_dot < 2 && result ? true : false;
  }

  bool SmartCalc::IsValidExpNotation(std::string::const_iterator it, std::string::const_iterator it_end) const noexcept {
    // 6.67384e-11;
    size_t size = std::distance(it, it_end);
    if (size <= 1) return false;
    bool result = true;
    int count_operator = 0;
    auto cp_it = ++it;
    result = (*cp_it == '+' || *cp_it ==  '-');
    for(; cp_it != it_end && count_operator < 2 && result; ++cp_it){
      if (IsOperator(*cp_it)) {
        if (*cp_it != '+' && *cp_it !=  '-') result = false;
        else count_operator++;
      }
      if (IsLetter(*cp_it)) result  = false;
      if (IsDot(*cp_it)) result  = false;
    } 
    return result;
  }

  bool SmartCalc::IsValidOperator(const std::string &str, int at_pos) const {
    /* valid -asin  -(   ((  (0  (-  ))  )-  )\0 -- +- *- /- ^- */
    bool result = false;
    auto it = str.begin() + at_pos;
    if (str[at_pos] == ')' && it == (str.end() - 1)) {
      result = true;
    } else if (IsOperator(str[at_pos])) { 
      result = IsValidUnari(str[at_pos + 1]);
    } else if (str[at_pos] == '(' && (str[at_pos + 1] == '(' || 
                str[at_pos + 1] == '-' || IsLetter(str[at_pos + 1]) || IsDigit(str[at_pos + 1]))) {
      result = true;
    } else if (str[at_pos] == ')' && (str[at_pos + 1] == ')' || IsOperator(str[at_pos + 1]))) {
      result = true;
    } else {
      result = false;
    }
    
    return result;
  }

  bool SmartCalc::IsValidUnari(const char second) const noexcept {
    /* valid -asin  -(   ((  (0  (-  ))  )-  )\0 -- +- *- /- ^- */
    bool result = false;
    if (second == '-' || IsLetter(second) || IsDigit(second) || second == '(') {
      result = true;
    } else if (IsOperator(second) || second == ')') {
      result = false;
    } 
    return result;
  }
  
  bool SmartCalc::IsValidString(const std::string &str){
    bool result = true;
    // bool operator_flag = false;
    int count_parthensis = 0;
    std::string token = "";
    auto it_begin = str.begin();
    for (auto it = str.begin(); it != str.end() && result; ++it){
      if (it == str.begin() && *it == '-' && IsValidUnari(str[1])) ++it;
      else if (it == str.begin() && IsOperator(*it))
      {
        result = false;
      }
      

      if (IsDigit(*it) || IsDot(*it)) {
        token.push_back(*it);
      } else if (IsLetter(*it)){
        if (*it != 'x' && *it != 'X') token.push_back(*it);
        
        if (*it == 'e' || *it == 'E') {
          ++it;
          if (it != str.end() && IsOperator(*it)) {
            token.push_back(*it);
            continue;
          }
        } else if (*it == 'x' || *it == 'X') {
          /* push num */
        }
        
      } else if (IsParenthesis(*it)){
        if (*it == '(') {
          count_parthensis++;
        } else {
          count_parthensis--;
        }
      }

      if (result && (IsOperator(*it) || IsParenthesis(*it))){
        result = IsValidOperator(str, std::distance(it_begin, it) /* it.base() - it_begin.base() */);

        if (result)
          result = IsValidNum(token.begin(), token.end()) || IsFunc(token);
        token.clear();
        if (count_parthensis < 0) result = false;
      }
      if (!IsOperator(*it) && !IsParenthesis(*it) && !IsDigit(*it) && !IsLetter(*it) && !IsDot(*it))
        result = false;
    }
    if (token.size()) result = IsValidNum(token.begin(), token.end());
    if (count_parthensis != 0) result = false;
    status_ = (result ? Status::kOk : Status::kError);
    return result;
  }

} // namespace s21