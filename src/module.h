#pragma once

#include <vector>
#include <string>

namespace xwasm
{
	class mem_t;
	class func_t;
	class type_t;
	class elem_t;
	class data_t;
	class table_t;
	class global_t;
	class import_t;
	class export_t;

	class value;
	class loader;
	class executor;

	class module
	{
		friend class loader;

	public:
		module( const std::string & val );

		~module();

	public:
		std::uint32_t start() const;

		const std::string & name() const;

		const xwasm::mem_t * mem_at( std::uint32_t val ) const;

		const xwasm::type_t * type_at( std::uint32_t val ) const;

		const xwasm::elem_t * elem_at( std::uint32_t val ) const;

		const xwasm::func_t * func_at( std::uint32_t val ) const;

		const xwasm::data_t * data_at( std::uint32_t val ) const;

		const xwasm::table_t * tabel_at( std::uint32_t val ) const;

		const xwasm::global_t * global_at( std::uint32_t val ) const;

		const xwasm::import_t * import_at( std::uint32_t val ) const;

		const xwasm::export_t * export_at( std::uint32_t val ) const;

	private:
		std::string _name;
		std::uint32_t _start = -1;
		std::vector<xwasm::mem_t> _mems;
		std::vector<xwasm::type_t> _types;
		std::vector<xwasm::elem_t> _elems;
		std::vector<xwasm::func_t> _funcs;
		std::vector<xwasm::data_t> _datas;
		std::vector<xwasm::table_t> _tabels;
		std::vector<xwasm::global_t> _globals;
		std::vector<xwasm::import_t> _imports;
		std::vector<xwasm::export_t> _exports;
	};
}
