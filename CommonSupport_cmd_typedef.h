#ifndef __INCLUDE_COMMONSUPPORT_CMD_TYPEDEF_H__
#define __INCLUDE_COMMONSUPPORT_CMD_TYPEDEF_H__

#define __CommonSupport_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__E_FNENAME)##_##_name##_##_index##_

// 传递函数名和索引, 拼接成 定义库名_名字_序号_定义库名, 比如 CommonSupport_test_0_CommonSupport
#define CommonSupport_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__CommonSupport_NAME(_index, _name))__LIB2_FNE_NAME_LEFT(__E_FNENAME)

// 传递函数名和索引, 拼接成 "定义库名_名字_序号_定义库名", 比如 "CommonSupport_test_0_CommonSupport"
#define CommonSupport_NAME_STR(_index, _name) ______E_FNENAME(__CommonSupport_NAME(_index, _name))

// 这个宏定义了所有的命令, 以后需要命令名数组, 声明命令等, 都可以使用这个宏
#define CommonSupport_DEF(_MAKE) \
_MAKE(0,"完美延时", PerfectDelay, "完美延时不卡界面。", 1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var+0)\
_MAKE(1,"无限传参", MultiToFirsthPointer, "将参数储存到内存，返回内存首指针地址。用于线程传参。失败返回0。", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 1)\
_MAKE(2,"无限传参还原", FirsthPointerToMulti, "将无限传参内存首指针还原到传入多个参数，成功返参数个数，失败返回0。", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 2)\
_MAKE(3,"自定义到指针", GetPorAddr, "自定义类型到指针地址，如果类型中包含文本型字节集只能放最前面且需要指定数量。", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 4)\
_MAKE(4,"指针到自定义", OutPorAddr, "将指针地址还原到自定义类，成功返自定义类型长度，失败返回0。", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 6)\
_MAKE(5,"标签反馈", SendLabMessage, "利用标签反馈事件，将结果返回处理窗口事件。线程与外界通信不崩溃渠道。", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 3,g_argumentInfo_CommonSupport_global_var + 8)\
_MAKE(6,"启动线程_无限整数参", CreateThreadMultiparameterInt, "增强型启动线程，支持任意多整数型参数。成功返回线程句柄，失败返回0。", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 11)\
_MAKE(7,"启动线程_无限文本参", CreateThreadMultiparameterText, "增强型启动线程，支持任意多文本型参数。成功返回线程句柄，失败返回0。", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 13)\
_MAKE(8,"创建", ExThreadPool, "创建线程池。成功返回真，失败返回假。", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 4,g_argumentInfo_CommonSupport_global_var + 15)\
_MAKE(9,"投递任务", ExQueueTaskItem, "向线程池投放任务，支持一个整数型作为参数的任务。成功返回真，失败返回假。", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 19)\
_MAKE(10,"投任务多整数参", ExCreateThreadMultiparameterInt, "向线程池投放任务，支持任意多整数型参数。成功返回真，失败返回假。", -1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 20)\
_MAKE(11,"投任务多文本参", ExCreateThreadMultiparameterText, "向线程池投放任务，支持任意多文本型参数。成功返回真，失败返回假。", -1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 21)\
_MAKE(12,"清空任务", ExCleanTask, "清空未开始工作的任务，已开始工作的任务不受影响。", -1, _CMD_OS(__OS_WIN),0, 0, 0, 0 ,0, 0, 0)\
_MAKE(13,"暂停", ExPause, "让线程池处于工作状态线程全部暂停。", -1, _CMD_OS(__OS_WIN),(DWORD)SDT_BOOL, 0, 0, 0 ,0, 0, 0)\
_MAKE(14,"恢复",ExRecover, "让线程池被暂停状态线程全部恢复工作。", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 0, 0)\
_MAKE(15,"刷新", ExRefresh, "刷新取线程池各项数据。", -1, _CMD_OS(__OS_WIN),0, 0, 0, 0 ,0, 0, 0)\
_MAKE(16,"取状态", ExReState, "取出工作状态0未创建或已销毁。1正在工作中。2空闲等待任务。3繁忙有任务正在排队。4正在销毁。", -1, _CMD_OS(__OS_WIN),(DWORD)SDT_INT, 0, 0, 0 ,0, 0, 0)\
_MAKE(17,"销毁", ExDestroy, "安全销毁线程池。成功返回真，失败返回假。", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 22)\
_MAKE(18,"创建", ExInitializeCriticalSection, "用来初始化一个临界资源对象", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)\
_MAKE(19,"进入", ExEnterCriticalSection, "引入互斥变量，让每个线程都按顺序地访问变量。", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)\
_MAKE(20,"尝试进入", ExTryEnterCriticalSection, "发现该资源已经被另一个线程访问，它就返回FALSE。在其他所有情况下，它均返回TRUE。运用这个函数，线程能够迅速查看它是否可以访问某个共享资源，如果不能访问，那么它可以继续执行某些其他操作，而不必进行等待。", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 0,0)\
_MAKE(21,"退出", ExLeaveCriticalSection, "放弃当前线程对锁定部分的所有权。一旦锁定部分的所有权被放弃，那么请求访问临界区的下一个线程，将可以对锁定部分进行操作。", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0,0)\
_MAKE(22,"销毁", ExDeleteCriticalSection, "删除临界资源对象释放由该对象使用的所有系统资源。成功返回真失败返回假。", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)

#endif