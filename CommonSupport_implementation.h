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


//��1��ȡ��ʱ
EXTERN_C VOID ThreadFun_WaitForObject(HANDLE handle);//��ʱ
EXTERN_C unsigned int __stdcall GetInterface_DelayTime(LPVOID lpParameter);//����Ϊ��ʱ����
EXTERN_C unsigned int __stdcall CreateMultiparameterInt(LPVOID lpParameter);//�����Ͷ��
EXTERN_C unsigned int __stdcall CreateMultiparameterText(LPVOID lpParameter);//�ı��Ͷ��
EXTERN_C  unsigned int __stdcall ExCreateMultiparameterInt(int lpParameter);//���߳������Ͷ��
EXTERN_C  unsigned int __stdcall ExCreateMultiparameterText(int lpParameter);//���߳��ı��Ͷ��

EXTERN_C LPBYTE GetMDataPtr(PMDATA_INF pInf, LPINT pnDataSize);
///�ڲ�ʹ��
EXTERN_C VOID _DelayTime(int second);

#endif