#include <fstream>
#include <iostream>

#include "loader.h"
#include "module.h"
#include "stream.h"
#include "sandbox.h"

int main()
{
	xwasm::module _module( "test" );
	xwasm::loader _loader;

	std::ifstream source( "D:\\wasm3-master\\test\\wasi\\test.wasm", std::ios::binary );

	xwasm::stream s( source );

	_loader.load( &_module, s );

	return 0;
}
