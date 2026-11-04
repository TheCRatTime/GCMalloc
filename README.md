# GCMalloc
**GCMalloc** - precision GC for C.

## Description
**GCMalloc** is a precision GC for C, written in C.

### Features
- **No memory leaks**: [dbg_alloc](https://github.com/TheCRatTime/dbg_alloc/)
  shows all blocks are freed (`tests/gc_test.c`).
- **Tri-color GC**.
- **Simple API**: only **INIT_GC()**, **DEINIT_GC()** in every function
  and use **GCMalloc()** (for dependencies need other functions, see `tests/gc_test.c`).
- **Cycle dependencies process**: no memory leaks.
- **C89**/**ANSI C**: compiles everywhere.

### Building
Needed:
- C Compiler
- CMake 3.10 and greater
- GNU Make

```bash
cmake -B build
cd build/
make
```

### Authors
TheCRatTime

### License
Project is under Apache 2.0 license
