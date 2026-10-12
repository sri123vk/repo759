#include "matmul.h"

#include <omp.h>

// Parallel version of HW02 mmul2 (i-k-j loop order, row-major).
// Each thread owns whole rows of C, so there are no write conflicts.
void mmul(const float *A, const float *B, float *C, const std::size_t n) {
#pragma omp parallel for schedule(static)
  for (std::size_t i = 0; i < n; i++) {
    float *Ci = C + i * n;
    for (std::size_t j = 0; j < n; j++) {
      Ci[j] = 0.0f;
    }
    for (std::size_t k = 0; k < n; k++) {
      const float a = A[i * n + k];
      const float *Bk = B + k * n;
      for (std::size_t j = 0; j < n; j++) {
        Ci[j] += a * Bk[j];
      }
    }
  }
}
