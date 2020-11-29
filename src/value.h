/*!
 * \file	value.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef VALUE_H__E6364686_056F_4953_A91E_8681078B9362
#define VALUE_H__E6364686_056F_4953_A91E_8681078B9362

#include <cstdint>

#include "opcode.h"

namespace xwasm
{
	class value
	{
	public:
		value();

		value( std::int32_t val );

		value( std::int64_t val );

		value( float val );

		value( double val );

		value( const xwasm::value & val );

		~value();

	public:
		value & operator=( std::int32_t val );

		value & operator=( std::int64_t val );

		value & operator=( float val );

		value & operator=( double val );

		value & operator=( const xwasm::value & val );

	public:
		xwasm::value_kind type;
		union
		{
			std::int32_t i32;
			std::int64_t i64;
			std::uint32_t u32;
			std::uint64_t u64;
			float f32;
			double f64;
		};
	};
}

#endif // VALUE_H__E6364686_056F_4953_A91E_8681078B9362
