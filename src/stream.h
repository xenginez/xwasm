/*!
 * \file	stream.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef STREAM_H__1BA34991_BA3D_4629_8A38_57C513A3CDFB
#define STREAM_H__1BA34991_BA3D_4629_8A38_57C513A3CDFB

#include <iostream>

#include "opcode.h"

namespace xwasm
{
	class XWASM_API stream
	{
	public:
		enum class type
		{
			STREAM,
			MEMORY,
		};

		enum class seek_dir
		{
			DIR_BEG,
			DIR_CUR,
			DIR_END,
		};

	public:
		static constexpr seek_dir beg = seek_dir::DIR_BEG;
		static constexpr seek_dir cur = seek_dir::DIR_CUR;
		static constexpr seek_dir end = seek_dir::DIR_END;
		
	public:
		stream();

		stream( std::istream & val );

		stream( const std::uint8_t * beg, const std::uint8_t * end );

	public:
		void clear();

		void reset( std::istream & val );

		void reset( const std::uint8_t * beg, const std::uint8_t * end );

	public:
		bool eof() const;

	public:
		int get();

		int peek();

		std::uint64_t tellg();

		xwasm::stream & read( char * ptr, std::uint64_t size );

		xwasm::stream & seekg( std::uint64_t offset, seek_dir dir );

	private:
		type _type;
		union
		{
			std::istream * _stream;
			struct  
			{
				const std::uint8_t * _beg;
				const std::uint8_t * _cur;
				const std::uint8_t * _end;
			};
		};
	};
}

#endif // STREAM_H__1BA34991_BA3D_4629_8A38_57C513A3CDFB
