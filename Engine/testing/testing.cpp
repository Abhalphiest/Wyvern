#include "testing.h"

void testMemoryAllocator(MemoryAllocator &allocator)
{

	int* test_int = Memory::allocate_new<int>(allocator);
	*test_int = 12;
	Memory::deallocate_delete<int>(allocator,*test_int);
}

void testDebugLog()
{


}

void testDebugConsole()
{

	
}