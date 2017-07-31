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
	m_memory_pool = (uptr)malloc(DEFAULT_MEMORY_ALLOC);
	m_memory_allocator = new LinearMemoryAllocator(DEFAULT_MEMORY_ALLOC, m_memory_pool);
}

MemoryManager::~MemoryManager()
{
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