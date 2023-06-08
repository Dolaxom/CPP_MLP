#include "s21_network.h"

#include <iostream>
#include <stdexcept>

namespace s21 {
S21Network::S21Network(uint32_t layersCount) {
  if (layersCount < minLayersCount || layersCount > maxLayersCount) {
    throw std::runtime_error("Wrong layers count");
  }

  layers.resize(layersCount);
  for (auto& layer : layers) {
      layer.resize(784);
  }
    layers.back().resize(26);
}

S21Network S21Network::createNetwork(uint32_t layersCount) {
  try {
    return S21Network(layersCount);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  return S21Network(4);
}
}  // namespace s21