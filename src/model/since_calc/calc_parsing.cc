#include "calc_model.h"

namespace s21 {

void SmartCalc::IsValidString(const std::string &str) {
  std::string lower_str = ToLower(str);
  int count_parthensis = 0;
  std::string token = "";

  for (auto it = lower_str.cbegin(); it != lower_str.end() && status_ == kOk; ++it){
    if (it == lower_str.begin()) ParseFirstUnari(&it, lower_str[1]);

    if (IsDigit(*it) || IsDot(*it) || IsLetter(*it)){        
      token.push_back(*it);
      if (*it == 'e' || *it == 'E') {
        ++it;
        if (it != lower_str.end() && IsOperator(*it)) {
          token.push_back(*it);
          continue;
        }
      }
    } 
    if (!status_ && (IsOperator(*it) || IsParenthesis(*it))){
      ParseToken(lower_str, token, it);
      ParseParenthesis(*it, &count_parthensis);
      token.clear();
    }
    if (!IsOperator(*it) && !IsParenthesis(*it) && !IsDigit(*it) && !IsLetter(*it) && !IsDot(*it))
      status_ = kError;
  }

  if (token.size() && !status_) ParseNum(token);
  if (count_parthensis != 0) status_ = kError;
}

void SmartCalc::ParseFirstUnari(std::string::const_iterator *it, const char ch) {
  if (**it == '-') {
    IsValidUnari(ch);
    ++(*it);
    token_line_pair.push_front({-1, Type::kUnary});
    // token_line_pair.push_front({0, Type::kMul});
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

void SmartCalc::ParseOperator(const std::string &str, int at_pos) {
  if (status_ == Status::kOk) IsValidOperator(str, at_pos);
  if (status_ == Status::kOk) {
    int tp =  GetType(str[at_pos]);
    if (tp == Type::kMinus && (IsOperator(str[at_pos - 1]) || str[at_pos - 1] == '(')) {
      token_line_pair.push_front({-1, Type::kUnary});
      // token_line_pair.push_front({0, Type::kMul});
    }
    else if (tp) {
      token_line_pair.push_front({0, tp});
    }
  }
}

void SmartCalc::ParseParenthesis(const char ch, int *count_parthensis) {
  if (ch == '(') {
    (*count_parthensis)++;
    token_line_pair.push_front({0, Type::kL_parenthesis});
  } else if (ch == ')') {
    (*count_parthensis)--;
    token_line_pair.push_front({0, Type::kR_parenthesis});
  }
  if ((*count_parthensis) < 0) status_ = kError;
}


void SmartCalc::ParseNum(const std::string &str) {
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

void SmartCalc::ParseToken(const std::string &str, const std::string &token, std::string::const_iterator it) {

  if (*it != '(' ){
    ParseNum(token); 
  } else {
    if (token.size()) status_ = IsFunc(token) ? kOk : kError;
    status_ = IsParenthesis(*it) && !status_ ? kOk : kError;
  }
  ParseOperator(str, std::distance(str.begin(), it));
  
}

void PrintRLisr(std::list<std::pair<double, short int>> &l){
  std::string str[20] = {"1 kNumber", "x kVariable", "+ kPlus", "- kMinus", "* kMul", 
      "/ kDiv", "^ kPow", "% kMod", "kSin", "kCos", "kTan", "kAsin", "kAcos", 
      "kAtan", "kSqrt", "kLog", "kLn", "( kL_parenthesis", ") kR_parenthesis", "~ kUnary"};
  std::cout << "\n";
  for (auto it = l.rbegin(); it != l.rend(); it++) {
    std::cout << (*it).first << "\t" << str[(*it).second] << "\n";
  }
  std::cout << "\n";
}
} // namespace s21
