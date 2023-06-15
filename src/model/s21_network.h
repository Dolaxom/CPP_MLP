#ifndef SRC_S21_NETWORK_H
#define SRC_S21_NETWORK_H

#include <cstdint>
#include <vector>

#include "s21_neuron.h"
#include "utils/s21_math.h"

namespace s21 {

class S21Network {
  using layer = std::vector<S21Neuron>;

 public:
  static S21Network createNetwork(uint32_t layersCount);
  void S21FeedForward(std::vector<double>& inputValues);
  void S21Backpropagation(std::vector<double>& expectedOutput);
  void S21UpdateWeights(std::vector<double>& inputValues, double learningRate);
  void S21Train(std::vector<std::vector<double>>& inputValues, std::vector<int>& outputValues, double learningRate, int epochs);


  std::vector<layer> layers_;


 private:
  explicit S21Network(uint32_t layersCount);
  std::vector<S21Matrix> weightMatrices_;
  void S21InitWeights();
  double S21CalculateError(const std::vector<double>& expectedOutput);

  uint32_t minLayersCount_ = 4;       // 1 in, 1 out, 2 hidden layers
  uint32_t maxLayersCount_ = 7;       // 1 in, 1 out, 5 hidden layers
  uint32_t imageSizeInPixels_ = 784;  // 28x28 pixels = 784 pixels
  uint32_t latinAlphabetSize_ = 26;
};

}  // namespace s21

#endif  // SRC_S21_NETWORK_H
