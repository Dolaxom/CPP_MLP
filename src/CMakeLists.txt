cmake_minimum_required(VERSION 3.25)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp model/utils/s21_dataset.cpp model/utils/s21_dataset.h model/s21_network.cpp model/s21_network.h model/s21_neuron.cpp model/s21_neuron.h model/utils/s21_math.cpp model/utils/s21_math.h)
