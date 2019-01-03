#pragma once

#include <stdint.h>

class Allocator {
public:
	Allocator(const uint32_t size) : m_Size(size) {
		this->m_Used = 0;
	}
	virtual ~Allocator() {};
	virtual void* Free() = 0;
protected:
	uint32_t m_Size;
	uint32_t m_Used;
};