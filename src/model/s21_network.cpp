#include "s21_network.h"

#include <iostream>
#include <random>
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
    S21Matrix tmpMatrix(rightPointer->size(), leftPointer->size());
    weightMatrices_.push_back(tmpMatrix);
    ++leftPointer;
    ++rightPointer;
  }
  S21InitWeights();
}

S21Network S21Network::createNetwork(uint32_t layersCount) {
  try {
    return S21Network(layersCount);
  } catch (std::exception& e) {
    std::cerr << e.what();
  }

  return S21Network(4);  // 4 is minimum layers count
}

void S21Network::S21InitWeights() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<double> dist(0.0, 1.0);

  for (auto& matrix : weightMatrices_) {
    double stdDeviation = sqrt(2.0 / (matrix.weightMatrix_[0].size() + matrix.weightMatrix_.size()));
    for (auto& vec : matrix.weightMatrix_) {
      for (auto& it : vec) {
        it = dist(mt) * stdDeviation;
      }
    }
  }
}

void S21Network::S21FeedForward(std::vector<double>& inputValues) {
  for (int i = 0; i < layers_.at(0).size(); i++) {
    layers_[0][i].S21NeuronValue() = inputValues[i];
  }

  int startLayer = 1; // skip input layer
  for (int i = startLayer; i < layers_.size(); i++) {
    for (int deep = 0; deep < layers_[i].size(); deep++) {
      for (int deepPrev = 0; deepPrev < layers_[i - 1].size(); deepPrev++) {
          layers_[i][deep].S21NeuronValue() += (layers_[i - 1][deepPrev].S21NeuronValue() * weightMatrices_[i - 1].weightMatrix_[deep][deepPrev]);
      }
      layers_[i][deep].S21NeuronValue() = S21Math::S21Sigmoid(layers_[i][deep].S21NeuronValue());
    }
  }
}

void S21Network::S21Backpropagation(std::vector<double> &expectedOutput) {
  // Calculate output layer error
  layer& outputLayer = layers_.back();
  for (int i = 0; i < outputLayer.size(); i++) {
    double output = outputLayer[i].S21NeuronValue();
    double error = (expectedOutput[i] - output) * output * (1 - output);
    outputLayer[i].S21NeuronValue() = error;
  }

  // Backpropagating Error to Hidden Layers
  for (int i = layers_.size() - 2; i > 0; i--) {
    layer& hiddenLayer = layers_[i];
    layer& nextLayer = layers_[i + 1];
    S21Matrix& weightMatrix = weightMatrices_[i];

    for (int j = 0; j < hiddenLayer.size(); j++) {
      double output = hiddenLayer[j].S21NeuronValue();
      double sum = 0.0;

      for (int k = 0; k < nextLayer.size(); k++) {
          double weight = weightMatrix.weightMatrix_[k][j];
          double error = nextLayer[k].S21NeuronValue();
          sum += weight * error;
      }

      double error = output * (1 - output) * sum;
      hiddenLayer[j].S21NeuronValue() = error;
    }
  }
}

void S21Network::S21UpdateWeights(std::vector<double> &inputValues,
                                  double learningRate) {
  for (int i = 0; i < weightMatrices_.size(); i++) {
    S21Matrix& weightMatrix = weightMatrices_[i];
    layer& currentLayer = layers_[i];
    layer& nextLayer = layers_[i + 1];

    for (int j = 0; j < nextLayer.size(); j++) {
      for (int k = 0; k < currentLayer.size(); k++) {
          double delta = learningRate * nextLayer[j].S21NeuronValue() * currentLayer[k].S21NeuronValue();
          weightMatrix.weightMatrix_[j][k] += delta;
      }
    }
  }
}

void S21Network::S21Train(std::vector<std::vector<double>> &inputValues,
                          std::vector<int> &outputValues, double learningRate,
                          int epochs) {
  if (inputValues.size() != outputValues.size()) {
    throw std::runtime_error("Input and output data sizes do not match");
  }

  for (int epoch = 0; epoch < epochs; epoch++) {
    double totalError = 0.0;

    for (int i = 0; i < inputValues.size(); i++) {
      std::vector<double>& input = inputValues[i];
      std::vector<double> expectedOutput(latinAlphabetSize_, 0.0);
      expectedOutput[outputValues[i]] = 1.0;

      S21FeedForward(input);
      totalError += S21CalculateError(expectedOutput);
      S21Backpropagation(expectedOutput);
      S21UpdateWeights(input, learningRate);
    }

    std::cout << "Epoch: " << epoch + 1 << ", Error: " << totalError << std::endl;
  }
}

double S21Network::S21CalculateError(const std::vector<double> &expectedOutput) {
  layer& outputLayer = layers_.back();
  double totalError = 0.0;

  for (int i = 0; i < outputLayer.size(); i++) {
    double output = outputLayer[i].S21NeuronValue();
    double error = expectedOutput[i] - output;
    totalError += error * error;
  }

  return totalError;
}

}  // namespace s21
