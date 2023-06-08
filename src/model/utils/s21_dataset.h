#ifndef SRC_S21_DATASET_H
#define SRC_S21_DATASET_H

#include <string>
#include <vector>

namespace s21 {

class S21Dataset {
 public:
  static void S21GetValuesFromCSV(const std::string& pathToCSVFile,
                                  std::vector<std::vector<double>>& inputValues,
                                  std::vector<int>& outputValues);
};

}  // namespace s21

#endif  // SRC_S21_DATASET_H
