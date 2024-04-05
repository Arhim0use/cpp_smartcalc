#include "calc_model.h"

namespace s21 {

std::vector<std::vector<double>> SmartCalc::GrafCalculation(
    const unsigned int accuracy, double start_pos, double end_pos) {
  std::vector<std::vector<double>> graf(3, std::vector<double>(accuracy));
  GrafCalculation(graf, accuracy, start_pos, end_pos);
  return graf;
}

std::vector<std::vector<double>> SmartCalc::GrafCalculation(
    const std::string &str, unsigned int accuracy, double start_pos,
    double end_pos) {
  token_line_pair.clear();

  std::vector<std::vector<double>> graf(3, std::vector<double>(accuracy));
  IsValidString(str);
  if (status_ == kOk) {
    ShuntingYard();
    GrafCalculation(graf, accuracy, start_pos, end_pos);
  }
  return graf;
}

void SmartCalc::GrafCalculation(std::vector<std::vector<double>> &graf,
                                unsigned int accuracy, double start_pos,
                                double end_pos) {
  double max = std::max((start_pos), (end_pos));
  double min = std::min((start_pos), (end_pos));
  if (max <= 0 && min <= 0) {
    max = fabs(max);
    min = fabs(min);
  }
  long double iterator = fabs(max - min) != 0. ? fabs(max - min) : max + min;

  iterator = iterator / (accuracy - 1);
  int i = 0;

  for (double x_val = start_pos; x_val <= end_pos && x_val < graf[0].size();
       x_val += iterator, i++) {
    status_ = kOk;
    graf[0].at(i) = x_val;
    db_var_x_ = x_val;
    graf[1].at(i) = Calculation(token_line_pair);
    graf[2].at(i) = status_;
  }
  graf[0].back() = (db_var_x_ = end_pos);
  graf[1].back() = Calculation(token_line_pair);
}

}  // namespace s21
