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

#include <deque>
#include <vector>

#include "value.h"
#include "stream.h"

namespace xwasm
{
	class module;

	class XWASM_API sandbox
	{
		friend class executor;

	private:
		struct private_p;

	public:
		sandbox();

		~sandbox();

	public:
		bool insert_module( xwasm::module && val );

		std::vector< const xwasm::module * > modules() const;

		const xwasm::module * find_module( const std::string & name );

		const xwasm::module * load( const std::string & name, xwasm::stream & source );

	public:
		int call( xwasm::value & result, const std::string & name, std::deque< xwasm::value > & params );

		template< typename ... Args > int call( const std::string & name, Args &&...args )
		{
			std::deque< xwasm::value > params;

			push_args( params, std::forward< Args >( args )... );

			xwasm::value result;
			return call( result, name, params );
		}

		template< typename ... Args > int call( xwasm::value & result, const std::string & name, Args &&...args )
		{
			std::deque< xwasm::value > params;

			push_args( params, std::forward< Args >( args )... );

			int ret = call( result, name, params );

			return ret;
		}

	public:
		xwasm::value set_memory( const xwasm::module * _module, std::uint8_t * ptr, std::uint64_t size );

		void get_memory( const xwasm::module * _module, xwasm::value index, std::uint8_t * ptr, std::uint64_t size );

		xwasm::value get_global( const xwasm::module * _module, const std::string & name );

		void set_global( const xwasm::module * _module, const std::string & name, xwasm::value val );

		xwasm::value get_table( const xwasm::module * _module, const std::string & name );

		void set_table( const xwasm::module * _module, const std::string & name, xwasm::value val );

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

		template< typename T > void push( std::deque< xwasm::value > & params, T val )
		{
			push( params, make( val ) );
		}

	private:
		private_p * _p;
	};
}

#endif // SANDBOX_H__B8B1DF89_04DB_4ED2_A3A8_F7372950271D
