// Ping.h: interface for the CPing class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PING_H__7B1A4E57_B538_4BE8_B8DF_FE9293876EE9__INCLUDED_)
#define AFX_PING_H__7B1A4E57_B538_4BE8_B8DF_FE9293876EE9__INCLUDED_

#include <winsock2.h>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPing  
{
	typedef struct tagICMP_HEADER
	{
		BYTE i_type;         //ICMP��������
		BYTE i_code;         //ICMP����
		USHORT i_cksum;      //�����
		USHORT i_id;         //��ʾ��
		USHORT i_seq;        //���к�
		DWORD  timestamp;    //ʱ���
	}IcmpHeader,ICMP_HEADER;
	typedef struct tagIP_HEADER
	{
		unsigned int h_len:4;     //IP�ײ�����
		unsigned int version:4;    //IP�İ汾
		unsigned char tos;         //��������
		unsigned short total_len;  //�ܵ����ݰ���С
		unsigned short ident;      //�����ʾ��
		unsigned short frag_and_flags; //��ʾ
		unsigned char ttl;
		unsigned char protocol;     //Э��
		unsigned short checksum;    //У���
		unsigned int sourceIP;      //ԭ��ַ
		unsigned int destIP;        //Ŀ���ַ
	}IpHeader,IP_HEADER;
	typedef struct   ip_option_hdr 
	{ 
		unsigned   char   code;    
		unsigned   char   len; 
		unsigned   char   ptr;    
		unsigned   long   addrs[9]; //�����9��IP��ַ�ṹ�� 4��9 ��36 
	}IpOptionHeader;    
#define DEF_PACKET_SIZE 32
#define ICMP_ECHO 8
	/*���IPͷ����*/
#define MAX_IP_HDR_SIZE 60
	/*��С��ICMP���ݱ���С*/
#define ICMP_MIN 8
	/*ICMP�������ͣ�����Ӧ��*/
#define ICMP_ECHOREPLY 0
	/*��ʾҪ��¼·��*/
#define IP_RECORD_ROUTE 7
#define IP_OPTIONS 1
	/*����ICMP���ݱ���С*/
#define MAX_PACKET 1024
public:
	USHORT GenerateIPChecksum(USHORT *pBuffer,int nSize);
	//void usage(char *progname);
	//void ValidateArgs(int argc,char **argv);    //��֤�������
	void DecodeIPOptions(char *buf,int bytes);   //����IPѡ��
	void Cleanup();  //�ͷ�Winsock���ӿ�
	void Ping(CString & info);
	void SetScoket(int timeout=1100);
	//����IPͷ
	void DecodeICMPHeader(char *buf,int bytes,SOCKADDR_IN *from,CString &info,DWORD i);
	//���ɼ����
	USHORT checksum(USHORT *buff,int size);
	//��ʼ��ICMP����
	void FillICMPData(char *icmp_data,int datasize);
	CPing(char *_lpdest);
	virtual ~CPing();


public:
	//friend class CThroughputTestClientDlg;
	SOCKET m_hSocket;
	IpOptionHeader  m_ipopt;   //IPѡ��ͷ;
	SOCKADDR_IN  m_addrDest;   //Ŀ���ַ
	SOCKADDR_IN  m_addrFrom;   //Դ��ַ
	char *icmp_data;           //ICMP����;
	char *recvbuf;             //���ջ���
	USHORT seq_no;             //�������к�
	char *lpdest;
	int  datasize;
	BOOL m_bRecordRout;
};

#endif // !defined(AFX_PING_H__7B1A4E57_B538_4BE8_B8DF_FE9293876EE9__INCLUDED_)
