#include "calc_model.h"

namespace s21 {

void SmartCalc::ShuntingYard() {
  if (!token_line_pair.size()) {
    token_line_pair.push_back({0, Type::kNumber});
    return;
  }
  auto token = token_line_pair.back();
  std::list<std::pair<double, short int>> qu;
  std::list<std::pair<double, short int>> stack;
  for (auto it = token_line_pair.rbegin(); it != token_line_pair.rend(); ++it) {
    token = *it;
    int priority = GetPriority((*it).second);
    if ((*it).second == kNumber || (*it).second == kVariable) {
      qu.push_back(*it);
    } else if (priority == 6 /* func */ || (*it).second == kL_parenthesis) {
      stack.push_back(*it);
    } else if (((*it).second >= kPlus && (*it).second <= kMod)) {
      PushOperator(priority, stack, qu, it);
    } else if ((*it).second == kR_parenthesis) {
      auto token = *it;
      PushCloseParenthesis(token, stack, qu);
    }
  }

  while (!stack.empty() && status_ != kError) {
    auto x = stack.back();
    qu.push_back(x);
    stack.pop_back();
  }

  token_line_pair = qu;
}

void SmartCalc::PushOperator(
    int &priority, std::list<std::pair<double, short>> &stack,
    std::list<std::pair<double, short>> &qu,
    std::reverse_iterator<std::list<std::pair<double, short>>::iterator> &it) {
  if (!stack.empty() && priority <= GetPriority(stack.back().second)) {
    int cp_pr = priority;
    while (!stack.empty() && cp_pr <= GetPriority(stack.back().second)) {
      if (stack.back().second != kL_parenthesis) {
        qu.push_back(stack.back());
      }
      stack.pop_back();
    }
  }
  stack.push_back(*it);
}

void SmartCalc::PushCloseParenthesis(std::pair<double, short> &token,
                                     std::list<std::pair<double, short>> &stack,
                                     std::list<std::pair<double, short>> &qu) {
  for (; !stack.empty() && token.second != kL_parenthesis;) {
    token = stack.back();
    if (token.second != kL_parenthesis) {
      qu.push_back(token);
    }
    stack.pop_back();
  }
}

int SmartCalc::GetPriority(const int token_type) const noexcept {
  int priority = 0;
  if (token_type == kNumber || token_type == kVariable) {
    priority = 1;
  } else if (token_type == kL_parenthesis || token_type == kR_parenthesis) {
    // ( )
    priority = 2;
  } else if (token_type >= kPlus && token_type <= kMinus) {
    // + -
    priority = 3;
  } else if (token_type == kPow) {
    // ^
    priority = 5;
  } else if (token_type >= kMul && token_type <= kMod) {
    // * / %
    priority = 4;
  } else if ((token_type >= kSin && token_type <= kLn) ||
             token_type == kUnary) {
    // funk && unary
    priority = 6;
  }
  return priority;
}

}  // namespace s21
