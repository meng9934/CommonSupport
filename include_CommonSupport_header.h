#ifndef __INCLUDE_COMMONSUPPORT_HEADER_H__
#define __INCLUDE_COMMONSUPPORT_HEADER_H__
#include "elib/lib2.h"
#include "elib/lang.h"
#include "elib/krnllib.h"
#include "elib/fnshare.h"

#include <tchar.h>

#include "CommonSupport_cmd_typedef.h"
#include "CommonSupport_implementation.h"



#define CommonSupport_EXTERN_C EXTERN_C




using namespace std;



#ifndef __E_STATIC_LIB
extern LIB_CONST_INFO g_ConstInfo_CommonSupport_global_var[];
extern int g_ConstInfo_CommonSupport_global_var_count;
extern CMD_INFO g_cmdInfo_CommonSupport_global_var[];
extern PFN_EXECUTE_CMD g_cmdInfo_CommonSupport_global_var_fun[];
extern int g_cmdInfo_CommonSupport_global_var_count;
extern ARG_INFO g_argumentInfo_CommonSupport_global_var[];
extern LIB_DATA_TYPE_INFO g_DataType_CommonSupport_global_var[];
extern int g_DataType_CommonSupport_global_var_count;
#endif

#define CommonSupport_DEF_CMD(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    EXTERN_C void CommonSupport_NAME(_index, _szEgName)(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);
    CommonSupport_DEF(CommonSupport_DEF_CMD) // 所有实现命令的声明

        
#endif
