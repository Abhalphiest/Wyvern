#include "memoryallocator.h"

class StackMemoryAllocator : public MemoryAllocator
{
public:
	StackMemoryAllocator(size_t size, void* rootAddress);
	~StackMemoryAllocator();

	void* allocate(size_t size, uint alignment) override;
		
	void deallocate(void* p) override;

private:
	StackMemoryAllocator(const StackMemoryAllocator&); //Prevent copies because it might cause errors
	StackMemoryAllocator& operator=(const StackMemoryAllocator&);

	struct AllocationHeader
	{
		//#if _DEBUG
		void* prev_address;
		//#endif
		uint adjustment;
	};

	//#if _DEBUG
	void* m_prev_position;
	//#endif

	void*  m_current_pos;
};