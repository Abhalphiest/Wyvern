#include "proxymemoryallocator.h"

ProxyMemoryAllocator::ProxyMemoryAllocator(Allocator& allocator)
	: Allocator(allocator.getSize(), allocator.getStart()), _allocator(allocator)
{

}

ProxyMemoryAllocator::~ProxyMemoryAllocator()
{

}

void* ProxyMemoryAllocator::allocate(size_t size, uint alignment)
{
	assert(size != 0);
	_num_allocations++;

	size_t mem = _allocator.getUsedMemory();

	void* p = _allocator.allocate(size, alignment);

	_used_memory += _allocator.getUsedMemory() - mem;

	return p;
}

void ProxyMemoryAllocator::deallocate(void* p)
{
	_num_allocations--;

	size_t mem = _allocator.getUsedMemory();

	_allocator.deallocate(p);

	_used_memory -= mem - _allocator.getUsedMemory();
}