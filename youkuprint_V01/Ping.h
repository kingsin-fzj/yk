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
		BYTE i_type;         //ICMP报文类型
		BYTE i_code;         //ICMP代码
		USHORT i_cksum;      //检验和
		USHORT i_id;         //标示符
		USHORT i_seq;        //序列号
		DWORD  timestamp;    //时间戳
	}IcmpHeader,ICMP_HEADER;
	typedef struct tagIP_HEADER
	{
		unsigned int h_len:4;     //IP首部长度
		unsigned int version:4;    //IP的版本
		unsigned char tos;         //服务类型
		unsigned short total_len;  //总的数据包大小
		unsigned short ident;      //特殊标示符
		unsigned short frag_and_flags; //表示
		unsigned char ttl;
		unsigned char protocol;     //协议
		unsigned short checksum;    //校验和
		unsigned int sourceIP;      //原地址
		unsigned int destIP;        //目标地址
	}IpHeader,IP_HEADER;
	typedef struct   ip_option_hdr 
	{ 
		unsigned   char   code;    
		unsigned   char   len; 
		unsigned   char   ptr;    
		unsigned   long   addrs[9]; //定义成9个IP地址结构， 4＊9 ＝36 
	}IpOptionHeader;    
#define DEF_PACKET_SIZE 32
#define ICMP_ECHO 8
	/*最大IP头长度*/
#define MAX_IP_HDR_SIZE 60
	/*最小的ICMP数据报大小*/
#define ICMP_MIN 8
	/*ICMP报文类型，回显应答*/
#define ICMP_ECHOREPLY 0
	/*表示要记录路由*/
#define IP_RECORD_ROUTE 7
#define IP_OPTIONS 1
	/*最大的ICMP数据报大小*/
#define MAX_PACKET 1024
public:
	USHORT GenerateIPChecksum(USHORT *pBuffer,int nSize);
	//void usage(char *progname);
	//void ValidateArgs(int argc,char **argv);    //验证输入参数
	void DecodeIPOptions(char *buf,int bytes);   //解析IP选项
	void Cleanup();  //释放Winsock链接库
	void Ping(CString & info);
	void SetScoket(int timeout=1100);
	//解析IP头
	void DecodeICMPHeader(char *buf,int bytes,SOCKADDR_IN *from,CString &info,DWORD i);
	//生成检验和
	USHORT checksum(USHORT *buff,int size);
	//初始化ICMP报文
	void FillICMPData(char *icmp_data,int datasize);
	CPing(char *_lpdest);
	virtual ~CPing();


public:
	//friend class CThroughputTestClientDlg;
	SOCKET m_hSocket;
	IpOptionHeader  m_ipopt;   //IP选项头;
	SOCKADDR_IN  m_addrDest;   //目标地址
	SOCKADDR_IN  m_addrFrom;   //源地址
	char *icmp_data;           //ICMP报文;
	char *recvbuf;             //接收缓冲
	USHORT seq_no;             //发送序列号
	char *lpdest;
	int  datasize;
	BOOL m_bRecordRout;
};

#endif // !defined(AFX_PING_H__7B1A4E57_B538_4BE8_B8DF_FE9293876EE9__INCLUDED_)
