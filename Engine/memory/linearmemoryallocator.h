#pragma once

#include"memoryallocator.h"

class LinearMemoryAllocator : public MemoryAllocator
{
public:
	LinearMemoryAllocator(size_t size, void* rootAddress);
	~LinearMemoryAllocator();

	void* allocate(size_t size, unsigned int alignment) override;

	void deallocate(void* p) override;

	void clear();

private:
	LinearMemoryAllocator(const LinearMemoryAllocator&); //Prevent copies because it might cause errors
	LinearMemoryAllocator& operator=(const LinearMemoryAllocator&);

	void* m_current_pos;
};