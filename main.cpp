#include "tests/linear/benchmark_linear.hpp"
#include "tests/malloc/benchmark_malloc.hpp"

int main() {
  benchmark_malloc();
  benchmark_linear();

  return 0;
}
