#include <cstdlib>

struct LinearAllocator {
  void *start;
  size_t size;
  size_t offset;
};

LinearAllocator createAllocator(size_t size) {
  LinearAllocator alloc;
  alloc.start = std::malloc(size);
  alloc.size = size;
  alloc.offset = 0;
  return alloc;
}

void *linearAllocate(LinearAllocator &alloc, size_t size) {
  if (alloc.offset + size > alloc.size) {
    return nullptr;
  }
  void *ptr = static_cast<char *>(alloc.start) + alloc.offset;
  alloc.offset += size;

  return ptr;
}
