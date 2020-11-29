/*!
 * \file	xwasm.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef XWASM_H__471A95BF_55DD_4ECE_93A0_DFB49F8E79A4
#define XWASM_H__471A95BF_55DD_4ECE_93A0_DFB49F8E79A4

#if COMPILER == COMPILER_MSVC
#   define DLL_IMPORT __declspec( dllimport )
#   define DLL_EXPORT __declspec( dllexport )
#elif COMPILER == COMPILER_GNUC || COMPILER == COMPILER_CLANG
#   define DLL_IMPORT __attribute__ ((visibility ("default")))
#   define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif

#ifdef XWASM_EXPORTS
#	define XWASM_API DLL_EXPORT
#else
#	define XWASM_API DLL_IMPORT
#endif // XWASM_EXPORTS

#endif // XWASM_H__471A95BF_55DD_4ECE_93A0_DFB49F8E79A4
