#include "stream.h"

xwasm::stream::stream()
	: _type( type::MEMORY ), _beg( nullptr ), _cur( nullptr ), _end( nullptr )
{

}

xwasm::stream::stream( std::istream & val )
	:_type( type::STREAM ), _stream( &val )
{

}

xwasm::stream::stream( std::uint8_t * beg, std::uint8_t * end )
	: _type( type::MEMORY ), _beg( beg ), _cur( beg ), _end( end )
{

}
void xwasm::stream::clear()
{
	_type = type::MEMORY;
	_beg = nullptr;
	_cur = nullptr;
	_end = nullptr;
}

void xwasm::stream::reset( std::istream & val )
{
	_type = type::STREAM;
	_stream = &val;
}

void xwasm::stream::reset( std::uint8_t * beg, std::uint8_t * end )
{
	_type = type::MEMORY;
	_beg = beg;
	_cur = beg;
	_end = end;
}

int xwasm::stream::get()
{
	if( _type == type::STREAM )
	{
		return _stream->get();
	}
	
	return *_cur++;
}

int xwasm::stream::peek()
{
	if( _type == type::STREAM )
	{
		return _stream->peek();
	}

	return *_cur;
}

bool xwasm::stream::eof() const
{
	if( _type == type::STREAM )
	{
		return _stream->eof();
	}

	return _cur >= _end;
}

std::uint64_t xwasm::stream::tellg()
{
	if( _type == type::STREAM )
	{
		return _stream->tellg();
	}

	return _cur - _beg;
}

xwasm::stream & xwasm::stream::read( char * ptr, std::uint64_t size )
{
	if( _type == type::STREAM )
	{
		_stream->read( ptr, size );
	}

	std::memcpy( ptr, _cur, size );
	_cur += size;

	return *this;
}

xwasm::stream & xwasm::stream::seekg( std::uint64_t offset, seek_dir dir )
{
	if( _type == type::STREAM )
	{
		switch( dir )
		{
		case seek_dir::DIR_BEG:
			_stream->seekg( offset, std::istream::beg );
			break;
		case seek_dir::DIR_CUR:
			_stream->seekg( offset, std::istream::cur );
			break;
		case seek_dir::DIR_END:
			_stream->seekg( offset, std::istream::end );
			break;
		}
	}

	switch( dir )
	{
	case seek_dir::DIR_BEG:
		_cur = _beg + offset;
		break;
	case seek_dir::DIR_CUR:
		_cur = _cur + offset;
		break;
	case seek_dir::DIR_END:
		_cur = _end + offset;
		break;
	}

	return *this;
}
