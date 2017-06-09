#pragma once
#include "wyvern.h"

template<typename T, uint size>
struct dynamic_array
{
	T* arr;
	uint capacity = size;
	uint count = 0;

	void push(T element) {}
	uint count() { return 0; }
	void resize(uint size) {}
	void clear() {}
	bool is_empty() {}
	
	//overload [] operator
};

template<typename T>
struct list
{
	T* list;
};