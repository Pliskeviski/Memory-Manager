#include "flag_allocation.h"

FlagAllocation::FlagAllocation(uint32_t size, uint32_t block_size) : Allocator(size), m_ChunkSize(block_size) {
	assert(size % block_size == 0);

	uint32_t positions = this->m_Size / this->m_ChunkSize;
	this->m_Block = malloc(size + positions);
	this->m_MemBlock = (void*)((uint32_t)this->m_Block + positions - block_size);
	this->m_Positions = this->m_Size / this->m_ChunkSize;
	this->Init();
}

void FlagAllocation::Init() {
	for (int i = 0; i < m_Positions; i++) {
		char* flagUsed;
		flagUsed = (((char*)this->m_Block + i));

		*flagUsed = 0;
	}
}

int32_t FlagAllocation::Alloc(const uint32_t size) {
	if (size > this->m_Size) return 0;

	int32_t total_found = size;
	uint32_t initial_pos = 0;

	uint32_t block_count = 0;

	for (int i = 0; i < m_Positions; i++) {
		char* is_used = (char*)(((uint32_t)this->m_Block + i));
		
		if (*is_used == 0) {
			total_found -= this->m_ChunkSize;
			block_count++;
		}
		else {
			total_found = size;
			initial_pos = i + 1;
			block_count = 0;
		}

		if (total_found <= 0) {
			for (int j = initial_pos; j < initial_pos + block_count; j++) {
				char* used = (char*)(((uint32_t)this->m_Block + j));
				*used = 1;
			}
			void* mem_pos = (void*)((uint32_t)this->m_MemBlock + (i * this->m_ChunkSize));
			this->m_umap[initial_pos] = mem_pos;
			return initial_pos;
		}
	}

	return -1;
}

void FlagAllocation::FreeBlock(uint32_t index, uint32_t size) {
	void* pos = this->getAddress(index);
	uint32_t size_pos = ceil(size / this->m_ChunkSize);

	for (int i = 0; i < size_pos; i++) {
		char* flag = (char*)(((uint32_t)this->m_Block + i));
		*flag = 0;
	}
}

void* FlagAllocation::Free() {
	free(this->m_MemBlock);
	return 0;
}

void* FlagAllocation::getAddress(uint32_t index) {
	return this->m_umap[index];
}


