#include "tests/linear/benchmark_linear.hpp"
#include "tests/malloc/benchmark_malloc.hpp"
#include "tests/stack/benchmark_stack.hpp"

int main() {
  benchmark_stack();
  benchmark_malloc();
  benchmark_linear();

  return 0;
}
