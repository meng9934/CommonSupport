#include "include_CommonSupport_header.h"

#ifndef __E_STATIC_LIB
//1=��������,2=Ӣ������,3=��ϸ����,4=��������,5=����ֵ,6=��־ LDT_
//����Ϊ���ڻ�˵����ʱ��Ч 7=��ԴID,8=�¼�����,9=����¼�����,10=������  11=�������� 12=��������ӳ���
//��Ϊ���ڡ��˵������Ϊö����������ʱ����Ч 13=��Ա����,14=��Ա��������


///�̳߳�
LIB_DATA_TYPE_ELEMENT sdt_elementxc[] = {
	{(DWORD)SDT_SUB_PTR,NULL,"�̳߳ؽṹָ��","minNumOfThread","�̳߳ش����ɹ��󱣴�Ľṹָ�롣",LES_HIDED,NULL},
	{(DWORD)SDT_SUB_PTR,NULL,"�̳߳��ӳ���","actionThread","�̳߳ش����ɹ��󱣴���̳߳��ӳ���ָ�롣",LES_HIDED,NULL},
	{(DWORD)SDT_SUB_PTR,NULL,"�̳߳ػص��ӳ���","reThread","�̳߳ش����ɹ��󱣴���̳߳ػص��ӳ���ָ�롣",LES_HIDED,NULL},
	{(DWORD)SDT_INT,NULL,"��С�߳���","minNumOfThread","�����̳߳�����С���߳��������С��2��������Ϊ2�̡߳�",NULL,2},
	{(DWORD)SDT_INT,NULL,"����߳���","maxNumOfThread","�̳߳��������߳���",NULL,4},
	{(DWORD)SDT_INT,NULL,"�ȴ��߳���","getWaitNumOfThread","��ȡ�̳߳��е�������м��ȴ�ִ�е�����������",NULL,NULL},
	{(DWORD)SDT_INT,NULL,"�����߳���","getIdleThreadNum","��ȡ�̳߳��еĴ����߳���,����̳߳ع������������ڴ档�ͷ��̵߳���С���߳�����",NULL,NULL},
	{(DWORD)SDT_INT,NULL,"�����߳���","getBusyThreadNum","��ȡ�̳߳������ڹ����߳��������Ϊ0��û��������ִ�С�",NULL,NULL}
};


int sdt_cmdInfosListxc[] = 
{
8,9,10,11,12,13,14,15,16,17
};
///�ٽ����
LIB_DATA_TYPE_ELEMENT sdt_ljxk[] = {
	{(DWORD)SDT_SUB_PTR,NULL,"���֤","Ex_CRITICAL_SECTION","������ʼ��һ���ٽ���Դ����",LES_HIDED,NULL}
};

int sdt_cmdInfosListljxk[] = {
18,19,20,21,22
};

LIB_DATA_TYPE_INFO g_DataType_CommonSupport_global_var[] = {
	{"�̳߳�Ex","CYXCC","����һ���̳߳�",sizeof(sdt_cmdInfosListxc) / sizeof(sdt_cmdInfosListxc[0]),sdt_cmdInfosListxc,_CMD_OS(__OS_WIN),0,0,0,0,0,0,sizeof(sdt_elementxc) / sizeof(sdt_elementxc[0]),sdt_elementxc},
	{"�ٽ����Ex","CYLJXK","�߳̿���ʹ���ٽ���Դ���������ͬ����������,�ö����ܱ�֤�ĸ��߳��ܹ���õ��ٽ���Դ���������ϵͳ�ܹ�ƽ�ĶԴ�ÿһ���߳�.",sizeof(sdt_cmdInfosListljxk) / sizeof(sdt_cmdInfosListljxk[0]),sdt_cmdInfosListljxk,_CMD_OS(__OS_WIN),0,0,0,0,0,0,sizeof(sdt_ljxk) / sizeof(sdt_ljxk[0]),sdt_ljxk}
};

int g_DataType_CommonSupport_global_var_count = sizeof(g_DataType_CommonSupport_global_var) / sizeof(g_DataType_CommonSupport_global_var[0]);

#endif



