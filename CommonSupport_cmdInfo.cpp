#include "include_CommonSupport_header.h"

//TODO ��̬����Ҫ�Ĳ���,���¼���еĺ�������������,��̬�����ʱ����Ҫȡ��������
#if !defined(__E_STATIC_LIB)
static ARG_INFO g_argumentInfo_CommonSupport_global_var[] = 
{
    // 1=��������, 2=������ϸ����, 3=ָ��ͼ������,��1��ʼ,0��ʾ��, 4=ͼ����Ŀ(��������)
    // 5=��������, 6=����Ĭ��ֵ,   7=������־ AS_ ��ͷ����
    // AS_HAS_DEFAULT_VALUE         ��Ĭ��ֵ,�����ڶ���������Ĭ��ֵ
    // AS_DEFAULT_VALUE_IS_EMPTY    Ĭ��ֵΪ��,�пɿձ�־
    // AS_RECEIVE_VAR               ֻ�ܴ��ݱ���,�൱�ڴ�����,���ݹ����Ŀ϶���������
    // AS_RECEIVE_VAR_ARRAY         ���ݹ����Ŀ϶��������������
    // AS_RECEIVE_VAR_OR_ARRAY      ���ݱ������������������
    // AS_RECEIVE_ARRAY_DATA        ��������
    // AS_RECEIVE_ALL_TYPE_DATA     ��������/������
    // AS_RECEIVE_VAR_OR_OTHER      ���Դ��� ����/����/����ֵ����


	/*000*/	{"��ʱʱ��","����",0,0, (DWORD)SDT_INT, 0, 0},
	/*001*/	{"�������","����Ҫ���浽�ڴ�ı���",0,0, (DWORD)_SDT_ALL, 0, 0},
	/*002*/	{"�ڴ�ָ��","����Ҫ��ԭ���������ڴ���ָ���ַ",0,0, (DWORD)SDT_INT, 0, 0},
	/*003*/	{"��ԭ����","�ο��ͣ�����Ҫ��ԭ���������������ͱ�������뱣��һ�á�",0,0,(DWORD)_SDT_ALL, 0, AS_RECEIVE_VAR},
	/*004*/	{"�������","�����Զ������ͣ�������ı��������ֽڼ����ı����ֽڼ�ֻ������ǰ�档",0,0, (DWORD)_SDT_ALL, 0, 0},
	/*005*/	{"�ı�������","ָ���ṹ�����������ı���+�ֽڼ���������,�ı�����ֻ������ǰ��,�����ʡ�ԣ���Ĭ�ϲ����ı����ֽڼ���",0,0, (DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*006*/	{"�Զ���ָ��","Ҫ��ԭ���Զ��嵽ָ���ַ",0,0, (DWORD)SDT_INT, 0, 0},
	/*007*/	{"�Զ������ͱ���","�ο� �Զ������ͱ���",0,0, (DWORD)_SDT_ALL, 0, AS_RECEIVE_VAR},
	/*008*/	{"��ǩ���","�����¼��ı�ǩ�����",0,0,(DWORD)SDT_INT, 0, 0},
	/*009*/	{"��Ϣֵ1","��ǩ�����¼�����1",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*010*/	{"��Ϣֵ2","��ǩ�����¼�����2",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*011*/	{"�ӳ���ָ��","�������ṩ�����߳�ʱ���������ӳ���ָ�롣",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*012*/	{"��������","�������ɽ�������������Ͳ�����",0,0,(DWORD)SDT_INT, 0, 0},
	/*013*/	{"�ӳ���ָ��","�������ṩ�����߳�ʱ���������ӳ���ָ�롣",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*014*/	{"��������","�������ɽ���������ı��Ͳ�����",0,0,(DWORD)SDT_TEXT, 0, 0},
	/*015*/	{"�ӳ���ָ��","�������ṩ�����߳�ʱ���������ӳ���ָ��",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*016*/	{"�ص��ӳ���ָ��","��Ϊ�գ���ִ�к�����Ҫ���ؽ��պ���,�ص���������:\r\n.�汾 2\r\n.�ӳ��� �ص�����\r\n.���� ����һ, ������",0,0,(DWORD)SDT_SUB_PTR, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*017*/	{"��С�߳���","�����̳߳�����С���߳��������С��2��������Ϊ2�̡߳�",0,0,(DWORD)SDT_INT, 0, 0},
	/*018*/	{"����߳���","�����̳߳��������߳��������С��4��������Ϊ4�̡߳�",0,0,(DWORD)SDT_INT, 0, 0},
	/*019*/	{"���ݲ���","��ִ�к�����Ҫ���ݵĲ���",0,0,(DWORD)SDT_INT, 0, 0},
	/*020*/	{"��������","�������ɽ�������������Ͳ�����",0,0,(DWORD)SDT_INT, 0, 0},
	/*021*/	{"��������","�������ɽ���������ı��Ͳ�����",0,0,(DWORD)SDT_TEXT, 0, 0},
	/*022*/	{"���ٷ�ʽ","0=�������٣��������أ��ȴ���ǰ����ִ�к󷵻� �棩��1=ǿ�����٣�ǿ�������̳߳ء��������� ��  ע�⣺�˷�ʽִ�к�ǿ�������̳߳أ�ǿ�Ҳ�����ʹ�ã�������ڴ�й¶����",0,0,(DWORD)SDT_INT, 0, 0},
	/*023*/	{"��ȴ�ʱ��","�˲���ֻ������������Ч����λ�����룬���ջ� 0 һֱ�ȴ��� �����˳�ʱʱ����������� �� ��",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};

#ifdef _DEBUG    // ������Ϊ��ȷ�ϲ�������Ƿ���ȷ, ��Ա�������һ����Ŵ�1������ȷ
const int dbg_cmd_arg_count__ = sizeof(g_argumentInfo_CommonSupport_global_var) / sizeof(g_argumentInfo_CommonSupport_global_var[0]);
#endif


#define CommonSupport_DEF_CMDINFO(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    { _szName, ______E_FNENAME(_szEgName), _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo },


// ������ÿ������Ķ���, �����Ϣ��ʾ��֧�ֿ��б���, ����ÿ����Ա������ϸ������һ���������Ϣ
CMD_INFO g_cmdInfo_CommonSupport_global_var[] = 
{
    CommonSupport_DEF(CommonSupport_DEF_CMDINFO)
};

int g_cmdInfo_CommonSupport_global_var_count = sizeof(g_cmdInfo_CommonSupport_global_var) / sizeof(g_cmdInfo_CommonSupport_global_var[0]);

#endif

