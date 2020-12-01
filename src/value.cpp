#include "value.h"

xwasm::value_data::value_data()
	:u64( 0 )
{

}

xwasm::value_data::value_data( std::int32_t val )
	: i32( val )
{

}

xwasm::value_data::value_data( std::int64_t val )
	: i64( val )
{

}

xwasm::value_data::value_data( std::uint32_t val )
	: u32( val )
{

}

xwasm::value_data::value_data( std::uint64_t val )
	: u64( val )
{

}

xwasm::value_data::value_data( float val )
	: f32( val )
{

}

xwasm::value_data::value_data( double val )
	: f64( val )
{

}

xwasm::value_data::value_data( const xwasm::value_data & val )
	: u64( val.u64 )
{

}


xwasm::value::value()
	:type( xwasm::value_kind::VALUE_UNSPECIFIED ), data( std::uint64_t( 0 ) )
{

}

xwasm::value::value( std::int32_t val )
	: type( xwasm::value_kind::VALUE_I32 ), data( val )
{

}

xwasm::value::value( std::int64_t val )
	: type( xwasm::value_kind::VALUE_I64 ), data( val )
{

}

xwasm::value::value( float val )
	: type( xwasm::value_kind::VALUE_F32 ), data( val )
{

}

xwasm::value::value( double val )
	:type( xwasm::value_kind::VALUE_F32 ), data( val )
{

}

xwasm::value::value( const xwasm::value & val )
	: type( val.type ), data( val.data )
{

}

xwasm::value::~value()
{ 
}

xwasm::value & xwasm::value::operator=( std::int32_t val )
{
	type = xwasm::value_kind::VALUE_I32;
	data.i32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( std::int64_t val )
{
	type = xwasm::value_kind::VALUE_I64;
	data.i64 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( float val )
{
	type = xwasm::value_kind::VALUE_F32;
	data.f32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( double val )
{
	type = xwasm::value_kind::VALUE_F64;
	data.f64 = val;

	return *this;
}
xwasm::value & xwasm::value::operator=( const xwasm::value & val )
{
	type = val.type;
	data = val.data;

	return *this;
}
