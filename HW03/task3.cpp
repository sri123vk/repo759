#include <chrono>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

#include "msort.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: ./task3 n t ts\n";
    return 1;
  }
  const std::size_t n = std::strtoull(argv[1], nullptr, 10);
  const int t = std::atoi(argv[2]);
  const std::size_t ts = std::strtoull(argv[3], nullptr, 10);

  std::vector<int> arr(n);
  std::mt19937 gen(759);
  std::uniform_int_distribution<int> dist(-1000, 1000);
  for (auto &v : arr)
    v = dist(gen);

  omp_set_num_threads(t);

  auto start = std::chrono::high_resolution_clock::now();
  msort(arr.data(), n, ts);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms = end - start;

  std::cout << arr[0] << "\n";
  std::cout << arr[n - 1] << "\n";
  std::cout << ms.count() << "\n";
  return 0;
}
