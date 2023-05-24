#include "CommonSupport_thread_pool.h"
ThreadPool::~ThreadPool()
{
	isExit = true;
	ResetEvent(stopEvent);
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)TOEXIT, NULL);
	CloseHandle(stopEvent);
	CloseHandle(completionPort);
	CloseHandle(dispatchThrad);
	dispatchThrad = NULL;
	completionPort = NULL;
	stopEvent = NULL;
}
//销毁线程（等待结束）
void ThreadPool::QueueExit()
{
	isExit = true;
	ResetEvent(stopEvent);
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)TOEXIT, NULL);
	CloseHandle(stopEvent);
	stopEvent = NULL;

}
//强制销毁线程
void ThreadPool::QueueCompelExit()
{
	isExit = true;
	ResetEvent(stopEvent);
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)COMPELEXIT, NULL);
	CloseHandle(stopEvent);
	stopEvent = NULL;
}
//清空未执行任务
void ThreadPool::QueueCleanTask()
{
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)CLEANTASK, NULL);
}


//对外暂停线程
void ThreadPool::QueuePause()
{
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)PAUSE, NULL);
}
//暂停指定的线程

bool ThreadPool::GetTaskPause()
{
	for (list<Thread*>::const_iterator it = busyThreadList.begin(); it != busyThreadList.end(); it++)
	{
		HANDLE h1 = (*it)->thread;
		SuspendThread(h1);
	}
	return (busyThreadList.size() > 0);
}

//对外恢复被暂停的线程
void ThreadPool::QueueRecover()
{
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)RECOVER, NULL);
}
//恢复被暂停线程
bool ThreadPool::GetTaskRecover()
{
	for (list<Thread*>::const_iterator it = busyThreadList.begin(); it != busyThreadList.end(); it++)
	{
		HANDLE h1 = (*it)->thread;
		ResumeThread(h1);
	}
	return (busyThreadList.size() > 0);
}
//清空未开始工始的任务
void ThreadPool::GetTaskExit()
{
	waitTaskLock.Lock();
	waitTaskList.clear();
	waitTaskLock.UnLock();
}
//强制退出线程
void ThreadPool::GetTaskCompelExit()
{
	waitTaskLock.Lock();
	waitTaskList.clear();
	waitTaskLock.UnLock();
	busyThreadLock.Lock();
	for (list<Thread*>::const_iterator it = busyThreadList.begin(); it != busyThreadList.end(); it++)
	{
		HANDLE hwnd1 = (*it)->thread;
		TerminateThread((*it)->thread, 0);
	}
	busyThreadList.clear();
	busyThreadLock.UnLock();
	idleThreadLock.Lock();
	idleThreadList.clear();
	idleThreadLock.UnLock();
}
void ThreadPool::MoveBusyThreadToIdleList(Thread* busyThread)
{

	idleThreadLock.Lock();
	idleThreadList.push_back(busyThread);
	idleThreadLock.UnLock();

	busyThreadLock.Lock();
	for (list<Thread*>::iterator it = busyThreadList.begin(); it != busyThreadList.end(); it++)
	{
		if (*it == busyThread)//找到工作完的线程
		{
			busyThreadList.erase(it);//释放工作线程
			break;
		}
	}
	busyThreadLock.UnLock();
	if (waitTaskList.size() == 0 && busyThreadList.size() == 0) //如果线程全部工作完成。清理线程到最少待机线程数。
	{
		if (idleThreadList.size() > minNumOfThread)
		{
			PostQueuedCompletionStatus(completionPort, 0, (DWORD)CLEANFREETASK, NULL);
		}

	}
}

void ThreadPool::DeleteIdleThread()
{
	idleThreadLock.Lock();
	size_t t = idleThreadList.size();
	size_t size = t - minNumOfThread;
	if (size > 0)
	{
		for (size_t i = 0; i < size; i++)
		{
			Thread* thread = idleThreadList.back();
			idleThreadList.pop_back();
			delete thread;			
		}
	}
	idleThreadLock.UnLock();
}
void ThreadPool::CreateIdleThread(size_t size)
{
	idleThreadLock.Lock();
	for (size_t i = 0; i < size; i++)
	{
		Thread* nowthreed = new Thread(this);
		idleThreadList.push_back(nowthreed);
	}
	idleThreadLock.UnLock();
}

ThreadPool::Thread* ThreadPool::GetIdleThread()
{
	Thread* thread = NULL;
	idleThreadLock.Lock();
	if (idleThreadList.size() > 0)
	{
		thread = idleThreadList.front();
		idleThreadList.pop_front();
	}
	idleThreadLock.UnLock();
	if (thread == NULL && GetBusyThreadNum() < maxNumOfThread)
	{
		thread = new Thread(this);
	}
	return thread;
}
void ThreadPool::GetTaskExcute()
{
	Thread* thread = NULL;
	thread = GetIdleThread();
	if (thread != NULL)
	{
		busyThreadLock.Lock();
		busyThreadList.push_back(thread);
		busyThreadLock.UnLock();
		thread->ExecuteTask();
	}
}

unsigned int ThreadPool::Thread::ThreadProc(PVOID pM)
{
	Thread* pThread = (Thread*)pM;
	BOOL bRet = FALSE;
	DWORD dwBytes = 0;
	DWORD opType = 0;
	OVERLAPPED* ol;
	WaitTask* waitTask;
	while (true) {
		BOOL bRet = GetQueuedCompletionStatus(pThread->controlPort, &dwBytes, (PULONG_PTR)&opType, &ol, INFINITE);
		if (opType == 1)
			break;
		waitTask = pThread->threadPool->GetWaitTask();//从队列中取出等待线程
		while (waitTask!=NULL)
		{
			int param = waitTask->param;
			int* task = waitTask->task;
			int* taskCb = waitTask->taskCb;
			_asm {
				mov ebx, param
				push ebx
				mov eax, task
				call eax
				mov ebx, taskCb
				cmp ebx, 0
				je ex
				push eax
				call ebx
				ex :
			}
			delete waitTask;
			waitTask = NULL;
			waitTask = pThread->threadPool->GetWaitTask();//从队列中取出等待线程
		}
		pThread->threadPool->MoveBusyThreadToIdleList(pThread);

	}
	return 0;
}

ThreadPool::Thread::Thread(ThreadPool* threadPool) :
	threadPool(threadPool)
{
	controlPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
	thread = (HANDLE)_beginthreadex(0, 0, ThreadProc, this, 0, 0);
}

ThreadPool::Thread::~Thread()
{
	PostQueuedCompletionStatus(controlPort, 0, 1, NULL);
	WaitForSingleObject(thread, INFINITE);
	CloseHandle(thread);
	CloseHandle(controlPort);
	controlPort = NULL;
	thread = NULL;
}

void ThreadPool::Thread::ExecuteTask()
{
	PostQueuedCompletionStatus(controlPort, 0, 0, NULL);
}

ThreadPool::WaitTask* ThreadPool::GetWaitTask()
{
	WaitTask* waitTask = NULL;
	waitTaskLock.Lock();
	if (waitTaskList.size() > 0)
	{
		waitTask = waitTaskList.front();
		waitTaskList.pop_front();
	}
	waitTaskLock.UnLock();
	return waitTask;
}

ThreadPool::ThreadPool(size_t minNumOfThread, size_t maxNumOfThread)
{
	if (minNumOfThread < 2)
		this->minNumOfThread = 2;
	else
		this->minNumOfThread = minNumOfThread;
	if (maxNumOfThread < 4)
		this->maxNumOfThread = 4;
	else
		this->maxNumOfThread = maxNumOfThread;
	isExit = false;
	CreateIdleThread(this->minNumOfThread);
	stopEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 1);
	dispatchThrad = (HANDLE)_beginthreadex(0, 0, GetTaskThreadProc, this, 0, 0);
}

//投递任务
BOOL ThreadPool::QueueTaskItem(int* task, int param, int* taskCb)
{
	waitTaskLock.Lock();
	WaitTask* waitTask = new WaitTask(task, param, taskCb);
	waitTaskList.push_back(waitTask);
	waitTaskLock.UnLock();
	PostQueuedCompletionStatus(completionPort, 0, (DWORD)GET_TASK, NULL);
	return TRUE;
}