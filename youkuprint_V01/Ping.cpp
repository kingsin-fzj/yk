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

//�ú����������IcmpHeader���� ����ѱ������Ϊ����������
void CPing::FillICMPData(char *icmp_data,int datasize)
{
	IcmpHeader *icmp_hdr=NULL;
	char        *datapart=NULL;

	icmp_hdr=(ICMP_HEADER *)icmp_data;
	icmp_hdr->i_type=ICMP_ECHO;          //��������
	icmp_hdr->i_code=0;
	icmp_hdr->i_id=(USHORT)GetCurrentProcessId();
	icmp_hdr->i_cksum=0;
	icmp_hdr->i_seq=0;
	datapart=icmp_data+sizeof(ICMP_HEADER);
}
// �ú������ڶԷ��ص�ICMPӦ���Ľ��н��� �õ�Զ��������Ϣ
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
	//�����¼·��ѡ��;
	if ((iphdrlen==MAX_IP_HDR_SIZE)&&(!icmpcount))
	{
		DecodeIPOptions(buf,bytes);
	}
	
	if (bytes<iphdrlen+ICMP_MIN)
	{
		AfxMessageBox("Too few bytes",MB_ICONERROR);
	}
	icmphdr=(IcmpHeader*)(buf+iphdrlen);
	//Ӧ�����޷�ʶ��

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
//���������Ҫ��¼·��ѡ�� �����Խ��յ������ݽ���IPѡ��
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

//����Ķ������ܶ������������ʵ�֣��ú�������ԭʼ�׽��ֵĴ��������ݵķ��ͺͽ��գ�������ǰ�漸���������г�ʼ���ͽ�������
void CPing::SetScoket(int timeout)
{
	//����ԭʼ�׽���,���ν�ָ����ICMPЭ��
//	CString info;
	m_hSocket=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);

	if (m_hSocket==INVALID_SOCKET)
	{
	//	printf("WSASocket() failed");
		AfxMessageBox("WSASocket() failed",MB_ICONERROR);
		return;
	}
	//��Ҫ���¼·��ѡ��
	if (m_bRecordRout)
	{
		//Ϊÿ�����͵�ICMP���ݰ�����·��ѡ�� t

		ZeroMemory(&m_ipopt,sizeof(m_ipopt));

		//����·��ѡ��
		m_ipopt.code=IP_RECORD_ROUTE;     //·��ѡ��
		m_ipopt.ptr=4;                    //��ַƫ����
		m_ipopt.len=39;                   //IPѡ��ͷ����

		int ret=setsockopt(m_hSocket,IPPROTO_IP,IP_OPTIONS,(char *)&m_ipopt,sizeof(m_ipopt));

		if (ret=SOCKET_ERROR)
		{
		//	printf("setsockopt(IP_OPTIONS) faild");
			AfxMessageBox("setsockopt(IP_OPTIONS) failed",MB_ICONERROR);
			return;
		}

	}

	//���÷��ͺͽ��ܳ�ʱֵ
	int bread=setsockopt(m_hSocket,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

	if (bread==SOCKET_ERROR)
	{
		//printf("setsockopt(SO_RCVTIMEO) failed");
		AfxMessageBox("setsockopt(SO_RCVTIMEO) failed",MB_ICONERROR);
		return;
	}

	timeout=1500;//��ʱֵΪ1000
	if (setsockopt(m_hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout))==SOCKET_ERROR)
	{
		printf("setsockopt(SO_SNDTIMEO) failed");
		return;
	}

	//ָ��Ŀ���ַ��Ϣ
	memset(&m_addrDest,0,sizeof(m_addrDest));
	m_addrDest.sin_family=AF_INET;
	if ((m_addrDest.sin_addr.s_addr=inet_addr(lpdest))==INADDR_NONE)
	{
		//������ĵ�ַΪ�������
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

	// ����ICMP�������ݰ�,�ȷ����ڴ�
	//�ڵ���FILLICMPDAte���IcmpHeader�ṹ.

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

	//��ʼ��������
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
		//�Խ��ܵ����ݾ�ϲ����
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
	//�Խ��ܵ����ݾ�ϲ����
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