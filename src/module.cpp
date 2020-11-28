#include "module.h"

#include "section_t.h"

xwasm::module::module( const std::string & val )
	:_name( val )
{

}

xwasm::module::~module()
{

}

std::uint32_t xwasm::module::start() const
{
	return _start;
}

const std::string & xwasm::module::name() const
{
	return _name;
}

const xwasm::mem_t * xwasm::module::mem_at( std::uint32_t val ) const
{
	return &_mems[val];
}

const xwasm::type_t * xwasm::module::type_at( std::uint32_t val ) const
{
	return &_types[val];
}

const xwasm::elem_t * xwasm::module::elem_at( std::uint32_t val ) const
{
	return &_elems[val];
}

const xwasm::func_t * xwasm::module::func_at( std::uint32_t val ) const
{
	return &_funcs[val];
}

const xwasm::data_t * xwasm::module::data_at( std::uint32_t val ) const
{
	return &_datas[val];
}

const xwasm::table_t * xwasm::module::tabel_at( std::uint32_t val ) const
{
	return &_tabels[val];
}

const xwasm::global_t * xwasm::module::global_at( std::uint32_t val ) const
{
	return &_globals[val];
}

const xwasm::import_t * xwasm::module::import_at( std::uint32_t val ) const
{
	return &_imports[val];
}

const xwasm::export_t * xwasm::module::export_at( std::uint32_t val ) const
{
	return &_exports[val];
}
