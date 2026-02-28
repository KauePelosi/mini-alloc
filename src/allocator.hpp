#pragma once
#include <cstdlib>

struct LinearAllocator {
  void *start;
  size_t size;
  size_t offset;
};
