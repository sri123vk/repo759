#include "matmul.h"

#include <algorithm>

void mmul1(const double* A, const double* B, double* C, const unsigned int n) {
  const std::size_t dimension = n;
  std::fill_n(C, dimension * dimension, 0.0);

  for (std::size_t i = 0; i < dimension; ++i) {
    for (std::size_t j = 0; j < dimension; ++j) {
      for (std::size_t k = 0; k < dimension; ++k) {
        C[i * dimension + j] += A[i * dimension + k] * B[k * dimension + j];
      }
    }
  }
}

void mmul2(const double* A, const double* B, double* C, const unsigned int n) {
  const std::size_t dimension = n;
  std::fill_n(C, dimension * dimension, 0.0);

  for (std::size_t i = 0; i < dimension; ++i) {
    for (std::size_t k = 0; k < dimension; ++k) {
      for (std::size_t j = 0; j < dimension; ++j) {
        C[i * dimension + j] += A[i * dimension + k] * B[k * dimension + j];
      }
    }
  }
}

void mmul3(const double* A, const double* B, double* C, const unsigned int n) {
  const std::size_t dimension = n;
  std::fill_n(C, dimension * dimension, 0.0);

  for (std::size_t j = 0; j < dimension; ++j) {
    for (std::size_t k = 0; k < dimension; ++k) {
      for (std::size_t i = 0; i < dimension; ++i) {
        C[i * dimension + j] += A[i * dimension + k] * B[k * dimension + j];
      }
    }
  }
}

void mmul4(const std::vector<double>& A, const std::vector<double>& B,
           double* C, const unsigned int n) {
  const std::size_t dimension = n;
  std::fill_n(C, dimension * dimension, 0.0);

  for (std::size_t i = 0; i < dimension; ++i) {
    for (std::size_t j = 0; j < dimension; ++j) {
      for (std::size_t k = 0; k < dimension; ++k) {
        C[i * dimension + j] += A[i * dimension + k] * B[k * dimension + j];
      }
    }
  }
}
