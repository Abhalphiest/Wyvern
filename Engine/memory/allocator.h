#pragma once

#include<assert.h>
#include<stdlib.h>

class Allocator
{
public:
	Allocator(size_t size, void* start)
	{
		_start = start;
		_size = size;

		_used_memory = 0;
		_num_allocations = 0;
	}

	virtual ~Allocator()
	{
		assert(_num_allocations == 0 && _used_memory == 0);

		_start = nullptr;
		_size = 0;
	}

	virtual void* allocate(size_t size, unsigned int alignment = 4) = 0;

	virtual void deallocate(void* p) = 0;

	void* getStart() const
	{
		return _start;
	}

	size_t getSize() const
	{
		return _size;
	}

	size_t getUsedMemory() const
	{
		return _used_memory;
	}

	size_t getNumAllocations() const
	{
		return _num_allocations;
	}

protected:
	void*         _start;
	size_t        _size;

	size_t        _used_memory;
	size_t        _num_allocations;
};

namespace allocator
{
	template<typename T>
	T* allocateNew(Allocator& allocator)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T;
	}

	template<typename T>
	T* allocateNew(Allocator& allocator, const T& t)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
	}

	template<typename T>
	void deallocateDelete(Allocator& allocator, T& object)
	{
		object.~T();
		allocator.deallocate(&object);
	}

	template<typename T>
	T* allocateArray(Allocator& allocator, size_t length)
	{
		ASSERT(length != 0);

		unsigned int headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		//Allocate extra space to store array length in the bytes before the array
		T* p = ((T*)allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T))) + headerSize;

		*(((size_t*)p) - 1) = length;

		for (size_t i = 0; i < length; i++)
			new (&p) T;

		return p;
	}

	template<typename T>
	void deallocateArray(Allocator& allocator, T* array)
	{
		ASSERT(array != nullptr);

		size_t length = *(((size_t*)array) - 1);

		for (size_t i = 0; i < length; i++)
			array.~T();

		//Calculate how much extra memory was allocated to store the length before the array
		unsigned int headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		allocator.deallocate(array - headerSize);
	}
};