#ifndef __INCLUDE_COMMONSUPPORT_IMPLEMENTATION_H__
#define __INCLUDE_COMMONSUPPORT_IMPLEMENTATION_H__

#include "elib/lib2.h"
#include "elib/lang.h"
#include "elib/krnllib.h"
#include "elib/fnshare.h"
#include <process.h>
#include <iostream>
#include <memory>

using namespace std;

typedef struct _THREADDATA
{
	int* sConnect;
	int lenth;
}*LPTHREADDATA, THREADDATA;


//第1个取延时
EXTERN_C VOID ThreadFun_WaitForObject(HANDLE handle);//延时
EXTERN_C unsigned int __stdcall GetInterface_DelayTime(LPVOID lpParameter);//参数为延时秒数
EXTERN_C unsigned int __stdcall CreateMultiparameterInt(LPVOID lpParameter);//整数型多参
EXTERN_C unsigned int __stdcall CreateMultiparameterText(LPVOID lpParameter);//文本型多参
EXTERN_C  unsigned int __stdcall ExCreateMultiparameterInt(int lpParameter);//多线程整数型多参
EXTERN_C  unsigned int __stdcall ExCreateMultiparameterText(int lpParameter);//多线程文本型多参

EXTERN_C LPBYTE GetMDataPtr(PMDATA_INF pInf, LPINT pnDataSize);
///内部使用
EXTERN_C VOID _DelayTime(int second);

#endif