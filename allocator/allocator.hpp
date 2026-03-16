#pragma once
#include <cstddef>
#include <cstdlib>

struct LinearAllocator {
  std::byte *start;
  size_t size;
  size_t offset;
};

LinearAllocator createAllocator(size_t size);
void *linearAllocate(LinearAllocator &alloc, size_t size);
void destroyAllocator(LinearAllocator &alloc);
