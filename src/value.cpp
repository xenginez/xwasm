#include "value.h"

xwasm::value::value()
	:_type( xwasm::value_kind::VALUE_UNSPECIFIED ), i32( 0 )
{

}

xwasm::value::value( std::int32_t val )
	: _type( xwasm::value_kind::VALUE_I32 ), i32( val )
{

}

xwasm::value::value( std::int64_t val )
	: _type( xwasm::value_kind::VALUE_I64 ), i64( val )
{

}

xwasm::value::value( float val )
	: _type( xwasm::value_kind::VALUE_F32 ), f32( val )
{

}

xwasm::value::value( double val )
	:_type( xwasm::value_kind::VALUE_F32 ), f64( val )
{

}

xwasm::value::value( const xwasm::value & val )
	: _type( val._type ), i64( val.i64 )
{

}

xwasm::value::~value()
{ 
}

xwasm::value & xwasm::value::operator=( std::int32_t val )
{
	_type = xwasm::value_kind::VALUE_I32;
	i32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( std::int64_t val )
{
	_type = xwasm::value_kind::VALUE_I64;
	i64 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( float val )
{
	_type = xwasm::value_kind::VALUE_F32;
	f32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( double val )
{
	_type = xwasm::value_kind::VALUE_F64;
	f64 = val;

	return *this;
}
xwasm::value & xwasm::value::operator=( const xwasm::value & val )
{
	_type = val._type;
	i64 = val.i64;

	return *this;
}

