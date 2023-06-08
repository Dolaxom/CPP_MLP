#include <iostream>
#include "model/utils/s21_dataset.h"

int main() {
    std::string path = "emnist-letters-trainSHORT.csv";
    std::vector<std::vector<double>> inputValues;
    std::vector<int> outputValues;

    s21::S21Dataset::S21GetValuesFromCSV(path, inputValues, outputValues);

    std::cout << outputValues.size();

    return 0;
}
