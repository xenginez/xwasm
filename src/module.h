/*!
 * \file	module.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/29
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MODULE_H__BDADF173_57AA_474A_BDF7_184C8DF7D02E
#define MODULE_H__BDADF173_57AA_474A_BDF7_184C8DF7D02E

#include <vector>
#include <string>

#include "section_t.h"

namespace xwasm
{
	class value;
	class loader;
	class sandbox;

	class XWASM_API module
	{
		friend class loader;
		friend class sandbox;

	public:
		module();

		~module();

	public:
		std::uint32_t start() const;

		const std::string & name() const;

	public:
		std::uint64_t mem_size() const;

		std::uint64_t type_size() const;

		std::uint64_t elem_size() const;

		std::uint64_t func_size() const;

		std::uint64_t data_size() const;

		std::uint64_t  tabel_size() const;

		std::uint64_t global_size() const;

		std::uint64_t import_size() const;

		std::uint64_t export_size() const;

	public:
		const xwasm::memory_t * memory_at( std::uint32_t val ) const;

		const xwasm::type_t * type_at( std::uint32_t val ) const;

		const xwasm::element_t * element_at( std::uint32_t val ) const;

		const xwasm::func_t * function_at( std::uint32_t val ) const;

		const xwasm::data_t * data_at( std::uint32_t val ) const;

		const xwasm::table_t * tabel_at( std::uint32_t val ) const;

		const xwasm::global_t * global_at( std::uint32_t val ) const;

		const xwasm::import_t * import_at( std::uint32_t val ) const;

		const xwasm::export_t * export_at( std::uint32_t val ) const;

	private:
		std::string _name;
		std::uint32_t _start = -1;
		std::vector<xwasm::type_t> _types;
		std::vector<xwasm::data_t> _datas;
		std::vector<xwasm::table_t> _tabels;
		std::vector<xwasm::func_t> _functions;
		std::vector<xwasm::memory_t> _memorys;
		std::vector<xwasm::global_t> _globals;
		std::vector<xwasm::import_t> _imports;
		std::vector<xwasm::export_t> _exports;
		std::vector<xwasm::element_t> _elements;
	};
}

#endif // MODULE_H__BDADF173_57AA_474A_BDF7_184C8DF7D02E
