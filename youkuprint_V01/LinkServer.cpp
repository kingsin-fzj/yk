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

/* CS数据结构体     */
/* 消息报头的结构体 */
typedef struct csHead
{
	int     cmd;                                                                    // 命令号
	int     subCmd;                                                                 // 子命令
	int     args;                                                                   // 报文数目
	char    pDBName[32];                                                            // 操作数据库名字
}CSHEAD;

/* 消息报文数据部分的结构体 */
typedef struct csData
{
	int     tag;                                                                    // 数据增量标识
	char    pQueryField[32];                                                        // 字段名或变量名
	char    pSql[512];                                                              // SQL语句内容
}CSDATA;

/* SC数据结构体     */
/* 消息报头的结构体 */
typedef struct scHead
{
	int     cmd;                                                                    // 命令号
	int     args;                                                                   // 报文数目
}SCHEAD;

/* 消息报文数据部分的结构体 */
typedef struct scData
{
	int     tag;                                                                    // 数据增量标识
	int     rtnValue;                                                               // 操作结果返回值
	char    pQueryFieldValues[128];                                                 // 记录查询后的查询值
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
		AfxMessageBox("创建网络链接失败!",MB_ICONERROR);
		//m_result.SetWindowText(NULL);
		return false;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_addr.s_addr=inet_addr(ip.GetBuffer(ip.GetLength()));
	addrSrv.sin_port=htons(port);

	if (connect(clientconn, (SOCKADDR *)&addrSrv,sizeof(addrSrv)) == SOCKET_ERROR) 	{
		AfxMessageBox("连接数据库异常，请检查IP和端口",MB_ICONERROR);
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
/* 函数名称：mySocketSend                                                                                            */
/* 功能描述：与产测服务器通信（插入/更新/查询SQL）                                                                   */
/* 入口参数：sqlName（数据库的名字）,cmd(SQL语句),parameter1（命令号：插入或者更新0x00020001；查询0x00020002）       */
/*           parameter2(预留)                                                                                        */
/* 出口参数：成功（TRUE）,失败（FALSE）                                                                              */
/* 全局变量：                                                                                                        */
/* 调用模块：                                                                                                        */
/* 作    者：刘兴民                                                                                                  */
/* 日    期：2014年12月31日                                                                                          */
/* ----------------------------------------------------------------------------------------------------------------- */
/* 修 改 人：                                                                                                        */
/* 日    期：                                                                                                        */
/* ----------------------------------------------------------------------------------------------------------------- */
/*********************************************************************************************************************/

BOOL ClientSocket::mySocketSend(CString sqlName, CString cmd, CString parameter1, int parameter2)
{
	int len = 0;
	int sendlen = 24;
	CString sendStr = "";
	CString sqlNameLenStr = "";
	CString sqlCMDLenStr = "";
	CString sqlCMDEndFlag = "FFFFFFFF";                                     // 协议结束标识

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
/* 函数名称：mySocketReceive                                                                                         */
/* 功能描述：接收产测服务器返回信息                                                                                  */
/* 入口参数：                                                                                                        */
/* 出口参数：失败（"ERROR"）,其他返回相应值                                                                          */
/* 全局变量：                                                                                                        */
/* 调用模块：                                                                                                        */
/* 作    者：刘兴民                                                                                                  */
/* 日    期：2014年12月20日                                                                                          */
/* ----------------------------------------------------------------------------------------------------------------- */
/* 修 改 人：                                                                                                        */
/* 日    期：                                                                                                        */
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

	memset(recvBuf, 0, RECV_BUFF_LEN);													 // 清空接收缓存
	readn = recv(clientconn, recvBuf, RECV_BUFF_LEN, 0);						     // 接收数据
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