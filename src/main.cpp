#include <iostream>
#include "model/s21_network.h"
#include "model/utils/s21_dataset.h"

int main() {
  std::string path = "emnist-letters-train.csv";
  std::vector<std::vector<double>> inputValues;
  std::vector<int> outputValues;
  s21::S21Dataset::S21GetValuesFromCSV(path, inputValues, outputValues);

  std::cout << "\ndataset ready\n";

  s21::S21Network net = s21::S21Network::createNetwork(4);

  std::cout << "\nnet ready\n";

  net.S21Train(inputValues, outputValues, 0.1, 10);

  net.S21FeedForward(inputValues[0]);

  std::cout << "result: ";

  for (int i = 0; i < net.layers_[6].size(); i++) {
    std::cout << i << ": " << net.layers_[6][i].S21NeuronValue() << "\n";
  }

  std::cout << "\nresult: ";
  for (auto it : net.layers_[6]) {
    std::cout << it.S21NeuronValue() << " ";
  }

  return 0;
}
