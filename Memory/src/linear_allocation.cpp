#include "linear_allocation.h"

#include <cstdlib>

LinearAllocation::LinearAllocation(const uint32_t size) : Allocator(size) {
	this->m_MemBlock = malloc(size);
	this->m_Current = this->m_MemBlock;
}

LinearAllocation::~LinearAllocation() {
}

void* LinearAllocation::Alloc(const uint32_t size) {
	if (this->m_Used >= this->m_Size) return NULL;

	void* ret_pos = m_Current;
	this->m_Current = (char*)this->m_Current + (sizeof(char) * size);
	this->m_Used += size;
	return ret_pos;
}

void* LinearAllocation::Reset() {
	this->m_Current = this->m_MemBlock;
	return this->m_Current;
}

void* LinearAllocation::Free() {
	free(this->m_MemBlock);

	this->m_Current = NULL;
	this->m_MemBlock = NULL;
	
	return this->m_MemBlock;
}
