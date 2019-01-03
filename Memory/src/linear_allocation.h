#pragma once

#include "Allocator.h"

class LinearAllocation : public Allocator {
public:
	LinearAllocation(const uint32_t size);
	~LinearAllocation();
	void* Alloc(const uint32_t size);
	void* Reset();
	void* Free();
private:
	void* m_MemBlock;
	void* m_Current;
};
