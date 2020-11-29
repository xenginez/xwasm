/*!
 * \file	section_t.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SECTION_T_H__DB2AAF38_0DB1_4FC3_BFE8_96BE7718FA8D
#define SECTION_T_H__DB2AAF38_0DB1_4FC3_BFE8_96BE7718FA8D

#include <vector>
#include <string>

#include "value.h"
#include "opcode.h"

namespace xwasm
{
	struct XWASM_API type_t
	{
		std::vector<xwasm::value_kind> params;
		std::vector<xwasm::value_kind> results;
	};

	struct XWASM_API import_t
	{
		std::string name;
		std::string modulename;
		xwasm::desc_kind desc_type;
		union
		{
			std::uint32_t typeidx;
			struct
			{
				std::uint32_t min;
				std::uint32_t max;
			} limits;
			struct
			{
				bool mut;
				xwasm::value_kind valuetype;
			} global;
		} desc;
	};

	struct XWASM_API func_t
	{
		bool cfunc;
		std::uint32_t typeidx;
		std::vector<std::uint8_t> codes;
		std::vector<xwasm::type_kind> locals;
	};

	struct XWASM_API table_t
	{
		std::uint32_t min;
		std::uint32_t max;
		xwasm::type_kind type;
	};

	struct XWASM_API mem_t
	{
		std::uint32_t min;
		std::uint32_t max;
	};

	struct XWASM_API global_t
	{
		bool mut;
		xwasm::value init;
		xwasm::value_kind type;
	};

	struct XWASM_API export_t
	{
		std::string name;
		std::uint32_t descidx;
		xwasm::desc_kind desctype;
	};

	struct XWASM_API elem_t
	{
		std::uint32_t table;
		std::int32_t offset;
		std::vector<std::uint32_t> inits;
	};

	struct XWASM_API data_t
	{
		std::uint32_t data;
		xwasm::value offset;
		std::vector<std::uint8_t> inits;
	};
}

#endif // SECTION_T_H__DB2AAF38_0DB1_4FC3_BFE8_96BE7718FA8D
