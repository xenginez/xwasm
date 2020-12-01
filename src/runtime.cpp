#include "runtime.h"

xwasm::runtime::runtime()
{

}

xwasm::runtime::~runtime()
{

}

void xwasm::runtime::init()
{
	for( size_t i = 0; i < _module.mem_size(); i++ )
	{
		_memorys.resize( _memorys.size() + _module.mem_at( i )->min * MEMORY_PAGE_SIZE );
	}

	for( size_t i = 0; i < _module.global_size(); i++ )
	{
		_globals.push_back( _module.global_at( i )->init.data );
	}

	for( size_t i = 0; i < _module.elem_size(); i++ )
	{
		for( size_t j = 0; j < _module.elem_at( i )->inits.size(); ++j )
		{
			_tables.push_back( _module.elem_at( i )->inits[j] );
		}
	}
}
