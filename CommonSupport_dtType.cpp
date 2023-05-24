#include "include_CommonSupport_header.h"

#ifndef __E_STATIC_LIB
//1=中文名字,2=英文名字,3=详细解释,4=命令数量,5=索引值,6=标志 LDT_
//类型为窗口或菜单组件时有效 7=资源ID,8=事件数量,9=组件事件数组,10=属性数  11=属性数组 12=组件交互子程序
//不为窗口、菜单组件或为枚举数据类型时才有效 13=成员数量,14=成员数据数组


///线程池
LIB_DATA_TYPE_ELEMENT sdt_elementxc[] = {
	{(DWORD)SDT_SUB_PTR,NULL,"线程池结构指针","minNumOfThread","线程池创建成功后保存的结构指针。",LES_HIDED,NULL},
	{(DWORD)SDT_SUB_PTR,NULL,"线程池子程序","actionThread","线程池创建成功后保存的线程池子程序指针。",LES_HIDED,NULL},
	{(DWORD)SDT_SUB_PTR,NULL,"线程池回调子程序","reThread","线程池创建成功后保存的线程池回调子程序指针。",LES_HIDED,NULL},
	{(DWORD)SDT_INT,NULL,"最小线程数","minNumOfThread","设置线程池中最小的线程数，如果小于2将被设置为2线程。",NULL,2},
	{(DWORD)SDT_INT,NULL,"最大线程数","maxNumOfThread","线程池中最大的线程数",NULL,4},
	{(DWORD)SDT_INT,NULL,"等待线程数","getWaitNumOfThread","获取线程池中的任务队列即等待执行的任务总数。",NULL,NULL},
	{(DWORD)SDT_INT,NULL,"空闲线程数","getIdleThreadNum","获取线程池中的待机线程数,如果线程池工作完则清理内存。释放线程到最小的线程数。",NULL,NULL},
	{(DWORD)SDT_INT,NULL,"工作线程数","getBusyThreadNum","获取线程池中正在工作线程数，如果为0则没有任务在执行。",NULL,NULL}
};


int sdt_cmdInfosListxc[] = 
{
8,9,10,11,12,13,14,15,16,17
};
///临界许可
LIB_DATA_TYPE_ELEMENT sdt_ljxk[] = {
	{(DWORD)SDT_SUB_PTR,NULL,"许可证","Ex_CRITICAL_SECTION","用来初始化一个临界资源对象",LES_HIDED,NULL}
};

int sdt_cmdInfosListljxk[] = {
18,19,20,21,22
};

LIB_DATA_TYPE_INFO g_DataType_CommonSupport_global_var[] = {
	{"线程池Ex","CYXCC","创建一个线程池",sizeof(sdt_cmdInfosListxc) / sizeof(sdt_cmdInfosListxc[0]),sdt_cmdInfosListxc,_CMD_OS(__OS_WIN),0,0,0,0,0,0,sizeof(sdt_elementxc) / sizeof(sdt_elementxc[0]),sdt_elementxc},
	{"临界许可Ex","CYLJXK","线程可以使用临界资源对象来解决同步互斥问题,该对象不能保证哪个线程能够获得到临界资源对象，因而该系统能公平的对待每一个线程.",sizeof(sdt_cmdInfosListljxk) / sizeof(sdt_cmdInfosListljxk[0]),sdt_cmdInfosListljxk,_CMD_OS(__OS_WIN),0,0,0,0,0,0,sizeof(sdt_ljxk) / sizeof(sdt_ljxk[0]),sdt_ljxk}
};

int g_DataType_CommonSupport_global_var_count = sizeof(g_DataType_CommonSupport_global_var) / sizeof(g_DataType_CommonSupport_global_var[0]);

#endif



