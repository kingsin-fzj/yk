
// youkuprint_V01.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cyoukuprint_V01App:
// �йش����ʵ�֣������ youkuprint_V01.cpp
//

class Cyoukuprint_V01App : public CWinApp
{
public:
	Cyoukuprint_V01App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cyoukuprint_V01App theApp;