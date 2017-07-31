#pragma once
#include "utility_memory.h"

template<typename T, uint size>
struct dynamic_array
{

public:
	void add(T element) {}
	uint count() { return 0; }
	void resize(uint size) {}
	void clear() {}
	void delete_at_index(uint index);

private:
	T* arr;
	uint capacity = size;
	uint count = 0;
	MemoryAllocator* memoryAllocator;
	
	//overload [] operator
};

template<typename T>
struct list
{
	T* list;
};