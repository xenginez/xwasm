/*!
 * \file	sandbox.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef SANDBOX_H__B8B1DF89_04DB_4ED2_A3A8_F7372950271D
#define SANDBOX_H__B8B1DF89_04DB_4ED2_A3A8_F7372950271D

#include <map>
#include <deque>
#include <string>

#include "value.h"
#include "stream.h"
#include "mem_view.hpp"

namespace xwasm
{
	class module;
	class executor;

	class sandbox
	{
		friend class executor;

	private:
		struct private_p;

	public:
		sandbox();

		~sandbox();

	public:
		const xwasm::module & load( const std::string & name, xwasm::stream & source );

	public:
		int call( xwasm::value & result, const std::string & name, std::deque< xwasm::value > & params );

		template< typename ... Args > int call( const std::string & name, Args &&...args )
		{
			std::deque< xwasm::value > params;

			push_args( params, std::forward< Args >( args )... );

			xwasm::value result;
			return call( result, name, params );
		}

		template< typename T, typename ... Args > int call( T & result, const std::string & name, Args &&...args )
		{
			std::deque< xwasm::value > params;

			push_args( params, std::forward< Args >( args )... );

			xwasm::value res;
			int ret = call( res, name, params );
			if( ret == 0 && res.type != value_kind::VALUE_UNSPECIFIED )
			{
				get_memory( res, &result, sizeof( result ) );
			}

			return ret;
		}

	private:
		void push_args( std::deque< xwasm::value > & args );

		template< typename T > void push_args( std::deque< xwasm::value > & params, T && val )
		{
			push( params, std::forward< T >( val ) );
		}

		template< typename T, typename ... Args > void push_args( std::deque< xwasm::value > & params, T && val, Args &&...args )
		{
			push( params, std::forward< T >( val ) );

			push_args( params, std::forward< Args >( args )... );
		}

	private:
		void push( std::deque< xwasm::value > & params, std::int8_t val );

		void push( std::deque< xwasm::value > & params, std::int16_t val );

		void push( std::deque< xwasm::value > & params, std::int32_t val );

		void push( std::deque< xwasm::value > & params, std::int64_t val );

		void push( std::deque< xwasm::value > & params, std::uint8_t val );

		void push( std::deque< xwasm::value > & params, std::uint16_t val );

		void push( std::deque< xwasm::value > & params, std::uint32_t val );

		void push( std::deque< xwasm::value > & params, std::uint64_t val );

		void push( std::deque< xwasm::value > & params, float val );

		void push( std::deque< xwasm::value > & params, double val );

		void push( std::deque< xwasm::value > & params, xwasm::mem_view val );

	private:
		xwasm::value set_memory( std::uint8_t * ptr, std::uint64_t size );

		void get_memory( xwasm::value index, std::uint8_t * ptr, std::uint64_t size );

	private:
		private_p * _p;
	};
}

#endif // SANDBOX_H__B8B1DF89_04DB_4ED2_A3A8_F7372950271D
