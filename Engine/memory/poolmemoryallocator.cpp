#include "poolmemoryallocator.h"

PoolMemoryAllocator::PoolMemoryAllocator(size_t objectSize, uint objectAlignment, size_t size, void* mem) 
	: Allocator(size, mem), _objectSize(objectSize), _objectAlignment(objectAlignment)
{
	assert(objectSize >= sizeof(void*));

	//Calculate adjustment needed to keep object correctly aligned
	uint adjustment = pointer_math::alignForwardAdjustment(mem, objectAlignment);

	_free_list = (void**)pointer_math::add(mem, adjustment);

	size_t numObjects = (size-adjustment)/objectSize;

	void** p = _free_list;

	//Initialize free blocks list
	for(size_t i = 0; i < numObjects-1; i++)
	{
		*p = pointer_math::add(p, objectSize );
		p = (void**) *p;
	}

	*p = nullptr;
}

PoolMemoryAllocator::~PoolMemoryAllocator()
{
	_free_list = nullptr;
}

void* PoolMemoryAllocator::allocate(size_t size, uint alignment)
{
	assert(size == _objectSize && alignment == _objectAlignment);

	if(_free_list == nullptr)
		return nullptr;

	void* p = _free_list;

	_free_list = (void**)(*_free_list);

	_used_memory += size;
	_num_allocations++;

	return p;
}

void PoolMemoryAllocator::deallocate(void* p)
{
	*((void**)p) = _free_list;

	_free_list = (void**)p;

	_used_memory -= _objectSize;
	_num_allocations--;
}