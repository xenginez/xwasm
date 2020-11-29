#include "sandbox.h"

#include <fstream>

#include "loader.h"
#include "module.h"
#include "stream.h"
#include "executor.h"
#include "section_t.h"

#include "errmsg.h"

struct runtime
{
	xwasm::module _module;
	std::vector< xwasm::value > _globals;
	std::vector< std::uint8_t > _memorys;
	std::vector< std::uint64_t > _tables;
};

struct xwasm::sandbox::private_p
{
	std::map< std::string, runtime > _runtimes;
};

xwasm::sandbox::sandbox()
	:_p( new private_p )
{

}

xwasm::sandbox::~sandbox()
{
	delete _p;
}

const xwasm::module & xwasm::sandbox::load( const std::string & name, xwasm::stream & source )
{
	if( _p->_runtimes.find( name ) != _p->_runtimes.end() )
	{
		return;
	}

	runtime & run = _p->_runtimes[name];

	run._module._name = name;

	xwasm::loader loader;

	loader.load( &run._module, source );

	for( const auto & it : run._module._mems )
	{
		run._memorys;
	}
	for( const auto & it : run._module._globals )
	{
		run._globals.push_back( it.init );
	}

	return run._module;
}

int xwasm::sandbox::call( xwasm::value & result, const std::string & name, std::deque< xwasm::value > & params )
{
	auto index = name.find_last_of( '.' );
	if( index != std::string::npos )
	{
		std::map< std::string, runtime >::iterator it = _p->_runtimes.find( { name.begin(), name.begin() + index - 1 } );
		if( it != _p->_runtimes.end() )
		{
			auto ex = std::find_if( it->second._module._exports.begin(), it->second._module._exports.end(), [name]( const xwasm::export_t & exprt )
						  {
							  return exprt.name == name;
						  } );
			if (ex != it->second._module._exports.end() )
			{
				if( ex->desctype == xwasm::desc_kind::DESC_FUNC )
				{
					xwasm::executor _exec( this );

					return _exec.exec( result, &it->second._module._funcs[ex->descidx], params );
				}
			}
		}
	}

	return ERR_FUNC_NOT_FOUND;
}

void xwasm::sandbox::push_args( std::deque< xwasm::value > & args )
{

}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::int8_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::int16_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::int32_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::int64_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::uint8_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::uint16_t val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::uint32_t val )
{
	params.push_back( static_cast< std::int64_t >( val ) );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, std::uint64_t val )
{
	params.push_back( static_cast< std::int64_t >( val ) );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, float val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, double val )
{
	params.push_back( val );
}

void xwasm::sandbox::push( std::deque< xwasm::value > & params, xwasm::mem_view val )
{
	params.push_back( set_memory( val.data, val.size ) );
}

xwasm::value xwasm::sandbox::set_memory( std::uint8_t * ptr, std::uint64_t size )
{

}

void xwasm::sandbox::get_memory( xwasm::value index, std::uint8_t * ptr, std::uint64_t size )
{

}
