#include "executor.h"

#include "errmsg.h"

#include "value.h"
#include "stream.h"
#include "endian.h"
#include "runtime.h"
#include "section_t.h"

inline void exec_unreachable( xwasm::executor * exec )
{
	( void )( exec );
}
inline void exec_nop( xwasm::executor * exec )
{
	( void )( exec );
}

inline void exec_block( xwasm::executor * exec );
inline void exec_loop( xwasm::executor * exec );
inline void exec_if( xwasm::executor * exec );
inline void exec_else( xwasm::executor * exec );

inline void exec_end( xwasm::executor * exec );

inline void exec_br( xwasm::executor * exec );
inline void exec_br_if( xwasm::executor * exec );
inline void exec_br_table( xwasm::executor * exec );
inline void exec_return( xwasm::executor * exec );
inline void exec_call( xwasm::executor * exec );
inline void exec_call_indirect( xwasm::executor * exec );

inline void exec_drop( xwasm::executor * exec );
inline void exec_select( xwasm::executor * exec );

inline void exec_get_local( xwasm::executor * exec );
inline void exec_set_local( xwasm::executor * exec );
inline void exec_tee_local( xwasm::executor * exec );
inline void exec_get_global( xwasm::executor * exec );
inline void exec_set_global( xwasm::executor * exec );

inline void exec_i32_load( xwasm::executor * exec );
inline void exec_i64_load( xwasm::executor * exec );
inline void exec_f32_load( xwasm::executor * exec );
inline void exec_f64_load( xwasm::executor * exec );
inline void exec_i32_load8_s( xwasm::executor * exec );
inline void exec_i32_load8_u( xwasm::executor * exec );
inline void exec_i32_load16_s( xwasm::executor * exec );
inline void exec_i32_load16_u( xwasm::executor * exec );
inline void exec_i64_load8_s( xwasm::executor * exec );
inline void exec_i64_load8_u( xwasm::executor * exec );
inline void exec_i64_load16_s( xwasm::executor * exec );
inline void exec_i64_load16_u( xwasm::executor * exec );
inline void exec_i64_load32_s( xwasm::executor * exec );
inline void exec_i64_load32_u( xwasm::executor * exec );
inline void exec_i32_store( xwasm::executor * exec );
inline void exec_i64_store( xwasm::executor * exec );
inline void exec_f32_store( xwasm::executor * exec );
inline void exec_f64_store( xwasm::executor * exec );
inline void exec_i32_store8( xwasm::executor * exec );
inline void exec_i32_store16( xwasm::executor * exec );
inline void exec_i64_store8( xwasm::executor * exec );
inline void exec_i64_store16( xwasm::executor * exec );
inline void exec_i64_store32( xwasm::executor * exec );
inline void exec_memory_size( xwasm::executor * exec );
inline void exec_memory_grow( xwasm::executor * exec );

inline void exec_i32_const( xwasm::executor * exec );
inline void exec_i64_const( xwasm::executor * exec );
inline void exec_f32_const( xwasm::executor * exec );
inline void exec_f64_const( xwasm::executor * exec );
inline void exec_i32_eqz( xwasm::executor * exec );
inline void exec_i32_eq( xwasm::executor * exec );
inline void exec_i32_ne( xwasm::executor * exec );
inline void exec_i32_lt_s( xwasm::executor * exec );
inline void exec_i32_lt_u( xwasm::executor * exec );
inline void exec_i32_gt_s( xwasm::executor * exec );
inline void exec_i32_gt_u( xwasm::executor * exec );
inline void exec_i32_le_s( xwasm::executor * exec );
inline void exec_i32_le_u( xwasm::executor * exec );
inline void exec_i32_ge_s( xwasm::executor * exec );
inline void exec_i32_ge_u( xwasm::executor * exec );
inline void exec_i64_eqz( xwasm::executor * exec );
inline void exec_i64_eq( xwasm::executor * exec );
inline void exec_i64_ne( xwasm::executor * exec );
inline void exec_i64_lt_s( xwasm::executor * exec );
inline void exec_i64_lt_u( xwasm::executor * exec );
inline void exec_i64_gt_s( xwasm::executor * exec );
inline void exec_i64_gt_u( xwasm::executor * exec );
inline void exec_i64_le_s( xwasm::executor * exec );
inline void exec_i64_le_u( xwasm::executor * exec );
inline void exec_i64_ge_s( xwasm::executor * exec );
inline void exec_i64_ge_u( xwasm::executor * exec );
inline void exec_f32_eq( xwasm::executor * exec );
inline void exec_f32_ne( xwasm::executor * exec );
inline void exec_f32_lt( xwasm::executor * exec );
inline void exec_f32_gt( xwasm::executor * exec );
inline void exec_f32_le( xwasm::executor * exec );
inline void exec_f32_ge( xwasm::executor * exec );
inline void exec_f64_eq( xwasm::executor * exec );
inline void exec_f64_ne( xwasm::executor * exec );
inline void exec_f64_lt( xwasm::executor * exec );
inline void exec_f64_gt( xwasm::executor * exec );
inline void exec_f64_le( xwasm::executor * exec );
inline void exec_f64_ge( xwasm::executor * exec );
inline void exec_i32_clz( xwasm::executor * exec );
inline void exec_i32_ctz( xwasm::executor * exec );
inline void exec_i32_popcnt( xwasm::executor * exec );
inline void exec_i32_add( xwasm::executor * exec );
inline void exec_i32_sub( xwasm::executor * exec );
inline void exec_i32_mul( xwasm::executor * exec );
inline void exec_i32_div_s( xwasm::executor * exec );
inline void exec_i32_div_u( xwasm::executor * exec );
inline void exec_i32_rem_s( xwasm::executor * exec );
inline void exec_i32_rem_u( xwasm::executor * exec );
inline void exec_i32_and( xwasm::executor * exec );
inline void exec_i32_or( xwasm::executor * exec );
inline void exec_i32_xor( xwasm::executor * exec );
inline void exec_i32_shl( xwasm::executor * exec );
inline void exec_i32_shr_s( xwasm::executor * exec );
inline void exec_i32_shr_u( xwasm::executor * exec );
inline void exec_i32_rotl( xwasm::executor * exec );
inline void exec_i32_rotr( xwasm::executor * exec );
inline void exec_i64_clz( xwasm::executor * exec );
inline void exec_i64_ctz( xwasm::executor * exec );
inline void exec_i64_popcnt( xwasm::executor * exec );
inline void exec_i64_add( xwasm::executor * exec );
inline void exec_i64_sub( xwasm::executor * exec );
inline void exec_i64_mul( xwasm::executor * exec );
inline void exec_i64_div_s( xwasm::executor * exec );
inline void exec_i64_div_u( xwasm::executor * exec );
inline void exec_i64_rem_s( xwasm::executor * exec );
inline void exec_i64_rem_u( xwasm::executor * exec );
inline void exec_i64_and( xwasm::executor * exec );
inline void exec_i64_or( xwasm::executor * exec );
inline void exec_i64_xor( xwasm::executor * exec );
inline void exec_i64_shl( xwasm::executor * exec );
inline void exec_i64_shr_s( xwasm::executor * exec );
inline void exec_i64_shr_u( xwasm::executor * exec );
inline void exec_i64_rotl( xwasm::executor * exec );
inline void exec_i64_rotr( xwasm::executor * exec );
inline void exec_f32_abs( xwasm::executor * exec );
inline void exec_f32_neg( xwasm::executor * exec );
inline void exec_f32_ceil( xwasm::executor * exec );
inline void exec_f32_floor( xwasm::executor * exec );
inline void exec_f32_trunc( xwasm::executor * exec );
inline void exec_f32_nearest( xwasm::executor * exec );
inline void exec_f32_sqrt( xwasm::executor * exec );
inline void exec_f32_add( xwasm::executor * exec );
inline void exec_f32_sub( xwasm::executor * exec );
inline void exec_f32_mul( xwasm::executor * exec );
inline void exec_f32_div( xwasm::executor * exec );
inline void exec_f32_min( xwasm::executor * exec );
inline void exec_f32_max( xwasm::executor * exec );
inline void exec_f32_copysign( xwasm::executor * exec );
inline void exec_f64_abs( xwasm::executor * exec );
inline void exec_f64_neg( xwasm::executor * exec );
inline void exec_f64_ceil( xwasm::executor * exec );
inline void exec_f64_floor( xwasm::executor * exec );
inline void exec_f64_trunc( xwasm::executor * exec );
inline void exec_f64_nearest( xwasm::executor * exec );
inline void exec_f64_sqrt( xwasm::executor * exec );
inline void exec_f64_add( xwasm::executor * exec );
inline void exec_f64_sub( xwasm::executor * exec );
inline void exec_f64_mul( xwasm::executor * exec );
inline void exec_f64_div( xwasm::executor * exec );
inline void exec_f64_min( xwasm::executor * exec );
inline void exec_f64_max( xwasm::executor * exec );
inline void exec_f64_copysign( xwasm::executor * exec );
inline void exec_i32_wrap_i64( xwasm::executor * exec );
inline void exec_i32_trunc_s_f32( xwasm::executor * exec );
inline void exec_i32_trunc_u_f32( xwasm::executor * exec );
inline void exec_i32_trunc_s_f64( xwasm::executor * exec );
inline void exec_i32_trunc_u_f64( xwasm::executor * exec );
inline void exec_i64_extend_s_i32( xwasm::executor * exec );
inline void exec_i64_extend_u_i32( xwasm::executor * exec );
inline void exec_i64_trunc_s_f32( xwasm::executor * exec );
inline void exec_i64_trunc_u_f32( xwasm::executor * exec );
inline void exec_i64_trunc_s_f64( xwasm::executor * exec );
inline void exec_i64_trunc_u_f64( xwasm::executor * exec );
inline void exec_f32_convert_s_i32( xwasm::executor * exec );
inline void exec_f32_convert_u_i32( xwasm::executor * exec );
inline void exec_f32_convert_s_i64( xwasm::executor * exec );
inline void exec_f32_convert_u_i64( xwasm::executor * exec );
inline void exec_f32_demote_f64( xwasm::executor * exec );
inline void exec_f64_convert_s_i32( xwasm::executor * exec );
inline void exec_f64_convert_u_i32( xwasm::executor * exec );
inline void exec_f64_convert_s_i64( xwasm::executor * exec );
inline void exec_f64_convert_u_i64( xwasm::executor * exec );
inline void exec_f64_promote_f32( xwasm::executor * exec );
inline void exec_i32_reinterpret_f32( xwasm::executor * exec );
inline void exec_i64_reinterpret_f64( xwasm::executor * exec );
inline void exec_f32_reinterpret_i32( xwasm::executor * exec );
inline void exec_f64_reinterpret_i64( xwasm::executor * exec );

namespace xwasm
{
	struct frame
	{
		xwasm::func_t * func;
		xwasm::runtime * runtime;
		std::uint64_t inst_index;
		std::uint64_t operand_index;
	};
}

struct xwasm::executor::private_p
{
	xwasm::sandbox * _sandbox;

	std::deque< xwasm::frame > _frames;

	xwasm::stream _stream;
	xwasm::func_t * _func;
	xwasm::runtime * _runtime;
	std::deque< xwasm::value > _operands;
};

xwasm::executor::executor( xwasm::sandbox * val )
	:_p( new private_p )
{
	_p->_sandbox = val;
}

xwasm::executor::~executor()
{
	delete _p;
}

int xwasm::executor::exec( xwasm::value & _result, xwasm::runtime * _runtime, xwasm::func_t * _func, const std::deque< xwasm::value > & _params )
{
	pushed();

	_p->_func = _func;
	_p->_runtime = _runtime;

	for( const auto & it : _params )
	{
		push( it );
	}

	if( _p->_func->cfunc )
	{
		typedef void( *cfunc_t )( xwasm::value *, xwasm::executor * );
		cfunc_t f = ( cfunc_t )_p->_func->codes.data();
		f( &_result, this );
	}
	else
	{
		_p->_stream.reset( _p->_func->codes.data(), _p->_func->codes.data() + _p->_func->codes.size() );

		xwasm::opcode op;
		while( !_p->_stream.eof() )
		{
			_p->_stream.read( ( char * )&op, sizeof( char ) );

			switch( op )
			{
			case xwasm::UNREACHABLE:
				exec_unreachable( this );
				break;
			case xwasm::NOP:
				exec_nop( this );
				break;
			case xwasm::BLOCK:
				exec_block( this );
				break;
			case xwasm::LOOP:
				exec_loop( this );
				break;
			case xwasm::IF:
				exec_if( this );
				break;
			case xwasm::ELSE:
				exec_else( this );
				break;
			case xwasm::END:
				exec_end( this );
				break;
			case xwasm::BR:
				exec_br( this );
				break;
			case xwasm::BR_IF:
				exec_br_if( this );
				break;
			case xwasm::BR_TABLE:
				exec_br_table( this );
				break;
			case xwasm::RETURN:
				exec_return( this );
				break;
			case xwasm::CALL:
				exec_call( this );
				break;
			case xwasm::CALL_INDIRECT:
				exec_call_indirect( this );
				break;
			case xwasm::DROP:
				exec_drop( this );
				break;
			case xwasm::SELECT:
				exec_select( this );
				break;
			case xwasm::GET_LOCAL:
				exec_get_local( this );
				break;
			case xwasm::SET_LOCAL:
				exec_set_local( this );
				break;
			case xwasm::TEE_LOCAL:
				exec_tee_local( this );
				break;
			case xwasm::GET_GLOBAL:
				exec_get_global( this );
				break;
			case xwasm::SET_GLOBAL:
				exec_set_global( this );
				break;
			case xwasm::I32_LOAD:
				exec_i32_load( this );
				break;
			case xwasm::I64_LOAD:
				exec_i64_load( this );
				break;
			case xwasm::F32_LOAD:
				exec_f32_load( this );
				break;
			case xwasm::F64_LOAD:
				exec_f64_load( this );
				break;
			case xwasm::I32_LOAD8_S:
				exec_i32_load8_s( this );
				break;
			case xwasm::I32_LOAD8_U:
				exec_i32_load8_u( this );
				break;
			case xwasm::I32_LOAD16_S:
				exec_i32_load16_s( this );
				break;
			case xwasm::I32_LOAD16_U:
				exec_i32_load16_u( this );
				break;
			case xwasm::I64_LOAD8_S:
				exec_i64_load8_s( this );
				break;
			case xwasm::I64_LOAD8_U:
				exec_i64_load8_u( this );
				break;
			case xwasm::I64_LOAD16_S:
				exec_i64_load16_s( this );
				break;
			case xwasm::I64_LOAD16_U:
				exec_i64_load16_u( this );
				break;
			case xwasm::I64_LOAD32_S:
				exec_i64_load32_s( this );
				break;
			case xwasm::I64_LOAD32_U:
				exec_i64_load32_u( this );
				break;
			case xwasm::I32_STORE:
				exec_i32_store( this );
				break;
			case xwasm::I64_STORE:
				exec_i64_store( this );
				break;
			case xwasm::F32_STORE:
				exec_f32_store( this );
				break;
			case xwasm::F64_STORE:
				exec_f64_store( this );
				break;
			case xwasm::I32_STORE8:
				exec_i32_store8( this );
				break;
			case xwasm::I32_STORE16:
				exec_i32_store16( this );
				break;
			case xwasm::I64_STORE8:
				exec_i64_store8( this );
				break;
			case xwasm::I64_STORE16:
				exec_i64_store16( this );
				break;
			case xwasm::I64_STORE32:
				exec_i64_store32( this );
				break;
			case xwasm::MEMORY_SIZE:
				exec_memory_size( this );
				break;
			case xwasm::MEMORY_GROW:
				exec_memory_grow( this );
				break;
			case xwasm::I32_CONST:
				exec_i32_const( this );
				break;
			case xwasm::I64_CONST:
				exec_i64_const( this );
				break;
			case xwasm::F32_CONST:
				exec_f32_const( this );
				break;
			case xwasm::F64_CONST:
				exec_f64_const( this );
				break;
			case xwasm::I32_EQZ:
				exec_i32_eqz( this );
				break;
			case xwasm::I32_EQ:
				exec_i32_eq( this );
				break;
			case xwasm::I32_NE:
				exec_i32_ne( this );
				break;
			case xwasm::I32_LT_S:
				exec_i32_lt_s( this );
				break;
			case xwasm::I32_LT_U:
				exec_i32_lt_u( this );
				break;
			case xwasm::I32_GT_S:
				exec_i32_gt_s( this );
				break;
			case xwasm::I32_GT_U:
				exec_i32_gt_u( this );
				break;
			case xwasm::I32_LE_S:
				exec_i32_le_s( this );
				break;
			case xwasm::I32_LE_U:
				exec_i32_le_u( this );
				break;
			case xwasm::I32_GE_S:
				exec_i32_ge_s( this );
				break;
			case xwasm::I32_GE_U:
				exec_i32_ge_u( this );
				break;
			case xwasm::I64_EQZ:
				exec_i64_eqz( this );
				break;
			case xwasm::I64_EQ:
				exec_i64_eq( this );
				break;
			case xwasm::I64_NE:
				exec_i64_ne( this );
				break;
			case xwasm::I64_LT_S:
				exec_i64_lt_s( this );
				break;
			case xwasm::I64_LT_U:
				exec_i64_lt_u( this );
				break;
			case xwasm::I64_GT_S:
				exec_i64_gt_s( this );
				break;
			case xwasm::I64_GT_U:
				exec_i64_gt_u( this );
				break;
			case xwasm::I64_LE_S:
				exec_i64_le_s( this );
				break;
			case xwasm::I64_LE_U:
				exec_i64_le_u( this );
				break;
			case xwasm::I64_GE_S:
				exec_i64_ge_s( this );
				break;
			case xwasm::I64_GE_U:
				exec_i64_ge_u( this );
				break;
			case xwasm::F32_EQ:
				exec_f32_eq( this );
				break;
			case xwasm::F32_NE:
				exec_f32_ne( this );
				break;
			case xwasm::F32_LT:
				exec_f32_lt( this );
				break;
			case xwasm::F32_GT:
				exec_f32_gt( this );
				break;
			case xwasm::F32_LE:
				exec_f32_le( this );
				break;
			case xwasm::F32_GE:
				exec_f32_ge( this );
				break;
			case xwasm::F64_EQ:
				exec_f64_eq( this );
				break;
			case xwasm::F64_NE:
				exec_f64_ne( this );
				break;
			case xwasm::F64_LT:
				exec_f64_lt( this );
				break;
			case xwasm::F64_GT:
				exec_f64_gt( this );
				break;
			case xwasm::F64_LE:
				exec_f64_le( this );
				break;
			case xwasm::F64_GE:
				exec_f64_ge( this );
				break;
			case xwasm::I32_CLZ:
				exec_i32_clz( this );
				break;
			case xwasm::I32_CTZ:
				exec_i32_ctz( this );
				break;
			case xwasm::I32_POPCNT:
				exec_i32_popcnt( this );
				break;
			case xwasm::I32_ADD:
				exec_i32_add( this );
				break;
			case xwasm::I32_SUB:
				exec_i32_sub( this );
				break;
			case xwasm::I32_MUL:
				exec_i32_mul( this );
				break;
			case xwasm::I32_DIV_S:
				exec_i32_div_s( this );
				break;
			case xwasm::I32_DIV_U:
				exec_i32_div_u( this );
				break;
			case xwasm::I32_REM_S:
				exec_i32_rem_s( this );
				break;
			case xwasm::I32_REM_U:
				exec_i32_rem_u( this );
				break;
			case xwasm::I32_AND:
				exec_i32_and( this );
				break;
			case xwasm::I32_OR:
				exec_i32_or( this );
				break;
			case xwasm::I32_XOR:
				exec_i32_xor( this );
				break;
			case xwasm::I32_SHL:
				exec_i32_shl( this );
				break;
			case xwasm::I32_SHR_S:
				exec_i32_shr_s( this );
				break;
			case xwasm::I32_SHR_U:
				exec_i32_shr_u( this );
				break;
			case xwasm::I32_ROTL:
				exec_i32_rotl( this );
				break;
			case xwasm::I32_ROTR:
				exec_i32_rotr( this );
				break;
			case xwasm::I64_CLZ:
				exec_i64_clz( this );
				break;
			case xwasm::I64_CTZ:
				exec_i64_ctz( this );
				break;
			case xwasm::I64_POPCNT:
				exec_i64_popcnt( this );
				break;
			case xwasm::I64_ADD:
				exec_i64_add( this );
				break;
			case xwasm::I64_SUB:
				exec_i64_sub( this );
				break;
			case xwasm::I64_MUL:
				exec_i64_mul( this );
				break;
			case xwasm::I64_DIV_S:
				exec_i64_div_s( this );
				break;
			case xwasm::I64_DIV_U:
				exec_i64_div_u( this );
				break;
			case xwasm::I64_REM_S:
				exec_i64_rem_s( this );
				break;
			case xwasm::I64_REM_U:
				exec_i64_rem_u( this );
				break;
			case xwasm::I64_AND:
				exec_i64_and( this );
				break;
			case xwasm::I64_OR:
				exec_i64_or( this );
				break;
			case xwasm::I64_XOR:
				exec_i64_xor( this );
				break;
			case xwasm::I64_SHL:
				exec_i64_shl( this );
				break;
			case xwasm::I64_SHR_S:
				exec_i64_shr_s( this );
				break;
			case xwasm::I64_SHR_U:
				exec_i64_shr_u( this );
				break;
			case xwasm::I64_ROTL:
				exec_i64_rotl( this );
				break;
			case xwasm::I64_ROTR:
				exec_i64_rotr( this );
				break;
			case xwasm::F32_ABS:
				exec_f32_abs( this );
				break;
			case xwasm::F32_NEG:
				exec_f32_neg( this );
				break;
			case xwasm::F32_CEIL:
				exec_f32_ceil( this );
				break;
			case xwasm::F32_FLOOR:
				exec_f32_floor( this );
				break;
			case xwasm::F32_TRUNC:
				exec_f32_trunc( this );
				break;
			case xwasm::F32_NEAREST:
				exec_f32_nearest( this );
				break;
			case xwasm::F32_SQRT:
				exec_f32_sqrt( this );
				break;
			case xwasm::F32_ADD:
				exec_f32_add( this );
				break;
			case xwasm::F32_SUB:
				exec_f32_sub( this );
				break;
			case xwasm::F32_MUL:
				exec_f32_mul( this );
				break;
			case xwasm::F32_DIV:
				exec_f32_div( this );
				break;
			case xwasm::F32_MIN:
				exec_f32_min( this );
				break;
			case xwasm::F32_MAX:
				exec_f32_max( this );
				break;
			case xwasm::F32_COPYSIGN:
				exec_f32_copysign( this );
				break;
			case xwasm::F64_ABS:
				exec_f64_abs( this );
				break;
			case xwasm::F64_NEG:
				exec_f64_neg( this );
				break;
			case xwasm::F64_CEIL:
				exec_f64_ceil( this );
				break;
			case xwasm::F64_FLOOR:
				exec_f64_floor( this );
				break;
			case xwasm::F64_TRUNC:
				exec_f64_trunc( this );
				break;
			case xwasm::F64_NEAREST:
				exec_f64_nearest( this );
				break;
			case xwasm::F64_SQRT:
				exec_f64_sqrt( this );
				break;
			case xwasm::F64_ADD:
				exec_f64_add( this );
				break;
			case xwasm::F64_SUB:
				exec_f64_sub( this );
				break;
			case xwasm::F64_MUL:
				exec_f64_mul( this );
				break;
			case xwasm::F64_DIV:
				exec_f64_div( this );
				break;
			case xwasm::F64_MIN:
				exec_f64_min( this );
				break;
			case xwasm::F64_MAX:
				exec_f64_max( this );
				break;
			case xwasm::F64_COPYSIGN:
				exec_f64_copysign( this );
				break;
			case xwasm::I32_WRAP_I64:
				exec_i32_wrap_i64( this );
				break;
			case xwasm::I32_TRUNC_S_F32:
				exec_i32_trunc_s_f32( this );
				break;
			case xwasm::I32_TRUNC_U_F32:
				exec_i32_trunc_u_f32( this );
				break;
			case xwasm::I32_TRUNC_S_F64:
				exec_i32_trunc_s_f64( this );
				break;
			case xwasm::I32_TRUNC_U_F64:
				exec_i32_trunc_u_f64( this );
				break;
			case xwasm::I64_EXTEND_S_I32:
				exec_i64_extend_s_i32( this );
				break;
			case xwasm::I64_EXTEND_U_I32:
				exec_i64_extend_u_i32( this );
				break;
			case xwasm::I64_TRUNC_S_F32:
				exec_i64_trunc_s_f32( this );
				break;
			case xwasm::I64_TRUNC_U_F32:
				exec_i64_trunc_u_f32( this );
				break;
			case xwasm::I64_TRUNC_S_F64:
				exec_i64_trunc_s_f64( this );
				break;
			case xwasm::I64_TRUNC_U_F64:
				exec_i64_trunc_u_f64( this );
				break;
			case xwasm::F32_CONVERT_S_I32:
				exec_f32_convert_s_i32( this );
				break;
			case xwasm::F32_CONVERT_U_I32:
				exec_f32_convert_u_i32( this );
				break;
			case xwasm::F32_CONVERT_S_I64:
				exec_f32_convert_s_i64( this );
				break;
			case xwasm::F32_CONVERT_U_I64:
				exec_f32_convert_u_i64( this );
				break;
			case xwasm::F32_DEMOTE_F64:
				exec_f32_demote_f64( this );
				break;
			case xwasm::F64_CONVERT_S_I32:
				exec_f64_convert_s_i32( this );
				break;
			case xwasm::F64_CONVERT_U_I32:
				exec_f64_convert_u_i32( this );
				break;
			case xwasm::F64_CONVERT_S_I64:
				exec_f64_convert_s_i64( this );
				break;
			case xwasm::F64_CONVERT_U_I64:
				exec_f64_convert_u_i64( this );
				break;
			case xwasm::F64_PROMOTE_F32:
				exec_f64_promote_f32( this );
				break;
			case xwasm::I32_REINTERPRET_F32:
				exec_i32_reinterpret_f32( this );
				break;
			case xwasm::I64_REINTERPRET_F64:
				exec_i64_reinterpret_f64( this );
				break;
			case xwasm::F32_REINTERPRET_I32:
				exec_f32_reinterpret_i32( this );
				break;
			case xwasm::F64_REINTERPRET_I64:
				exec_f64_reinterpret_i64( this );
				break;
			default:
				return ERR_INST_CODE;
				break;
			}
		}

		if( ! _p->_runtime->_module.type_at( _func->typeidx )->results.empty() )
		{
			_result = pop();
		}
	}

	poped();

	return 0;
}

xwasm::func_t * xwasm::executor::cur_func() const
{
	return _p->_func;
}

xwasm::stream * xwasm::executor::cur_stream() const
{
	return &_p->_stream;
}

xwasm::runtime * xwasm::executor::cur_runtime() const
{
	return _p->_runtime;
}

xwasm::sandbox * xwasm::executor::cur_sandbox() const
{
	return _p->_sandbox;
}

void xwasm::executor::push( xwasm::value val )
{
	_p->_operands.push_back( val );
}

xwasm::value xwasm::executor::pop()
{
	xwasm::value result;

	if( !_p->_operands.empty() )
	{
		result = _p->_operands.back();
		_p->_operands.pop_back();
	}

	return result;
}

void xwasm::executor::pushed()
{
	xwasm::frame frame;

	frame.func = _p->_func;
	frame.runtime = _p->_runtime;
	frame.inst_index = _p->_stream.tellg();
	frame.operand_index = _p->_operands.size();

	_p->_frames.emplace_back( frame );
}

void xwasm::executor::poped()
{
	xwasm::frame frame = _p->_frames.back();

	_p->_func = frame.func;
	_p->_runtime = frame.runtime;
	_p->_stream.reset( _p->_func->codes.data(), _p->_func->codes.data() + _p->_func->codes.size() );
	_p->_stream.seekg( frame.inst_index, xwasm::stream::beg );
	_p->_operands.erase( _p->_operands.begin() + frame.operand_index, _p->_operands.end() );

	_p->_frames.pop_back();
}
