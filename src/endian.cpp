#include "endian.h"

constexpr bool xwasm::is_big_endian()
{
	std::uint32_t val = 0x12345678;
	char * p = ( char * )&val;

	return *p == 0x12;
}

constexpr std::uint16_t xwasm::to_little_uint16( std::uint16_t val )
{
	if( xwasm::is_big_endian() )
	{
		return ( val >> 8 ) | ( val << 8 );
	}

	return val;
}

constexpr std::uint32_t xwasm::to_little_uint32( std::uint32_t val )
{
	if( xwasm::is_big_endian() )
	{
		return xwasm::to_little_uint16( val ) | xwasm::to_little_uint16( val >> 16 );
	}

	return val;
}

constexpr std::uint64_t xwasm::to_little_uint64( std::uint64_t val )
{
	if( xwasm::is_big_endian() )
	{
		return xwasm::to_little_uint32( val ) | xwasm::to_little_uint32( val >> 32 );
	}

	return val;
}

std::int32_t xwasm::get_leb128_int32( xwasm::stream & source )
{
	int32_t ret = 0;
	for( int i = 0; i < 5; ++i )
	{
		if( source.eof() )
		{
			return -1;
		}
		int32_t byte = source.get();
		ret |= ( byte & 0x7F ) << ( 7 * i );

		if( i == 4 && byte & 0x80 )
		{
			return -1;
		}

		if( ( byte & 0x80 ) == 0 )
		{
			if( byte & 0x40 )
			{
				switch( i )
				{
				case 0:
					ret |= 0xFFFFFF80;
					break;
				case 1:
					ret |= 0xFFFFC000;
					break;
				case 2:
					ret |= 0xFFE00000;
					break;
				case 3:
					ret |= 0xF0000000;
					break;
				default:
					break;
				}
			}
			break;
		}
	}

	return xwasm::to_little_uint32( ret );
}

std::int64_t xwasm::get_leb128_int64( xwasm::stream & source )
{
	int64_t ret = 0;
	for( int i = 0; i < 10; i++ )
	{
		if( source.eof() )
		{
			return -1;
		}
		int64_t byte = source.get();
		ret |= ( byte & 0x7F ) << ( 7 * i );

		if( i == 9 && byte & 0x80 )
		{
			return -1;
		}

		if( ( byte & 0x80 ) == 0 )
		{
			if( byte & 0x40 )
			{
				switch( i )
				{
				case 0:
					ret |= 0xFFFFFFFFFFFFFF80;
					break;
				case 1:
					ret |= 0xFFFFFFFFFFFFC000;
					break;
				case 2:
					ret |= 0xFFFFFFFFFFE00000;
					break;
				case 3:
					ret |= 0xFFFFFFFFF0000000;
					break;
				case 4:
					ret |= 0xFFFFFFF800000000;
					break;
				case 5:
					ret |= 0xFFFFFC0000000000;
					break;
				case 6:
					ret |= 0xFFFE000000000000;
					break;
				case 7:
					ret |= 0xFF00000000000000;
					break;
				case 8:
					ret |= 0x8000000000000000;
					break;
				default:
					break;
				}
			}
			break;
		}
	}
	return xwasm::to_little_uint64( ret );
}

std::uint32_t xwasm::get_leb128_uint32( xwasm::stream & source )
{
	std::uint32_t ret = 0;

	for( int i = 0; i < 5; ++i )
	{
		if( source.eof() )
		{
			return -1;
		}

		std::uint32_t byte = source.get();
		ret |= ( byte & 0x7F ) << ( 7 * i );

		if( i == 4 )
		{
			if( byte & 0x80 )
			{
				return -1;
			}
		}

		if( ( byte & 0x80 ) == 0 )
		{
			break;
		}
	}

	return xwasm::to_little_uint32( ret );
}
