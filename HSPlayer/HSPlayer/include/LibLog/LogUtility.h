// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LOGUTILITY_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LOGUTILITY_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef __LOGUTILITY_LIBRARY_INCLUDE_H__
#define __LOGUTILITY_LIBRARY_INCLUDE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HW_DEFAULT_LOG_FILE        "HwLogMessage.log"
#define HW_DEFAULT_LOG_FILE_SIZE   (100 * 1024 * 1024)
#define HW_DEFAULT_LOG_FILE_INDEX   10
#define HW_DEFAULT_LOG_FORMAT       "<%d><%p><%x>:%m%n"

#define HW_DEFAULT_STDOUT			1
#define HW_DEFAULT_STDOUT_FORMAT    "<%d><%p><%x>:%m%n"

#define HW_DEFAULT_LOG_LEVEL        log_error

#ifdef _WIN32
#define HWLOGFUN_CALL  __stdcall
#else
#define HWLOGFUN_CALL  
#endif

// Log级别
typedef enum __enumLogLevel{
	log_fatal = 0,
	log_alert  = 100,
	log_crit   = 200,
	log_error  = 300, 
	log_warn   = 400,
	log_notice = 500,
	log_info   = 600,
	log_debug  = 700,
}HwLogLevel;

void HWLOGFUN_CALL Hw_Set_Log_Config_File(const char* sConfigFile);

void HWLOGFUN_CALL Hw_Set_Log_Level(HwLogLevel eLevel);

// 设置log对象的行为,LogFileName为打印log到文件,level为打印的log级别
// LogFormat为log打印的格式,默认为"%d %c %p: %m%n"
// %c,log对象的名字,%d 日期时间,%m 消息,%n 换行符
// %p,级别,%R 从1970年1月1日0时开始到目前为止的秒数；
// %u 进程开始到目前为止的时钟周期数；
// 注意:全局对象不能用NotSet级别
void HWLOGFUN_CALL Hw_Set_Log_File(const char* fileName,unsigned int maxFileSize ,unsigned int maxBackupIndex,const char* sLogFormat);

// 1 print to stdout, 0 no
void HWLOGFUN_CALL Hw_Set_Log_Stdout(int printStdout,const char* sLogFormat);

void HWLOGFUN_CALL Hw_Write_Log(HwLogLevel eLevel,const char* sFuntion, const char* sContext,...);

void HWLOGFUN_CALL Hw_Write_Log2(const char* logObjectName,HwLogLevel eLevel,const char* sFuntion, const char* sContext,...);

#ifdef _WIN32
#define HW_WRITE_LOG(level,context,...) Hw_Write_Log(level,__FUNCTION__,context, __VA_ARGS__)
#else
#define HW_WRITE_LOG(level,context...) Hw_Write_Log(level,__FUNCTION__,context)
#endif

#ifdef _WIN32
#define HW_WRITE_LOG2(objName,level,context,...) Hw_Write_Log2(objName,level,__FUNCTION__,context, __VA_ARGS__)
#else
#define HW_WRITE_LOG2(objName,level,context...) Hw_Write_Log2(objName,level,__FUNCTION__,context)
#endif
#ifdef __cplusplus
}
#endif
#endif //__LOGUTILITY_LIBRARY_INCLUDE_H__
