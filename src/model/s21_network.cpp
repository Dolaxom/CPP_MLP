#include "s21_network.h"

#include <iostream>
#include <stdexcept>

namespace s21 {
S21Network::S21Network(uint32_t layersCount) {
  if (layersCount < minLayersCount_ || layersCount > maxLayersCount_) {
    throw std::runtime_error("Wrong layers count");
  }

  // create neurons matrix
  layers_.resize(layersCount);
  for (auto& layer : layers_) {
    layer.resize(imageSizeInPixels_);
  }
  layers_.back().resize(latinAlphabetSize_);

  // create weight matrices
  std::vector<S21Neuron>* leftPointer = &layers_[0];
  std::vector<S21Neuron>* rightPointer = &layers_[1];
  for (int i = 0; i < layersCount - 1; i++) {
    S21Matrix tmpMatrix(leftPointer->size(), rightPointer->size());
    weightMatrices_.push_back(tmpMatrix);
    ++leftPointer;
    ++rightPointer;
  }
}

S21Network S21Network::createNetwork(uint32_t layersCount) {
  try {
    return S21Network(layersCount);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  return S21Network(4);  // 4 is minimum layers count
}
}  // namespace s21