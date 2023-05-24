#include "CommonSupport_implementation.h"

#define DTT_IS_SYS_DATA_TYPE    1


#ifndef _DEBUG
#define VASSERT(expr, expr_desc) ((void)0)
#else
#define VASSERT(expr, expr_desc) \
    do { if (!(expr) && \
    (1 == _CrtDbgReport(_CRT_ASSERT, (__FILE__), __LINE__, \
    NULL, #expr##"\nProblem: "##expr_desc))) \
    _CrtDbgBreak();}while(0)
#endif


//第1个取延时
EXTERN_C VOID _DelayTime(int second)
{
	LPVOID apam = (LPVOID)second;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, GetInterface_DelayTime, apam, 0, NULL);
	if (hThread > 0) {
		ThreadFun_WaitForObject(hThread);
		CloseHandle(hThread);
	}
}

EXTERN_C VOID ThreadFun_WaitForObject(HANDLE handle)
{
	MSG msg;
	while (TRUE) {
		DWORD dwRet = MsgWaitForMultipleObjects(1, &handle, FALSE, INFINITE, QS_ALLINPUT);
		switch (dwRet) {
		case WAIT_OBJECT_0:
			break;
		case WAIT_OBJECT_0 + 1:
			PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			DispatchMessage(&msg);
			continue;
		default:
			break;
		}
		break;
	}
}
//参数为延时秒数
EXTERN_C unsigned int __stdcall GetInterface_DelayTime(LPVOID lpParameter)
{
	int m = (int)lpParameter;
	Sleep(m);
	return 0;
}
//整数型多参
EXTERN_C  unsigned int __stdcall CreateMultiparameterInt(LPVOID lpParameter)
{
	LPTHREADDATA ppData = (LPTHREADDATA)lpParameter;
	int len = ppData->lenth;
	int* p = ppData->sConnect;
	int hMem_Pi = *p;//第一个值为子程序指针地址
	int narg = len - 1;
	_asm {
		mov ecx, narg
		mov ebx, p
		entry :
		mov eax, [ebx + ecx * 4]
		mov eax, [eax]
		push eax
		dec ecx
		cmp ecx, 0
		ja entry
		mov eax, hMem_Pi
		call eax
	}
	delete ppData;
	return 0;
}
//文本型多参
EXTERN_C unsigned int __stdcall CreateMultiparameterText(LPVOID lpParameter)
{
	LPTHREADDATA ppData = (LPTHREADDATA)lpParameter;
	int len = ppData->lenth;
	int* p = ppData->sConnect;
	int hMem_Pi = *p;//第一个值为子程序指针地址
	int narg = len - 1;
	_asm {
		mov ecx, narg
		mov ebx, p
		entry :
		mov eax, [ebx + ecx * 4]
		push eax
		dec ecx
		cmp ecx, 0
		ja entry
		mov eax, hMem_Pi
		call eax
	}
	HeapFree(GetProcessHeap(), 0, p);
	delete ppData;
	return 0;
}
//线程池整数型多参
EXTERN_C  unsigned int __stdcall  ExCreateMultiparameterInt(int lpParameter)
{
	LPTHREADDATA ppData = (LPTHREADDATA)lpParameter;
	int len = ppData->lenth;
	int* p = ppData->sConnect;
	int hMem_Pi = *p;//第一个值为子程序指针地址
	int narg = len - 1;
	int revalue = 0;
	_asm {
		mov ecx, narg
		mov ebx, p
		entry :
		mov eax, [ebx + ecx * 4]
		mov eax, [eax]
		push eax
		dec ecx
		cmp ecx, 0
		ja entry
		mov ecx, hMem_Pi
		call ecx
		mov revalue,eax
	}
	HeapFree(GetProcessHeap(), 0, p);
	delete ppData;
	return revalue;
}
//线程池文本型多参
EXTERN_C  unsigned int __stdcall ExCreateMultiparameterText(int lpParameter)
{
	LPTHREADDATA ppData = (LPTHREADDATA)lpParameter;
	int len = ppData->lenth;
	int* p = ppData->sConnect;
	int hMem_Pi = *p;//第一个值为子程序指针地址
	int narg = len - 1;
	int revalue = 0;
	_asm {
		mov ecx, narg
		mov ebx, p
		entry :
		mov eax, [ebx + ecx * 4]
		push eax
		dec ecx
		cmp ecx, 0
		ja entry
		mov eax, hMem_Pi
		call eax
		mov revalue,eax
	}
	HeapFree(GetProcessHeap(), 0, p);	
	delete ppData;
	return revalue;
}


//取通用变量指针长度
EXTERN_C LPBYTE GetMDataPtr(PMDATA_INF pInf, LPINT pnDataSize)
{
	VASSERT(GetDataTypeType(pInf->m_dtDataType) == DTT_IS_SYS_DATA_TYPE,"GetDataTypeType");

	switch (pInf->m_dtDataType)
	{
	case (DWORD)SDT_BYTE:
		*pnDataSize = sizeof(BYTE);
		return (LPBYTE)&pInf->m_byte;
	case (DWORD)SDT_SHORT:
		*pnDataSize = sizeof(SHORT);
		return (LPBYTE)&pInf->m_short;
	case (DWORD)SDT_INT:
		*pnDataSize = sizeof(INT);
		return (LPBYTE)&pInf->m_int;
	case (DWORD)SDT_INT64:
		*pnDataSize = sizeof(INT64);
		return (LPBYTE)&pInf->m_int64;
	case (DWORD)SDT_FLOAT:
		*pnDataSize = sizeof(FLOAT);
		return (LPBYTE)&pInf->m_float;
	case (DWORD)SDT_DOUBLE:
		*pnDataSize = sizeof(DOUBLE);
		return (LPBYTE)&pInf->m_double;
	case (DWORD)SDT_BOOL:
		*pnDataSize = sizeof(BOOL);
		return (LPBYTE)&pInf->m_bool;
	case (DWORD)SDT_DATE_TIME:
		*pnDataSize = sizeof(DATE);
		return (LPBYTE)&pInf->m_date;
	case (DWORD)SDT_SUB_PTR:
		*pnDataSize = sizeof(DWORD);
		return (LPBYTE)&pInf->m_dwSubCodeAdr;
	case (DWORD)SDT_TEXT:
		*pnDataSize = strlen(pInf->m_pText) + 1;
		return (LPBYTE)pInf->m_pText;
	case (DWORD)SDT_BIN: {
		LPBYTE pBinData = pInf->m_pBin + sizeof(INT) * 2;
		*pnDataSize = *(LPINT)(pBinData - sizeof(INT));
		return pBinData; }
	default:
		VASSERT(FALSE, "other type");
		return NULL;
	}
}

