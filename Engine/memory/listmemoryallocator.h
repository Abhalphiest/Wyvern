#include "memoryallocator.h"

class ListMemoryAllocator : public MemoryAllocator
{
public:
	ListMemoryAllocator(size_t size, void* rootAddress);
	~ListMemoryAllocator();

	void* allocate(size_t size, uint alignment) override;
		
	void deallocate(void* p) override;

private:

	struct AllocationHeader
	{
		size_t size;
		uint     adjustment;
	};

	struct FreeBlock
	{
		size_t     size;
		FreeBlock* next;
	};

	ListMemoryAllocator(const ListMemoryAllocator&); //Prevent copies because it might cause errors
	ListMemoryAllocator& operator=(const ListMemoryAllocator&);

	FreeBlock* _free_blocks;
};