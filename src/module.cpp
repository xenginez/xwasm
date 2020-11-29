#include "module.h"

#include "section_t.h"

xwasm::module::module()
{

}

xwasm::module::~module()
{

}

std::uint32_t xwasm::module::start() const
{
	if( _start == -1 )
	{
		for( std::uint32_t i = 0; i < _exports.size(); ++i )
		{
			if( _exports[i].name == "_start" )
			{
				return i;
			}
		}
	}

	return _start;
}

const std::string & xwasm::module::name() const
{
	return _name;
}

std::uint64_t xwasm::module::mem_size() const
{
	return _mems.size();
}

std::uint64_t xwasm::module::type_size() const
{
	return _types.size();
}

std::uint64_t xwasm::module::elem_size() const
{
	return _elems.size();
}

std::uint64_t xwasm::module::func_size() const
{
	return _funcs.size();
}

std::uint64_t xwasm::module::data_size() const
{
	return _datas.size();
}

std::uint64_t xwasm::module::tabel_size() const
{
	return _tabels.size();
}

std::uint64_t xwasm::module::global_size() const
{
	return _globals.size();
}

std::uint64_t xwasm::module::import_size() const
{
	return _imports.size();
}

std::uint64_t xwasm::module::export_size() const
{
	return _exports.size();
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
