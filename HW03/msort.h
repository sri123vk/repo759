#ifndef MSORT_H
#define MSORT_H
#include <cstddef>
#include <omp.h>
void msort(int* arr, const std::size_t n, const std::size_t threshold);
#endif
