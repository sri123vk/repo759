#include "convolution.h"

#include <omp.h>

// Parallel version of HW02 convolve.
// Out-of-bounds padding rule from HW02:
//   - exactly one of the row/column indices out of range -> 1
//   - both out of range (corner)                          -> 0
void convolve(const float *image, float *output, std::size_t n,
              const float *mask, std::size_t m) {
  const long N = static_cast<long>(n);
  const long M = static_cast<long>(m);
  const long r = (M - 1) / 2;

#pragma omp parallel for collapse(2) schedule(static)
  for (long x = 0; x < N; x++) {
    for (long y = 0; y < N; y++) {
      float sum = 0.0f;
      for (long i = 0; i < M; i++) {
        const long xi = x + i - r;
        const bool in_x = (xi >= 0 && xi < N);
        for (long j = 0; j < M; j++) {
          const long yj = y + j - r;
          const bool in_y = (yj >= 0 && yj < N);
          float f;
          if (in_x && in_y) {
            f = image[xi * N + yj];
          } else if (in_x || in_y) {
            f = 1.0f;
          } else {
            f = 0.0f;
          }
          sum += mask[i * M + j] * f;
        }
      }
      output[x * N + y] = sum;
    }
  }
}
