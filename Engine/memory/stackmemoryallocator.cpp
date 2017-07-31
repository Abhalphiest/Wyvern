//#include "stackmemoryallocator.h"
//
//StackMemoryAllocator::StackMemoryAllocator(size_t size, void* rootAddress) 
//	: MemoryAllocator(size, rootAddress), m_current_pos(rootAddress)
//{
//	assert(size > 0);
//
//	//#if _DEBUG
//	m_prev_position    = nullptr;
//	//#endif
//}
//
//StackMemoryAllocator::~StackMemoryAllocator()
//{
//	//#if _DEBUG
//	m_prev_position      = nullptr;
//	//#endif
//
//	m_current_pos   = nullptr;
//}
//
//void* StackMemoryAllocator::allocate(size_t size, uint alignment)
//{
//	assert(size != 0);
//
//	uint adjustment = alignForwardAdjustmentWithHeader(m_current_pos, alignment, sizeof(AllocationHeader));
//
//	if(m_used_memory + adjustment + size > m_size)
//		return nullptr;
//
//	void* aligned_address = add(_current_pos, adjustment);
//
//	//Add Allocation Header
//	AllocationHeader* header = (AllocationHeader*)(pointer_math::subtract(aligned_address, sizeof(AllocationHeader)));
//
//	header->adjustment   = adjustment;
//
//	//#if _DEBUG
//	header->prev_address = m_prev_position;
//
//	_prev_position        = aligned_address;
//	//#endif
//
//	_current_pos = pointer_math::add(aligned_address, size);
//
//	m_used_memory += size + adjustment;
//	m_num_allocations++;
//
//	return aligned_address;
//}
//
//void StackMemoryAllocator::deallocate(void* p)
//{
//	assert( p == m_prev_position );
//
//	//Access the AllocationHeader in the bytes before p
//	AllocationHeader* header = (AllocationHeader*)(subtract(p, sizeof(AllocationHeader)));
//
//	m_used_memory -= (uptr)m_current_pos - (uptr)p + header->adjustment;
//
//	m_current_pos = pointer_math::subtract(p, header->adjustment);
//
//	//#if _DEBUG
//	m_prev_position = header->prev_address;
//	//#endif
//
//	m_num_allocations--;
//}