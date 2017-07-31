#include"memorymanager.h"

void MemoryManager::InitializeMemoryManager()
{
	if (!g_MemoryManager)
	{
		g_MemoryManager = new MemoryManager();
	}
}

void MemoryManager::Release()
{
	if (g_MemoryManager)
	{
		delete g_MemoryManager;
		g_MemoryManager = nullptr;
	}
}

MemoryManager::MemoryManager()
{
	m_memory_pool = (byte*)malloc(DEFAULT_MEMORY_ALLOC);
	m_memory_pool[0] = 2;
	m_memory_allocator = new LinearMemoryAllocator(DEFAULT_MEMORY_ALLOC, m_memory_pool);
	void* utility_root = m_memory_allocator->allocate(UTILITY_MEMORY_ALLOC, 4);
	m_utility_allocator = new ListMemoryAllocator(UTILITY_MEMORY_ALLOC, utility_root);
}

MemoryManager::~MemoryManager()
{
	if (m_utility_allocator)
	{
		delete m_utility_allocator;
		m_utility_allocator = nullptr;
	}

	// free these two last, in this order, all other memory depends on them
	if (m_memory_allocator)
	{
		m_memory_allocator->clear();
		delete m_memory_allocator;
		m_memory_allocator = nullptr;
	}
	if (m_memory_pool)
	{
		delete m_memory_pool;
		m_memory_pool = nullptr;
	}
}