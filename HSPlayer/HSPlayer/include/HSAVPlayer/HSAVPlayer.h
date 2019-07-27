#ifndef __HSAVPLAYER_H__
#define __HSAVPLAYER_H__

#include "AVPlayerDef.h"

#ifdef __cplusplus
extern "C"{
#endif

//1 ��ʼ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Initial( );

//2 �ͷ���Դ
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Free();

//3 ���ļ�,����ɹ� �򷵻�0,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenRecFile(  char * sFileName, HANDLE * handle);

//4 �ر��ļ�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseRecFile( HANDLE handle );

//5 ��ȡ�ļ�����ʱ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetFileTotalTime( HANDLE handle, long *lTime );

//6 ������Ƶ
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenStream(AV_STREAM_INFO* pStreamHead, HANDLE * handle);

//7 �ر���Ƶ��, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseStream( HANDLE handle );

//8 �������뺯��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_InputData( HANDLE handle, char * buf, long lSize, AV_STREAM_INFO *pStream);

//9 ��������
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenSound( HANDLE handle );

//10 �ر���Ƶ
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseSound(HANDLE handle);

//11 ��������,ȡֵ��Χ��0- 0Xff
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetVolume( HANDLE handle, long lVolume );

//12 ��ʼ����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Play( HANDLE handle, HWND hWnd );

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Play2( HANDLE handle, HWND hWnd ,int displayType);

//13 ֹͣ����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Stop( HANDLE handle );

//14 ��ͣ,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Pause( HANDLE handle, long lPause );

//15 �����ļ��ط�λ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetPlayTime( HANDLE handle, long lSecond );

//16 ��ȡ�ļ��ط�ʱ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetPlayTime( HANDLE handle, long * lSecond );

//17 ���ò����ٶ�, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSpeed( HANDLE handle, long lSpeed );

//18 ��ȡ�����ٵ�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetSpeed( HANDLE handle,long *lSpeed );

//19 ��֡����,��֡����ط�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OneByOne( HANDLE handle );

//20 ץ��
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Snapshot( HANDLE handle, const char * sFileName,long lPicType = 0 );
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Snapshot( HANDLE handle, const char * sFileName,enum HsCaptureType lPicType);
#endif
//21 ˢ�º���
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Refresh( HANDLE handle );

//22 ��ȡͼ���С,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetPictureSize( HANDLE handle, long * lWidth, long * lHeight );


//24 ������ʾ�ص�����,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDrawCallBack( HANDLE hHandle, HsDrawCallback DrawCallBack, void* lpcContext );

//25 �Ŵ���ʾָ������
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_ShowRect( HANDLE handle, RECT *pRect );

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_PaintShape(HANDLE hHandle,AV_PAINT_PARAM* paintParam,int nCount);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_PaintClean(HANDLE hHandle);

//26 ���ٶ��ʵ��������˳�,���ٶ��ʵ�����˳�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetStopFlag( HANDLE handle );

//27¼�� ʱ����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord( HANDLE handle, const char* filename, int second);
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord2( HANDLE handle, const char* filename, int second,int frameRate=0);
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord2( HANDLE handle, const char* filename, int second,int frameRate);
#endif

//28ֹͣ¼��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopRecord( HANDLE handle );

//27¼�� ʱ����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother( HANDLE handle, const char* filename, int second);
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother2( HANDLE handle, const char* filename, int second,int frameRate=0);
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother2( HANDLE handle, const char* filename, int second,int frameRate);
#endif

//28ֹͣ¼��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopRecordAnother( HANDLE handle );

//29���û����е�֡��,����������,ͬʱ��������ʱ nFrame һ�㲻Ҫ����60
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetFrameCache( HANDLE handle,unsigned long nFrame );

//32 ��Ϣ�ص�����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetMSGCallBack( HANDLE handle,HsAVMessageCallBack msgCallBack ,void* lpContext);

//33 ��Ƶ�ص�����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetAVDataCallBack( HANDLE handle, HsAVDataCallBack avCallBack , void* lpContext);

//34��ȡ��Ƶ�������е�֡��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetVideoFrame( HANDLE handle,  long *frame);

//35�����Ƶ����Ƶ������
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_ResetVideoBuffer( HANDLE handle);

//36��ȡ����Ƶ����,2012.7.2 add
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetStreamInfo( HANDLE handle, AV_STREAM_INFO*pInfo);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetStreamInfo( HANDLE handle, AV_STREAM_INFO *pInfo);

//37���ý���ص�,2012.7.3 add

#ifdef HXHT_PLAYER

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDecodeCallBack( HANDLE handle, HXHT_DecodeCallBack decfun, long param);

#else

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDecodeCallBack( HANDLE handle, HsDecodeCallBack decfun, void* lpcontext);
#endif

//��ȡ��Ƶ������״̬
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetVideoBufferInfo( HANDLE handle,  int *total, int *stock, int *frames);

//������Ļ˺�ѿ���, ctrl=0(Ĭ��),��Դ���ñȽϸ�      <0 ������
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetVertBlank( HANDLE handle,  long ctrl);

#ifdef WIN32
//������Ƶ��Ƭͼ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSliceImage( HANDLE handle,HWND hWnd,int nSeek=0);

//��¼���ļ�ץ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile(const char * sRecFileName, const char * sPicFileName,int nSeek = 0,int lPicType = 0,int quality = 80 );

//��¼���ļ�ץ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile2(const char * sRecFileName, int fileType,const char * sPicFileName,int nSeek = 0,int lPicType = 0,int quality = 80 );

HSAVPLAYER_API void HSAVPLAYER_CALLBACK HS_SetWindowMode(HANDLE handle,int wndMode);

HSAVPLAYER_API void HSAVPLAYER_CALLBACK HS_SetLookAtParam(HANDLE handle,int winIndex,AV_LOOKAT_PARAM *lookatParam);

//�򿪲ɼ�����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenCaptureSound(HANDLE * handle,int audioCode,int nSamplesPerSec=8000,int wBitsPerSample=16,int nChannels=1);
#else
//������Ƶ��Ƭͼ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSliceImage( HANDLE handle,HWND hWnd,int nSeek);

//��¼���ļ�ץ��
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile(const char * sRecFileName, const char * sPicFileName,int nSeek,int lPicType,int quality );

//�򿪲ɼ�����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenCaptureSound(HANDLE * handle,int audioCode,int nSamplesPerSec,int wBitsPerSample,int nChannels);
#endif
//��ʼ�ɼ�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartCaptureSound(HANDLE handle);
//ֹͣ�ɼ�
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopCaptureSound(HANDLE handle);
//�رղɼ�����
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseCaptureSound(HANDLE handle);

//6 ������Ƶ
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenStreamRecord(char* filename,AV_STREAM_INFO* pStreamInfo, HANDLE * handle);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_InputRecordData( HANDLE handle, char * buf, long lSize, AV_STREAM_INFO *pStream);
//7 �ر���Ƶ��, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseStreamRecord( HANDLE handle );

#ifdef __cplusplus
}
#endif

#endif