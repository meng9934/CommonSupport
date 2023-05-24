#include "include_CommonSupport_header.h"

//TODO 静态库需要的部分,会记录所有的函数名到数组里,静态编译的时候需要取回命令名
#if !defined(__E_STATIC_LIB)
static ARG_INFO g_argumentInfo_CommonSupport_global_var[] = 
{
    // 1=参数名称, 2=参数详细解释, 3=指定图像索引,从1开始,0表示无, 4=图像数目(用作动画)
    // 5=参数类型, 6=参数默认值,   7=参数标志 AS_ 开头常量
    // AS_HAS_DEFAULT_VALUE         有默认值,倒数第二个参数是默认值
    // AS_DEFAULT_VALUE_IS_EMPTY    默认值为空,有可空标志
    // AS_RECEIVE_VAR               只能传递变量,相当于传引用,传递过来的肯定不是数组
    // AS_RECEIVE_VAR_ARRAY         传递过来的肯定是数组变量引用
    // AS_RECEIVE_VAR_OR_ARRAY      传递变量或者数组变量引用
    // AS_RECEIVE_ARRAY_DATA        传递数组
    // AS_RECEIVE_ALL_TYPE_DATA     传递数组/非数组
    // AS_RECEIVE_VAR_OR_OTHER      可以传递 变量/数据/返回值数据


	/*000*/	{"延时时间","毫秒",0,0, (DWORD)SDT_INT, 0, 0},
	/*001*/	{"传入变量","传入要保存到内存的变量",0,0, (DWORD)_SDT_ALL, 0, 0},
	/*002*/	{"内存指针","传入要还原到变量的内存首指针地址",0,0, (DWORD)SDT_INT, 0, 0},
	/*003*/	{"还原变量","参考型，传入要还原到变量，变量类型必须跟传入保持一置。",0,0,(DWORD)_SDT_ALL, 0, AS_RECEIVE_VAR},
	/*004*/	{"传入变量","传入自定义类型，如包含文本型数据字节集，文本型字节集只能在最前面。",0,0, (DWORD)_SDT_ALL, 0, 0},
	/*005*/	{"文本参数量","指定结构中所包含的文本参+字节集参数总量,文本参数只能在最前面,如果被省略，则默认不带文本型字节集。",0,0, (DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*006*/	{"自定义指针","要还原的自定义到指针地址",0,0, (DWORD)SDT_INT, 0, 0},
	/*007*/	{"自定义类型变量","参考 自定义类型变量",0,0, (DWORD)_SDT_ALL, 0, AS_RECEIVE_VAR},
	/*008*/	{"标签句柄","反馈事件的标签句柄。",0,0,(DWORD)SDT_INT, 0, 0},
	/*009*/	{"信息值1","标签反馈事件参数1",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*010*/	{"信息值2","标签反馈事件参数2",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*011*/	{"子程序指针","本参数提供创建线程时欲启动的子程序指针。",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*012*/	{"参数数据","本参数可接受任意多整数型参数。",0,0,(DWORD)SDT_INT, 0, 0},
	/*013*/	{"子程序指针","本参数提供创建线程时欲启动的子程序指针。",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*014*/	{"参数数据","本参数可接受任意多文本型参数。",0,0,(DWORD)SDT_TEXT, 0, 0},
	/*015*/	{"子程序指针","本参数提供创建线程时欲启动的子程序指针",0,0,(DWORD)SDT_SUB_PTR, 0, 0},
	/*016*/	{"回调子程序指针","可为空，被执行函数所要返回接收函数,回调函数样版:\r\n.版本 2\r\n.子程序 回调函数\r\n.参数 参数一, 整数型",0,0,(DWORD)SDT_SUB_PTR, 0, AS_DEFAULT_VALUE_IS_EMPTY},
	/*017*/	{"最小线程数","设置线程池中最小的线程数，如果小于2将被设置为2线程。",0,0,(DWORD)SDT_INT, 0, 0},
	/*018*/	{"最大线程数","设置线程池中最大的线程数，如果小于4将被设置为4线程。",0,0,(DWORD)SDT_INT, 0, 0},
	/*019*/	{"传递参数","被执行函数所要传递的参数",0,0,(DWORD)SDT_INT, 0, 0},
	/*020*/	{"参数数据","本参数可接受任意多整数型参数。",0,0,(DWORD)SDT_INT, 0, 0},
	/*021*/	{"参数数据","本参数可接受任意多文本型参数。",0,0,(DWORD)SDT_TEXT, 0, 0},
	/*022*/	{"销毁方式","0=正常销毁（清空任务池，等待当前任务执行后返回 真），1=强制销毁（强制销毁线程池。立即返回 真  注意：此方式执行后强制销毁线程池，强烈不建议使用，会造成内存泄露。）",0,0,(DWORD)SDT_INT, 0, 0},
	/*023*/	{"最长等待时间","此参数只对正常销毁有效。单位：毫秒，留空或 0 一直等待。 否则到了超时时间会立即返回 假 。",0,0,(DWORD)SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};

#ifdef _DEBUG    // 这里是为了确认参数序号是否正确, 成员数比最后一个序号大1就是正确
const int dbg_cmd_arg_count__ = sizeof(g_argumentInfo_CommonSupport_global_var) / sizeof(g_argumentInfo_CommonSupport_global_var[0]);
#endif


#define CommonSupport_DEF_CMDINFO(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    { _szName, ______E_FNENAME(_szEgName), _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo },


// 易语言每个命令的定义, 会把信息显示在支持库列表里, 这里每个成员都是详细的描述一个命令的信息
CMD_INFO g_cmdInfo_CommonSupport_global_var[] = 
{
    CommonSupport_DEF(CommonSupport_DEF_CMDINFO)
};

int g_cmdInfo_CommonSupport_global_var_count = sizeof(g_cmdInfo_CommonSupport_global_var) / sizeof(g_cmdInfo_CommonSupport_global_var[0]);

#endif

