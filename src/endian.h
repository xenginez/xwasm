/*!
 * \file	endian.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ENDIAN_H__311AE07B_CB53_44FD_8742_9F340A208F0F
#define ENDIAN_H__311AE07B_CB53_44FD_8742_9F340A208F0F

#include "stream.h"

namespace xwasm
{
	constexpr bool is_big_endian();


	constexpr std::uint16_t to_little_uint16( std::uint16_t val );

	constexpr std::uint32_t to_little_uint32( std::uint32_t val );

	constexpr std::uint64_t to_little_uint64( std::uint64_t val );


	std::int32_t get_leb128_int32( xwasm::stream & source );

	std::int64_t get_leb128_int64( xwasm::stream & source );

	std::uint32_t get_leb128_uint32( xwasm::stream & source );
}

#endif // ENDIAN_H__311AE07B_CB53_44FD_8742_9F340A208F0F
