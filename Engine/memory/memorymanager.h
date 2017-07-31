#pragma once
#include "definitions.h"
#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#ifndef DEFAULT_MEMORY_ALLOC
#define DEFAULT_MEMORY_ALLOC 4294967295 //fairly arbitrary choice.. max_size of vector on my laptop
#endif

#include"memoryallocator.h"
#include"linearmemoryallocator.h"
#include"listmemoryallocator.h"

class MemoryManager
{
public:
	static void InitializeMemoryManager();
	static void Release();

private:
	uptr m_memory_pool;
	LinearMemoryAllocator* m_memory_allocator;
	ListMemoryAllocator* m_utility_allocator;

	// no touching..
	MemoryManager();
	~MemoryManager();
	MemoryManager(const MemoryManager& other) {};

};

extern MemoryManager* g_MemoryManager;
#endif