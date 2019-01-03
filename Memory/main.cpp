#include "include/Memory.h"

int main() {
	Memory::static_pointer<int> a;
	Memory::static_pointer<int> b;
	Memory::static_pointer<unsigned short> c;
	Memory::static_pointer<int> d;

	Memory::dynamic_pointer<int> y;
	Memory::dynamic_pointer<int> z;

	b.Free();
	Memory::static_pointer<void>::Frag(1);

	Memory::static_pointer<long> f;

	f = 10;
	b = 10;
	c = 100;
	d = c + f;
	
	std::cin.get();
}