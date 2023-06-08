#include "s21_math.h"

#include <cmath>

namespace s21 {
double S21Math::S21Sigmoid(double x) { return 1 / (1 + std::pow(M_E, -x)); }
}  // namespace s21