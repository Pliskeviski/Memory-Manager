#pragma once

#include "Allocator.h"

#include <assert.h>

#include <iostream>

#include <unordered_map>

class FlagAllocation : public Allocator {
public:
	FlagAllocation(uint32_t size, uint32_t block_size);
	void Init();
	int32_t Alloc(const uint32_t size);
	void FreeBlock(uint32_t index, uint32_t size);
	void* Free();
	void* getAddress(uint32_t index);

	bool Frag(uint32_t max_amount); // TODO
private:
	void* m_Block;
	void* m_MemBlock;
	std::unordered_map<int, void*> m_umap;
	uint32_t m_Positions;
	uint32_t m_ChunkSize;
};