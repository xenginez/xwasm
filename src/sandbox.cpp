#include "sandbox.h"

#include <fstream>

#include "loader.h"
#include "module.h"
#include "stream.h"
#include "runtime.h"
#include "executor.h"
#include "section_t.h"

struct xwasm::sandbox::private_p
{
	std::vector< xwasm::runtime > _runtimes;
};

xwasm::sandbox::sandbox()
	:_p( new private_p )
{

}

xwasm::sandbox::~sandbox()
{
	delete _p;
}

std::vector< const xwasm::module * > xwasm::sandbox::modules() const
{
	std::vector< const xwasm::module * > result;

	for( const auto & it : _p->_runtimes )
	{
		result.push_back( &it._module );
	}

	return result;
}

bool xwasm::sandbox::insert_module( xwasm::module && val )
{
	if( find_module( val._name ) != nullptr )
	{
		return false;
	}

	runtime run;

	run._module = std::move( val );

	_p->_runtimes.emplace_back( std::move( run ) );

	_p->_runtimes.back().init();

	return true;
}

const xwasm::module * xwasm::sandbox::find_module( const std::string & name )
{
	for( const auto & it : _p->_runtimes )
	{
		if( it._module._name == name )
		{
			return &it._module;
		}
	}

	return nullptr;
}

const xwasm::module * xwasm::sandbox::load( const std::string & name, xwasm::stream & source )
{
	if( auto p = find_module( name ) )
	{
		return p;
	}

	runtime run;

	run._module._name = name;

	xwasm::loader loader;

	loader.load( &run._module, source );

	_p->_runtimes.emplace_back( std::move( run ) );

	_p->_runtimes.back().init();

	return &_p->_runtimes.back()._module;
}

int xwasm::sandbox::call( xwasm::value & result, const std::string & name, std::deque< xwasm::value > & params )
{
	auto index = name.find_last_of( '.' );
	if( index != std::string::npos )
	{
		std::string modulename( name.begin(), name.begin() + index );
		std::string funcname( name.begin() + index + 1, name.end() );

		for( auto & it : _p->_runtimes )
		{
			if( it._module._name == modulename )
			{
				auto ex = std::find_if( it._module._exports.begin(), it._module._exports.end(), [funcname]( const xwasm::export_t & exprt )
										{
											return exprt.name == funcname;
										} );
				if( ex != it._module._exports.end() )
				{
					if( ex->desctype == xwasm::desc_kind::DESC_FUNC )
					{
						xwasm::executor _exec( this );

						return _exec.exec( result, &it, &it._module._functions[ex->descidx], params );
					}
				}
			}
		}
	}

	return ERR_FUNC_NOT_FOUND;
}

xwasm::value xwasm::sandbox::set_memory( const xwasm::module * _module, std::uint8_t * ptr, std::uint64_t size )
{
	return {};
}

void xwasm::sandbox::get_memory( const xwasm::module * _module, xwasm::value index, std::uint8_t * ptr, std::uint64_t size )
{

}

xwasm::value xwasm::sandbox::get_global( const xwasm::module * _module, const std::string & name )
{
	return {};
}

void xwasm::sandbox::set_global( const xwasm::module * _module, const std::string & name, xwasm::value val )
{

}

xwasm::value xwasm::sandbox::get_table( const xwasm::module * _module, const std::string & name )
{
	return {};
}

void xwasm::sandbox::set_table( const xwasm::module * _module, const std::string & name, xwasm::value val )
{

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
