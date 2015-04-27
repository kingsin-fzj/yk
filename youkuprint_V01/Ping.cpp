// Ping.cpp: implementation of the CPing class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ping.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPing::CPing(char *_lpdest)
{
	icmp_data=NULL;
	seq_no=0;
	recvbuf=NULL;
	m_bRecordRout=FALSE;
	m_hSocket=INVALID_SOCKET;
	lpdest=_lpdest;
	datasize=DEF_PACKET_SIZE;

	WSADATA wsaDate;
	if (WSAStartup(MAKEWORD(2,2),&wsaDate)!=0)
	{
		AfxMessageBox("WSAStartup() failed!",MB_ICONERROR);
		return;
	}
}

CPing::~CPing()
{

}

USHORT CPing::GenerateIPChecksum(USHORT *pBuffer, int nSize)
{
	unsigned long cksum=0;
	while (nSize>1)
	{
		cksum+=*pBuffer++;
		nSize-=sizeof(USHORT);
	}
	if(nSize)
		cksum+=*(UCHAR *)pBuffer;
	cksum=(cksum>>16)+(cksum&0xffff);
	cksum+=(cksum>>16);
	return (USHORT)(~cksum);
}

//该函数用于填充IcmpHeader报文 这里把报文填充为回显请求报文
void CPing::FillICMPData(char *icmp_data,int datasize)
{
	IcmpHeader *icmp_hdr=NULL;
	char        *datapart=NULL;

	icmp_hdr=(ICMP_HEADER *)icmp_data;
	icmp_hdr->i_type=ICMP_ECHO;          //回显请求
	icmp_hdr->i_code=0;
	icmp_hdr->i_id=(USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum=0;
	icmp_hdr->i_seq=0;
	datapart=icmp_data+sizeof(ICMP_HEADER);
}
// 该函数用于对返回的ICMP应答报文进行解析 得到远程主机信息
void CPing::DecodeICMPHeader(char *buf,int bytes,SOCKADDR_IN *from,CString &info,DWORD i)
{
	IpHeader       *iphdr=NULL; 
	IcmpHeader     *icmphdr=NULL;
	unsigned short iphdrlen;
	DWORD          tick;
	static int     icmpcount=0;

	iphdr=(IpHeader *)buf;
	iphdrlen=iphdr->h_len*4;
	tick=GetTickCount();
	//如果记录路由选项;
	if ((iphdrlen==MAX_IP_HDR_SIZE)&&(!icmpcount))
	{
		DecodeIPOptions(buf,bytes);
	}
	
	if (bytes<iphdrlen+ICMP_MIN)
	{
		AfxMessageBox("Too few bytes",MB_ICONERROR);
	}
	icmphdr=(IcmpHeader*)(buf+iphdrlen);
	//应答报文无法识别

	if (icmphdr->i_type!=ICMP_ECHOREPLY)
	{
	//	AfxMessageBox("nonecho type");
		return;
	}
//	info.Format("%d byte from %s: icmp_seq=%d time:%d ms",bytes,inet_ntoa(from->sin_addr),icmphdr->i_seq,tick-icmphdr->timestamp);
//	printf("%d byte from %s:",bytes,inet_ntoa(from->sin_addr));
//	printf("icmp_seq=%d",icmphdr->i_seq);
//	printf("time:%d ms",tick-icmphdr->timestamp);
//	printf("\n");
	info.Format("Reply from %s: bytes=%d time=%dms TTL=%d",inet_ntoa(from->sin_addr),bytes/2,tick-i,(int)iphdr->ttl);
/*	printf("Reply from %s: bytes=%d ",inet_ntoa(from->sin_addr),bytes/2);
	//	printf("icmp_seq=%d",icmphdr->i_seq);
	printf("time=%dms ",tick-icmphdr->timestamp);
	printf("TTL=%d",(int)iphdr->ttl);
	icmpcount++;*/
	return;
}
//假如程序需要记录路由选项 则必须对接收到的数据解析IP选项
void CPing::DecodeIPOptions(char *buf,int bytes)
{
	IpOptionHeader *ipopt=NULL;
	IN_ADDR        inaddr;
	int            i;
	HOSTENT        *host=NULL; 

	ipopt=(IpOptionHeader *)(buf+20);

	printf("RR:   ");
	for (i=0;i<(ipopt->ptr/4)-1;i++)
	{
		inaddr.S_un.S_addr=ipopt->addrs[i];
		if (i!=0)
		{
			printf("      ");
			
		}
		host=gethostbyaddr((char *)&inaddr.S_un.S_addr,sizeof(inaddr.S_un.S_addr),AF_INET);
		if (host)
		{
			printf("(%-15s)%s\n",inet_ntoa(inaddr),host->h_name);
		}
		else
		{
			printf("(%-15s)\n",inet_ntoa(inaddr));
		}
	}
	return;
}

//程序的多数功能都在这个函数中实现，该函数负责原始套接字的创建、数据的发送和接收，并调用前面几个函数进行初始化和解析报文
void CPing::SetScoket(int timeout)
{
	//创建原始套接字,改涛戒指用于ICMP协议
//	CString info;
	m_hSocket=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);

	if (m_hSocket==INVALID_SOCKET)
	{
	//	printf("WSASocket() failed");
		AfxMessageBox("WSASocket() failed",MB_ICONERROR);
		return;
	}
	//若要求记录路由选项
	if (m_bRecordRout)
	{
		//为每个发送的ICMP数据包加入路由选项 t

		ZeroMemory(&m_ipopt,sizeof(m_ipopt));

		//设置路由选项
		m_ipopt.code=IP_RECORD_ROUTE;     //路由选项
		m_ipopt.ptr=4;                    //地址偏移量
		m_ipopt.len=39;                   //IP选项头长度

		int ret=setsockopt(m_hSocket,IPPROTO_IP,IP_OPTIONS,(char *)&m_ipopt,sizeof(m_ipopt));

		if (ret=SOCKET_ERROR)
		{
		//	printf("setsockopt(IP_OPTIONS) faild");
			AfxMessageBox("setsockopt(IP_OPTIONS) failed",MB_ICONERROR);
			return;
		}

	}

	//设置发送和接受超时值
	int bread=setsockopt(m_hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

	if (bread==SOCKET_ERROR)
	{
		//printf("setsockopt(SO_RCVTIMEO) failed");
		AfxMessageBox("setsockopt(SO_RCVTIMEO) failed",MB_ICONERROR);
		return;
	}

	timeout=1500;//超时值为1000
	if (setsockopt(m_hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		printf("setsockopt(SO_SNDTIMEO) failed");
		return;
	}

	//指定目标地址信息
	memset(&m_addrDest,0,sizeof(m_addrDest));
	m_addrDest.sin_family=AF_INET;
	if ((m_addrDest.sin_addr.s_addr=inet_addr(lpdest))==INADDR_NONE)
	{
		//若输入的地址为计算机名
		struct hostent *hp=NULL;

		if ((hp=gethostbyname(lpdest))!=NULL)
		{
			memcpy(&(m_addrDest.sin_addr),hp->h_addr,hp->h_length);
			m_addrDest.sin_family=hp->h_addrtype;
		//	printf("m_addrDest.sin_addr=%s\n",inet_ntoa(m_addrDest.sin_addr));
		}
		else
		{
		//	printf("gethostbyname() failed\n");
			AfxMessageBox("gethostbyname() failed",MB_ICONERROR);
			return;
		}
	}

	// 创建ICMP报文数据包,先分配内存
	//在调用FILLICMPDAte填充IcmpHeader结构.

	datasize+=sizeof(IcmpHeader);
	icmp_data=(char *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MAX_PACKET);

	recvbuf=(char *)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,MAX_PACKET);
	if (!icmp_data)
	{
		//printf("HeapAlloc() failed");
		AfxMessageBox("HeapAlloc() failed",MB_ICONERROR);
		return;
	}
	memset(icmp_data,0,MAX_PACKET);
	FillICMPData(icmp_data,datasize);

	//开始发送数据
/*	while(true)
	{
		static int nCount=0;
		int        bwrote;

		if (nCount++==4)
		{
			break;
		}

		((IcmpHeader *)icmp_data)->i_cksum=0;
		((IcmpHeader *)icmp_data)->timestamp=GetTickCount();
		((IcmpHeader *)icmp_data)->i_seq=seq_no++;
		((IcmpHeader *)icmp_data)->i_cksum=checksum((USHORT *)icmp_data,datasize);

		bwrote=sendto(m_hSocket,icmp_data,datasize,0,(sockaddr *)&m_addrDest,sizeof(m_addrDest));
		if (bwrote==SOCKET_ERROR)
		{
			if (WSAGetLastError()==WSAETIMEDOUT)
			{
				//m_ping.SetWindowText("Request time out.\r\n");
			//	AfxMessageBox(workPath);
			//	printf("time out \n");
				continue;
			}
			AfxMessageBox("sendto() failed",MB_ICONERROR);
			return;
		}
		if (bwrote<datasize)
		{
			//printf("Wirte %d bytes\n",bwrote);
		}
		int fromlen=sizeof(m_addrFrom);
		bread=recvfrom(m_hSocket,recvbuf,MAX_PACKET,0,(sockaddr *)&m_addrFrom,&fromlen);
		if (bread==SOCKET_ERROR)
		{
			if (WSAGetLastError()==WSAETIMEDOUT)
			{
				printf("time out \n");
				continue;
			}
			printf("recvfrom() failed\n");
			return;
		}
		//对接受的数据惊喜解析
		DecodeICMPHeader(recvbuf,bread,&m_addrFrom);
	}*/
}
void CPing::Ping(CString &info)
{
//	static int nCount=0;
	int        bwrote;
	((IcmpHeader *)icmp_data)->i_cksum=0;
	int i=GetTickCount();
	((IcmpHeader *)icmp_data)->timestamp=i;
	//	((IcmpHeader *)icmp_data)->i_seq=seq_no++;
	((IcmpHeader *)icmp_data)->i_cksum=checksum((USHORT *)icmp_data,datasize);
	
	bwrote=sendto(m_hSocket,icmp_data,datasize,0,(sockaddr *)&m_addrDest,sizeof(m_addrDest));
	if (bwrote==SOCKET_ERROR)
	{
		if (WSAGetLastError()==WSAETIMEDOUT)
		{
			//printf("Request time out.\n");
			info="Request time out.";
		}
		else
		{
			info="Destination host unreachable.";	
		}
		Sleep(1000);
		//AfxMessageBox("sendto() failed",MB_ICONERROR);
		return;
	}
	if (bwrote<datasize)
	{
		//printf("Wirte %d bytes\n",bwrote);
	}
	int fromlen=sizeof(m_addrFrom);
	int bread=recvfrom(m_hSocket,recvbuf,MAX_PACKET,0,(sockaddr *)&m_addrFrom,&fromlen);
	if (bread==SOCKET_ERROR)
	{
		if (WSAGetLastError()==WSAETIMEDOUT)
		{
			info="Request time out.";
			return;
		//	continue;
		}
	//	printf("recvfrom() failed\n");
		return;
	}
	//对接受的数据惊喜解析
	DecodeICMPHeader(recvbuf,bread,&m_addrFrom,info,i);
	Sleep(1000);
}
USHORT CPing::checksum(USHORT *buff,int size)
{
	unsigned long cksum=0;
	while (size>1)
	{
		cksum+=*buff++;
		size-=sizeof(USHORT);
	}
	if(size)
		cksum+=*(UCHAR *)buff;
	cksum=(cksum>>16)+(cksum&0xffff);
	cksum+=(cksum>>16);
	return (USHORT)(~cksum);
}
void CPing::Cleanup()
{
	WSACleanup();
}