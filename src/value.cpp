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


xwasm::value::value()
	:type( xwasm::value_kind::VALUE_UNSPECIFIED ), i32( 0 )
{

}

xwasm::value::value( std::int32_t val )
	: type( xwasm::value_kind::VALUE_I32 ), i32( val )
{

}

xwasm::value::value( std::int64_t val )
	: type( xwasm::value_kind::VALUE_I64 ), i64( val )
{

}

xwasm::value::value( float val )
	: type( xwasm::value_kind::VALUE_F32 ), f32( val )
{

}

xwasm::value::value( double val )
	:type( xwasm::value_kind::VALUE_F32 ), f64( val )
{

}

xwasm::value::value( const xwasm::value & val )
	: type( val.type ), i64( val.i64 )
{

}

xwasm::value::~value()
{ 
}

xwasm::value & xwasm::value::operator=( std::int32_t val )
{
	type = xwasm::value_kind::VALUE_I32;
	i32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( std::int64_t val )
{
	type = xwasm::value_kind::VALUE_I64;
	i64 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( float val )
{
	type = xwasm::value_kind::VALUE_F32;
	f32 = val;

	return *this;
}

xwasm::value & xwasm::value::operator=( double val )
{
	type = xwasm::value_kind::VALUE_F64;
	f64 = val;

	return *this;
}
xwasm::value & xwasm::value::operator=( const xwasm::value & val )
{
	type = val.type;
	i64 = val.i64;

	return *this;
}
