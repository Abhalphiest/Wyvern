#pragma once

#include "definitions.h"
#include "align.h"
#include <assert.h>
#include <stdlib.h>

class MemoryAllocator
{
public:
	MemoryAllocator(size_t size, void* rootAddress)
	{
		m_rootAddress = rootAddress;
		m_size = size;

		m_usedMemory = 0;
		m_numAllocations = 0;
	}

	virtual ~MemoryAllocator()
	{
		assert(m_numAllocations == 0 && m_usedMemory == 0);

		m_rootAddress = nullptr;
		m_size = 0;
	}

	virtual void* allocate(size_t size, uint alignment = 4) = 0;

	virtual void deallocate(void* p) = 0;

	void* get_root_address() const
	{
		return m_rootAddress;
	}

	size_t get_size() const
	{
		return m_size;
	}

	size_t get_used_memory() const
	{
		return m_usedMemory;
	}

	size_t get_num_allocations() const
	{
		return m_numAllocations;
	}

protected:
	void*         m_rootAddress;
	size_t        m_size;

	size_t        m_usedMemory;
	size_t        m_numAllocations;
};

namespace Memory
{
	template<typename T>
	T* allocate_new(MemoryAllocator& MemoryAllocator)
	{
		return new (MemoryAllocator.allocate(sizeof(T), __alignof(T))) T;
	}

	template<typename T>
	T* allocate_new(MemoryAllocator& MemoryAllocator, const T& t)
	{
		return new (MemoryAllocator.allocate(sizeof(T), __alignof(T))) T(t);
	}

	template<typename T>
	void deallocate_delete(MemoryAllocator& MemoryAllocator, T& object)
	{
		object.~T();
		MemoryAllocator.deallocate(&object);
	}

	template<typename T>
	T* allocate_array(MemoryAllocator& MemoryAllocator, uint length)
	{
		assert(length != 0);

		uint headerSize = sizeof(uint) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		//Allocate extra space to store array length in the bytes before the array
		T* p = ((T*)MemoryAllocator.allocate(sizeof(T)*(length + headerSize), __alignof(T))) + headerSize;

		*(((size_t*)p) - 1) = length;

		for (size_t i = 0; i < length; i++)
			new (&p) T;

		return p;
	}

	template<typename T>
	void deallocate_array(MemoryAllocator& MemoryAllocator, T* array)
	{
		assert(array != nullptr);

		size_t length = *(((size_t*)array) - 1);

		for (size_t i = 0; i < length; i++)
			array.~T();

		//Calculate how much extra memory was allocated to store the length before the array
		unsigned int headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		MemoryAllocator.deallocate(array - headerSize);
	}
};