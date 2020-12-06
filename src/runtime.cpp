#include "runtime.h"

xwasm::runtime::runtime()
{

}

xwasm::runtime::~runtime()
{

}

void xwasm::runtime::init()
{
	for( std::uint32_t i = 0; i < _module.mem_size(); i++ )
	{
		_memorys.resize( _memorys.size() + _module.memory_at( i )->min * MEMORY_PAGE_SIZE );
	}

	for( std::uint32_t i = 0; i < _module.global_size(); i++ )
	{
		_globals.push_back( _module.global_at( i )->init.data );
	}

	for( std::uint32_t i = 0; i < _module.elem_size(); i++ )
	{
		for( std::uint32_t j = 0; j < _module.element_at( i )->inits.size(); ++j )
		{
			_tables.push_back( _module.element_at( i )->inits[j] );
		}
	}
}
