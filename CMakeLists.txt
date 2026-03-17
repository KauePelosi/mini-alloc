cmake_minimum_required(VERSION 3.16)

project(mini_alloc)

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)

add_executable(main.out
    main.cpp

    allocator/allocator.cpp

    config/benchmark_config.cpp

    tests/malloc/benchmark_malloc.cpp
    tests/linear/benchmark_linear.cpp
    tests/stack/benchmark_stack.cpp
)

target_include_directories(main.out PRIVATE
    allocator
    config
    tests/malloc
    tests/linear
    tests/stack
)

target_compile_options(main.out PRIVATE
    -O2
    -Wall
    -Wextra
)

set_target_properties(main.out PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
