#include <chrono>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

#include "matmul.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: ./task1 n t\n";
    return 1;
  }
  const std::size_t n = std::strtoull(argv[1], nullptr, 10);
  const int t = std::atoi(argv[2]);

  std::vector<float> A(n * n), B(n * n), C(n * n, 0.0f);

  std::mt19937 gen(759);
  std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
  for (std::size_t i = 0; i < n * n; i++) {
    A[i] = dist(gen);
    B[i] = dist(gen);
  }

  omp_set_num_threads(t);

  auto start = std::chrono::high_resolution_clock::now();
  mmul(A.data(), B.data(), C.data(), n);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms = end - start;

  std::cout << C[0] << "\n";
  std::cout << C[n * n - 1] << "\n";
  std::cout << ms.count() << "\n";
  return 0;
}
