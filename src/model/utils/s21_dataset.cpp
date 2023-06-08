#include "s21_dataset.h"

#include <fstream>
#include <sstream>

namespace s21 {
void S21Dataset::S21GetValuesFromCSV(
    const std::string& pathToCSVFile,
    std::vector<std::vector<double>>& inputValues,
    std::vector<int>& outputValues) {
  std::ifstream csvFile(pathToCSVFile);
  if (!csvFile.is_open()) {
    return;
  }

  double maxColorValue = 0xFF;  // 0xFF = 255

  std::string line;
  while (std::getline(csvFile, line)) {
    std::stringstream ss(line);
    std::string token;
    std::vector<double> inputRow;

    std::getline(ss, token, ',');
    outputValues.push_back(std::stoi(token));

    while (std::getline(ss, token, ',')) {
      if (!token.empty()) {
        double pixelValue = std::stod(token) / maxColorValue;
        inputRow.push_back(pixelValue);
      }
    }

    if (!inputRow.empty()) {
      inputValues.push_back(inputRow);
    }
  }

  csvFile.close();
}
}  // namespace s21
