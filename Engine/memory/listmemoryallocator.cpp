#include "listmemoryallocator.h"

ListMemoryAllocator::ListMemoryAllocator(size_t size, void* rootAddress) 
	: MemoryAllocator(size, rootAddress), m_free_blocks((FreeBlock*)rootAddress)
{
	assert(size > sizeof(FreeBlock));

	m_free_blocks->size  = size;
	m_free_blocks->next = nullptr;
}

ListMemoryAllocator::~ListMemoryAllocator()
{
	m_free_blocks        = nullptr;
}

void* ListMemoryAllocator::allocate(size_t size, uint alignment)
{
	assert(size != 0 && alignment != 0);

	FreeBlock* prev_free_block = nullptr;
	FreeBlock* free_block     = m_free_blocks;

	while(free_block != nullptr)
	{
		//Calculate adjustment needed to keep object correctly aligned
		uint adjustment = alignForwardAdjustmentWithHeader(free_block, alignment, sizeof(AllocationHeader));

		size_t total_size = size + adjustment;

		//If allocation doesn't fit in this FreeBlock, try the next
		if(free_block->size < total_size)
		{
			prev_free_block = free_block;
			free_block = free_block->next;
			continue;
		}

		static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), "sizeof(AllocationHeader) < sizeof(FreeBlock)");

		//If allocations in the remaining memory will be impossible
		if(free_block->size - total_size <= sizeof(AllocationHeader))
		{
			//Increase allocation size instead of creating a new FreeBlock
			total_size = free_block->size;

			if(prev_free_block != nullptr)
				prev_free_block->next = free_block->next;
			else
				m_free_blocks = free_block->next;
		}
		else
		{
			//Else create a new FreeBlock containing remaining memory
			FreeBlock* next_block = (FreeBlock*)(add(free_block, total_size) );
			next_block->size = free_block->size - total_size;
			next_block->next = free_block->next;
			
			if(prev_free_block != nullptr)
				prev_free_block->next = next_block;
			else
				m_free_blocks = next_block;
		}

		uptr aligned_address = (uptr)free_block + adjustment;
	
		AllocationHeader* header = (AllocationHeader*)(aligned_address - sizeof(AllocationHeader));
		header->size             = total_size;
		header->adjustment       = adjustment;

		m_usedMemory += total_size;
		m_numAllocations++;

		assert(alignForwardAdjustment((void*)aligned_address, alignment) == 0);

		return (void*)aligned_address;
	}

	//assert(false && "Couldn't find free block large enough!");

	return nullptr;
}

void ListMemoryAllocator::deallocate(void* p)
{
	assert(p != nullptr);

	AllocationHeader* header = (AllocationHeader*)subtract(p, sizeof(AllocationHeader));

	uptr   block_start = reinterpret_cast<uptr>(p) - header->adjustment;
	size_t block_size  = header->size;
	uptr   block_end   = block_start + block_size;

	FreeBlock* prev_free_block = nullptr;
	FreeBlock* free_block = m_free_blocks;

	while(free_block != nullptr)
	{
		if( (uptr) free_block >= block_end )
			break;

		prev_free_block = free_block;
		free_block = free_block->next;
	}

	if(prev_free_block == nullptr)
	{
		prev_free_block = (FreeBlock*) block_start;
		prev_free_block->size = block_size;
		prev_free_block->next = m_free_blocks;

		m_free_blocks = prev_free_block;
	} else if((uptr) prev_free_block + prev_free_block->size == block_start)
	{
		prev_free_block->size += block_size;
	} else
	{
		FreeBlock* temp = (FreeBlock*) block_start;
		temp->size = block_size;
		temp->next = prev_free_block->next;
		prev_free_block->next = temp;

		prev_free_block = temp;
	}

	if( free_block != nullptr && (uptr) free_block == block_end)
	{
		prev_free_block->size += free_block->size;
		prev_free_block->next = free_block->next;
	}

	m_numAllocations--;
	m_usedMemory -= block_size;
}