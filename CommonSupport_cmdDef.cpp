#include "include_CommonSupport_header.h"
#include "CommonSupport_implementation.h"
#include "CommonSupport_thread_pool.h"

// ���ø�ʽ: ������ʱ
// ����<1>: ������, ����˵��: "��λ����"

CommonSupport_EXTERN_C void CommonSupport_PerfectDelay_0_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, GetInterface_DelayTime, (LPVOID)pArgInf[0].m_int, 0, NULL);
	if (hThread > 0) {
		ThreadFun_WaitForObject(hThread);
		CloseHandle(hThread);
	}

}

// ���޴��� �������Ҫ���浽�ڴ�ı���

CommonSupport_EXTERN_C void CommonSupport_MultiToFirsthPointer_1_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	if (nArgCount > 0)
	{
		int* apamDatas = new int[nArgCount];
		for (INT i = 0; i < nArgCount; i++)
		{
			int len = 0;
			PMDATA_INF now_por = pArgInf + i;
			LPBYTE mem_address = GetMDataPtr(now_por, &len);
			LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
			RtlMoveMemory(saveAddr, mem_address, len);
			apamDatas[i] = (int)saveAddr;
		}
		int len1 = nArgCount * sizeof(int);
		LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len1);
		RtlMoveMemory(saveAddr, apamDatas, len1);
		delete[] apamDatas;
		pRetData->m_int = (int)saveAddr;
	}
	else
	{
		pRetData->m_int = 0;
	}

}

// ���޴��λ�ԭ

CommonSupport_EXTERN_C void CommonSupport_FirsthPointerToMulti_2_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* hMem_Pi = pArgInf[0].m_pInt;
	int len = HeapSize(GetProcessHeap(), HEAP_NO_SERIALIZE, hMem_Pi)/ sizeof(int);
	if (len == 0)
	{
		pRetData->m_int = 0;
		return;
	}
	for (INT i = 1; i < nArgCount; i++)
	{
		void** p = pArgInf[i].m_ppCompoundData;
		int* data_Addr = (int*)(*(hMem_Pi + i - 1));
		int len1 = HeapSize(GetProcessHeap(), HEAP_NO_SERIALIZE, data_Addr);
		switch (pArgInf[i].m_dtDataType)
		{
		case (DWORD)SDT_TEXT: {
			*p = CloneTextData((char*)data_Addr); break;
		}
		case (DWORD)SDT_BIN: *p = CloneBinData((LPBYTE)data_Addr, len1); break;
		default:
			memcpy(p, data_Addr, len1);
			break;
		}
	}
	
	pRetData->m_int = nArgCount - 1;
}

// �Զ��嵽ָ��
CommonSupport_EXTERN_C void CommonSupport_GetPorAddr_3_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int len = HeapSize(GetProcessHeap(), HEAP_NO_SERIALIZE, pArgInf[0].m_ppCompoundData);
	if (len == 0)
	{
		pRetData->m_int = 0;
		return;
	}
	LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
	RtlMoveMemory(saveAddr, pArgInf[0].m_ppCompoundData, len);
	int xb = pArgInf[1].m_int + 1;
	int* reDatas = new int[xb];
	reDatas[0] = (int)saveAddr;
	void** p = pArgInf[0].m_ppCompoundData;

	for (int i = 1; i < xb; i++)
	{
		void* pp = *(p + i - 1);
		int str_len = HeapSize(GetProcessHeap(),HEAP_NO_SERIALIZE,pp);
		LPVOID tempSaveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, str_len);
		RtlMoveMemory(tempSaveAddr, pp, str_len);
		reDatas[i] = (int)tempSaveAddr;
	}
	int len1 = xb * sizeof(int);
	LPVOID reSaveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len1);
	RtlMoveMemory(reSaveAddr, reDatas, len1);
	delete[] reDatas;
	pRetData->m_int = (int)reSaveAddr;

}

// ָ�뵽�Զ���
CommonSupport_EXTERN_C void CommonSupport_OutPorAddr_4_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* hMem_Pi = pArgInf[0].m_pInt;
	int aplen = LocalSize(hMem_Pi) / sizeof(int);
	if (aplen == 0)
	{
		pRetData->m_int = 0;
		return;
	}

	int* data_Addr = (int*)(*(hMem_Pi));
	int len = LocalSize(data_Addr);

	for (INT i = 1; i < aplen; i++) {
		int* data_Addr1 = (int*)(*(hMem_Pi + i));
		int mui = (i - 1) * 4;
		_asm {
			mov eax, data_Addr
			mov ecx, mui
			add eax, ecx
			mov ecx, data_Addr1
			mov[eax], ecx
		}
	}
	void** p = pArgInf[1].m_ppCompoundData;
	RtlMoveMemory(*p, data_Addr, len);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, data_Addr);
	pRetData->m_int = (int)*p;

}

// ��ǩ����", "SendLabMessage", "���ñ�ǩ�����¼�����������ش������¼����߳������ͨ�Ų�����������

CommonSupport_EXTERN_C void CommonSupport_SendLabMessage_5_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	HWND lab_hwnd = (HWND)pArgInf[0].m_int;
	int wparm = pArgInf[1].m_int;
	int lparm = pArgInf[2].m_int;
	SendMessage(lab_hwnd, 32885, wparm, lparm);
	pRetData->m_bool = true;

}
// �����߳�����������, ��ǿ�������̣߳�֧����������
CommonSupport_EXTERN_C void CommonSupport_CreateThreadMultiparameterInt_6_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* apamDatas = new int[nArgCount];
	apamDatas[0] = (int)pArgInf[0].m_pInt;
	for (INT i = 1; i < nArgCount; i++)
	{
		int len = 0;
		PMDATA_INF now_por = pArgInf + i;
		LPBYTE mem_address = GetMDataPtr(now_por, &len);
		LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		RtlMoveMemory(saveAddr, mem_address, len);
		apamDatas[i] = (int)saveAddr;
	}

	LPTHREADDATA pData = new THREADDATA;
	pData->sConnect = apamDatas;
	pData->lenth = nArgCount;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, CreateMultiparameterInt, (LPVOID)pData, 0, NULL);
	pRetData->m_int = (int)hThread;

}
// �����߳������ı��� ��ǿ�������̣߳�֧��������ı��Ͳ���
CommonSupport_EXTERN_C void CommonSupport_CreateThreadMultiparameterText_7_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* apamDatas = new int[nArgCount];
	apamDatas[0] = (int)pArgInf[0].m_pInt;
	for (INT i = 1; i < nArgCount; i++)
	{
		int len = 0;
		PMDATA_INF now_por = pArgInf + i;
		LPBYTE mem_address = GetMDataPtr(now_por, &len);
		LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		RtlMoveMemory(saveAddr, mem_address, len);
		apamDatas[i] = (int)saveAddr;
	}
	LPTHREADDATA pData = new THREADDATA;
	pData->sConnect = apamDatas;
	pData->lenth = nArgCount;
	HANDLE hThread = (HANDLE)_beginthreadex(NULL, 0, CreateMultiparameterText, (LPVOID)pData, 0, NULL);
	pRetData->m_int = (int)hThread;

}
// �����̳߳�
CommonSupport_EXTERN_C void CommonSupport_ExThreadPool_8_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf != 0)
	{
		pRetData->m_bool = false;
		return;
	}
	int* actionThread = (int*)pArgInf[1].m_pCompoundData;
	int* reThread = (int*)pArgInf[2].m_pCompoundData;
	int mix = (int)pArgInf[3].m_int;
	int max = (int)pArgInf[4].m_int;
	ThreadPool* threadPool = new ThreadPool(mix, max);
	*pInf = (int)threadPool;
	*(++pInf) = (int)actionThread;
	*(++pInf) = (int)reThread;
	*(++pInf) = threadPool->GetMinNumOfThread();
	*(++pInf) = threadPool->GetWaitNumOfThread(); //�ȴ��߳��� 
	*(++pInf) = threadPool->GetIdleThreadNum();//�����߳���
	*(++pInf) = threadPool->GetBusyThreadNum();//��ǰ�����߳���
	pRetData->m_bool = true;
}

// Ͷ������
CommonSupport_EXTERN_C void CommonSupport_ExQueueTaskItem_9_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		pRetData->m_bool = false;
		return;
	}
	ThreadPool* pthread = (ThreadPool*)*pInf;
	if (pthread->isExit)
	{
		pRetData->m_bool = false;
		return;
	}
	int* rw = (int*)*(++pInf);
	int* rw_ret = (int*)*(++pInf);
	int apam = pArgInf[1].m_int;
	pthread->QueueTaskItem(rw, apam, rw_ret);
	pRetData->m_bool = true;

}
// Ͷ�����������
CommonSupport_EXTERN_C void CommonSupport_ExCreateThreadMultiparameterInt_10_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		pRetData->m_bool = false;
		return;
	}
	ThreadPool* pthread = (ThreadPool*)*pInf;
	if (pthread->isExit)
	{
		pRetData->m_bool = false;
		return;
	}
	int rw = (int)*(++pInf);
	int* rw_ret = (int*)*(++pInf);
	int* apamDatas = new int[nArgCount];
	apamDatas[0] = rw;
	for (INT i = 1; i < nArgCount; i++)
	{
		int len = 0;
		PMDATA_INF now_por = pArgInf + i;
		LPBYTE mem_address = GetMDataPtr(now_por, &len);
		LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		RtlMoveMemory(saveAddr, mem_address, len);
		apamDatas[i] = (int)saveAddr;
	}
	LPTHREADDATA pData = new THREADDATA;
	pData->sConnect = apamDatas;
	pData->lenth = nArgCount;
	pthread->QueueTaskItem((int*)ExCreateMultiparameterInt, (int)pData, rw_ret);
	pRetData->m_bool = true;
}

// Ͷ������ı���
CommonSupport_EXTERN_C void CommonSupport_ExCreateThreadMultiparameterText_11_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		pRetData->m_bool = false;
		return;
	}
	ThreadPool* pthread = (ThreadPool*)*pInf;
	if (pthread->isExit)
	{
		pRetData->m_bool = false;
		return;
	}
	int rw = (int)*(++pInf);
	int* rw_ret = (int*)*(++pInf);
	int* apamDatas = new int[nArgCount];
	apamDatas[0] = rw;
	for (INT i = 1; i < nArgCount; i++)
	{
		int len = 0;
		PMDATA_INF now_por = pArgInf + i;
		LPBYTE mem_address = GetMDataPtr(now_por, &len);
		LPVOID saveAddr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
		RtlMoveMemory(saveAddr, mem_address, len);
		apamDatas[i] = (int)saveAddr;
	}
	LPTHREADDATA pData = new THREADDATA;
	pData->sConnect = apamDatas;
	pData->lenth = nArgCount;
	pthread->QueueTaskItem((int*)ExCreateMultiparameterText, (int)pData, rw_ret);
	pRetData->m_bool = true;
}

// ������� ���δ��ʼ�����������ѿ�ʼ������������Ӱ�졣
CommonSupport_EXTERN_C void CommonSupport_ExCleanTask_12_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		return;
	}
	ThreadPool* threadPool = (ThreadPool*)*pInf;
	threadPool->QueueCleanTask();
}
// ���̳߳ش��ڹ���״̬�߳�ȫ����ͣ
CommonSupport_EXTERN_C void CommonSupport_ExPause_13_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		return;
	}
	ThreadPool* threadPool = (ThreadPool*)*pInf;
	pRetData->m_bool = threadPool->GetTaskPause();
}

// ���̳߳ر���ͣ״̬�߳�ȫ���ָ�����
CommonSupport_EXTERN_C void CommonSupport_ExRecover_14_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		return;
	}
	ThreadPool* threadPool = (ThreadPool*)*pInf;
	pRetData->m_bool = threadPool->GetTaskRecover();
}
// ˢ��ȡ�̳߳ظ�������
CommonSupport_EXTERN_C void CommonSupport_ExRefresh_15_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		return;
	}
	ThreadPool* threadPool = (ThreadPool*)*pInf;
	pInf = pInf + 2;
	*(++pInf) = threadPool->GetMinNumOfThread();
	*(++pInf) = threadPool->GetMaxNumOfThread();
	*(++pInf) = threadPool->GetWaitNumOfThread(); //�ȴ��߳��� 
	*(++pInf) = threadPool->GetIdleThreadNum(); //�����߳���
	*(++pInf) = threadPool->GetBusyThreadNum(); //��ǰ�����߳���
}
// ȡ״̬ ȡ������״̬0δ������������1���ڹ�����2���еȴ�����3��æ�����������Ŷ�4��������
CommonSupport_EXTERN_C void CommonSupport_ExReState_16_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == 0)
	{
		pRetData->m_int = 0;
		return;
	}
	ThreadPool* pthread = (ThreadPool*)*pInf;
	if (pthread->isExit)
	{
		pRetData->m_int = 4;
	}
	else if (pthread->GetWaitNumOfThread() > 0)
	{
		pRetData->m_int = 3;
	}
	else if (pthread->GetBusyThreadNum() == 0)
	{
		pRetData->m_int = 2;
	}
	else
	{
		pRetData->m_int = 1;
	}
}

// ��ȫ�����̳߳�
CommonSupport_EXTERN_C void CommonSupport_ExDestroy_17_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	INT* pInf = (int*)pArgInf[0].m_pCompoundData;
	ThreadPool* threadPool = (ThreadPool*)*pInf;
	if (*pInf == 0)
	{
		pRetData->m_bool = true;
		return;
	}
	INT _state = (int)pArgInf[1].m_int;
	INT MaxTime = (int)pArgInf[2].m_int;
	switch (_state)
	{
	case 0:
		if (threadPool->GetBusyThreadNum() > 0 && threadPool->isExit == false) { threadPool->QueueExit(); }
		break;
	case 1:
		if (threadPool->GetBusyThreadNum() > 0 && threadPool->isExit == false) { threadPool->QueueCompelExit(); }
		break;
	default:
		break;
	}
	int waitetime = 0;
	while (threadPool->GetBusyThreadNum() > 0) {
		++waitetime;
		if (MaxTime > 0 && waitetime >= MaxTime)
		{
			pRetData->m_bool = false;;
			return;
		}
		_DelayTime(1);
	}
	threadPool->QueueExit();
	_DelayTime(100);
	
	delete threadPool;
	threadPool = NULL;
	*pInf = 0;
	pRetData->m_bool = true;
}
// �����ٽ����
CommonSupport_EXTERN_C void CommonSupport_ExInitializeCriticalSection_18_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf != NULL)
	{
		return;
	}
	RTL_CRITICAL_SECTION* cs = new RTL_CRITICAL_SECTION;
	*pInf = (int)cs;
	__try { InitializeCriticalSection(cs); }
	__except (EXCEPTION_EXECUTE_HANDLER) {}
}
// �����ٽ����
CommonSupport_EXTERN_C void CommonSupport_ExEnterCriticalSection_19_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == NULL)
	{
		return;
	}
	RTL_CRITICAL_SECTION* cs = (RTL_CRITICAL_SECTION*)*pInf;
	EnterCriticalSection(cs);
}
// ���Խ����ٽ����
CommonSupport_EXTERN_C void CommonSupport_ExTryEnterCriticalSection_20_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == NULL)
	{
		return;
	}
	RTL_CRITICAL_SECTION* cs = (RTL_CRITICAL_SECTION*)*pInf;
	BOOL ret = TryEnterCriticalSection(cs);
	pRetData->m_bool = ret;
}
// �˳��ٽ����
CommonSupport_EXTERN_C void CommonSupport_ExLeaveCriticalSection_21_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == NULL)
	{
		return;
	}
	RTL_CRITICAL_SECTION* cs = (RTL_CRITICAL_SECTION*)*pInf;
	LeaveCriticalSection(cs);
}
// �����ٽ����
CommonSupport_EXTERN_C void CommonSupport_ExDeleteCriticalSection_22_CommonSupport(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)
{
	int* pInf = (int*)pArgInf[0].m_pCompoundData;
	if (*pInf == NULL)
	{
		return;
	}
	RTL_CRITICAL_SECTION* cs = (RTL_CRITICAL_SECTION*)*pInf;
	DeleteCriticalSection(cs);
	*pInf = 0;
}
