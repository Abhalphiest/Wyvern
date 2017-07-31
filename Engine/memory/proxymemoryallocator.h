#include "allocator.h"

class ProxyMemoryAllocator : public MemoryAllocator
{
public:
	ProxyMemoryAllocator(Allocator& allocator);
	~ProxyMemoryAllocator();

	void* allocate(size_t size, uint alignment) override;
		
	void deallocate(void* p) override;

private:
	ProxyMemoryAllocator(const ProxyMemoryAllocator&); //Prevent copies because it might cause errors
	ProxyMemoryAllocator& operator=(const ProxyMemoryAllocator&);

	MemoryAllocator& _allocator;
};