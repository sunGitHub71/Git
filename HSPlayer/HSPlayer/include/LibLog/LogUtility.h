// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LOGUTILITY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LOGUTILITY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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

// Log����
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

// ����log�������Ϊ,LogFileNameΪ��ӡlog���ļ�,levelΪ��ӡ��log����
// LogFormatΪlog��ӡ�ĸ�ʽ,Ĭ��Ϊ"%d %c %p: %m%n"
// %c,log���������,%d ����ʱ��,%m ��Ϣ,%n ���з�
// %p,����,%R ��1970��1��1��0ʱ��ʼ��ĿǰΪֹ��������
// %u ���̿�ʼ��ĿǰΪֹ��ʱ����������
// ע��:ȫ�ֶ�������NotSet����
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
