/*!
 * \file	executor.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef EXECUTOR_H__826B6F3F_633B_40A8_805E_1AF411656A89
#define EXECUTOR_H__826B6F3F_633B_40A8_805E_1AF411656A89

#include <deque>

#include "value.h"

namespace xwasm
{
	struct func_t;
	
	class value;
	class module;
	class stream;
	class runtime;
	class sandbox;

	class executor
	{
	public:
		struct private_p;

	public:
		executor( xwasm::sandbox * val );

		~executor();

	public:
		int exec( xwasm::value & _result, xwasm::runtime * _runtime, xwasm::func_t * _func, const std::deque< xwasm::value > & _params );

	public:
		xwasm::func_t * cur_func() const;

		xwasm::stream * cur_stream() const;

		xwasm::runtime * cur_runtime() const;

		xwasm::sandbox * cur_sandbox() const;

	public:
		void push( xwasm::value_data val );

		xwasm::value_data pop();

	public:
		void pushed();

		void poped();

	private:
		private_p * _p;
	};
}

#endif // EXECUTOR_H__826B6F3F_633B_40A8_805E_1AF411656A89
