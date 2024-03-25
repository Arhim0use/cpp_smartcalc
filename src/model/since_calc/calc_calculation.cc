#include "calc_model.h"

namespace s21
{

double SmartCalc::ProcessAndCalculate(const std::string &str) {
  double res = 0.;
  IsValidString(str);
  if (status_ != Status::kError) {
    ShuntingYard();
    res = Calculation();
  }
  return res;
}

double SmartCalc::Calculation() {
  if (token_line_pair.size() == 1 && token_line_pair.back().second == kVariable){
    return db_var_x_;
  }
  std::list<std::pair<double, short int>> qu = token_line_pair;
  std::list<std::pair<double, short int>> stack;
  double val_1 = 0, val_2 = 0;

  do {
    if (qu.front().second == kNumber) {
      stack.push_back(qu.front());
      qu.pop_front();
    } else if (qu.front().second == kVariable) {
      stack.push_back({db_var_x_, kVariable});
      qu.pop_front();
    } else if (qu.front().second > kVariable) {
      val_2 = stack.back().first;
      stack.pop_back();
      if (GetPriority(qu.front().second) != 6 /* func */) {
        val_1 = stack.back().first;
        stack.pop_back();
      } else {
        val_1 = 0;
      }
      stack.push_back({FuncWork(val_1, val_2, qu.front().second), kNumber});
      qu.pop_front();
    }
    if (stack.back().first == NAN || stack.back().first == INFINITY || stack.back().first == -INFINITY)
      status_ = Status::kError;
  } while (!qu.empty() && status_ == Status::kOk);
  if (status_ == Status::kError){
    stack.push_back({0,0});
  }
  return  stack.back().first;
}
  
double SmartCalc::FuncWork(double val_1, double val_2, int type) const {
  double result = 0.;
  if (type == kPlus) {
    result = val_1 + val_2;
  } else if (type == kMinus) {
    result = val_1 - val_2;
  } else if (type == kMul) {
    result = val_1 * val_2;
  } else if (type == kDiv) {
    result = val_1 / val_2;
  } else if (type == kPow) {
    result = pow(val_1, val_2);
  } else if (type == kMod) {
    result = fmod(val_1, val_2);
  } else if (type == kSin) {
    result = sin(val_2);
  } else if (type == kCos) {
    result = cos(val_2);
  } else if (type == kTan) {
    result = tan(val_2);
  } else if (type == kAsin) {
    result = asin(val_2);
  } else if (type == kAcos) {
    result = acos(val_2);
  } else if (type == kAtan) {
    result = atan(val_2);
  } else if (type == kSqrt) {
    result = sqrt(val_2);
  } else if (type == kLog) {
    result = log10(val_2);
  } else if (type == kLn) {
    result = log(val_2);
  }
  return result;
}

} // namespace s21
