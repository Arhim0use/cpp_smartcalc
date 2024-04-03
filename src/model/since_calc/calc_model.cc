#include "calc_model.h"

namespace s21 {

SmartCalc::SmartCalc()
    : db_var_x_(0.),
      calcus_line_("0"),
      token_line_pair(std::list<std::pair<double, short int>>()),
      status_(kOk){};
SmartCalc::~SmartCalc() = default;

double SmartCalc::ProcessAndCalculate(const std::string &str) {
  double res = 0.;
  token_line_pair.clear();
  status_ = kOk;
  IsValidString(str);
  if (status_ != Status::kError) {
    ShuntingYard();
    res = Calculation(token_line_pair);
  }
  return res;
}

int SmartCalc::GetStatus() const noexcept { return status_; }

void SmartCalc::SetVarX(const std::string &str) {
  status_ = kOk;
  db_var_x_ = SetVar(str, db_var_x_);
}

}  // namespace s21
