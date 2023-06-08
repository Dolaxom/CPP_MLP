#include "s21_math.h"

#include <cmath>

namespace s21 {
S21Matrix::S21Matrix(uint32_t rows, uint32_t columns) {
  weightMatrix_.resize(rows);

  for (auto& row : weightMatrix_) {
    row.resize(columns);
  }
}

double S21Math::S21Sigmoid(double x) { return 1 / (1 + std::pow(M_E, -x)); }
}  // namespace s21
