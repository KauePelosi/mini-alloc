#include "allocator.hpp"
#include <iostream>

int main() {
  LinearAllocator alloc = createAllocator(64);
  int *a = static_cast<int *>(linearAllocate(alloc, sizeof(int)));
  int *b = static_cast<int *>(linearAllocate(alloc, sizeof(int)));
  double *c = static_cast<double *>(linearAllocate(alloc, sizeof(double)));

  if (!a || !b || !c) {
    std::cout << "Out of memory\n";
    return 1;
  }
  *a = 10;
  *b = 20;
  *c = 3.14;

  std::cout << "a: " << a << " = " << *a << "\n";
  std::cout << "b: " << b << " = " << *b << "\n";
  std::cout << "c: " << c << " = " << *c << "\n";

  return 0;
}
