#include "msort.h"

#include <algorithm>
#include <omp.h>
#include <vector>

namespace {

// Serial, non-recursive sort used below the threshold.
void insertion_sort(int *a, std::size_t n) {
  for (std::size_t i = 1; i < n; i++) {
    const int key = a[i];
    std::size_t j = i;
    while (j > 0 && a[j - 1] > key) {
      a[j] = a[j - 1];
      j--;
    }
    a[j] = key;
  }
}

// Merge sorted a[0, mid) and a[mid, n) using tmp[0, n) as scratch.
void merge(int *a, int *tmp, std::size_t mid, std::size_t n) {
  std::size_t i = 0, j = mid, k = 0;
  while (i < mid && j < n) {
    tmp[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];
  }
  while (i < mid)
    tmp[k++] = a[i++];
  while (j < n)
    tmp[k++] = a[j++];
  std::copy(tmp, tmp + n, a);
}

void msort_rec(int *a, int *tmp, std::size_t n, std::size_t threshold) {
  if (n < 2)
    return;
  if (n <= threshold) {
    insertion_sort(a, n);
    return;
  }
  const std::size_t half = n / 2;

  // Each half works on a disjoint slice of a and tmp, so no races.
#pragma omp task firstprivate(a, tmp, half, threshold)
  msort_rec(a, tmp, half, threshold);

#pragma omp task firstprivate(a, tmp, half, n, threshold)
  msort_rec(a + half, tmp + half, n - half, threshold);

#pragma omp taskwait
  merge(a, tmp, half, n);
}

} // namespace

void msort(int *arr, const std::size_t n, const std::size_t threshold) {
  std::vector<int> tmp(n);
  int *t = tmp.data();
#pragma omp parallel
#pragma omp single
  msort_rec(arr, t, n, threshold);
}
