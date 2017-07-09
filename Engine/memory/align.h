#pragma once


inline void* alignForward(void* address, unsigned int alignment)
{
	return (void*)((reinterpret_cast(address)+static_cast(alignment - 1)) & static_cast(~(alignment - 1)));
}

inline unsigned int alignForwardAdjustment(const void* address, unsigned int alignment)
{
	unsigned int adjustment = alignment - (reinterpret_cast(address) & static_cast(alignment - 1));

	if (adjustment == alignment)
		return 0; //already aligned

	return adjustment;
}

inline unsigned int alignForwardAdjustmentWithHeader(const void* address, unsigned int alignment, unsigned int headerSize)
{
	unsigned int adjustment = alignForwardAdjustment(address, alignment);

	unsigned int neededSpace = headerSize;

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