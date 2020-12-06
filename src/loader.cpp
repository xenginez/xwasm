#include "loader.h"

#include "module.h"
#include "endian.h"
#include "section_t.h"

int skip_section( xwasm::section_kind section, xwasm::stream & _source )
{
	_source.seekg( 8, xwasm::stream::beg );

	if( _source.eof() )
	{
		return -1;
	}

	while( _source.peek() < section && _source.peek() != 0x00 )
	{
		if( _source.eof() )
		{
			return -1;
		}

		_source.get();

		std::uint32_t size = xwasm::get_leb128_uint32( _source );

		_source.seekg( size, xwasm::stream::cur );
	}

	if( _source.get() == section )
	{
		return xwasm::get_leb128_uint32( _source );
	}

	return -1;
}

xwasm::loader::loader()
{

}

xwasm::loader::~loader()
{

}

int xwasm::loader::load( module * _module, xwasm::stream & _source )
{
#define CHECK( FUNC ) ret = FUNC( _module, _source ); if( ret != 0 ) return ret

	int ret = 0;

	CHECK( load_magic );
	CHECK( load_type );
	CHECK( load_import );
	CHECK( load_function );
	CHECK( load_table );
	CHECK( load_memory );
	CHECK( load_global );
	CHECK( load_export );
	CHECK( load_start );
	CHECK( load_element );
	CHECK( load_code );
	CHECK( load_data );

	return ret;

#undef CHECK
}

int xwasm::loader::load_magic( module * _module, xwasm::stream & _source )
{
	std::uint32_t magic = 0;
	_source.read( ( char * )&magic, sizeof( magic ) );

	if( magic != MAGIC_NUMBER )
	{
		return ERR_MAGIC_NUMBER;
	}

	std::uint32_t version = 0;
	_source.read( ( char * )&version, sizeof( magic ) );

	if( version != VERSION_NUMBER )
	{
		return ERR_MAGIC_NUMBER;
	}

	return 0;
}

int xwasm::loader::load_type( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::TYPE, _source ) >= 1 )
	{
		for( std::uint32_t type_size = get_leb128_uint32( _source ); type_size > 0; type_size-- )
		{
			if( _source.get() != TYPE_FUNC )
			{
				return ERR_STREAM_CODE;
			}

			type_t type;

			for( std::uint32_t params_size = get_leb128_uint32( _source ); params_size > 0; params_size-- )
			{
				switch( _source.get() )
				{
				case type_kind::TYPE_I32:
					type.params.push_back( value_kind::VALUE_I32 );
					break;
				case type_kind::TYPE_I64:
					type.params.push_back( value_kind::VALUE_I64 );
					break;
				case type_kind::TYPE_F32:
					type.params.push_back( value_kind::VALUE_F32 );
					break;
				case type_kind::TYPE_F64:
					type.params.push_back( value_kind::VALUE_F64 );
					break;
				default:
					break;
				}
			}

			for( std::uint32_t result_size = get_leb128_uint32( _source ); result_size > 0; result_size-- )
			{
				switch( _source.get() )
				{
				case type_kind::TYPE_I32:
					type.results.push_back( value_kind::VALUE_I32 );
					break;
				case type_kind::TYPE_I64:
					type.results.push_back( value_kind::VALUE_I64 );
					break;
				case type_kind::TYPE_F32:
					type.results.push_back( value_kind::VALUE_F32 );
					break;
				case type_kind::TYPE_F64:
					type.results.push_back( value_kind::VALUE_F64 );
					break;
				default:
					break;
				}
			}

			_module->_types.push_back( type );
		}
	}

	return 0;
}

int xwasm::loader::load_import( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::IMPORT, _source ) >= 1 )
	{
		char buf[4096] = { 0 };

		for( std::uint32_t import_size = get_leb128_uint32( _source ); import_size > 0; import_size-- )
		{
			import_t imp;

			std::uint32_t modulelen = get_leb128_uint32( _source );
			_source.read( buf, modulelen );
			buf[modulelen] = '\0';
			imp.modulename = buf;

			std::uint32_t namelen = get_leb128_uint32( _source );
			_source.read( buf, namelen );
			buf[namelen] = '\0';
			imp.name = buf;

			switch( ( desc_kind )( _source.get() ) )
			{
			case desc_kind::DESC_FUNC:
			{
				imp.desc_type = desc_kind::DESC_FUNC;
				imp.desc.typeidx = get_leb128_uint32( _source );
				break;
			}
			case desc_kind::DESC_TABLE:
			{
				if( _source.get() != TYPE_TABLE_ANYFUNC )
				{
					return ERR_STREAM_CODE;
				}

				imp.desc_type = desc_kind::DESC_TABLE;
				int flag = _source.get();
				imp.desc.limits.min = get_leb128_uint32( _source );
				if( flag == 0x01 )
				{
					imp.desc.limits.max = get_leb128_uint32( _source );
				}
				break;
			}
			case desc_kind::DESC_MEM:
			{
				imp.desc_type = desc_kind::DESC_MEM;
				int flag = _source.get();
				imp.desc.limits.min = get_leb128_uint32( _source );
				if( flag == 0x01 )
				{
					imp.desc.limits.max = get_leb128_uint32( _source );
				}
				break;
			}
			case desc_kind::DESC_GLOBAL:
			{
				imp.desc_type = desc_kind::DESC_GLOBAL;
				switch( _source.get() )
				{
				case type_kind::TYPE_I32:
					imp.desc.global.valuetype = value_kind::VALUE_I32;
					break;
				case type_kind::TYPE_I64:
					imp.desc.global.valuetype = value_kind::VALUE_I64;
					break;
				case type_kind::TYPE_F32:
					imp.desc.global.valuetype = value_kind::VALUE_F32;
					break;
				case type_kind::TYPE_F64:
					imp.desc.global.valuetype = value_kind::VALUE_F64;
					break;
				default:
					return ERR_STREAM_CODE;
					break;
				}
				int mut = _source.get();
				if( mut == 0x01 || mut == 0x00 )
				{
					imp.desc.global.mut = mut;
				}
				else
				{
					return ERR_STREAM_CODE;
				}
				break;
			}
			default:
				return ERR_STREAM_CODE;
				break;
			}

			_module->_imports.push_back( imp );
		}
	}

	return 0;
}

int xwasm::loader::load_function( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::FUNCTION, _source ) >= 1 )
	{
		for( std::uint32_t func_size = get_leb128_uint32( _source ); func_size > 0; func_size-- )
		{
			func_t func;

			func.cfunc = false;
			func.typeidx = get_leb128_uint32( _source );

			_module->_functions.push_back( func );
		}
	}

	return 0;
}

int xwasm::loader::load_table( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::TABLE, _source ) >= 1 )
	{
		for( std::uint32_t table_size = get_leb128_uint32( _source ); table_size > 0; table_size-- )
		{
			table_t table;

			table.type = ( type_kind )( _source.get() );
			if( table.type != type_kind::TYPE_TABLE_ANYFUNC )
			{
				return ERR_STREAM_CODE;
			}

			int flag = _source.get();

			table.min = get_leb128_uint32( _source );
			if( flag == 0x01 )
			{
				table.max = get_leb128_uint32( _source );
			}

			_module->_tabels.push_back( table );
		}
	}

	return 0;
}

int xwasm::loader::load_memory( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::MEMORY, _source ) >= 1 )
	{
		for( std::uint32_t mem_size = get_leb128_uint32( _source ); mem_size > 0; mem_size-- )
		{
			memory_t mem;

			int flag = _source.get();
			mem.min = get_leb128_uint32( _source );
			if( flag == 0x01 )
			{
				mem.max = get_leb128_uint32( _source );
			}

			_module->_memorys.push_back( mem );
		}
	}

	return 0;
}

int xwasm::loader::load_global( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::GLOBAL, _source ) >= 1 )
	{
		for( std::uint32_t global_size = get_leb128_uint32( _source ); global_size > 0; global_size-- )
		{
			global_t global;

			switch( _source.get() )
			{
			case type_kind::TYPE_I32:
				global.type = value_kind::VALUE_I32;
				break;
			case type_kind::TYPE_I64:
				global.type = value_kind::VALUE_I64;
				break;
			case type_kind::TYPE_F32:
				global.type = value_kind::VALUE_F32;
				break;
			case type_kind::TYPE_F64:
				global.type = value_kind::VALUE_F64;
				break;
			default:
				break;
			}

			global.mut = _source.get();

			switch( _source.get() )
			{
			case opcode::I32_CONST:
				global.init = get_leb128_int32( _source );
				break;
			case opcode::I64_CONST:
				global.init = get_leb128_int64( _source );
				break;
			case opcode::F32_CONST:
			{
				std::uint32_t val;
				_source.read( ( char * )&val, sizeof( float ) );
				global.init.type = value_kind::VALUE_F32;
				global.init.data = to_little_uint32( val );
				break;
			}
			case opcode::F64_CONST:
			{
				std::uint64_t val;
				_source.read( ( char * )&val, sizeof( double ) );
				global.init.type = value_kind::VALUE_F64;
				global.init.data = to_little_uint64( val );
				break;
			}
			default:
				break;
			}
		}
	}

	return 0;
}

int xwasm::loader::load_export( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::EXPORT, _source ) >= 1 )
	{
		char buf[4096] = { 0 };

		for( std::uint32_t export_size = get_leb128_uint32( _source ); export_size > 0; export_size-- )
		{
			export_t exp;

			std::uint32_t len = get_leb128_uint32( _source );
			_source.read( buf, len );
			buf[len] = '\0';

			exp.name = buf;
			exp.desctype = ( desc_kind )_source.get();
			exp.descidx = get_leb128_uint32( _source );

			_module->_exports.push_back( exp );
		}
	}

	return 0;
}

int xwasm::loader::load_start( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::START, _source ) >= 1 )
	{
		_module->_start = get_leb128_uint32( _source );
	}

	return 0;
}

int xwasm::loader::load_element( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::ELEMENT, _source ) >= 1 )
	{
		for( std::uint32_t elem_size = get_leb128_uint32( _source ); elem_size > 0; elem_size-- )
		{
			element_t elem;

			elem.table = get_leb128_uint32( _source );

			if( _source.get() == opcode::I32_CONST )
			{
				elem.offset = get_leb128_int32( _source );
			}

			for( std::uint32_t init_size = get_leb128_uint32( _source ); init_size > 0; init_size-- )
			{
				elem.inits.push_back( get_leb128_uint32( _source ) );
			}

			_module->_elements.push_back( elem );
		}
	}

	return 0;
}

int xwasm::loader::load_code( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::CODE, _source ) >= 1 )
	{
		char buf[4096] = { 0 };

		std::uint32_t code_size = get_leb128_uint32( _source );
		for( std::uint32_t i = 0; i < code_size; ++i )
		{
			std::uint32_t body_size = get_leb128_uint32( _source );
			auto streampos = _source.tellg();
			func_t & func = _module->_functions[i];

			for( std::uint32_t local_size = get_leb128_uint32( _source ); local_size > 0; local_size-- )
			{
				std::uint32_t type_size = get_leb128_uint32( _source );
				type_kind type = ( type_kind )_source.get();
				while( type_size-- )
				{
					func.locals.push_back( type );
				}
			}

			streampos += body_size;
			std::uint64_t size = streampos - _source.tellg();
			func.codes.resize( size );
			_source.read( ( char * )func.codes.data(), func.codes.size() );
		}
	}

	return 0;
}

int xwasm::loader::load_data( module * _module, xwasm::stream & _source )
{
	if( skip_section( section_kind::DATA, _source ) >= 1 )
	{
		for( std::uint32_t data_size = get_leb128_uint32( _source ); data_size > 0; data_size-- )
		{
			data_t data;

			data.data = get_leb128_uint32( _source );

			if( _source.get() == opcode::I32_CONST )
			{
				data.offset = get_leb128_int32( _source );
			}

			_source.get();

			std::uint32_t init_size = get_leb128_uint32( _source );
			data.inits.resize( init_size );
			_source.read( ( char * )data.inits.data(), init_size );

			_module->_datas.push_back( data );
		}
	}

	return 0;
}
