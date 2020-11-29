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

namespace xwasm
{
	class func_t;

	class value;
	class sandbox;

	class executor
	{
	public:
		struct private_p;

	public:
		executor( xwasm::sandbox * val );

		~executor();

	public:
		int exec( xwasm::value & result, func_t * func, const std::deque< xwasm::value > & params );

	private:
		void push( xwasm::value val );

		xwasm::value pop();

	private:
		void pushed();

		void poped();

	private:
		private_p * _p;
	};
}

#endif // EXECUTOR_H__826B6F3F_633B_40A8_805E_1AF411656A89
