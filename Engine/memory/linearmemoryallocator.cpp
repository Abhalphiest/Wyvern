#pragma once

#include"linearMemoryAllocator.h"
#include"align.h"

LinearMemoryAllocator::LinearMemoryAllocator(size_t size, void* rootAddress)
	: MemoryAllocator(size, rootAddress), m_current_pos(rootAddress)
{
	assert(size > 0);
	assert(rootAddress != nullptr);
}

LinearMemoryAllocator::~LinearMemoryAllocator()
{
	m_current_pos = nullptr;
}

void* LinearMemoryAllocator::allocate(size_t size, uint alignment)
{
	assert(size != 0);

	uint adjustment = alignForwardAdjustment(m_current_pos, alignment);

	if (m_usedMemory + adjustment + size > m_size)
		return nullptr;

	intptr_t aligned_address = (intptr_t)m_current_pos + adjustment;

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