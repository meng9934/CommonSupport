#ifndef __INCLUDE_COMMONSUPPORT_THREAD_POOL_H__
#define __INCLUDE_COMMONSUPPORT_THREAD_POOL_H__
#include <Windows.h>
#include <process.h>
#include <list>

using namespace std;

#define PULONG_PTR PULONG

class ThreadPool
{
private:
	//�߳��ٽ�����
	class CriticalSectionLock
	{
	private:
		CRITICAL_SECTION cs;//�ٽ���
	public:
		CriticalSectionLock() {
			__try { InitializeCriticalSection(&cs); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}
		~CriticalSectionLock() { DeleteCriticalSection(&cs); }
		void Lock() { EnterCriticalSection(&cs); }
		void UnLock() { LeaveCriticalSection(&cs); }
	};
	// ��ִ�е�������
	class WaitTask
	{
	public:
		WaitTask(int* task, int param, int* taskCb)
		{
			this->task = task;
			this->param = param;
			this->taskCb = taskCb;
		}
		~WaitTask() { task = NULL; taskCb = NULL; param = 0; }
		int* task;                    // Ҫִ�е�����
		int param;                    // �������
		int* taskCb;            // �ص�������
	};
	// �߳���(�ڲ���)
	class Thread
	{
	public:
		Thread(ThreadPool* threadPool);
		~Thread();
		HANDLE  thread;                                                    // �߳̾��
		HANDLE controlPort;											// ���ƶ˿�
		void ExecuteTask();												  // �ָ��߳�ִ������
	private:
		ThreadPool* threadPool;											// �����̳߳�
		static unsigned int __stdcall ThreadProc(PVOID pM);                // �̺߳���
	};
public:
	ThreadPool(size_t minNumOfThread = 2, size_t maxNumOfThread = 10);
	~ThreadPool();
	void QueuePause();									//������ͣ
	void QueueRecover();								//����ָ�
	void QueueCompelExit();								//ǿ���˳�
	void QueueExit();									//�˳�
	void QueueCleanTask();								//��������
	BOOL QueueTaskItem(int* task, int param, int* taskCb);//ִ������


	static unsigned int __stdcall GetTaskThreadProc(PVOID pM)
	{
		ThreadPool* threadPool = (ThreadPool*)pM;
		BOOL bRet = FALSE;
		DWORD dwBytes = 0;
		DWORD opType = 0;
		OVERLAPPED* ol;
		while (WAIT_OBJECT_0 == WaitForSingleObject(threadPool->stopEvent, 0))
		{
			BOOL bRet = GetQueuedCompletionStatus(threadPool->completionPort, &dwBytes, (PULONG_PTR)&opType, &ol, INFINITE);
			switch (opType) {
			case TOEXIT:
				threadPool->GetTaskExit();
				break;
			case COMPELEXIT:
				threadPool->GetTaskCompelExit();
				break;
			case PAUSE:
				threadPool->GetTaskPause();
				break;
			case RECOVER:
				threadPool->GetTaskRecover();
				break;
			case GET_TASK:
				threadPool->GetTaskExcute();
				break;
			case CLEANTASK:
				threadPool->GetTaskExit();
				break;
			case CLEANFREETASK:  // ɾ�������߳�
				threadPool->DeleteIdleThread();
				break;
			}

		}
		return 0;
	}
	size_t GetWaitNumOfThread() { return waitTaskList.size();  }    // ��ȡ�̳߳��еȴ�������
	size_t GetIdleThreadNum() { return idleThreadList.size(); }    // ��ȡ�̳߳��п����߳���
	size_t GetBusyThreadNum() { return busyThreadList.size();}    // ��ȡ�̳߳��еĹ����߳���
	size_t GetMinNumOfThread() { return minNumOfThread; }    // ��ȡ�̳߳ش����߳���
	size_t GetMaxNumOfThread() { return maxNumOfThread; }    // ��ȡ�̳߳�����߳���
	Thread* GetIdleThread();                                    // ��ȡ�����߳�
	void MoveBusyThreadToIdleList(Thread* busyThread);            // æµ�̼߳�������б�
	void DeleteIdleThread();                            // ɾ�������߳�
	void GetTaskExcute();                                        // �����������ȡ����ִ��
	WaitTask* GetWaitTask();                                        // �����������ȡ����
	bool GetTaskPause();                                        // �����������ִ����ͣ
	bool GetTaskRecover();										// �����������ִ�лָ�
	void GetTaskCompelExit();									//ǿ���˳�
	void GetTaskExit();											//���δ�����߳�
	CriticalSectionLock waitTaskLock;							//�����б���
	list<WaitTask*> waitTaskList;                                // �����б�
	CriticalSectionLock idleThreadLock;							// �����߳��б���
	list<Thread*> idleThreadList;								// �����߳��б�
	CriticalSectionLock busyThreadLock;                            // æµ�߳��б���
	list<Thread*> busyThreadList;                                // æµ�߳��б�
	void CreateIdleThread(size_t size);							//���������߳�
	bool isExit;												//�˳���ʶ


	HANDLE                    dispatchThrad;                        // �ַ������߳�
	HANDLE                    completionPort;                        // ��ɶ˿�
	size_t                    maxNumOfThread;                        // �̳߳��������߳���
	size_t                    minNumOfThread;                        // �̳߳�����С���߳���
	HANDLE                    stopEvent;                            // ֪ͨ�߳��˳���ʱ��

	enum WAIT_OPERATION_TYPE
	{
		GET_TASK,
		TOEXIT,
		PAUSE,
		RECOVER,
		COMPELEXIT,
		CLEANTASK,
		CLEANFREETASK
	};
};

#endif