# Mini-Malloc: A Step-by-Step Memory Allocator in C++

This project is an educational journey into the world of low-level memory management. By building a memory allocator from scratch, you will gain a deep, practical understanding of how memory is requested, managed, and released in a C++ environment. This is not about replacing `malloc`; it's about understanding what `malloc` does.

---

## Project Goal

To implement a series of memory allocators, each building upon the last, to explore concepts like pointer arithmetic, memory layout, fragmentation, and alignment.

## Structure

This project is divided into four main phases. Each phase has a clear objective and a set of tasks. You should aim to complete one phase before moving to the next.

```
mini-malloc/
├── src/
│   ├── allocator.cpp
│   ├── allocator.hpp
│   └── main.cpp
├── tests/
├── CMakeLists.txt
└── README.md
```

---

### Phase 1: The Linear (or Arena) Allocator

**Objective:** Understand the most basic form of allocation: reserving a large chunk of memory and handing out pieces of it sequentially.

**Core Concepts:**
*   Pointer arithmetic.
*   Reserving memory on the heap (`new char[...]` or `malloc`).
*   The difference between memory reservation and allocation.

**Tasks:**

- [ ] **1.1: Reserve a Fixed-Size Buffer:** In your `Allocator` class, create a constructor that allocates a large, fixed-size block of memory (e.g., 1MB) using `new std::byte[SIZE]`. This is your "heap."
- [ ] **1.2: Implement `alloc(size_t size)`:**
    -   Create a pointer or offset that tracks the current position within your buffer.
    -   The `alloc` function should check if there is enough space remaining.
    -   If so, it returns a pointer to the current offset and moves the offset forward by `size`.
    -   If not, it should return `nullptr`.
- [ ] **1.3: Implement a `reset()` function:** Since this allocator has no `free` mechanism, the only way to reclaim memory is to reset the entire arena. This function will simply reset your offset back to the beginning of the buffer.

**Definition of Done for Phase 1:** You can allocate memory for simple types and see their addresses increase sequentially. You can reset the allocator to reuse the memory.

---

### Phase 2: The Free-List Allocator

**Objective:** Implement a true `free` mechanism by tracking memory blocks with a linked list embedded directly within the heap itself.

**Core Concepts:**
*   Data structures within raw memory.
*   Internal vs. External Fragmentation.
*   Block splitting and coalescing (optional for now).

**Tasks:**

- [ ] **2.1: Define the Block Header:** Create a `struct BlockHeader` that contains:
    -   `size_t size`: The size of the data block that follows.
    -   `bool is_free`: A flag to indicate if the block is available.
    -   `BlockHeader* next`: A pointer to the next block in the list.
- [ ] **2.2: Initialize the Free List:** When your allocator starts, the entire heap should be treated as a single, large, free block.
- [ ] **2.3: Re-implement `alloc(size_t size)`:**
    -   Iterate through the linked list of blocks.
    -   Find the first block that is `is_free` and has `size >= requested_size` (this is the "First-Fit" strategy).
    -   Mark the block as `is_free = false`.
    -   (Optional, but recommended) If the block is much larger than requested, split it into two blocks: one for the user and one for the remaining free space.
    -   Return a pointer to the memory region *after* the header.
- [ ] **2.4: Implement `free(void* ptr)`:**
    -   Given a pointer to the data, you must calculate the address of its corresponding `BlockHeader` (by moving the pointer backward).
    -   Mark the block as `is_free = true`.
    -   (Advanced) Implement coalescing: if the block next to the newly freed block is also free, merge them into a single, larger free block.

**Definition of Done for Phase 2:** You can allocate and deallocate memory blocks of various sizes. Your allocator can reuse freed blocks for new allocations.

---

### Phase 3: Handling Memory Alignment

**Objective:** Ensure that the memory returned by your allocator is suitable for storing any data type, respecting the CPU's alignment requirements.

**Core Concepts:**
*   `alignof` and `alignas` keywords.
*   Padding.
*   Bitwise operations for masking and alignment calculation.

**Tasks:**

- [ ] **3.1: Modify `alloc` to be Alignment-Aware:**
    -   The `alloc` function should now take an optional `alignment` parameter.
    -   When searching for a free block, you must calculate not only the space for the requested `size` but also any extra "padding" needed to return an address that meets the alignment.
- [ ] **3.2: Store Allocation Metadata:** You can no longer simply return a pointer. You need to store the original pointer (before alignment padding) so that `free` knows where the *actual* block header is.

**Definition of Done for Phase 3:** Your allocator can correctly allocate memory for a `struct` with strict alignment requirements, and Valgrind/ASan reports no alignment errors.

---

### Phase 4: C++ Integration

**Objective:** Make your allocator compatible with the C++ Standard Library and idioms.

**Core Concepts:**
*   Placement `new`.
*   Destructor calls.
*   The `std::allocator` concept.

**Tasks:**

- [ ] **4.1: Use Placement `new`:** Write test cases that use your `alloc` function to get raw memory, and then construct a C++ object in that memory using `new(ptr) MyObject()`. Remember to call the destructor manually (`ptr->~MyObject()`) before freeing the memory.
- [ ] **4.2 (Challenge): Implement a `std::allocator`-compatible interface:**
    -   Create a template class `MySTLAllocator<T>`.
    -   Implement the required member functions: `allocate`, `deallocate`, `construct`, `destroy`.
    -   Instantiate an STL container with your allocator: `std::vector<int, MySTLAllocator<int>> my_vector;`

**Definition of Done for Phase 4:** You can successfully use an `std::vector` that uses your custom allocator for all its internal memory needs.
