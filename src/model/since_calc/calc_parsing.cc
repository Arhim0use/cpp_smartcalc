#include "calc_model.h"

namespace s21 {
  
  void SmartCalc::PushFirstUnari(std::string::const_iterator *it, const char ch) {
    if (**it == '-') {
      IsValidUnari(ch);
      ++(*it);
      token_line_pair.push_front({-1, type::kNumber});
      token_line_pair.push_front({0, type::kMul});
    } else if (IsOperator(**it)) {
      status_ = kError;
    }
  }
  
  // void SmartCalc::PushUnari(const std::string &str) {

  // }
  
  // void SmartCalc::PushOperator(const std::string &str) {

  // }

  void SmartCalc::PushParenthesis(const char ch, int *count_parthensis) {
    if (ch == '(') {
      (*count_parthensis)++;
      token_line_pair.push_front({0, type::kL_parenthesis});
    } else {
      (*count_parthensis)--;
      token_line_pair.push_front({0, type::kR_parenthesis});
    }
    if ((*count_parthensis) < 0) status_ = kError;
  }

  // void SmartCalc::PushNum(const std::string &str) {

  // }

  // void SmartCalc::PushFunk(const std::string &str) {

  // }


  void SmartCalc::IsValidString(const std::string &str) {

    int count_parthensis = 0;
    std::string token = "";
    auto it_begin = str.begin();
    for (auto it = str.begin(); it != str.end() && status_ == kOk; ++it){
      if (it == str.begin()) PushFirstUnari(&it, str[1]);

      if (IsDigit(*it) || IsDot(*it)) {
        token.push_back(*it);
      } else if (IsLetter(*it)){        
        token.push_back(*it);
        if (*it == 'e' || *it == 'E') {
          ++it;
          if (it != str.end() && IsOperator(*it)) {
            token.push_back(*it);
            continue;
          }
        }
        if (*it == 'x' || *it == 'X')
          token_line_pair.push_front({db_var_x_, type::kNumber});
      } else if (IsParenthesis(*it)){
        PushParenthesis(*it, &count_parthensis);
        // if (*it == '(') {
        //   count_parthensis++;
        //   // token_line_pair.push_front(0, type::kL_parenthesis);
        // } else {
        //   count_parthensis--;
        //   // token_line_pair.push_front(0, type::kR_parenthesis);
        // }
        // if (count_parthensis < 0) status_ = kError;
      }

      if (!status_ && (IsOperator(*it) || IsParenthesis(*it))){
        IsValidOperator(str, std::distance(it_begin, it));
        if (*it != '(' ){
          IsValidNum(token); 
        }else {
          if (token.size()) status_ = IsFunc(token) ? kOk : kError;
          status_ = IsParenthesis(*it) && !status_ ? kOk : kError;
        }

        token.clear();
      }
      if (!IsOperator(*it) && !IsParenthesis(*it) && !IsDigit(*it) && !IsLetter(*it) && !IsDot(*it))
        status_ = kError;
    }

    if (token.size() && !status_) IsValidNum(token);
    if (count_parthensis != 0) status_ = kError;
    PrintRLisr(token_line_pair);
  }

void PrintRLisr(std::list<std::pair<double, short int>> &l){
  std::string str[19] = {"kNumber", "kVariable", "kPlus", "kMinus", "kMul", 
      "kDiv", "kPow", "kMod", "kSin", "kCos", "kTan", "kAsin", "kAcos", 
      "kAtan", "kSqrt", "kLog", "kLn", "kL_parenthesis", "kR_parenthesis"};
  std::cout << "\n";
  for (auto it = l.rbegin(); it != l.rend(); it++) {
    std::cout << (*it).first << " " << str[(*it).second] << "\t";
  }
  std::cout << "\n";
}
} // namespace s21
