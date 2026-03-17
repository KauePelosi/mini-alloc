#include "benchmark_linear.hpp"
#include "../../allocator/allocator.hpp"
#include "../../config/benchmark_config.hpp"
#include <chrono>
#include <iostream>

void benchmark_linear() {
  LinearAllocator alloc = createAllocator(ITERATIONS * sizeof(int));
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < ITERATIONS; i++) {
    int *p = static_cast<int *>(linearAllocate(alloc, sizeof(int)));
    if (!p) {
      std::cout << "Out of memory\n";
      break;
    }
    *p = i;
    sink = *p;
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "Linear Allocator: " << duration.count() << "ms\n";
}
