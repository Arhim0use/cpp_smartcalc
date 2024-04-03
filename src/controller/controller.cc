#include "controller.h"

namespace s21 {
SmartCalcController::SmartCalcController() = default;
SmartCalcController::~SmartCalcController() = default;

bool SmartCalcController::GetStatus() const noexcept {
  return controller_.GetStatus();
}
void SmartCalcController::SetVarX(const std::string &str) {
  controller_.SetVarX(str);
}
double SmartCalcController::Calculate(const std::string &str) {
  return controller_.ProcessAndCalculate(str);
}

std::vector<std::vector<double>> SmartCalcController::GrafCalculation(
    const int accuracy, const double start_pos, const double end_pos) {
  return controller_.GrafCalculation(accuracy, start_pos, end_pos);
}

std::vector<std::vector<double>> SmartCalcController::GrafCalculation(
    const std::string &str, const int accuracy, const double start_pos,
    const double end_pos) {
  return controller_.GrafCalculation(str, accuracy, start_pos, end_pos);
}

}  // namespace s21
