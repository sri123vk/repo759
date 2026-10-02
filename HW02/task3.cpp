#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "matmul.h"

int main() {
  constexpr unsigned int n = 1024;
  const std::size_t count = static_cast<std::size_t>(n) * n;

  double* A = new double[count];
  double* B = new double[count];
  double* C = new double[count];

  std::mt19937 generator(759);
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  for (std::size_t i = 0; i < count; ++i) {
    A[i] = distribution(generator);
  }

  for (std::size_t i = 0; i < count; ++i) {
    B[i] = distribution(generator);
  }

  const std::vector<double> vector_A(A, A + count);
  const std::vector<double> vector_B(B, B + count);

  std::cout << std::setprecision(10) << n << '\n';

  const auto measure = [&](auto multiply) {
    const auto start = std::chrono::steady_clock::now();
    multiply();
    const auto end = std::chrono::steady_clock::now();

    const double milliseconds =
        std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << milliseconds << '\n' << C[count - 1] << '\n';
  };

  measure([&] { mmul1(A, B, C, n); });
  measure([&] { mmul2(A, B, C, n); });
  measure([&] { mmul3(A, B, C, n); });
  measure([&] { mmul4(vector_A, vector_B, C, n); });

  delete[] A;
  delete[] B;
  delete[] C;

  return 0;
}
