#pragma once
#include"definitions.h"

inline void* alignForward(void* address, byte alignment)
{
	return (void*)(((intptr_t)(address)+(alignment - 1)) & (~(alignment - 1)));
}

inline byte alignForwardAdjustment(const void* address, byte alignment)
{
	byte adjustment = alignment - ((intptr_t)(address) & (alignment - 1));

	if (adjustment == alignment)
		return 0; //already aligned

	return adjustment;
}

inline byte alignForwardAdjustmentWithHeader(const void* address, byte alignment, byte headerSize)
{
	byte adjustment = alignForwardAdjustment(address, alignment);

	byte neededSpace = headerSize;

	if (adjustment < neededSpace)
	{
		neededSpace -= adjustment;

		//Increase adjustment to fit header
		adjustment += alignment * (neededSpace / alignment);

		if (neededSpace % alignment > 0)
			adjustment += alignment;
	}

	return adjustment;
}

inline uptr add(void* ptr, size_t offset)
{
	uptr castptr = (uptr)ptr;
	return castptr + offset;
}

inline uptr subtract(void* ptr, size_t offset)
{
	uptr castptr = (uptr)ptr;
	return castptr - offset;
}