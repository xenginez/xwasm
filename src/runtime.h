/*!
 * \file	runtime.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/29
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef RUNTIME_H__CECB55DF_075F_4E63_AC12_17A16C6EA1D8
#define RUNTIME_H__CECB55DF_075F_4E63_AC12_17A16C6EA1D8

#include "value.h"
#include "module.h"

namespace xwasm
{
	class runtime
	{
	public:
		runtime();

		~runtime();

	public:
		void init();

	public:
		xwasm::module _module;
		std::vector< std::uint8_t > _memorys;
		std::vector< std::uint32_t > _tables;
		std::vector< xwasm::value_data > _locals;
		std::vector< xwasm::value_data > _globals;
	};
}

#endif // RUNTIME_H__CECB55DF_075F_4E63_AC12_17A16C6EA1D8
