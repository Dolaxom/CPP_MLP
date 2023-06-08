#ifndef SRC_S21_MATH_H
#define SRC_S21_MATH_H

#include <cstdint>
#include <vector>

namespace s21 {

class S21Matrix {
 public:
  S21Matrix(uint32_t rows, uint32_t columns);

 private:
  std::vector<std::vector<double>> weightMatrix_;
};

class S21Math {
 public:
  S21Math() = delete;

  static double S21Sigmoid(double x);
};

}  // namespace s21

#endif  // SRC_S21_MATH_H
