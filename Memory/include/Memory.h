#pragma once

#include "../src/Manager.h"

#include "../src/linear_allocation.h"
#include "../src/flag_allocation.h"
#include <iostream>

namespace Memory {
	static Manager m_Manager = Manager();
	static FlagAllocation m_FlagAllocator = FlagAllocation(16, 2);
	static LinearAllocation m_LinearAllocator = LinearAllocation(8);

	template<typename T>
	class static_pointer {
	public:
		static_pointer() {
			this->m_Index = m_FlagAllocator.Alloc(sizeof(T));
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
		}

		void Free() {
			m_FlagAllocator.FreeBlock(this->m_Index, sizeof(T));
		}

		T& operator=(T rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			*this->m_Variable = rhs;
			return *this->m_Variable;
		}

		static_pointer<T>& operator=(static_pointer<T> rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			*this->m_Variable = *rhs.m_Variable;
			return *this;
		}

		T operator+(const T& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable + rhs;
		}

		T operator-(const T& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable - rhs;
		}

		T operator/(const T& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable / rhs;
		}

		T operator*(const T& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable * rhs;
		}

		template<typename U>
		T operator+(static_pointer<U>& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable + *rhs.m_Variable;
		}

		template<typename U>
		T operator-(static_pointer<U>& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable - *rhs.m_Variable;
		}

		template<typename U>
		T operator/(static_pointer<U>& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable / *rhs.m_Variable;
		}

		template<typename U>
		T operator*(static_pointer<U>& rhs) {
			this->m_Variable = (T*)m_FlagAllocator.getAddress(this->m_Index);
			return *this->m_Variable * *rhs.m_Variable;
		}

		T* m_Variable;


		static void Frag(uint32_t max_amount) {
			m_FlagAllocator.Frag(max_amount);
		};
	private:
		uint32_t m_Index;
	};

	template<typename T>
	class dynamic_pointer {
	public:
		dynamic_pointer() {
			this->m_Variable = (T*)m_LinearAllocator.Alloc(sizeof(T));
		}

		~dynamic_pointer() {
			m_LinearAllocator.Free();
		}

		T& operator=(T rhs) {
			*this->m_Variable = rhs;
			return *this->m_Variable;
		}

		dynamic_pointer<T>& operator=(dynamic_pointer<T> rhs) {
			*this->m_Variable = *rhs.m_Variable;
			return *this;
		}

		T operator+(const T& rhs) {
			return *this->m_Variable + rhs;
		}

		T operator-(const T& rhs) {
			return *this->m_Variable - rhs;
		}

		T operator/(const T& rhs) {
			return *this->m_Variable / rhs;
		}

		T operator*(const T& rhs) {
			return *this->m_Variable * rhs;
		}

		T operator+(dynamic_pointer<T>& rhs) {
			return *this->m_Variable + *rhs.m_Variable;
		}

		T operator-(dynamic_pointer<T>& rhs) {
			return *this->m_Variable - *rhs.m_Variable;
		}

		T operator/(dynamic_pointer<T>& rhs) {
			return *this->m_Variable / *rhs.m_Variable;
		}

		T operator*(dynamic_pointer<T>& rhs) {
			return *this->m_Variable * *rhs.m_Variable;
		}
	private:
		T* m_Variable;
	};
}