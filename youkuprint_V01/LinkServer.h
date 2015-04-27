// lientSocket.h: interface for the ClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIENTSOCKET_H__ABF7536F_68EA_4C13_805A_050417EFC29F__INCLUDED_)
#define AFX_LIENTSOCKET_H__ABF7536F_68EA_4C13_805A_050417EFC29F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <winsock.h>
#pragma comment(lib,"wsock32.lib")
class ClientSocket  
{
private:
	SOCKET clientconn; 
public:
	void CloseSocket();
	bool GetInfo(CString &info);
	bool SendCheckSnCmd(CString sn);
	bool ConnectServer(CString ip,int port);
	CString mySocketReceive();
	BOOL mySocketSend(CString sqlName, CString cmd, CString parameter1, int parameter2);
	ClientSocket();
	virtual ~ClientSocket();

};

#endif // !defined(AFX_LIENTSOCKET_H__ABF7536F_68EA_4C13_805A_050417EFC29F__INCLUDED_)