/*!
 * \file	loader.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef LOADER_H__B36673EF_1F57_48B7_B636_FB36F2216F19
#define LOADER_H__B36673EF_1F57_48B7_B636_FB36F2216F19

#include "stream.h"

namespace xwasm
{
	class module;

	class loader
	{
	public:
		loader();

		~loader();

	public:
		int load( module * _module, xwasm::stream & _source );

	private:
		int load_magic( module * _module, xwasm::stream & _source );

		int load_type( module * _module, xwasm::stream & _source );

		int load_import( module * _module, xwasm::stream & _source );

		int load_function( module * _module, xwasm::stream & _source );

		int load_table( module * _module, xwasm::stream & _source );

		int load_memory( module * _module, xwasm::stream & _source );

		int load_global( module * _module, xwasm::stream & _source );

		int load_export( module * _module, xwasm::stream & _source );

		int load_start( module * _module, xwasm::stream & _source );

		int load_element( module * _module, xwasm::stream & _source );

		int load_code( module * _module, xwasm::stream & _source );

		int load_data( module * _module, xwasm::stream & _source );
	};
}

#endif // LOADER_H__B36673EF_1F57_48B7_B636_FB36F2216F19
