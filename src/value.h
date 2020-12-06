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

#include "types.h"

namespace xwasm
{
	class XWASM_API value
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
		xwasm::value_data data;
		xwasm::value_kind type;
	};
}

#endif // VALUE_H__E6364686_056F_4953_A91E_8681078B9362
