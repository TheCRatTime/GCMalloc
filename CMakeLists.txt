cmake_minimum_required(VERSION 3.10)

project(GCMalloc C)

include(CTest)

enable_testing()

add_executable(gc_test tests/gc_test.c)
target_include_directories(gc_test PRIVATE include)
add_test(NAME gc_memory_leak COMMAND gc_test)
add_executable(old_gc tests/old_gc.c)
target_include_directories(old_gc PRIVATE include)
add_test(NAME gc_old_objects COMMAND old_gc)
