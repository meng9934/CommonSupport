#include "include_CommonSupport_header.h"



EXTERN_C INT WINAPI CommonSupport_ProcessNotifyLib_CommonSupport(INT nMsg, DWORD dwParam1, DWORD dwParam2);
#ifndef __E_STATIC_LIB
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:    // ��һ�α�����,LoadLibrary���ؾʹ���
        break;
    case DLL_PROCESS_DETACH:    // DLL���ͷ�
        break;
    case DLL_THREAD_ATTACH:     // �߳�ӳ��
        break;
    case DLL_THREAD_DETACH:     // �߳�ж��
        break;
    }
    return TRUE;
}

#define CommonSupport_DEF_CMD_PTR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    CommonSupport_NAME(_index, _szEgName),

PFN_EXECUTE_CMD g_cmdInfo_CommonSupport_global_var_fun[] = { CommonSupport_DEF(CommonSupport_DEF_CMD_PTR) };

static LIB_INFO g_LibInfo_CommonSupport_global_var = 
{
    /*m_dwLibFormatVer*/        LIB_FORMAT_VER, // ���ʽ��, Ӧ�õ���LIB_FORMAT_VER
    /*m_szGuid*/                "361C58F8-3D5B-4d02-9137-C4BD515941B0", // ��Ӧ�ڱ����ΨһGUID��, ����ΪNULL���, ������а汾�˴���Ӧ��ͬ
    /*m_nMajorVersion*/         2, // ��������汾��, �������0
    /*m_nMinorVersion*/         0, // ����Ĵΰ汾��
    /*m_nBuildNumber*/          3, // �����汾��, ����Դ˰汾�����κδ���

    /*m_nRqSysMajorVer*/        3, // ����Ҫ��������ϵͳ�����汾��
    /*m_nRqSysMinorVer*/        0, // ����Ҫ��������ϵͳ�Ĵΰ汾��
    /*m_nRqSysKrnlLibMajorVer*/ 3, // ����Ҫ��ϵͳ����֧�ֿ�����汾��
    /*m_nRqSysKrnlLibMinorVer*/ 0, // ����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾��

    /*m_szName*/                "���̸߳���֧�ֿ�", // ����, ����ΪNULL���
    /*m_nLanguage*/             __GBK_LANG_VER, // ����֧�ֵ�����
    /*m_szExplain*/             "�ṩ���̴߳����������㷽�������ص��������̳߳ء�", // ����ϸ����
    /*m_dwState*/               _LIB_OS(__OS_WIN), // _LIB_OS() | LBS_ ��ͷ����, ����ǲ��,������� LBS_IDE_PLUGIN

    /*m_szAuthor*/              "meng9934", // ����
    /*m_szZipCode*/             "", // �ʱ�
    /*m_szAddress*/             "�㶫ʡ������", // ��ַ
    /*m_szPhoto*/               "", // ��ϵ�绰
    /*m_szFax*/                 "", // ����
    /*m_szEmail*/               "meng9934@qq.com", // ����
    /*m_szHomePage*/            "", // ��ҳ
    /*m_szOther*/               "ף��һ����˳�������³ɣ�", // ������Ϣ

    /*m_nDataTypeCount*/        g_DataType_CommonSupport_global_var_count, // �������Զ����������͵���Ŀ
    /*g_DataType_web*/          g_DataType_CommonSupport_global_var, // ���������е��Զ�����������

    /*m_nCategoryCount*/        1, // ȫ�����������Ŀ, ��Ϊ0
    /*m_szzCategory*/           _T("0000�̸߳���\0"
                                "\0"), // ȫ�����������Ŀ, ��Ϊ0

    /*m_nCmdCount*/             g_cmdInfo_CommonSupport_global_var_count, // �������ṩ����������(ȫ�������������)����Ŀ, ��Ϊ0
    /*m_pBeginCmdInfo*/         g_cmdInfo_CommonSupport_global_var, // �������ṩ����������
    /*m_pCmdsFunc*/             g_cmdInfo_CommonSupport_global_var_fun, // ָ��ÿ�������ʵ�ִ����׵�ַ, ��ΪNULL

    /*m_pfnRunAddInFn*/         NULL, // ��ΪNULL,������IDEϵͳ��Ӹ�������, ���ṩ���ܻᱻ�Զ���ӵ�IDE�ġ����ߡ��˵���
                                         // �й�AddIn���ܵ�˵��, �����ַ���˵��һ�����ܡ���һ��Ϊ��������
                                         // (����һ��20�ַ�, ���ϣ�����г�ʼλ�ö������Զ����뵽���߲˵�, ��
                                         // ����Ӧ����@��ʼ, ��ʱ����յ�ֵΪ -(nAddInFnIndex + 1) �ĵ���֪ͨ), 
                                         // �ڶ���Ϊ������ϸ����(����һ��60�ַ�), ����������մ�������
    /*m_szzAddInFnInfo*/        NULL, // ������ϸ����(����һ��60�ַ�), ����������մ�����

    /*m_pfnNotify*/             CommonSupport_ProcessNotifyLib_CommonSupport, // ����ΪNULL,��������ͨѶ���ӳ���

    /*m_pfnSuperTemplate*/      NULL, // ģ�� ��ΪNULL
                                         //  �й�SuperTemplate��˵��, �����ַ���˵��һ��SuperTemplate��
                                         //  ��һ��ΪSuperTemplate����(����һ��30�ַ�), �ڶ���Ϊ��ϸ����(����), 
                                         //  ����������մ�������
    /*m_szzSuperTemplateInfo*/  NULL, // ģ�� ��ΪNULL

    /*m_nLibConstCount*/        g_ConstInfo_CommonSupport_global_var_count, // ����Ԥ�ȶ�������г�������
    /*m_pLibConst*/             g_ConstInfo_CommonSupport_global_var, // ����Ԥ�ȶ�������г���

    /*m_szzDependFiles*/        NULL // ��ΪNULL, ����������������Ҫ����������֧���ļ�
};

EXTERN_C PLIB_INFO WINAPI GetNewInf()
{
    return &g_LibInfo_CommonSupport_global_var;
}

#define CommonSupport_DEF_CMDNAME_STR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    ______E_FNENAME(CommonSupport_NAME(_index, _szEgName)),

// ������, �������̬����ʹ��
static const LPCSTR g_cmdNamesCommonSupport[] = { CommonSupport_DEF(CommonSupport_DEF_CMDNAME_STR) };

#endif
EXTERN_C INT WINAPI CommonSupport_ProcessNotifyLib_CommonSupport(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    int nRet = NR_OK;
    switch (nMsg)
    {
#ifndef __E_STATIC_LIB
    // ������������ʵ�ֺ����ĵĺ�����������(char*[]), ֧�־�̬����Ķ�̬����봦��
    case NL_GET_CMD_FUNC_NAMES:
    {
        return (INT)g_cmdNamesCommonSupport;
    }
    // ���ش���ϵͳ֪ͨ�ĺ�������(PFN_NOTIFY_LIB��������), ֧�־�̬����Ķ�̬����봦��
    case NL_GET_NOTIFY_LIB_FUNC_NAME:
    {
        return (INT)"CommonSupport_ProcessNotifyLib_CommonSupport";
    }
    // ���ؾ�̬����������������̬���ļ����б�(��ʽΪ\0�ָ����ı�,��β����\0), ֧�־�̬����Ķ�̬����봦��
    // kernel32.lib user32.lib gdi32.lib �ȳ��õ�ϵͳ�ⲻ��Ҫ���ڴ��б���
    // ����NULL��NR_ERR��ʾ��ָ�������ļ�
    case NL_GET_DEPENDENT_LIBS:
    {
        return (INT)"\0\0";
    }
#endif
    // ��֪��֪ͨϵͳ�õĺ���ָ��,��װ��֧�ֿ�ǰ֪ͨ,�����ж��,��֪ͨ��ֵӦ�ø���ǰ����֪ͨ��ֵ,���Է���ֵ
    // ��ɽ��˺���ָ���¼�����Ա�����Ҫʱʹ����֪ͨ��Ϣ��ϵͳ
    // dwParam1: (PFN_NOTIFY_SYS)
    case NL_SYS_NOTIFY_FUNCTION:
    {
        // �ѳ�ʼ�����¼�ת���� fnshare.cpp ��ִ��, ��fnshare��ĺ�������ʹ��
        ProcessNotifyLib(nMsg, dwParam1, dwParam2);
        break;
    }
    // ֪֧ͨ�ֿ��ͷ���Դ׼���˳����ͷ�ָ���ĸ�������
    case NL_FREE_LIB_DATA:
    {
        break;
    }
    // ��֧�ֿ���IDE�б��û�ȡ��ѡ����ͱ�֪ͨ
    case NL_UNLOAD_FROM_IDE:
    {
        break;
    }
    // ����NR_DELAY_FREE��ʾ��֧�ֿ���Ҫ���ӳ��ͷ�
    case NR_DELAY_FREE:
    {
        break;
    }
    // ��IDE�Ѿ�׼���ý����û�������,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�
    // ע��: ���û���֧�ֿ����öԻ�����ȡ����ѡ��֧�ֿ��ѡ���µ�֧�ֿ��,��֪ͨ�ᱻ�ٴη���,֧�ֿ�����Ҫ����ô������
    case NL_IDE_READY:
    {
        break;
    }
    // ���û���IDE�е�������Ҽ����������˵�ǰ,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�
    // dwParam1: �������˵����(HMENU)
    // dwParam2: �������˵���������������(e.exe)�е���ԴID
    case NL_RIGHT_POPUP_MENU_SHOW:
    {
        break;
    }
    // ��IDE׼����ʾ�¼����Ա�Ի���֮ǰ,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�
    // ����1��ʾ��֪ͨ��������IDE���ݷ������������ָ�����³�Ա,����2��ʾ��֪ͨ��������IDE��ֹ����³�Ա,����0��ʾδ������
    // dwParam1: �ṩ�������Ա������(ADD_NEW_ELEMENT_TYPE)
    // dwParam2:
    //   ���dwParam1ΪNAN_NEW_VAR,��Ϊһ��ָ��RES_NEW_VAR_INFO��ָ��;
    //   ���dwParam1ΪNAN_NEW_SUB,��Ϊһ��ָ���������ӳ������Ƶ��ı�ָ��;
    //   ���dwParam1ΪNAN_NEW_CONST_RES,��Ϊһ��ָ��RES_NEW_CONST_RES_INFO��ָ��
    case NL_ADD_NEW_ELEMENT:
    {
        break;
    }
    default:
        nRet = NR_ERR;
        break;
    }
    return nRet;
}


