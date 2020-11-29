/*!
 * \file	errmsg.h
 *
 * \author	ZhengYuanQing
 * \date	2020/11/28
 * \email	zhengyuanqing.95@gmail.com
 *
 */
#ifndef ERRMSG_H__E1624E2B_8FB5_47A9_B76F_F8E552C28630
#define ERRMSG_H__E1624E2B_8FB5_47A9_B76F_F8E552C28630

constexpr int ERR_NO = 0;
constexpr int ERR_MAGIC_NUMBER = 1;
constexpr int ERR_STREAM_UNEXPECTED_HALT = 2;
constexpr int ERR_STREAM_CODE = 3;
constexpr int ERR_FUNC_NOT_FOUND = 4;
constexpr int ERR_INST_CODE = 5;

constexpr int ERR_UNKNOWN = 10;

constexpr const char * err_msg[] =
{
	"",
	"magic number != 0x6D736100",
	"stream unexpected halt",
	"stream error code",
	"the corresponding function was not found",
	"the wrong instruction code",
	"",
	"",
	"",
	"",
	"unknown error"
};

#endif // ERRMSG_H__E1624E2B_8FB5_47A9_B76F_F8E552C28630
