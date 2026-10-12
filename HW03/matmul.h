#ifndef MATMUL_H
#define MATMUL_H
#include <cstddef>
#include <omp.h>
void mmul(const float* A, const float* B, float* C, const std::size_t n);
#endif
