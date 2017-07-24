#pragma once

#include"linearMemoryAllocator.h"
#include"align.h"

LinearMemoryAllocator::LinearMemoryAllocator(uint size, void* rootAddress)
	: MemoryAllocator(size, rootAddress), m_current_pos(rootAddress)
{
	assert(size > 0);
	assert(rootAddress != nullptr);
}

LinearMemoryAllocator::~LinearMemoryAllocator()
{
	m_current_pos = nullptr;
}

void* LinearMemoryAllocator::allocate(uint size, uint alignment)
{
	assert(size != 0);

	uint adjustment = alignForwardAdjustment(m_current_pos, alignment);

	if (m_usedMemory + adjustment + size > m_size)
		return nullptr;

	unsigned int aligned_address = (uint)m_current_pos + adjustment;

	m_current_pos = (void*)(aligned_address + size);

	m_usedMemory += size + adjustment;
	m_numAllocations++;

	return (void*)aligned_address;
}

void LinearMemoryAllocator::deallocate(void* p)
{
	assert(false && "Use clear() instead");
}

void LinearMemoryAllocator::clear()
{
	m_numAllocations = 0;
	m_usedMemory = 0;

	m_current_pos = m_rootAddress;
}