#include "xwasm.h"

#include <fstream>

int main()
{
	xwasm::sandbox sndbox;

	std::ifstream file( "E:\\wasm3\\test\\fuzz\\corpus\\fib32.wasm", std::ios::binary );
	xwasm::stream source( file );
	sndbox.load( "fib32", source );

	std::int32_t i = 123;

	std::cout << "input number: ";
	while( std::cin >> i )
	{
		if( i == 0 )
		{
			break;
		}

		std::cout << std::endl;

		xwasm::value result;
		if( sndbox.call( result, "fib32.fib", i ) == 0 )
		{
			std::cout << result.data.u64 << std::endl;
		}

		std::cout << "input number: ";
	}

	return 0;
}