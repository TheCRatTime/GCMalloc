/* gc_test.c - test GC garbage collection.
   for checks using dbg_alloc:
       https://github.com/TheCRatTime/dbg_alloc/
*/

#define DBG_ALLOC_SOURCE
#define GC_MALLOC_SOURCE
#define WRAP_REAL_MALLOC
#define DEBUG

#include <dbg_alloc.h>
#include <GCmalloc.h>

#include <stdio.h>

static void PtrHandler(void* ptr) {
  printf("GC really freed %p\n", ptr);
}

typedef struct HardStruct {
  struct HardStruct* cycle_dep;
} HardStruct;

static void TestFunc(void) {
  HardStruct* ptr1 = NULL;
  HardStruct* ptr2 = NULL;
  HardStruct* garbage = NULL; /* unused */

  GC_INIT();

  ptr1 = (HardStruct*)GCMalloc(sizeof(HardStruct));
  ptr2 = (HardStruct*)GCMallocRaw(sizeof(HardStruct)); /* No registering to roots */
  garbage = (HardStruct*)GCMalloc(sizeof(HardStruct)); /* unused */

  /* If you want, you can set destructor, for example: */
  GCRegDestructor(ptr1, PtrHandler);
  GCRegDestructor(ptr2, PtrHandler);
  GCRegDestructor(garbage, PtrHandler);

  GCAddDependency(ptr1, ptr2);
  GCAddDependency(ptr2, ptr1);

  ptr1->cycle_dep = ptr2;
  ptr2->cycle_dep = ptr1;
  garbage->cycle_dep = ptr1;

  RunGC();

  GCUnregisterRoot(garbage);

  RunGC();
  
  GCreturn;
}

int main(void) {
  InitAllocator(4096);
  
  printf("TestFunc()\n");
  
  TestFunc();
  
  printf("RunGC()\n");
  
  RunGC();

  AllocatorLog();
  KillAllocator();
  
  return 0;
}
