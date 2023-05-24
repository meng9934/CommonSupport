#ifndef __INCLUDE_COMMONSUPPORT_CMD_TYPEDEF_H__
#define __INCLUDE_COMMONSUPPORT_CMD_TYPEDEF_H__

#define __CommonSupport_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__E_FNENAME)##_##_name##_##_index##_

// ���ݺ�����������, ƴ�ӳ� �������_����_���_�������, ���� CommonSupport_test_0_CommonSupport
#define CommonSupport_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__CommonSupport_NAME(_index, _name))__LIB2_FNE_NAME_LEFT(__E_FNENAME)

// ���ݺ�����������, ƴ�ӳ� "�������_����_���_�������", ���� "CommonSupport_test_0_CommonSupport"
#define CommonSupport_NAME_STR(_index, _name) ______E_FNENAME(__CommonSupport_NAME(_index, _name))

// ����궨�������е�����, �Ժ���Ҫ����������, ���������, ������ʹ�������
#define CommonSupport_DEF(_MAKE) \
_MAKE(0,"������ʱ", PerfectDelay, "������ʱ�������档", 1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var+0)\
_MAKE(1,"���޴���", MultiToFirsthPointer, "���������浽�ڴ棬�����ڴ���ָ���ַ�������̴߳��Ρ�ʧ�ܷ���0��", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 1)\
_MAKE(2,"���޴��λ�ԭ", FirsthPointerToMulti, "�����޴����ڴ���ָ�뻹ԭ���������������ɹ�������������ʧ�ܷ���0��", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 2)\
_MAKE(3,"�Զ��嵽ָ��", GetPorAddr, "�Զ������͵�ָ���ַ����������а����ı����ֽڼ�ֻ�ܷ���ǰ������Ҫָ��������", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 4)\
_MAKE(4,"ָ�뵽�Զ���", OutPorAddr, "��ָ���ַ��ԭ���Զ����࣬�ɹ����Զ������ͳ��ȣ�ʧ�ܷ���0��", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 6)\
_MAKE(5,"��ǩ����", SendLabMessage, "���ñ�ǩ�����¼�����������ش������¼����߳������ͨ�Ų�����������", 1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 3,g_argumentInfo_CommonSupport_global_var + 8)\
_MAKE(6,"�����߳�_����������", CreateThreadMultiparameterInt, "��ǿ�������̣߳�֧������������Ͳ������ɹ������߳̾����ʧ�ܷ���0��", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 11)\
_MAKE(7,"�����߳�_�����ı���", CreateThreadMultiparameterText, "��ǿ�������̣߳�֧��������ı��Ͳ������ɹ������߳̾����ʧ�ܷ���0��", 1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_INT, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 13)\
_MAKE(8,"����", ExThreadPool, "�����̳߳ء��ɹ������棬ʧ�ܷ��ؼ١�", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 4,g_argumentInfo_CommonSupport_global_var + 15)\
_MAKE(9,"Ͷ������", ExQueueTaskItem, "���̳߳�Ͷ������֧��һ����������Ϊ���������񡣳ɹ������棬ʧ�ܷ��ؼ١�", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 19)\
_MAKE(10,"Ͷ�����������", ExCreateThreadMultiparameterInt, "���̳߳�Ͷ������֧������������Ͳ������ɹ������棬ʧ�ܷ��ؼ١�", -1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 20)\
_MAKE(11,"Ͷ������ı���", ExCreateThreadMultiparameterText, "���̳߳�Ͷ������֧��������ı��Ͳ������ɹ������棬ʧ�ܷ��ؼ١�", -1, CT_ALLOW_APPEND_NEW_ARG, (DWORD)SDT_BOOL, 0, 0, 0 ,0, 1,g_argumentInfo_CommonSupport_global_var + 21)\
_MAKE(12,"�������", ExCleanTask, "���δ��ʼ�����������ѿ�ʼ������������Ӱ�졣", -1, _CMD_OS(__OS_WIN),0, 0, 0, 0 ,0, 0, 0)\
_MAKE(13,"��ͣ", ExPause, "���̳߳ش��ڹ���״̬�߳�ȫ����ͣ��", -1, _CMD_OS(__OS_WIN),(DWORD)SDT_BOOL, 0, 0, 0 ,0, 0, 0)\
_MAKE(14,"�ָ�",ExRecover, "���̳߳ر���ͣ״̬�߳�ȫ���ָ�������", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 0, 0)\
_MAKE(15,"ˢ��", ExRefresh, "ˢ��ȡ�̳߳ظ������ݡ�", -1, _CMD_OS(__OS_WIN),0, 0, 0, 0 ,0, 0, 0)\
_MAKE(16,"ȡ״̬", ExReState, "ȡ������״̬0δ�����������١�1���ڹ����С�2���еȴ�����3��æ�����������Ŷӡ�4�������١�", -1, _CMD_OS(__OS_WIN),(DWORD)SDT_INT, 0, 0, 0 ,0, 0, 0)\
_MAKE(17,"����", ExDestroy, "��ȫ�����̳߳ء��ɹ������棬ʧ�ܷ��ؼ١�", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 2,g_argumentInfo_CommonSupport_global_var + 22)\
_MAKE(18,"����", ExInitializeCriticalSection, "������ʼ��һ���ٽ���Դ����", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)\
_MAKE(19,"����", ExEnterCriticalSection, "���뻥���������ÿ���̶߳���˳��ط��ʱ�����", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)\
_MAKE(20,"���Խ���", ExTryEnterCriticalSection, "���ָ���Դ�Ѿ�����һ���̷߳��ʣ����ͷ���FALSE����������������£���������TRUE����������������߳��ܹ�Ѹ�ٲ鿴���Ƿ���Է���ĳ��������Դ��������ܷ��ʣ���ô�����Լ���ִ��ĳЩ���������������ؽ��еȴ���", -1, _CMD_OS(__OS_WIN), (DWORD)SDT_BOOL, 0, 0, 0 ,0, 0,0)\
_MAKE(21,"�˳�", ExLeaveCriticalSection, "������ǰ�̶߳��������ֵ�����Ȩ��һ���������ֵ�����Ȩ����������ô��������ٽ�������һ���̣߳������Զ��������ֽ��в�����", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0,0)\
_MAKE(22,"����", ExDeleteCriticalSection, "ɾ���ٽ���Դ�����ͷ��ɸö���ʹ�õ�����ϵͳ��Դ���ɹ�������ʧ�ܷ��ؼ١�", -1, _CMD_OS(__OS_WIN), 0, 0, 0, 0 ,0, 0, 0)

#endif