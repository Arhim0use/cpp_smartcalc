#include "calc_model.h"

namespace s21 {
  
  void SmartCalc::PushFirstUnari(std::string::const_iterator *it, const char ch) {
    if (**it == '-') {
      IsValidUnari(ch);
      ++(*it);
      token_line_pair.push_front({-1, Type::kNumber});
      token_line_pair.push_front({0, Type::kMul});
    } else if (IsOperator(**it)) {
      status_ = kError;
    }
  }

  int SmartCalc::GetType(const char ch) const {
    int size = 7;
    char op[size] = "+-*/^%";
    for (int i = 0; i < size; i++) {
      if (op[i] == ch)
        return i + Type::kPlus;
    }
    return 0;
  }

  void SmartCalc::PushOperator(const std::string &str, int at_pos) {
    if (status_ == Status::kOk) IsValidOperator(str, at_pos);
    if (status_ == Status::kOk) {
      int tp =  GetType(str[at_pos]);
      if (tp == Type::kMinus && (IsOperator(str[at_pos - 1]) || str[at_pos - 1] == '(')) {
        token_line_pair.push_front({-1, Type::kNumber});
        token_line_pair.push_front({0, Type::kMul});
      }
      else if (tp) {
        token_line_pair.push_front({0, tp});
      }
    }
  }
  
  void SmartCalc::PushOpenParenthesis(const char ch, int *count_parthensis) {
    if (ch == '(') {
      (*count_parthensis)++;
      token_line_pair.push_front({0, Type::kL_parenthesis});
    } 
  }

  void SmartCalc::PushCloseParenthesis(const char ch, int *count_parthensis) {
    if  (ch == ')') {
      (*count_parthensis)--;
      token_line_pair.push_front({0, Type::kR_parenthesis});
    }
    if ((*count_parthensis) < 0) status_ = kError;
  }

  void SmartCalc::PushNum(const std::string &str) {
    IsValidNum(str); 
    if (status_ == Status::kOk && str.size()) {
      if (str == "x" || str == "X")
        token_line_pair.push_front({db_var_x_, Type::kVariable});
      else 
        token_line_pair.push_front({std::stold(str), Type::kNumber});
    }
  }

  bool SmartCalc::IsFunc(const std::string &str) {
    int size = 9;
    std::string function[size] = {"sin",  "cos",  "tan", "asin",
                        "acos", "atan", "sqrt", "log", "ln"};
    bool result = false;
    for(int i = 0; i < size && !result ; i++){
      result = str == function[i];
      if (result) token_line_pair.push_front({0, i + Type::kSin});
    }
    return result;
  }

  void SmartCalc::PushToken(const std::string &str, const std::string &token, std::string::const_iterator it) {

    if (*it == '(')
      std::cout << "hello";
    if (*it != '(' ){
      PushNum(token); 
    } else {
      if (token.size()) status_ = IsFunc(token) ? kOk : kError;
      status_ = IsParenthesis(*it) && !status_ ? kOk : kError;
    }
    PushOperator(str, std::distance(str.begin(), it));
    
  }


  void SmartCalc::IsValidString(const std::string &str) {

    int count_parthensis = 0;
    std::string token = "";
    for (auto it = str.begin(); it != str.end() && status_ == kOk; ++it){
      if (it == str.begin()) PushFirstUnari(&it, str[1]);

      if (IsDigit(*it) || IsDot(*it) || IsLetter(*it)){        
        token.push_back(*it);
        if (*it == 'e' || *it == 'E') {
          ++it;
          if (it != str.end() && IsOperator(*it)) {
            token.push_back(*it);
            continue;
          }
        }
      } 

      if (!status_ && (IsOperator(*it) || IsParenthesis(*it))){
        PushToken(str, token, it);
        PushOpenParenthesis(*it, &count_parthensis);
        PushCloseParenthesis(*it, &count_parthensis);
        token.clear();
      }
      if (!IsOperator(*it) && !IsParenthesis(*it) && !IsDigit(*it) && !IsLetter(*it) && !IsDot(*it))
        status_ = kError;
    }

    if (token.size() && !status_) PushNum(token);
    if (count_parthensis != 0) status_ = kError;
    PrintRLisr(token_line_pair);
  }

void PrintRLisr(std::list<std::pair<double, short int>> &l){
  std::string str[19] = {"1 kNumber", "x kVariable", "+ kPlus", "- kMinus", "* kMul", 
      "/ kDiv", "^ kPow", "% kMod", "kSin", "kCos", "kTan", "kAsin", "kAcos", 
      "kAtan", "kSqrt", "kLog", "kLn", "( kL_parenthesis", ") kR_parenthesis"};
  std::cout << "\n";
  for (auto it = l.rbegin(); it != l.rend(); it++) {
    std::cout << (*it).first << "\t" << str[(*it).second] << "\n";
  }
  std::cout << "\n";
}
} // namespace s21
