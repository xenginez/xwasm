/*!
 * \file	mem_view.hpp
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef MEM_VIEW_HPP__4A2A8DE2_46DC_46B4_975D_C1FE6183DCAE
#define MEM_VIEW_HPP__4A2A8DE2_46DC_46B4_975D_C1FE6183DCAE

#include <string>
#include <vector>

namespace xwasm
{
	struct mem_view
	{
		std::uint64_t size;
		std::uint8_t * data;
	};

	template< typename T > mem_view make( T * ptr, std::uint64_t size )
	{
		return { size, static_cast< std::uint8_t * >( ptr ) };
	}

	template< typename ... Args > mem_view make( const std::vector< Args... > & arr )
	{
		return { arr.size(), static_cast< std::uint8_t * >( arr.data() ) };
	}

	template< typename ... Args > mem_view make( const std::basic_string< Args... > & str )
	{
		return { str.size(), static_cast< std::uint8_t * >( str.c_str() ) };
	}

}

#endif // MEM_VIEW_HPP__4A2A8DE2_46DC_46B4_975D_C1FE6183DCAE
