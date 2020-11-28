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
#include <string>

namespace xwasm
{
	class module;
	class executor;

	class sandbox
	{
		friend class executor;

	public:
		sandbox();

		~sandbox();

	public:
		void load( const std::string & path );

	private:
		std::map<std::string, module> _modules;
	};
}

#endif // SANDBOX_H__B8B1DF89_04DB_4ED2_A3A8_F7372950271D
