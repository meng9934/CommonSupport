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
	//线程临界区锁
	class CriticalSectionLock
	{
	private:
		CRITICAL_SECTION cs;//临界区
	public:
		CriticalSectionLock() {
			__try { InitializeCriticalSection(&cs); }
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}
		~CriticalSectionLock() { DeleteCriticalSection(&cs); }
		void Lock() { EnterCriticalSection(&cs); }
		void UnLock() { LeaveCriticalSection(&cs); }
	};
	// 待执行的任务类
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
		int* task;                    // 要执行的任务
		int param;                    // 任务参数
		int* taskCb;            // 回调的任务
	};
	// 线程类(内部类)
	class Thread
	{
	public:
		Thread(ThreadPool* threadPool);
		~Thread();
		HANDLE  thread;                                                    // 线程句柄
		HANDLE controlPort;											// 控制端口
		void ExecuteTask();												  // 恢复线程执行任务
	private:
		ThreadPool* threadPool;											// 所属线程池
		static unsigned int __stdcall ThreadProc(PVOID pM);                // 线程函数
	};
public:
	ThreadPool(size_t minNumOfThread = 2, size_t maxNumOfThread = 10);
	~ThreadPool();
	void QueuePause();									//对外暂停
	void QueueRecover();								//对外恢复
	void QueueCompelExit();								//强制退出
	void QueueExit();									//退出
	void QueueCleanTask();								//清理任务
	BOOL QueueTaskItem(int* task, int param, int* taskCb);//执行任务


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
			case CLEANFREETASK:  // 删除空闲线程
				threadPool->DeleteIdleThread();
				break;
			}

		}
		return 0;
	}
	size_t GetWaitNumOfThread() { return waitTaskList.size();  }    // 获取线程池中等待任务数
	size_t GetIdleThreadNum() { return idleThreadList.size(); }    // 获取线程池中空闲线程数
	size_t GetBusyThreadNum() { return busyThreadList.size();}    // 获取线程池中的工作线程数
	size_t GetMinNumOfThread() { return minNumOfThread; }    // 获取线程池待机线程数
	size_t GetMaxNumOfThread() { return maxNumOfThread; }    // 获取线程池最大线程数
	Thread* GetIdleThread();                                    // 获取空闲线程
	void MoveBusyThreadToIdleList(Thread* busyThread);            // 忙碌线程加入空闲列表
	void DeleteIdleThread();                            // 删除空闲线程
	void GetTaskExcute();                                        // 从任务队列中取任务执行
	WaitTask* GetWaitTask();                                        // 从任务队列中取任务
	bool GetTaskPause();                                        // 从任务队列中执行暂停
	bool GetTaskRecover();										// 从任务队列中执行恢复
	void GetTaskCompelExit();									//强制退出
	void GetTaskExit();											//清空未工作线程
	CriticalSectionLock waitTaskLock;							//任务列表锁
	list<WaitTask*> waitTaskList;                                // 任务列表
	CriticalSectionLock idleThreadLock;							// 工作线程列表锁
	list<Thread*> idleThreadList;								// 工作线程列表
	CriticalSectionLock busyThreadLock;                            // 忙碌线程列表锁
	list<Thread*> busyThreadList;                                // 忙碌线程列表
	void CreateIdleThread(size_t size);							//创建工作线程
	bool isExit;												//退出标识


	HANDLE                    dispatchThrad;                        // 分发任务线程
	HANDLE                    completionPort;                        // 完成端口
	size_t                    maxNumOfThread;                        // 线程池中最大的线程数
	size_t                    minNumOfThread;                        // 线程池中最小的线程数
	HANDLE                    stopEvent;                            // 通知线程退出的时间

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