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

namespace xwasm
{
	class executor
	{
	public:
		executor();

		~executor();

	public:
		int call();

		int stop();

		int pause();

		int resume();
	};
}

#endif // EXECUTOR_H__826B6F3F_633B_40A8_805E_1AF411656A89
