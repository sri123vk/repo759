#include <chrono>
#include <cstdlib>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

#include "convolution.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: ./task2 n t\n";
    return 1;
  }
  const std::size_t n = std::strtoull(argv[1], nullptr, 10);
  const int t = std::atoi(argv[2]);
  const std::size_t m = 3;

  std::vector<float> image(n * n), output(n * n), mask(m * m);

  std::mt19937 gen(759);
  std::uniform_real_distribution<float> img_dist(-10.0f, 10.0f);
  std::uniform_real_distribution<float> mask_dist(-1.0f, 1.0f);
  for (auto &v : image) v = img_dist(gen);
  for (auto &v : mask) v = mask_dist(gen);

  omp_set_num_threads(t);

  auto start = std::chrono::high_resolution_clock::now();
  convolve(image.data(), output.data(), n, mask.data(), m);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms = end - start;

  std::cout << output[0] << "\n";
  std::cout << output[n * n - 1] << "\n";
  std::cout << ms.count() << "\n";
  return 0;
}
