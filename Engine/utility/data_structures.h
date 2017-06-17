#pragma once
//#include "wyvern.h"

template<typename T, uint size>
struct dynamic_array
{
	T* arr;
	uint capacity = size;
	uint count = 0;

	void add(T element) {}
	uint count() { return 0; }
	void resize(uint size) {}
	void clear() {}
	void delete_at_index(uint index);
	
	//overload [] operator
};

template<typename T>
struct list
{
	T* list;
};