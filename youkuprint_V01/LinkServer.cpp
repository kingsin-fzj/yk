// lientSocket.cpp: implementation of the ClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LinkServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define RECV_BUFF_LEN                   20480
char recvBuf[RECV_BUFF_LEN];

/* CS���ݽṹ��     */
/* ��Ϣ��ͷ�Ľṹ�� */
typedef struct csHead
{
	int     cmd;                                                                    // �����
	int     subCmd;                                                                 // ������
	int     args;                                                                   // ������Ŀ
	char    pDBName[32];                                                            // �������ݿ�����
}CSHEAD;

/* ��Ϣ�������ݲ��ֵĽṹ�� */
typedef struct csData
{
	int     tag;                                                                    // ����������ʶ
	char    pQueryField[32];                                                        // �ֶ����������
	char    pSql[512];                                                              // SQL�������
}CSDATA;

/* SC���ݽṹ��     */
/* ��Ϣ��ͷ�Ľṹ�� */
typedef struct scHead
{
	int     cmd;                                                                    // �����
	int     args;                                                                   // ������Ŀ
}SCHEAD;

/* ��Ϣ�������ݲ��ֵĽṹ�� */
typedef struct scData
{
	int     tag;                                                                    // ����������ʶ
	int     rtnValue;                                                               // �����������ֵ
	char    pQueryFieldValues[128];                                                 // ��¼��ѯ��Ĳ�ѯֵ
}SCDATA;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ClientSocket::ClientSocket()
{

}

ClientSocket::~ClientSocket()
{

}

bool ClientSocket::ConnectServer(CString ip,int port)
{

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested=MAKEWORD(2,2);

	if (WSAStartup(wVersionRequested,&wsaData)!=0)
	{
		//MessageBox("")
		WSACleanup();
		return false;
	}

	clientconn= socket(AF_INET,SOCK_STREAM,0);
	if (clientconn==INVALID_SOCKET)
	{
		closesocket(clientconn);
		AfxMessageBox("������������ʧ��!",MB_ICONERROR);
		//m_result.SetWindowText(NULL);
		return false;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_addr.s_addr=inet_addr(ip.GetBuffer(ip.GetLength()));
	addrSrv.sin_port=htons(port);

	if (connect(clientconn, (SOCKADDR *)&addrSrv,sizeof(addrSrv)) == SOCKET_ERROR) 	{
		AfxMessageBox("�������ݿ��쳣������IP�Ͷ˿�",MB_ICONERROR);
		WSACleanup();  
		closesocket(clientconn);
		return false;
	}
	return true;
}

bool ClientSocket::SendCheckSnCmd(CString sn)
{
	CString GetMacCmd="CHECK SN::"+sn+"0xFF";
	char *CGetMacCmd=GetMacCmd.GetBuffer(GetMacCmd.GetLength());
	int lenstr=strlen(CGetMacCmd);
	int len=send(clientconn,CGetMacCmd,strlen(CGetMacCmd),0);
	if (len=strlen(CGetMacCmd))
	{
		return true;
	}
	return false;
}


bool ClientSocket::GetInfo(CString &info)
{
	int len=0;
	char cinfo[256];
	ZeroMemory(cinfo,sizeof(cinfo));
	do 
	{
		if ((len=recv(clientconn,cinfo,sizeof(cinfo),0))>0)
		{
			CString strbuff=cinfo;
			info=info+strbuff;
			ZeroMemory(cinfo,sizeof(cinfo));
		}
		else
		{
			return false;
		}
	} while (info.Find("0xFF")==-1);
	info=info.Mid(0,info.Find("0xFF"));
	return true; 
}

void ClientSocket::CloseSocket()
{
	closesocket(clientconn);
	WSACleanup();
}

/*********************************************************************************************************************/
/* �������ƣ�mySocketSend                                                                                            */
/* ��������������������ͨ�ţ�����/����/��ѯSQL��                                                                   */
/* ��ڲ�����sqlName�����ݿ�����֣�,cmd(SQL���),parameter1������ţ�������߸���0x00020001����ѯ0x00020002��       */
/*           parameter2(Ԥ��)                                                                                        */
/* ���ڲ������ɹ���TRUE��,ʧ�ܣ�FALSE��                                                                              */
/* ȫ�ֱ�����                                                                                                        */
/* ����ģ�飺                                                                                                        */
/* ��    �ߣ�������                                                                                                  */
/* ��    �ڣ�2014��12��31��                                                                                          */
/* ----------------------------------------------------------------------------------------------------------------- */
/* �� �� �ˣ�                                                                                                        */
/* ��    �ڣ�                                                                                                        */
/* ----------------------------------------------------------------------------------------------------------------- */
/*********************************************************************************************************************/

BOOL ClientSocket::mySocketSend(CString sqlName, CString cmd, CString parameter1, int parameter2)
{
	int len = 0;
	int sendlen = 24;
	CString sendStr = "";
	CString sqlNameLenStr = "";
	CString sqlCMDLenStr = "";
	CString sqlCMDEndFlag = "FFFFFFFF";                                     // Э�������ʶ

	len = strlen(parameter1);
	if (10 != len)
	{
		return FALSE;
	}
	parameter1 = parameter1.Mid(2);

	len = strlen(sqlName);
	sqlNameLenStr.Format("%08X", len);

	len = strlen(cmd);
	sqlCMDLenStr.Format("%08X", len);

	sendStr = parameter1 + sqlNameLenStr + sqlName + sqlCMDLenStr + cmd + sqlCMDEndFlag;
	sendlen = sendStr.GetLength();

	char *pSendBuffer = new char[sendlen+10];
	if (NULL == pSendBuffer)
	{
		return FALSE;
	}
	memset(pSendBuffer, 0, sendlen+10);
	memcpy(pSendBuffer, sendStr, sendlen);

	send(clientconn, pSendBuffer, sendlen, 0);

	delete [] pSendBuffer;

	return TRUE;
}
/*********************************************************************************************************************/
/* �������ƣ�mySocketReceive                                                                                         */
/* �������������ղ��������������Ϣ                                                                                  */
/* ��ڲ�����                                                                                                        */
/* ���ڲ�����ʧ�ܣ�"ERROR"��,����������Ӧֵ                                                                          */
/* ȫ�ֱ�����                                                                                                        */
/* ����ģ�飺                                                                                                        */
/* ��    �ߣ�������                                                                                                  */
/* ��    �ڣ�2014��12��20��                                                                                          */
/* ----------------------------------------------------------------------------------------------------------------- */
/* �� �� �ˣ�                                                                                                        */
/* ��    �ڣ�                                                                                                        */
/* ----------------------------------------------------------------------------------------------------------------- */
/*********************************************************************************************************************/
CString ClientSocket::mySocketReceive()
{    
	int i;
	int readn;
	int recvlen = 0;
	char *p;
	CString recvCMDStr = "";
	CString recvStr = "";
	CString retRecvStr = "";
	CString retRecvLenStr = "";
	CString strtemp = "";

	memset(recvBuf, 0, RECV_BUFF_LEN);													 // ��ս��ջ���
	readn = recv(clientconn, recvBuf, RECV_BUFF_LEN, 0);						     // ��������
	if (readn < 0)
	{
		return "ERROR";
	}
	recvStr = recvBuf;

	recvCMDStr = recvStr.Mid(0, 8);
	if ("00020010" != recvCMDStr)
	{
		return "ERROR";
	}

	recvCMDStr = recvStr.Right(8);
	if ("FFFFFFFF" != recvCMDStr)
	{
		return "ERROR";
	}

	retRecvLenStr = recvStr.Mid(8, 8);
	//recvlen = _tstoi(LPCTSTR(retRecvLenStr));
	sscanf(retRecvLenStr,"%x",&recvlen);

	if ((recvlen+24) > RECV_BUFF_LEN)
	{
		return "ERROR";
	}

	p = recvBuf + 16;

	for (i = 0; i < recvlen; i++)
	{
		strtemp.Format("%c", *(char *)(p+i));
		retRecvStr += strtemp;
	}

	return retRecvStr;
}