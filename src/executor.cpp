#include "executor.h"

#include "errmsg.h"

#include "value.h"
#include "stream.h"
#include "section_t.h"

struct frame
{
	xwasm::func_t * func;
	std::uint64_t inst_index;
	std::uint64_t operand_index;
};

struct xwasm::executor::private_p
{
	xwasm::sandbox * _sandbox;

	std::deque< frame > _frames;

	xwasm::stream _insts;
	xwasm::func_t * _func;
	std::deque< xwasm::value > _operands;
};

inline void exec_unreachable( xwasm::executor::private_p * _p )
{

}
inline void exec_nop( xwasm::executor::private_p * _p )
{

}

inline void exec_block( xwasm::executor::private_p * _p );
inline void exec_loop( xwasm::executor::private_p * _p );
inline void exec_if( xwasm::executor::private_p * _p );
inline void exec_else( xwasm::executor::private_p * _p );

inline void exec_end( xwasm::executor::private_p * _p );

inline void exec_br( xwasm::executor::private_p * _p );
inline void exec_br_if( xwasm::executor::private_p * _p );
inline void exec_br_table( xwasm::executor::private_p * _p );
inline void exec_return( xwasm::executor::private_p * _p );
inline void exec_call( xwasm::executor::private_p * _p );
inline void exec_call_indirect( xwasm::executor::private_p * _p );

inline void exec_drop( xwasm::executor::private_p * _p );
inline void exec_select( xwasm::executor::private_p * _p );

inline void exec_get_local( xwasm::executor::private_p * _p );
inline void exec_set_local( xwasm::executor::private_p * _p );
inline void exec_tee_local( xwasm::executor::private_p * _p );
inline void exec_get_global( xwasm::executor::private_p * _p );
inline void exec_set_global( xwasm::executor::private_p * _p );

inline void exec_i32_load( xwasm::executor::private_p * _p );
inline void exec_i64_load( xwasm::executor::private_p * _p );
inline void exec_f32_load( xwasm::executor::private_p * _p );
inline void exec_f64_load( xwasm::executor::private_p * _p );
inline void exec_i32_load8_s( xwasm::executor::private_p * _p );
inline void exec_i32_load8_u( xwasm::executor::private_p * _p );
inline void exec_i32_load16_s( xwasm::executor::private_p * _p );
inline void exec_i32_load16_u( xwasm::executor::private_p * _p );
inline void exec_i64_load8_s( xwasm::executor::private_p * _p );
inline void exec_i64_load8_u( xwasm::executor::private_p * _p );
inline void exec_i64_load16_s( xwasm::executor::private_p * _p );
inline void exec_i64_load16_u( xwasm::executor::private_p * _p );
inline void exec_i64_load32_s( xwasm::executor::private_p * _p );
inline void exec_i64_load32_u( xwasm::executor::private_p * _p );
inline void exec_i32_store( xwasm::executor::private_p * _p );
inline void exec_i64_store( xwasm::executor::private_p * _p );
inline void exec_f32_store( xwasm::executor::private_p * _p );
inline void exec_f64_store( xwasm::executor::private_p * _p );
inline void exec_i32_store8( xwasm::executor::private_p * _p );
inline void exec_i32_store16( xwasm::executor::private_p * _p );
inline void exec_i64_store8( xwasm::executor::private_p * _p );
inline void exec_i64_store16( xwasm::executor::private_p * _p );
inline void exec_i64_store32( xwasm::executor::private_p * _p );
inline void exec_memory_size( xwasm::executor::private_p * _p );
inline void exec_memory_grow( xwasm::executor::private_p * _p );

inline void exec_i32_const( xwasm::executor::private_p * _p );
inline void exec_i64_const( xwasm::executor::private_p * _p );
inline void exec_f32_const( xwasm::executor::private_p * _p );
inline void exec_f64_const( xwasm::executor::private_p * _p );
inline void exec_i32_eqz( xwasm::executor::private_p * _p );
inline void exec_i32_eq( xwasm::executor::private_p * _p );
inline void exec_i32_ne( xwasm::executor::private_p * _p );
inline void exec_i32_lt_s( xwasm::executor::private_p * _p );
inline void exec_i32_lt_u( xwasm::executor::private_p * _p );
inline void exec_i32_gt_s( xwasm::executor::private_p * _p );
inline void exec_i32_gt_u( xwasm::executor::private_p * _p );
inline void exec_i32_le_s( xwasm::executor::private_p * _p );
inline void exec_i32_le_u( xwasm::executor::private_p * _p );
inline void exec_i32_ge_s( xwasm::executor::private_p * _p );
inline void exec_i32_ge_u( xwasm::executor::private_p * _p );
inline void exec_i64_eqz( xwasm::executor::private_p * _p );
inline void exec_i64_eq( xwasm::executor::private_p * _p );
inline void exec_i64_ne( xwasm::executor::private_p * _p );
inline void exec_i64_lt_s( xwasm::executor::private_p * _p );
inline void exec_i64_lt_u( xwasm::executor::private_p * _p );
inline void exec_i64_gt_s( xwasm::executor::private_p * _p );
inline void exec_i64_gt_u( xwasm::executor::private_p * _p );
inline void exec_i64_le_s( xwasm::executor::private_p * _p );
inline void exec_i64_le_u( xwasm::executor::private_p * _p );
inline void exec_i64_ge_s( xwasm::executor::private_p * _p );
inline void exec_i64_ge_u( xwasm::executor::private_p * _p );
inline void exec_f32_eq( xwasm::executor::private_p * _p );
inline void exec_f32_ne( xwasm::executor::private_p * _p );
inline void exec_f32_lt( xwasm::executor::private_p * _p );
inline void exec_f32_gt( xwasm::executor::private_p * _p );
inline void exec_f32_le( xwasm::executor::private_p * _p );
inline void exec_f32_ge( xwasm::executor::private_p * _p );
inline void exec_f64_eq( xwasm::executor::private_p * _p );
inline void exec_f64_ne( xwasm::executor::private_p * _p );
inline void exec_f64_lt( xwasm::executor::private_p * _p );
inline void exec_f64_gt( xwasm::executor::private_p * _p );
inline void exec_f64_le( xwasm::executor::private_p * _p );
inline void exec_f64_ge( xwasm::executor::private_p * _p );
inline void exec_i32_clz( xwasm::executor::private_p * _p );
inline void exec_i32_ctz( xwasm::executor::private_p * _p );
inline void exec_i32_popcnt( xwasm::executor::private_p * _p );
inline void exec_i32_add( xwasm::executor::private_p * _p );
inline void exec_i32_sub( xwasm::executor::private_p * _p );
inline void exec_i32_mul( xwasm::executor::private_p * _p );
inline void exec_i32_div_s( xwasm::executor::private_p * _p );
inline void exec_i32_div_u( xwasm::executor::private_p * _p );
inline void exec_i32_rem_s( xwasm::executor::private_p * _p );
inline void exec_i32_rem_u( xwasm::executor::private_p * _p );
inline void exec_i32_and( xwasm::executor::private_p * _p );
inline void exec_i32_or( xwasm::executor::private_p * _p );
inline void exec_i32_xor( xwasm::executor::private_p * _p );
inline void exec_i32_shl( xwasm::executor::private_p * _p );
inline void exec_i32_shr_s( xwasm::executor::private_p * _p );
inline void exec_i32_shr_u( xwasm::executor::private_p * _p );
inline void exec_i32_rotl( xwasm::executor::private_p * _p );
inline void exec_i32_rotr( xwasm::executor::private_p * _p );
inline void exec_i64_clz( xwasm::executor::private_p * _p );
inline void exec_i64_ctz( xwasm::executor::private_p * _p );
inline void exec_i64_popcnt( xwasm::executor::private_p * _p );
inline void exec_i64_add( xwasm::executor::private_p * _p );
inline void exec_i64_sub( xwasm::executor::private_p * _p );
inline void exec_i64_mul( xwasm::executor::private_p * _p );
inline void exec_i64_div_s( xwasm::executor::private_p * _p );
inline void exec_i64_div_u( xwasm::executor::private_p * _p );
inline void exec_i64_rem_s( xwasm::executor::private_p * _p );
inline void exec_i64_rem_u( xwasm::executor::private_p * _p );
inline void exec_i64_and( xwasm::executor::private_p * _p );
inline void exec_i64_or( xwasm::executor::private_p * _p );
inline void exec_i64_xor( xwasm::executor::private_p * _p );
inline void exec_i64_shl( xwasm::executor::private_p * _p );
inline void exec_i64_shr_s( xwasm::executor::private_p * _p );
inline void exec_i64_shr_u( xwasm::executor::private_p * _p );
inline void exec_i64_rotl( xwasm::executor::private_p * _p );
inline void exec_i64_rotr( xwasm::executor::private_p * _p );
inline void exec_f32_abs( xwasm::executor::private_p * _p );
inline void exec_f32_neg( xwasm::executor::private_p * _p );
inline void exec_f32_ceil( xwasm::executor::private_p * _p );
inline void exec_f32_floor( xwasm::executor::private_p * _p );
inline void exec_f32_trunc( xwasm::executor::private_p * _p );
inline void exec_f32_nearest( xwasm::executor::private_p * _p );
inline void exec_f32_sqrt( xwasm::executor::private_p * _p );
inline void exec_f32_add( xwasm::executor::private_p * _p );
inline void exec_f32_sub( xwasm::executor::private_p * _p );
inline void exec_f32_mul( xwasm::executor::private_p * _p );
inline void exec_f32_div( xwasm::executor::private_p * _p );
inline void exec_f32_min( xwasm::executor::private_p * _p );
inline void exec_f32_max( xwasm::executor::private_p * _p );
inline void exec_f32_copysign( xwasm::executor::private_p * _p );
inline void exec_f64_abs( xwasm::executor::private_p * _p );
inline void exec_f64_neg( xwasm::executor::private_p * _p );
inline void exec_f64_ceil( xwasm::executor::private_p * _p );
inline void exec_f64_floor( xwasm::executor::private_p * _p );
inline void exec_f64_trunc( xwasm::executor::private_p * _p );
inline void exec_f64_nearest( xwasm::executor::private_p * _p );
inline void exec_f64_sqrt( xwasm::executor::private_p * _p );
inline void exec_f64_add( xwasm::executor::private_p * _p );
inline void exec_f64_sub( xwasm::executor::private_p * _p );
inline void exec_f64_mul( xwasm::executor::private_p * _p );
inline void exec_f64_div( xwasm::executor::private_p * _p );
inline void exec_f64_min( xwasm::executor::private_p * _p );
inline void exec_f64_max( xwasm::executor::private_p * _p );
inline void exec_f64_copysign( xwasm::executor::private_p * _p );
inline void exec_i32_wrap_i64( xwasm::executor::private_p * _p );
inline void exec_i32_trunc_s_f32( xwasm::executor::private_p * _p );
inline void exec_i32_trunc_u_f32( xwasm::executor::private_p * _p );
inline void exec_i32_trunc_s_f64( xwasm::executor::private_p * _p );
inline void exec_i32_trunc_u_f64( xwasm::executor::private_p * _p );
inline void exec_i64_extend_s_i32( xwasm::executor::private_p * _p );
inline void exec_i64_extend_u_i32( xwasm::executor::private_p * _p );
inline void exec_i64_trunc_s_f32( xwasm::executor::private_p * _p );
inline void exec_i64_trunc_u_f32( xwasm::executor::private_p * _p );
inline void exec_i64_trunc_s_f64( xwasm::executor::private_p * _p );
inline void exec_i64_trunc_u_f64( xwasm::executor::private_p * _p );
inline void exec_f32_convert_s_i32( xwasm::executor::private_p * _p );
inline void exec_f32_convert_u_i32( xwasm::executor::private_p * _p );
inline void exec_f32_convert_s_i64( xwasm::executor::private_p * _p );
inline void exec_f32_convert_u_i64( xwasm::executor::private_p * _p );
inline void exec_f32_demote_f64( xwasm::executor::private_p * _p );
inline void exec_f64_convert_s_i32( xwasm::executor::private_p * _p );
inline void exec_f64_convert_u_i32( xwasm::executor::private_p * _p );
inline void exec_f64_convert_s_i64( xwasm::executor::private_p * _p );
inline void exec_f64_convert_u_i64( xwasm::executor::private_p * _p );
inline void exec_f64_promote_f32( xwasm::executor::private_p * _p );
inline void exec_i32_reinterpret_f32( xwasm::executor::private_p * _p );
inline void exec_i64_reinterpret_f64( xwasm::executor::private_p * _p );
inline void exec_f32_reinterpret_i32( xwasm::executor::private_p * _p );
inline void exec_f64_reinterpret_i64( xwasm::executor::private_p * _p );


xwasm::executor::executor( xwasm::sandbox * val )
	:_p( new private_p )
{
	_p->_sandbox = val;
}

xwasm::executor::~executor()
{
	delete _p;
}

int xwasm::executor::exec( xwasm::value & result, func_t * func, const std::deque< xwasm::value > & params )
{
	_p->_func = func;
	_p->_insts.reset( func->codes.data(), func->codes.data() + func->codes.size() );

	for( const auto & it : params )
	{
		push( it );
	}

	xwasm::opcode op;
	while( !_p->_insts.eof() )
	{
		_p->_insts.read( op );

		switch( op )
		{
		case xwasm::UNREACHABLE:
			exec_unreachable( _p );
			break;
		case xwasm::NOP:
			exec_nop( _p );
			break;
		case xwasm::BLOCK:
			exec_block( _p );
			break;
		case xwasm::LOOP:
			exec_loop( _p );
			break;
		case xwasm::IF:
			exec_if( _p );
			break;
		case xwasm::ELSE:
			exec_else( _p );
			break;
		case xwasm::END:
			exec_end( _p );
			break;
		case xwasm::BR:
			exec_br( _p );
			break;
		case xwasm::BR_IF:
			exec_br_if( _p );
			break;
		case xwasm::BR_TABLE:
			exec_br_table( _p );
			break;
		case xwasm::RETURN:
			exec_return( _p );
			break;
		case xwasm::CALL:
			exec_call( _p );
			break;
		case xwasm::CALL_INDIRECT:
			exec_call_indirect( _p );
			break;
		case xwasm::DROP:
			exec_drop( _p );
			break;
		case xwasm::SELECT:
			exec_select( _p );
			break;
		case xwasm::GET_LOCAL:
			exec_get_local( _p );
			break;
		case xwasm::SET_LOCAL:
			exec_set_local( _p );
			break;
		case xwasm::TEE_LOCAL:
			exec_tee_local( _p );
			break;
		case xwasm::GET_GLOBAL:
			exec_get_global( _p );
			break;
		case xwasm::SET_GLOBAL:
			exec_set_global( _p );
			break;
		case xwasm::I32_LOAD:
			exec_i32_load( _p );
			break;
		case xwasm::I64_LOAD:
			exec_i64_load( _p );
			break;
		case xwasm::F32_LOAD:
			exec_f32_load( _p );
			break;
		case xwasm::F64_LOAD:
			exec_f64_load( _p );
			break;
		case xwasm::I32_LOAD8_S:
			exec_i32_load8_s( _p );
			break;
		case xwasm::I32_LOAD8_U:
			exec_i32_load8_u( _p );
			break;
		case xwasm::I32_LOAD16_S:
			exec_i32_load16_s( _p );
			break;
		case xwasm::I32_LOAD16_U:
			exec_i32_load16_u( _p );
			break;
		case xwasm::I64_LOAD8_S:
			exec_i64_load8_s( _p );
			break;
		case xwasm::I64_LOAD8_U:
			exec_i64_load8_u( _p );
			break;
		case xwasm::I64_LOAD16_S:
			exec_i64_load16_s( _p );
			break;
		case xwasm::I64_LOAD16_U:
			exec_i64_load16_u( _p );
			break;
		case xwasm::I64_LOAD32_S:
			exec_i64_load32_s( _p );
			break;
		case xwasm::I64_LOAD32_U:
			exec_i64_load32_u( _p );
			break;
		case xwasm::I32_STORE:
			exec_i32_store( _p );
			break;
		case xwasm::I64_STORE:
			exec_i64_store( _p );
			break;
		case xwasm::F32_STORE:
			exec_f32_store( _p );
			break;
		case xwasm::F64_STORE:
			exec_f64_store( _p );
			break;
		case xwasm::I32_STORE8:
			exec_i32_store8( _p );
			break;
		case xwasm::I32_STORE16:
			exec_i32_store16( _p );
			break;
		case xwasm::I64_STORE8:
			exec_i64_store8( _p );
			break;
		case xwasm::I64_STORE16:
			exec_i64_store16( _p );
			break;
		case xwasm::I64_STORE32:
			exec_i64_store32( _p );
			break;
		case xwasm::MEMORY_SIZE:
			exec_memory_size( _p );
			break;
		case xwasm::MEMORY_GROW:
			exec_memory_grow( _p );
			break;
		case xwasm::I32_CONST:
			exec_i32_const( _p );
			break;
		case xwasm::I64_CONST:
			exec_i64_const( _p );
			break;
		case xwasm::F32_CONST:
			exec_f32_const( _p );
			break;
		case xwasm::F64_CONST:
			exec_f64_const( _p );
			break;
		case xwasm::I32_EQZ:
			exec_i32_eqz( _p );
			break;
		case xwasm::I32_EQ:
			exec_i32_eq( _p );
			break;
		case xwasm::I32_NE:
			exec_i32_ne( _p );
			break;
		case xwasm::I32_LT_S:
			exec_i32_lt_s( _p );
			break;
		case xwasm::I32_LT_U:
			exec_i32_lt_u( _p );
			break;
		case xwasm::I32_GT_S:
			exec_i32_gt_s( _p );
			break;
		case xwasm::I32_GT_U:
			exec_i32_gt_u( _p );
			break;
		case xwasm::I32_LE_S:
			exec_i32_le_s( _p );
			break;
		case xwasm::I32_LE_U:
			exec_i32_le_u( _p );
			break;
		case xwasm::I32_GE_S:
			exec_i32_ge_s( _p );
			break;
		case xwasm::I32_GE_U:
			exec_i32_ge_u( _p );
			break;
		case xwasm::I64_EQZ:
			exec_i64_eqz( _p );
			break;
		case xwasm::I64_EQ:
			exec_i64_eq( _p );
			break;
		case xwasm::I64_NE:
			exec_i64_ne( _p );
			break;
		case xwasm::I64_LT_S:
			exec_i64_lt_s( _p );
			break;
		case xwasm::I64_LT_U:
			exec_i64_lt_u( _p );
			break;
		case xwasm::I64_GT_S:
			exec_i64_gt_s( _p );
			break;
		case xwasm::I64_GT_U:
			exec_i64_gt_u( _p );
			break;
		case xwasm::I64_LE_S:
			exec_i64_le_s( _p );
			break;
		case xwasm::I64_LE_U:
			exec_i64_le_u( _p );
			break;
		case xwasm::I64_GE_S:
			exec_i64_ge_s( _p );
			break;
		case xwasm::I64_GE_U:
			exec_i64_ge_u( _p );
			break;
		case xwasm::F32_EQ:
			exec_f32_eq( _p );
			break;
		case xwasm::F32_NE:
			exec_f32_ne( _p );
			break;
		case xwasm::F32_LT:
			exec_f32_lt( _p );
			break;
		case xwasm::F32_GT:
			exec_f32_gt( _p );
			break;
		case xwasm::F32_LE:
			exec_f32_le( _p );
			break;
		case xwasm::F32_GE:
			exec_f32_ge( _p );
			break;
		case xwasm::F64_EQ:
			exec_f64_eq( _p );
			break;
		case xwasm::F64_NE:
			exec_f64_ne( _p );
			break;
		case xwasm::F64_LT:
			exec_f64_lt( _p );
			break;
		case xwasm::F64_GT:
			exec_f64_gt( _p );
			break;
		case xwasm::F64_LE:
			exec_f64_le( _p );
			break;
		case xwasm::F64_GE:
			exec_f64_ge( _p );
			break;
		case xwasm::I32_CLZ:
			exec_i32_clz( _p );
			break;
		case xwasm::I32_CTZ:
			exec_i32_ctz( _p );
			break;
		case xwasm::I32_POPCNT:
			exec_i32_popcnt( _p );
			break;
		case xwasm::I32_ADD:
			exec_i32_add( _p );
			break;
		case xwasm::I32_SUB:
			exec_i32_sub( _p );
			break;
		case xwasm::I32_MUL:
			exec_i32_mul( _p );
			break;
		case xwasm::I32_DIV_S:
			exec_i32_div_s( _p );
			break;
		case xwasm::I32_DIV_U:
			exec_i32_div_u( _p );
			break;
		case xwasm::I32_REM_S:
			exec_i32_rem_s( _p );
			break;
		case xwasm::I32_REM_U:
			exec_i32_rem_u( _p );
			break;
		case xwasm::I32_AND:
			exec_i32_and( _p );
			break;
		case xwasm::I32_OR:
			exec_i32_or( _p );
			break;
		case xwasm::I32_XOR:
			exec_i32_xor( _p );
			break;
		case xwasm::I32_SHL:
			exec_i32_shl( _p );
			break;
		case xwasm::I32_SHR_S:
			exec_i32_shr_s( _p );
			break;
		case xwasm::I32_SHR_U:
			exec_i32_shr_u( _p );
			break;
		case xwasm::I32_ROTL:
			exec_i32_rotl( _p );
			break;
		case xwasm::I32_ROTR:
			exec_i32_rotr( _p );
			break;
		case xwasm::I64_CLZ:
			exec_i64_clz( _p );
			break;
		case xwasm::I64_CTZ:
			exec_i64_ctz( _p );
			break;
		case xwasm::I64_POPCNT:
			exec_i64_popcnt( _p );
			break;
		case xwasm::I64_ADD:
			exec_i64_add( _p );
			break;
		case xwasm::I64_SUB:
			exec_i64_sub( _p );
			break;
		case xwasm::I64_MUL:
			exec_i64_mul( _p );
			break;
		case xwasm::I64_DIV_S:
			exec_i64_div_s( _p );
			break;
		case xwasm::I64_DIV_U:
			exec_i64_div_u( _p );
			break;
		case xwasm::I64_REM_S:
			exec_i64_rem_s( _p );
			break;
		case xwasm::I64_REM_U:
			exec_i64_rem_u( _p );
			break;
		case xwasm::I64_AND:
			exec_i64_and( _p );
			break;
		case xwasm::I64_OR:
			exec_i64_or( _p );
			break;
		case xwasm::I64_XOR:
			exec_i64_xor( _p );
			break;
		case xwasm::I64_SHL:
			exec_i64_shl( _p );
			break;
		case xwasm::I64_SHR_S:
			exec_i64_shr_s( _p );
			break;
		case xwasm::I64_SHR_U:
			exec_i64_shr_u( _p );
			break;
		case xwasm::I64_ROTL:
			exec_i64_rotl( _p );
			break;
		case xwasm::I64_ROTR:
			exec_i64_rotr( _p );
			break;
		case xwasm::F32_ABS:
			exec_f32_abs( _p );
			break;
		case xwasm::F32_NEG:
			exec_f32_neg( _p );
			break;
		case xwasm::F32_CEIL:
			exec_f32_ceil( _p );
			break;
		case xwasm::F32_FLOOR:
			exec_f32_floor( _p );
			break;
		case xwasm::F32_TRUNC:
			exec_f32_trunc( _p );
			break;
		case xwasm::F32_NEAREST:
			exec_f32_nearest( _p );
			break;
		case xwasm::F32_SQRT:
			exec_f32_sqrt( _p );
			break;
		case xwasm::F32_ADD:
			exec_f32_add( _p );
			break;
		case xwasm::F32_SUB:
			exec_f32_sub( _p );
			break;
		case xwasm::F32_MUL:
			exec_f32_mul( _p );
			break;
		case xwasm::F32_DIV:
			exec_f32_div( _p );
			break;
		case xwasm::F32_MIN:
			exec_f32_min( _p );
			break;
		case xwasm::F32_MAX:
			exec_f32_max( _p );
			break;
		case xwasm::F32_COPYSIGN:
			exec_f32_copysign( _p );
			break;
		case xwasm::F64_ABS:
			exec_f64_abs( _p );
			break;
		case xwasm::F64_NEG:
			exec_f64_neg( _p );
			break;
		case xwasm::F64_CEIL:
			exec_f64_ceil( _p );
			break;
		case xwasm::F64_FLOOR:
			exec_f64_floor( _p );
			break;
		case xwasm::F64_TRUNC:
			exec_f64_trunc( _p );
			break;
		case xwasm::F64_NEAREST:
			exec_f64_nearest( _p );
			break;
		case xwasm::F64_SQRT:
			exec_f64_sqrt( _p );
			break;
		case xwasm::F64_ADD:
			exec_f64_add( _p );
			break;
		case xwasm::F64_SUB:
			exec_f64_sub( _p );
			break;
		case xwasm::F64_MUL:
			exec_f64_mul( _p );
			break;
		case xwasm::F64_DIV:
			exec_f64_div( _p );
			break;
		case xwasm::F64_MIN:
			exec_f64_min( _p );
			break;
		case xwasm::F64_MAX:
			exec_f64_max( _p );
			break;
		case xwasm::F64_COPYSIGN:
			exec_f64_copysign( _p );
			break;
		case xwasm::I32_WRAP_I64:
			exec_i32_wrap_i64( _p );
			break;
		case xwasm::I32_TRUNC_S_F32:
			exec_i32_trunc_s_f32( _p );
			break;
		case xwasm::I32_TRUNC_U_F32:
			exec_i32_trunc_u_f32( _p );
			break;
		case xwasm::I32_TRUNC_S_F64:
			exec_i32_trunc_s_f64( _p );
			break;
		case xwasm::I32_TRUNC_U_F64:
			exec_i32_trunc_u_f64( _p );
			break;
		case xwasm::I64_EXTEND_S_I32:
			exec_i64_extend_s_i32( _p );
			break;
		case xwasm::I64_EXTEND_U_I32:
			exec_i64_extend_u_i32( _p );
			break;
		case xwasm::I64_TRUNC_S_F32:
			exec_i64_trunc_s_f32( _p );
			break;
		case xwasm::I64_TRUNC_U_F32:
			exec_i64_trunc_u_f32( _p );
			break;
		case xwasm::I64_TRUNC_S_F64:
			exec_i64_trunc_s_f64( _p );
			break;
		case xwasm::I64_TRUNC_U_F64:
			exec_i64_trunc_u_f64( _p );
			break;
		case xwasm::F32_CONVERT_S_I32:
			exec_f32_convert_s_i32( _p );
			break;
		case xwasm::F32_CONVERT_U_I32:
			exec_f32_convert_u_i32( _p );
			break;
		case xwasm::F32_CONVERT_S_I64:
			exec_f32_convert_s_i64( _p );
			break;
		case xwasm::F32_CONVERT_U_I64:
			exec_f32_convert_u_i64( _p );
			break;
		case xwasm::F32_DEMOTE_F64:
			exec_f32_demote_f64( _p );
			break;
		case xwasm::F64_CONVERT_S_I32:
			exec_f64_convert_s_i32( _p );
			break;
		case xwasm::F64_CONVERT_U_I32:
			exec_f64_convert_u_i32( _p );
			break;
		case xwasm::F64_CONVERT_S_I64:
			exec_f64_convert_s_i64( _p );
			break;
		case xwasm::F64_CONVERT_U_I64:
			exec_f64_convert_u_i64( _p );
			break;
		case xwasm::F64_PROMOTE_F32:
			exec_f64_promote_f32( _p );
			break;
		case xwasm::I32_REINTERPRET_F32:
			exec_i32_reinterpret_f32( _p );
			break;
		case xwasm::I64_REINTERPRET_F64:
			exec_i64_reinterpret_f64( _p );
			break;
		case xwasm::F32_REINTERPRET_I32:
			exec_f32_reinterpret_i32( _p );
			break;
		case xwasm::F64_REINTERPRET_I64:
			exec_f64_reinterpret_i64( _p );
			break;
		default:
			return ERR_INST_CODE;
			break;
		}
	}

	return 0;
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
	frame _frame;

	_frame.func = _p->_func;
	_frame.inst_index = _p->_insts.tellg();
	_frame.operand_index = _p->_operands.size();

	_p->_frames.emplace_back( _frame );
}

void xwasm::executor::poped()
{
	frame _frame = _p->_frames.back();

	_p->_func = _frame.func;
	_p->_insts.reset( _p->_func->codes.data(), _p->_func->codes.data() + _p->_func->codes.size() );
	_p->_insts.seekg( _frame.inst_index, xwasm::stream::beg );
	_p->_operands.erase( _p->_operands.begin() + _frame.operand_index, _p->_operands.end() );

	_p->_frames.pop_back();
}
