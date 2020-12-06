/*!
 * \file	types.h
 *
 * \author	ZhengYuanQing
 * \date	2020/12/06
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef TYPES_H__2025D581_2243_4DA9_9199_37A4A25C1857
#define TYPES_H__2025D581_2243_4DA9_9199_37A4A25C1857

#if COMPILER == COMPILER_MSVC
#   define DLL_IMPORT __declspec( dllimport )
#   define DLL_EXPORT __declspec( dllexport )
#elif COMPILER == COMPILER_GNUC || COMPILER == COMPILER_CLANG
#   define DLL_IMPORT __attribute__ ((visibility ("default")))
#   define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

#ifdef XWASM_EXPORT
#	define XWASM_API DLL_EXPORT
#else
#	define XWASM_API
#endif // XWASM_EXPORT

#ifdef _WIN32
#pragma warning( disable: 4251 )
#else

#endif

namespace xwasm
{
	static constexpr unsigned int MAGIC_NUMBER = 0x6D736100;
	static constexpr unsigned int VERSION_NUMBER = 0x01;
	static constexpr unsigned int MEMORY_PAGE_SIZE = 65536;

	static constexpr unsigned int ERR_NO = 0;
	static constexpr unsigned int ERR_MAGIC_NUMBER = 1;
	static constexpr unsigned int ERR_STREAM_UNEXPECTED_HALT = 2;
	static constexpr unsigned int ERR_STREAM_CODE = 3;
	static constexpr unsigned int ERR_FUNC_NOT_FOUND = 4;
	static constexpr unsigned int ERR_INST_CODE = 5;

	static constexpr unsigned int ERR_UNKNOWN = 10;

	constexpr const char * err_msg[] =
	{
		"",
		"magic number != 0x6D736100",
		"stream unexpected halt",
		"stream error code",
		"the corresponding function was not found",
		"the wrong instruction code",
		"",
		"",
		"",
		"",
		"unknown error"
	};

	enum section_kind
	{
		MAGIC = 0,
		TYPE = 1,
		IMPORT = 2,
		FUNCTION = 3,
		TABLE = 4,
		MEMORY = 5,
		GLOBAL = 6,
		EXPORT = 7,
		START = 8,
		ELEMENT = 9,
		CODE = 10,
		DATA = 11,
	};

	enum type_kind
	{
		TYPE_I32 = 0x7F,
		TYPE_I64 = 0x7E,
		TYPE_F32 = 0x7D,
		TYPE_F64 = 0x7C,
		TYPE_FUNC = 0x60,
		TYPE_TABLE_ANYFUNC = 0x70,
	};

	enum value_kind
	{
		VALUE_UNSPECIFIED = 0,
		VALUE_I32,
		VALUE_I64,
		VALUE_F32,
		VALUE_F64,
	};

	enum desc_kind
	{
		DESC_FUNC = 0x00,
		DESC_TABLE = 0x01,
		DESC_MEM = 0x02,
		DESC_GLOBAL = 0x03,
	};

	enum opcode : std::uint8_t
	{
		// memidx			u32
		// typeidx			u32
		// funcidx			u32
		// tableidx			u32
		// localidx			u32
		// labelidx			u32
		// globalidx		u32
		// offset           u32
		// align            u32

		UNREACHABLE = 0x00, // ()
		NOP = 0x01, // ()
		BLOCK = 0x02, // (block|instr end)
		LOOP = 0x03, // (block|instr end)
		IF = 0x04, // (block|instr else)
		ELSE = 0x05, // (instr end)

		END = 0x0B, // ()
		BR = 0x0C, // (labelidx)
		BR_IF = 0x0D, // (labelidx)
		BR_TABLE = 0x0E, // (labelidx)
		RETURN = 0x0F, // ()
		CALL = 0x10, // (funcidx)
		CALL_INDIRECT = 0x11, // ()

		DROP = 0x1A, // ()
		SELECT = 0x1B, // ()

		GET_LOCAL = 0x20, // (localidx)
		SET_LOCAL = 0x21, // (localidx)
		TEE_LOCAL = 0x22, // (localidx)
		GET_GLOBAL = 0x23, // (globalidx)
		SET_GLOBAL = 0x24, // (globalidx)

		I32_LOAD = 0x28, // (memidx, offset, align)
		I64_LOAD = 0x29, // (memidx, offset, align)
		F32_LOAD = 0x2A, // (memidx, offset, align)
		F64_LOAD = 0x2B, // (memidx, offset, align)
		I32_LOAD8_S = 0x2C, // (memidx, offset, align)
		I32_LOAD8_U = 0x2D, // (memidx, offset, align)
		I32_LOAD16_S = 0x2E, // (memidx, offset, align)
		I32_LOAD16_U = 0x2F, // (memidx, offset, align)
		I64_LOAD8_S = 0x30, // (memidx, offset, align)
		I64_LOAD8_U = 0x31, // (memidx, offset, align)
		I64_LOAD16_S = 0x32, // (memidx, offset, align)
		I64_LOAD16_U = 0x33, // (memidx, offset, align)
		I64_LOAD32_S = 0x34, // (memidx, offset, align)
		I64_LOAD32_U = 0x35, // (memidx, offset, align)
		I32_STORE = 0x36, // (memidx, offset, align)
		I64_STORE = 0x37, // (memidx, offset, align)
		F32_STORE = 0x38, // (memidx, offset, align)
		F64_STORE = 0x39, // (memidx, offset, align)
		I32_STORE8 = 0x3A, // (memidx, offset, align)
		I32_STORE16 = 0x3B, // (memidx, offset, align)
		I64_STORE8 = 0x3C, // (memidx, offset, align)
		I64_STORE16 = 0x3D, // (memidx, offset, align)
		I64_STORE32 = 0x3E, // (memidx, offset, align)
		MEMORY_SIZE = 0x3F, // ()
		MEMORY_GROW = 0x40, // ()
		I32_CONST = 0x41, // (i32)
		I64_CONST = 0x42, // (i64)
		F32_CONST = 0x43, // (f32)
		F64_CONST = 0x44, // (f64)
		I32_EQZ = 0x45, // ()
		I32_EQ = 0x46, // ()
		I32_NE = 0x47, // ()
		I32_LT_S = 0x48, // ()
		I32_LT_U = 0x49, // ()
		I32_GT_S = 0x4A, // ()
		I32_GT_U = 0x4B, // ()
		I32_LE_S = 0x4C, // ()
		I32_LE_U = 0x4D, // ()
		I32_GE_S = 0x4E, // ()
		I32_GE_U = 0x4F, // ()
		I64_EQZ = 0x50, // ()
		I64_EQ = 0x51, // ()
		I64_NE = 0x52, // ()
		I64_LT_S = 0x53, // ()
		I64_LT_U = 0x54, // ()
		I64_GT_S = 0x55, // ()
		I64_GT_U = 0x56, // ()
		I64_LE_S = 0x57, // ()
		I64_LE_U = 0x58, // ()
		I64_GE_S = 0x59, // ()
		I64_GE_U = 0x5A, // ()
		F32_EQ = 0x5B, // ()
		F32_NE = 0x5C, // ()
		F32_LT = 0x5D, // ()
		F32_GT = 0x5E, // ()
		F32_LE = 0x5F, // ()
		F32_GE = 0x60, // ()
		F64_EQ = 0x61, // ()
		F64_NE = 0x62, // ()
		F64_LT = 0x63, // ()
		F64_GT = 0x64, // ()
		F64_LE = 0x65, // ()
		F64_GE = 0x66, // ()
		I32_CLZ = 0x67, // ()
		I32_CTZ = 0x68, // ()
		I32_POPCNT = 0x69, // ()
		I32_ADD = 0x6A, // ()
		I32_SUB = 0x6B, // ()
		I32_MUL = 0x6C, // ()
		I32_DIV_S = 0x6D, // ()
		I32_DIV_U = 0x6E, // ()
		I32_REM_S = 0x6F, // ()
		I32_REM_U = 0x70, // ()
		I32_AND = 0x71, // ()
		I32_OR = 0x72, // ()
		I32_XOR = 0x73, // ()
		I32_SHL = 0x74, // ()
		I32_SHR_S = 0x75, // ()
		I32_SHR_U = 0x76, // ()
		I32_ROTL = 0x77, // ()
		I32_ROTR = 0x78, // ()
		I64_CLZ = 0x79, // ()
		I64_CTZ = 0x7A, // ()
		I64_POPCNT = 0x7B, // ()
		I64_ADD = 0x7C, // ()
		I64_SUB = 0x7D, // ()
		I64_MUL = 0x7E, // ()
		I64_DIV_S = 0x7F, // ()
		I64_DIV_U = 0x80, // ()
		I64_REM_S = 0x81, // ()
		I64_REM_U = 0x82, // ()
		I64_AND = 0x83, // ()
		I64_OR = 0x84, // ()
		I64_XOR = 0x85, // ()
		I64_SHL = 0x86, // ()
		I64_SHR_S = 0x87, // ()
		I64_SHR_U = 0x88, // ()
		I64_ROTL = 0x89, // ()
		I64_ROTR = 0x8A, // ()
		F32_ABS = 0x8B, // ()
		F32_NEG = 0x8C, // ()
		F32_CEIL = 0x8D, // ()
		F32_FLOOR = 0x8E, // ()
		F32_TRUNC = 0x8F, // ()
		F32_NEAREST = 0x90, // ()
		F32_SQRT = 0x91, // ()
		F32_ADD = 0x92, // ()
		F32_SUB = 0x93, // ()
		F32_MUL = 0x94, // ()
		F32_DIV = 0x95, // ()
		F32_MIN = 0x96, // ()
		F32_MAX = 0x97, // ()
		F32_COPYSIGN = 0x98, // ()
		F64_ABS = 0x99, // ()
		F64_NEG = 0x9A, // ()
		F64_CEIL = 0x9B, // ()
		F64_FLOOR = 0x9C, // ()
		F64_TRUNC = 0x9D, // ()
		F64_NEAREST = 0x9E, // ()
		F64_SQRT = 0x9F, // ()
		F64_ADD = 0xA0, // ()
		F64_SUB = 0xA1, // ()
		F64_MUL = 0xA2, // ()
		F64_DIV = 0xA3, // ()
		F64_MIN = 0xA4, // ()
		F64_MAX = 0xA5, // ()
		F64_COPYSIGN = 0xA6, // ()
		I32_WRAP_I64 = 0xA7, // ()
		I32_TRUNC_S_F32 = 0xA8, // ()
		I32_TRUNC_U_F32 = 0xA9, // ()
		I32_TRUNC_S_F64 = 0xAA, // ()
		I32_TRUNC_U_F64 = 0xAB, // ()
		I64_EXTEND_S_I32 = 0xAC, // ()
		I64_EXTEND_U_I32 = 0xAD, // ()
		I64_TRUNC_S_F32 = 0xAE, // ()
		I64_TRUNC_U_F32 = 0xAF, // ()
		I64_TRUNC_S_F64 = 0xB0, // ()
		I64_TRUNC_U_F64 = 0xB1, // ()
		F32_CONVERT_S_I32 = 0xB2, // ()
		F32_CONVERT_U_I32 = 0xB3, // ()
		F32_CONVERT_S_I64 = 0xB4, // ()
		F32_CONVERT_U_I64 = 0xB5, // ()
		F32_DEMOTE_F64 = 0xB6, // ()
		F64_CONVERT_S_I32 = 0xB7, // ()
		F64_CONVERT_U_I32 = 0xB8, // ()
		F64_CONVERT_S_I64 = 0xB9, // ()
		F64_CONVERT_U_I64 = 0xBA, // ()
		F64_PROMOTE_F32 = 0xBB, // ()
		I32_REINTERPRET_F32 = 0xBC, // ()
		I64_REINTERPRET_F64 = 0xBD, // ()
		F32_REINTERPRET_I32 = 0xBE, // ()
		F64_REINTERPRET_I64 = 0xBF, // ()
	};

	union value_data
	{
		value_data();
		value_data( std::int32_t val );
		value_data( std::int64_t val );
		value_data( std::uint32_t  val );
		value_data( std::uint64_t val );
		value_data( float  val );
		value_data( double val );
		value_data( const value_data & val );

		std::int32_t i32;
		std::int64_t i64;
		std::uint32_t u32;
		std::uint64_t u64;
		float f32;
		double f64;
	};

}

#endif // TYPES_H__2025D581_2243_4DA9_9199_37A4A25C1857
