#ifndef __AV_PLAYER_DEF_H__
#define __AV_PLAYER_DEF_H__

#ifdef WIN32
#define HSAVPLAYER_CALLBACK CALLBACK
#define HSAVPLAYER_DLL
#ifdef HSAVPLAYER_DLL
#ifdef HSAVPLAYER_EXPORTS
#define HSAVPLAYER_API extern "C" __declspec(dllexport)
#else
#define HSAVPLAYER_API extern "C" __declspec(dllimport)
#endif
#else
#define HSAVPLAYER_API extern "C"
#endif
#else
#define HSAVPLAYER_API
#define HSAVPLAYER_CALLBACK
#ifndef __HS_DATA_TYPE
#define __HS_DATA_TYPE
typedef void* HANDLE;
typedef void* HDC;
typedef void* HWND;
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef DWORD COLORREF;
typedef short SHORT;
typedef long LONG;
typedef unsigned long ULONG;
typedef unsigned int UINT;
typedef struct __rect
{
	int left;
	int top;
	int right;
	int bottom;
}RECT;
#endif
#endif

typedef struct _AV_STREAM_INFO
{
	unsigned short	videoCoder;		//��Ƶ���뷽ʽ
	unsigned short	audioCoder;		//��Ƶ���뷽ʽ
	unsigned short	frameRate;		//֡��
	unsigned short	bitRate;			//������
	unsigned short	nWidth;			// ��Ƶ��
	unsigned short	nHeight;			// ��Ƶ��
	unsigned short	frameType;		// H264֡���� �����涨��
	unsigned short     isKeyFrame;		//�Ƿ�Ϊ�ؼ�֡
	unsigned short	type;			//�������ͣ�0 ��Ƶ�� 1 ��Ƶ  2����ͷ��Ϣ
	unsigned short	res;			//���ֽ�Ϊ������Ƶ���� 0:����ʾ������ʱ�ȴ������п����ٲ���,4:����ʾ������ʱֱ�Ӷ���.���ֽ�Ϊ��������ȡÿһ֡Դ���ݵķ�ʽ 0x1200:ͨ��ff_read_frame����ȡÿһ֡
	unsigned int    nStamp;			// ʱ����Ϣ����λ��
	unsigned int    nStampExt;		// ʱ����Ϣ����λ����
}AV_STREAM_INFO;

typedef struct _AV_STREAM_INFO_EX
{
	unsigned short	videoCoder;		//��Ƶ���뷽ʽ
	unsigned short	audioCoder;		//��Ƶ���뷽ʽ
	unsigned short	frameRate;		//֡��
	unsigned short	videoBitRate;			//������
	unsigned short	nWidth;			// ��Ƶ��
	unsigned short	nHeight;			// ��Ƶ��
	unsigned short	frameType;		// H264֡���� �����涨��
	unsigned short     isKeyFrame;		//�Ƿ�Ϊ�ؼ�֡
	unsigned short	type;			//�������ͣ�0 ��Ƶ�� 1 ��Ƶ  2����ͷ��Ϣ
	unsigned int	res;			//���ֽ�Ϊ������Ƶ���� 0:����ʾ������ʱ�ȴ������п����ٲ���,4:����ʾ������ʱֱ�Ӷ���.���ֽ�Ϊ��������ȡÿһ֡Դ���ݵķ�ʽ 0x1200:ͨ��ff_read_frame����ȡÿһ֡
	int			nStamp;			// ʱ����Ϣ����λ����
	unsigned short audioBitRate;    //��Ƶ����
	unsigned short sampleRate;      //��Ƶ������
	unsigned short channels;        //��Ƶ������
}AV_STREAM_INFO_EX;
//��������ݻص�
typedef struct _AV_FRAME_INFO
{ 
	int nWidth;	 // �������λΪ���أ��������Ƶ������Ϊ0
	int nHeight;	// ����ߣ���λΪ���أ��������Ƶ������Ϊ0
	int nStamp;	 // ʱ����Ϣ����λ����
	int nType;		//�������ͣ����±�
	int nFrameRate;// ����ʱ������ͼ��֡��
}AV_FRAME_INFO; 

typedef struct __tagAVLookAtParam
{
	//����/�ڹ�ģʽ default: vDegrees=0.0f, hDefress=0.0f, depth=getMaxZDepth(handle)
	float vDegrees;
	float hDegrees;
	float Depth;
	//չ��ģʽ Offset:  +move left, -move left, default: 0.0f
	float vOffset;
	float hOffset;
}AV_LOOKAT_PARAM;

typedef struct __tagAvColor
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
	unsigned char alpha;
}AV_COLOR;

typedef struct __tagAvPoint
{
	int x;
	int y;
}AV_POINT;

typedef enum __enumAvPaintShapeType
{
	AV_PAINT_SHAPE_TYPE_LINE,
	AV_PAINT_SHAPE_TYPE_RECTANGLE,
	AV_PAINT_SHAPE_TYPE_CIRCLE,
}AV_PAINT_SHAPE_TYPE;

typedef enum __enumAvLineType
{
	AV_LINE_TYPE_SOLID,
	AV_LINE_TYPE_DOTTED,
}AV_LINE_TYPE;

typedef struct __tagAvPaintParam
{
	int paintId;
	AV_POINT point[4];
	AV_COLOR color;
	int lineWidth;
	AV_LINE_TYPE lineType;
	AV_PAINT_SHAPE_TYPE shapeType;
}AV_PAINT_PARAM;

//�ص���������

//�豸��Ϣ�ص�����
typedef void(HSAVPLAYER_CALLBACK *HsAVMessageCallBack)(HANDLE handle, long msgType,  void*lpStruct, void *lpContext);

//��Ƶ���ݻص�����
typedef void ( HSAVPLAYER_CALLBACK* HsAVDataCallBack )( HANDLE handle, char* pBuf, long nSize, AV_FRAME_INFO* pBufInfo, void *lpContext  );

//��Ƶ��ʾ�ص�����
typedef void ( HSAVPLAYER_CALLBACK* HsDrawCallback )( HANDLE hHandle, HDC hDC, void *lpContext );

//����ص�����
typedef void ( HSAVPLAYER_CALLBACK * HsDecodeCallBack ) ( HANDLE hHandle, char * py, char*pu, char*pv,int ystride,int uvstride, AV_FRAME_INFO * pFrameInfo, void* lpContext  );

//FRAME_INFO.avType
enum AV_Stream_Type
{
	AV_STREAM_VIDEO = 0,
	AV_STREAM_AUDIO,
	AV_STREAM_HEADER,
};


//FRAME_INFO.nalType
#define H264_NAL_TYPE_SLICE      1
#define H264_NAL_TYPE_IDR        5
#define H264_NAL_TYPE_SEI        6
#define H264_NAL_TYPE_SPS        7
#define H264_NAL_TYPE_PPS        8
//#define NAL_TYPE_SEQ_END    9
//#define NAL_TYPE_STREAM_END 10

//FRAME_INFO.videoCoder
#ifndef HS_VIDEO_CODER_H264
#define HS_VIDEO_CODER_H264				96
#define HS_VIDEO_CODER_MJPEG				26
#define HS_VIDEO_CODER_MPEG4				99
#define HS_VIDEO_CODER_H265				150
#define HS_VIDEO_CODER_YUV420           300
#endif

//FRAME_INFO.audioCoder
#define HS_AUDIO_CODER_G711_A				0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define HS_AUDIO_CODER_G711_U				0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define HS_AUDIO_CODER_G726_16KBPS			0x04  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
#define HS_AUDIO_CODER__G726_24KBPS			0x05  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
#define HS_AUDIO_CODER_G726_32KBPS			0x06  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
#define HS_AUDIO_CODER_G726_40KBPS			0x07  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
#define HS_AUDIO_CODER_PCM                  0x13
#define HS_AUDIO_CODER_ADPCM                0x14
#define HS_AUDIO_CODER_AAC                  0x20
enum HsCaptureType
{
	HS_CAPTURE_JPEG = 0,//Ĭ��
	HS_CAPTURE_BMP,
	HS_CAPTURE_PNG,
	HS_CAPTURE_GIF,
};

/*************************** ��Ϣ ********************************/
//״̬��Ϣ
enum HS_MSG_TYPE
{
	//¼��״̬void*lpStruct = char*filename
	HS_MSG_RECORD_BEGIN = 0x100,			//��һ֡����д��ʱ�ص���������Ϣ
	HS_MSG_RECORD_WRITE_ERROR,			//¼���쳣����,д�ļ�ʧ��
	HS_MSG_RECORD_FORMAT_CHANGED,	//����Ƶ��ʽ,�ֱ���,֡�ʷ����ı�,�ڲ��Ѿ�ֹͣ¼��,�������Ҫ¼������Ҫ���µ��ÿ�ʼ¼��, һ�����Ϣ����Ƶ��������
	HS_MSG_RECORD_PACKET_FINISH	,		//¼�������,�ڲ��Ѿ�����ֹͣ¼��,�ⲿֱ���ٵ��ÿ�ʼ¼�񼴿�
	
	//����һ��¼���ļ�,������ר��¼�Ʊ���¼��void*lpStruct = char*filename
	HS_MSG_RECORD_BEGIN_ANOTHER,				//ͬ��
	HS_MSG_RECORD_WRITE_ERROR_ANOTHER,		//ͬ��
	HS_MSG_RECORD_FORMAT_CHANGED_ANOTHER,	//ͬ��
	HS_MSG_RECORD_PACKET_FINISH_ANOTHER,		//ͬ��
	//����ʹ��
	HS_MSG_REPLAY_FINISHED = 0X400,		//�ļ��طŽ���
};

#endif




