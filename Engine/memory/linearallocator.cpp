#pragma once

#include"linearallocator.h"
#include"align.h"

LinearAllocator::LinearAllocator(size_t size, void* start)
	: Allocator(size, start), _current_pos(start)
{
	assert(size > 0);
}

LinearAllocator::~LinearAllocator()
{
	_current_pos = nullptr;
}

void* LinearAllocator::allocate(size_t size, unsigned int alignment)
{
	assert(size != 0);

	unsigned int adjustment = alignForwardAdjustment(_current_pos, alignment);

	if (_used_memory + adjustment + size > _size)
		return nullptr;

	unsigned int aligned_address = (unsigned int)_current_pos + adjustment;

	_current_pos = (void*)(aligned_address + size);

	_used_memory += size + adjustment;
	_num_allocations++;

	return (void*)aligned_address;
}

void LinearAllocator::deallocate(void* p)
{
	assert(false && "Use clear() instead");
}

void LinearAllocator::clear()
{
	_num_allocations = 0;
	_used_memory = 0;

	_current_pos = _start;
}