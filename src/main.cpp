#include <fstream>

#include "xwasm.h"

int main()
{
	xwasm::sandbox sandbox;

	std::ifstream source( "D:\\wasm3-master\\test\\wasi\\test.wasm", std::ios::binary );

	xwasm::stream s( source );

	sandbox.load( "test", s );

	return 0;
}
