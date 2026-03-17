#include "benchmark_malloc.hpp"
#include "../../config/benchmark_config.hpp"
#include <chrono>
#include <cstdlib>
#include <iostream>

void benchmark_malloc() {
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < ITERATIONS; i++) {
    int *p = (int *)malloc(sizeof(int));
    *p = i;
    sink = *p;
    free(p);
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "malloc/free: " << duration.count() << "us\n";
}
