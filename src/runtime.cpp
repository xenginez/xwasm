#include "runtime.h"

xwasm::runtime::runtime()
{

}

xwasm::runtime::~runtime()
{

}

void xwasm::runtime::init()
{
	_memorys.resize( _module.mem_at( 0 )->min * MEMORY_PAGE_SIZE );

	for( size_t i = 0; i < _module.global_size(); i++ )
	{
		_globals.push_back( _module.global_at( i )->init.u64 );
	}

	for( size_t i = 0; i < _module.elem_at( 0 )->inits.size(); ++i )
	{
		_tables.push_back( _module.elem_at( 0 )->inits[i] );
	}
}
