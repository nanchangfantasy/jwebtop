//////////////////////////////////////////////////////////////////////////  
/// ����fastipc�õ������ݽṹ�ͱ���  
///  
/// @version	1.0 
/// @author		washheart@163.com
/// @date       2015-10-22  
////////////////////////////////////////////////////////////////////////// 
#pragma once

#ifndef FastIPC_model_H
#define FastIPC_model_H
#include <Windows.h>
#include <string>

// ������������
#define ERR_ServerCreate        100 // ����������ʧ��
#define ERR_ClientCreate		101	// �ͻ��˴���ʧ��
#define ERR_EventCreate_W		201 // ����������д�¼�ʧ��
#define ERR_EventCreate_R		202 // �������������¼�ʧ��
#define ERR_EventOpen_W			203 // �ͻ��˴�д�¼�ʧ��
#define ERR_EventOpen_R			204 // �ͻ��˴򿪶��¼�ʧ��
#define ERR_EventWait_W			205 // �ͻ��˵ȴ���д�¼�ʧ��
#define ERR_EventWait_R			206 // �������ȴ��ɶ��¼�ʧ��
#define ERR_MappingCreate       301	// ����������ӳ���ļ�ʧ��
#define ERR_MappingOpen			302	// ���ͻ��˴�ӳ���ļ�ʧ��
#define ERR_MappingMap			303 // ������/�ͻ���ӳ���ڴ��ļ�ʧ��

#define PACK_ID_LEN				100	// MemBuff�ṹ��packId�ĳ���

// ������Ϣ���ͳ���
#define MSG_TYPE_NORMAL			0	// ��������Ϣ
#define MSG_TYPE_PART			1	// ����Ϣ��һ�������ݵ�һ����
#define MSG_TYPE_END			2	// ����Ϣ��һ�������ݵĽ�β

// �����ڴ�״̬����
#define MEM_CAN_WRITE			0	 // �ڴ洦�ڿ�д״̬
#define MEM_CAN_READ			1	// �ڴ洦�ڿɶ�״̬
#define	MEM_IS_BUSY				2	// �ڴ洦��æµ״̬�������ڶ���Ҳ������д��

namespace fastipc{
	// ���干���ڴ������ݽṹ
	struct MemBuff{

		/// �ڴ�״̬��ȡֵ[MEM_CAN_WRITE��MEM_CAN_READ��MEM_IS_BUSY]
		/// ��ʼ״̬Ϊ��дMEM_CAN_WRITE��
		volatile LONG	state = MEM_CAN_WRITE;	

		/// ������Ϣ�����ͣ�ȡֵ[MSG_TYPE_NORMAL��MSG_TYPE_PART��MSG_TYPE_END]
		/// ��ʼ״̬Ϊ��дMSG_TYPE_NORMAL��
		LONG			msgType;

		/// ���ڲ����Ƿ���ʧ�ܺ��ط������⣬�ҷ���ʱ��˳���ͣ����Կ��Ա�ҪpackIdx������
		/// ��һ�������ݿ鱻���ʱ�����������packIdx=-1,���ÿ�����װ����
		//  LONG			packIdx;		

		// ��һ�������ݱ���ַ���ʱ��ͨ��packId����ֵĿ���֯��һ��packIdһ��ȡuuid
		char			packId[PACK_ID_LEN];	

		/// ��ǰ�ڴ湲�����е���Ч���ݵĳ��� 
		DWORD			dataLen;

		/// ����������ݡ�
		/// ע�ⲻҪ����������鳤�������ţ�ʵ�ʴ��������ݳ�����Server��Client��blockSize�����ơ�
		/// �������������ǽṹ�����һ��Ԫ�ص��ص���ʵ�ֶ�̬����Ĺ��ܣ��Ա�Server��Client��ָ����������С��
		char			data[1];				
	};

	// �������ݶ�ȡ������ݽṹ����MemBuf����Ҫ������data�Ǹ�ָ�루�ڱ�����������������Ҳ���㣩
	struct _declspec(dllexport)  MemBlock{
		LONG			msgType;
		char			packId[PACK_ID_LEN];
		DWORD			dataLen;
		char*			data = NULL;
		~MemBlock(){ if (data)delete[] data;/*����������ڴ�*/ }
	};
	/// ���ɷ�������ƣ�����������������д�¼����ڴ��ļ����ڴ���fastipc�ķ����ʱʹ��
	/// @return �������ɵķ��������ƣ��˴�������һ��uuid
	_declspec(dllexport) 	std::wstring genServerName();

	/// ���ɷ�������ƣ�����������������д�¼����ڴ��ļ���һ�����ڿͻ����ٴδ��������������Ӧ����˵Ļ�д��ʱ��ʹ��
	/// @param servername �ͻ��˵�ǰ��Ӧ�ķ������˵�����
	/// @return һ���µķ�������ƣ��˴�Ϊ��servername_c
	_declspec(dllexport) std::wstring genServerName(const std::wstring servername);

	/// ���ݷ���������������ڴ���д����¼�������
	/// @param servername �������˵�����
	/// @return д����¼������ƣ��˴�Ϊ��servername_w
	_declspec(dllexport) std::wstring genWritedEventName(const std::wstring servername);

	/// ���ݷ���������������ڴ���������¼�������
	/// @param servername �������˵�����
	/// @return ������¼������ƣ��˴�Ϊ��servername_r
	_declspec(dllexport) std::wstring genReadedEventName(const std::wstring servername);

	/// ���ݷ���������������ڴ����ڴ�ӳ���ļ�������
	/// @param servername �������˵�����
	/// @return �ڴ�ӳ���ļ������ƣ��˴�Ϊ��servername_m
	_declspec(dllexport) std::wstring genMappingFileName(const std::wstring servername);
};
#endif