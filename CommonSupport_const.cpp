//#define    CT_NULL 0
//#define    CT_NUM  1      // value sample: 3.1415926
//#define    CT_BOOL 2      // value sample: 1
//#define    CT_TEXT 3      // value sample: "abc"
//LPCSTR m_szName;          // ������
//LPCSTR m_szEgName;        // Ӣ����
//LPCSTR m_szExplain;       // ˵��
//SHORT  m_shtLayout;       // ����Ϊ 1
//SHORT  m_shtType;         // ��������, CT_NULL=�ճ���, CT_NUM=��ֵ��,double����ֵ, CT_BOOL=�߼���, CT_TEXT=�ı���
//LPCSTR m_szText;          // CT_TEXT
//DOUBLE m_dbValue;         // CT_NUM��CT_BOOL
#include "include_CommonSupport_header.h"

#ifndef __E_STATIC_LIB
LIB_CONST_INFO g_ConstInfo_CommonSupport_global_var[] ={
{
	_WT("��Ϣֵ_��ǩ"),_WT("LabMsg"), NULL,1, CT_NUM, NULL, 32885 
}
};
int g_ConstInfo_CommonSupport_global_var_count = 1;

#endif
