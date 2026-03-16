#include "allocator.hpp"
#include <cstddef>
#include <cstdlib>

LinearAllocator createAllocator(size_t size) {
  LinearAllocator alloc;
  alloc.start = static_cast<std::byte *>(std::malloc(size));
  alloc.size = size;
  alloc.offset = 0;
  return alloc;
}

void *linearAllocate(LinearAllocator &alloc, size_t size) {
  if (alloc.offset + size > alloc.size) {
    return nullptr;
  }
  std::byte *ptr = alloc.start + alloc.offset;
  alloc.offset += size;

  return ptr;
}

void destroyAllocator(LinearAllocator &alloc) {
  std::free(alloc.start);
  alloc.start = nullptr;
  alloc.size = 0;
  alloc.offset = 0;
}
