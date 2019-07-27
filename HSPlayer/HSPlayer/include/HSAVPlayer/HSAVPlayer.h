#ifndef __HSAVPLAYER_H__
#define __HSAVPLAYER_H__

#include "AVPlayerDef.h"

#ifdef __cplusplus
extern "C"{
#endif

//1 初始化
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Initial( );

//2 释放资源
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Free();

//3 打开文件,如果成功 则返回0,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenRecFile(  char * sFileName, HANDLE * handle);

//4 关闭文件
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseRecFile( HANDLE handle );

//5 获取文件播放时间
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetFileTotalTime( HANDLE handle, long *lTime );

//6 打开音视频
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenStream(AV_STREAM_INFO* pStreamHead, HANDLE * handle);

//7 关闭视频流, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseStream( HANDLE handle );

//8 数据输入函数
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_InputData( HANDLE handle, char * buf, long lSize, AV_STREAM_INFO *pStream);

//9 播放声音
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenSound( HANDLE handle );

//10 关闭音频
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseSound(HANDLE handle);

//11 设置音量,取值范围是0- 0Xff
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetVolume( HANDLE handle, long lVolume );

//12 开始播放
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Play( HANDLE handle, HWND hWnd );

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Play2( HANDLE handle, HWND hWnd ,int displayType);

//13 停止播放
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Stop( HANDLE handle );

//14 暂停,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Pause( HANDLE handle, long lPause );

//15 设置文件回放位置
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetPlayTime( HANDLE handle, long lSecond );

//16 获取文件回放时长
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetPlayTime( HANDLE handle, long * lSecond );

//17 设置播放速度, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSpeed( HANDLE handle, long lSpeed );

//18 获取播放速递
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetSpeed( HANDLE handle,long *lSpeed );

//19 单帧播放,单帧往后回放
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OneByOne( HANDLE handle );

//20 抓拍
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Snapshot( HANDLE handle, const char * sFileName,long lPicType = 0 );
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Snapshot( HANDLE handle, const char * sFileName,enum HsCaptureType lPicType);
#endif
//21 刷新函数
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_Refresh( HANDLE handle );

//22 获取图像大小,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetPictureSize( HANDLE handle, long * lWidth, long * lHeight );


//24 设置显示回调函数,
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDrawCallBack( HANDLE hHandle, HsDrawCallback DrawCallBack, void* lpcContext );

//25 放大显示指定区域
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_ShowRect( HANDLE handle, RECT *pRect );

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_PaintShape(HANDLE hHandle,AV_PAINT_PARAM* paintParam,int nCount);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_PaintClean(HANDLE hHandle);

//26 加速多个实例对象的退出,加速多个实例的退出
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetStopFlag( HANDLE handle );

//27录像 时间秒
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord( HANDLE handle, const char* filename, int second);
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord2( HANDLE handle, const char* filename, int second,int frameRate=0);
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecord2( HANDLE handle, const char* filename, int second,int frameRate);
#endif

//28停止录像
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopRecord( HANDLE handle );

//27录像 时间秒
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother( HANDLE handle, const char* filename, int second);
#ifdef WIN32
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother2( HANDLE handle, const char* filename, int second,int frameRate=0);
#else
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartRecordAnother2( HANDLE handle, const char* filename, int second,int frameRate);
#endif

//28停止录像
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopRecordAnother( HANDLE handle );

//29设置缓存中的帧数,增加流畅度,同时会增加延时 nFrame 一般不要大于60
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetFrameCache( HANDLE handle,unsigned long nFrame );

//32 消息回调函数
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetMSGCallBack( HANDLE handle,HsAVMessageCallBack msgCallBack ,void* lpContext);

//33 视频回调函数
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetAVDataCallBack( HANDLE handle, HsAVDataCallBack avCallBack , void* lpContext);

//34获取视频缓存区中的帧数
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetVideoFrame( HANDLE handle,  long *frame);

//35清空视频和音频缓存区
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_ResetVideoBuffer( HANDLE handle);

//36获取音视频参数,2012.7.2 add
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetStreamInfo( HANDLE handle, AV_STREAM_INFO*pInfo);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetStreamInfo( HANDLE handle, AV_STREAM_INFO *pInfo);

//37设置解码回调,2012.7.3 add

#ifdef HXHT_PLAYER

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDecodeCallBack( HANDLE handle, HXHT_DecodeCallBack decfun, long param);

#else

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetDecodeCallBack( HANDLE handle, HsDecodeCallBack decfun, void* lpcontext);
#endif

//获取视频缓存区状态
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_GetVideoBufferInfo( HANDLE handle,  int *total, int *stock, int *frames);

//设置屏幕撕裂控制, ctrl=0(默认),资源暂用比较高      <0 不控制
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetVertBlank( HANDLE handle,  long ctrl);

#ifdef WIN32
//设置视频分片图像
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSliceImage( HANDLE handle,HWND hWnd,int nSeek=0);

//从录像文件抓拍
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile(const char * sRecFileName, const char * sPicFileName,int nSeek = 0,int lPicType = 0,int quality = 80 );

//从录像文件抓拍
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile2(const char * sRecFileName, int fileType,const char * sPicFileName,int nSeek = 0,int lPicType = 0,int quality = 80 );

HSAVPLAYER_API void HSAVPLAYER_CALLBACK HS_SetWindowMode(HANDLE handle,int wndMode);

HSAVPLAYER_API void HSAVPLAYER_CALLBACK HS_SetLookAtParam(HANDLE handle,int winIndex,AV_LOOKAT_PARAM *lookatParam);

//打开采集声音
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenCaptureSound(HANDLE * handle,int audioCode,int nSamplesPerSec=8000,int wBitsPerSample=16,int nChannels=1);
#else
//设置视频分片图像
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SetSliceImage( HANDLE handle,HWND hWnd,int nSeek);

//从录像文件抓拍
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_SnapshotFromFile(const char * sRecFileName, const char * sPicFileName,int nSeek,int lPicType,int quality );

//打开采集声音
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenCaptureSound(HANDLE * handle,int audioCode,int nSamplesPerSec,int wBitsPerSample,int nChannels);
#endif
//开始采集
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StartCaptureSound(HANDLE handle);
//停止采集
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_StopCaptureSound(HANDLE handle);
//关闭采集声音
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseCaptureSound(HANDLE handle);

//6 打开音视频
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_OpenStreamRecord(char* filename,AV_STREAM_INFO* pStreamInfo, HANDLE * handle);

HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_InputRecordData( HANDLE handle, char * buf, long lSize, AV_STREAM_INFO *pStream);
//7 关闭视频流, 
HSAVPLAYER_API long HSAVPLAYER_CALLBACK HS_CloseStreamRecord( HANDLE handle );

#ifdef __cplusplus
}
#endif

#endif