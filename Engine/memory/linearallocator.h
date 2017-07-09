#pragma once

#include"allocator.h"

class LinearAllocator : public Allocator
{
public:
	LinearAllocator(size_t size, void* start);
	~LinearAllocator();

	void* allocate(size_t size, unsigned int alignment) override;

	void deallocate(void* p) override;

	void clear();

private:
	LinearAllocator(const LinearAllocator&); //Prevent copies because it might cause errors
	LinearAllocator& operator=(const LinearAllocator&);

	void* _current_pos;
};