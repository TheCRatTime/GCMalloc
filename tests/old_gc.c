/* old_gc.c - test GC old objects. */

#define GC_MALLOC_SOURCE
#define DBG_ALLOC_SOURCE
#define DEBUG
#define WRAP_REAL_MALLOC
#include <dbg_alloc.h>
#include <GCmalloc.h>

#include <assert.h>
#include <stdio.h>

int main(void) {
  int* old = NULL;
  int* new_ptr = NULL;
  GCObject* obj = NULL;
  GC_INIT();
  
  if (InitAllocator((1024 * 1024) * 5) == -1) {
    printf("Initialization failed\n");
    return 1;
  }

  old = (int*)GCMalloc(sizeof(int));
  new_ptr = (int*)GCMalloc(sizeof(int));
  
  if (!old || !new_ptr) {
    printf("Allocation failed\n");
    return 1;
  }

  obj = (GCObject*)(void*)((char*)old - sizeof(GCObject));

  obj->metadata |= 0xB0;

  RunGC(1);

  assert(GCObjColor(obj) == GC_COLOR_BLACK);

  GC_DEINIT();

  GC_FULL_RUN();  
  GC_FULL_RUN();

  AllocatorLog();
  KillAllocator();
  
  return 0;
}
