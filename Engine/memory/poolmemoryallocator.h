#include "memoryallocator.h"

class PoolMemoryAllocator : public MemoryAllocator
{
public:
	PoolMemoryAllocator(size_t objectSize, uint objectAlignment, size_t size, void* mem);
	~PoolMemoryAllocator();

	void* allocate(size_t size, uint alignment) override;
		
	void deallocate(void* p) override;

private:
	PoolMemoryAllocator(const PoolMemoryAllocator&); //Prevent copies because it might cause errors
	PoolMemoryAllocator& operator=(const PoolMemoryAllocator&);

	size_t     _objectSize;
	uint         _objectAlignment;

	void**     _free_list;
};