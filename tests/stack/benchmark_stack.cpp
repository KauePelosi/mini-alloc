#include "../../config/benchmark_config.hpp"
#include <chrono>
#include <iostream>

void benchmark_stack() {
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < ITERATIONS; i++) {
    int value = i;
    sink = value;
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << "stack: " << duration.count() << "ms\n";
}
