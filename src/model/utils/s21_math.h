#ifndef SRC_S21_MATH_H
#define SRC_S21_MATH_H

#include <cstdint>
#include <vector>

namespace s21 {

struct S21Matrix {
  S21Matrix(uint32_t rows, uint32_t columns);

  std::vector<std::vector<double>> weightMatrix_;
};

class S21Math {
 public:
  S21Math() = delete;

  static double S21Sigmoid(double x);
};

}  // namespace s21

#endif  // SRC_S21_MATH_H
