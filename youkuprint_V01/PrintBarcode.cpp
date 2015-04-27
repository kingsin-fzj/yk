#include "StdAfx.h"
#include "PrintBarcode.h"
#include <Windows.h>
#include <stdio.h>
#include <WinSpool.h>


CPrintBarcode::CPrintBarcode(void)
{

}


CPrintBarcode::~CPrintBarcode(void)
{
}


/**********************************************************************
* ��������	: Str2SubA
* ��������	: �����ӡ���ã�������õı�ǩ��Ϣ���͸���ӡ����ӡ
* �������  : strDoc-��ǩ��Ϣ
* �������	: ��
* �� �� ֵ	: int   
**********************************************************************/
int CPrintBarcode::SendZPL2Printer(CString strDoc1)
{
	HANDLE hPrinter;
	DOC_INFO_1 DocInfo;
	TCHAR *pszPrinterName;

	TCHAR *RWBuf1;
	DWORD dwBufLength1;
	DWORD dwByteRW = 0;

	memset(&DocInfo,0,sizeof(DOC_INFO_1));
	DocInfo.pDatatype = _T("RAW");
	DocInfo.pDocName = _T("BarCode_2D");
	DocInfo.pOutputFile = NULL;

	dwBufLength1 = strDoc1.GetLength();
	RWBuf1=strDoc1.GetBuffer(strDoc1.GetLength());

	//win95/98
	CPrintDialog pd(FALSE);
	if(!pd.GetDefaults())
	{
		AfxMessageBox(_T("��ȡĬ�ϴ�ӡ��ʧ��"));
		return -1;
	}
	CString strTemp_PrinterName = pd.GetDeviceName();
	pszPrinterName = strTemp_PrinterName.GetBuffer(strTemp_PrinterName.GetLength());

	if(!OpenPrinter(pszPrinterName,&hPrinter,NULL))
		return -2;
	if(!StartDocPrinter(hPrinter,1,(LPBYTE)&DocInfo))
		return -3;
	if(!StartPagePrinter(hPrinter))
		return -4;
	if(!WritePrinter(hPrinter,RWBuf1,dwBufLength1,&dwByteRW))
		return -5;
	if(!EndPagePrinter(hPrinter))
		return -6;
	if(!EndDocPrinter(hPrinter))
		return -7;

	strDoc1.ReleaseBuffer();

	//Win95/98
	strTemp_PrinterName.ReleaseBuffer();

	return 0;
}

/**********************************************************************
* ��������	: Str2SubA
* ��������	: �����ӡ���ã�����������ת��Ϊ�����ӡ����ʶ����ִ�
* �������  : str-��������
* �������	: ��
* �� �� ֵ	: CString
**********************************************************************/
CString CPrintBarcode::Str2SubA(CString str)
{
	int Val_0 = 16;
	int Val_A = 33;
	CString strSubA;
	CString strTmp;

	for (int i = 0; i < str.GetLength(); i++)
	{
		if (str.GetAt(i) >= '0' && str.GetAt(i) <= '9')
		{
			strTmp.Format(_T("%d"), str.GetAt(i)-'0'+Val_0);
			strSubA += strTmp;
		} 
		else if (str.GetAt(i) >= 'A' && str.GetAt(i) <= 'Z')
		{
			strTmp.Format(_T("%d"), str.GetAt(i)-'A'+Val_A);
			strSubA += strTmp;
		}
		if (str.GetAt(i) == '-')
		{
			strTmp.Format(_T("%d"), 13);
			strSubA += strTmp;
		} 
		if (str.GetAt(i) == ';')
		{
			strTmp.Format(_T("%d"), 27);
			strSubA += strTmp;
		} 
	}
	return strSubA;
}

/**********************************************************************
* ��������	: CreateZPLText
* ��������	: �����ӡ���ã���ӡһ���ַ�����֧��Ӣ�ģ�
* �������  : iStartX-��ǩ��ʼX����
iStartY-��ǩ��ʼY����
iHeight-�ַ��߶�
iWidth-�ַ����
strText-�ַ�����
* �������	: ��
* �� �� ֵ	: CString 
**********************************************************************/
CString CPrintBarcode::CreateZPLText(int iStartX,
	int iStartY,
	int iHeight,
	int iWidth,
	CString strText)
{
	CString strZPLCode=_T(""),strData=_T("");
	/*   char strStartX[16] = {0};
	char strStartY[16] = {0};
	char strHeight[16] = {0};
	char strWidth[16] = {0};

	itoa(iStartX, strStartX, 10);
	itoa(iStartY, strStartY, 10);
	itoa(iHeight, strHeight, 10);
	itoa(iWidth, strWidth, 10);*/


	CString strStartX;
	CString strStartY;
	CString strHeight;
	CString strWidth;

	strStartX.Format(_T("%d"),iStartX);
	strStartY.Format(_T("%d"),strStartY);
	strHeight.Format(_T("%d"),iHeight);
	strWidth.Format(_T("%d"),iWidth);
	//�ַ���ʼλ��

	//	strZPLCode = "~DYE:A.TTF,B,T,367112,,";
	strZPLCode = strZPLCode + _T("^FO") + strStartX + _T(",") + strStartY;
	//�ַ�������
	strZPLCode = strZPLCode + _T("^A0N,")+strHeight+_T(",")+strWidth+_T("^FD") + strText +_T("^FS\n");

	return strZPLCode;
}


/**********************************************************************
* ��������	: CreateZPLCode
* ��������	: �����ӡ���ã���ӡһ������ͼ��
* �������  : iStartX-��ǩ��ʼX����
iStartY-��ǩ��ʼY����
iHeight-�����߸߶�
strCode-��������
iWeight-������ϸ�߿�ȣ�Ĭ�ϲ���Ϊ2
* �������	: ��
* �� �� ֵ	: CString
**********************************************************************/
CString CPrintBarcode::CreateZPLCode(int iStartX,
	int iStartY,
	int iHeight,
	CString strCode,
	int iWeight)
{
	CString strZPLCode;
	/*	char strStartX[16] = {0};
	char strStartY[16] = {0};
	char strHeight[16] = {0};
	char strWeight[16] = {0};

	itoa(iStartX, strStartX, 10);
	itoa(iStartY, strStartY, 10);
	itoa(iHeight, strHeight, 10);
	itoa(iWeight, strWeight, 10);
	*/
	CString strStartX;
	CString strStartY;
	CString strHeight;
	CString strWeight;

	strStartX.Format(_T("%d"),iStartX);
	strStartY.Format(_T("%d"),iStartY);
	strHeight.Format(_T("%d"),iHeight);
	strWeight.Format(_T("%d"),iWeight);

	//strZPLCode = "XA^FO100,100^BY3^BCN,100,N,N,N^FD123BBBBBBAAA^FS";

	//��������ʼλ��
	strZPLCode = strZPLCode + _T("^FO") + strStartX + _T(",") + strStartY;
	//����������
	strZPLCode = strZPLCode + _T("^BY") + strWeight + _T("^BCN,") + strHeight + _T(",N,N,N^FD>9") + strCode + _T("^FS\n");
	//strZPLCode = strZPLCode + _T("^BY") + strWeight + _T("^BCN,") + strHeight + _T(",N,N,N^FD") + strCode + _T("^FS\n");
	return strZPLCode;
}

/***********************************************************************
* �������ƣ�PrintEntrance
* �������ܣ����ղ��������ݣ�����Ӧ����
* ���������data-������ݵĽṹ��
data->strCompanyName;          //ZTE����
data->strProductName;          //��Ʒ����
data->strModel;                //����ͺ�
data->strNum;                  //��    ��
data->strZTEMaterialCode;      //���ϱ���
data->strProductionBatch;      //��������
data->strCN;				   //��������
data->EN[i];                   //���к�EN
data->SN[i];                   //���к�SN
* �����������
* �� �� ֵ��BOOL
***********************************************************************/

BOOL CPrintBarcode::PrintEntrance(DATA *pdata)
{
	CString new_Buffer=_T("");
	CString sBarCodeCMD=_T("");
	CString strfpDoc=_T("");
	int iNum=0;
	int numENSN=0;
	/*if(data->strCompanyName == _T("") || data->strProductName == _T("") || data->strModel == _T("") || data->strNum == _T("")
	|| data->strZTEMaterialCode == _T("") || data->strProductionBatch == _T("") || data->strCN == _T(""))
		return false;*/

	//�����ǹ��ڴ�ӡ���ֵĺ���

	HINSTANCE m_Handle;
	m_Handle=LoadLibrary(_T("./Fnthex32.dll"));
	if(!m_Handle)
	{
		AfxMessageBox(_T("Load FntHex32.dll fail!"));
		return FALSE;
	}
	int (__stdcall * Getfonthex)(CString,CString,int,int,int,int,int,CString);
	Getfonthex=(int (__stdcall *) (CString,CString,int,int,int,int,int,CString))GetProcAddress(m_Handle,"GETFONTHEX");
	//========================================================================
	//��Ʒ����
	////for(int i=0;i<100000;i++)
		////new_Buffer+=" ";
	////Getfonthex(_T("SN & MAC Labels"), _T("Arial"),0, 80 , 0, 1, 0, new_Buffer); kingsin
	////new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR01"));
	////sBarCodeCMD +=new_Buffer;
	////sBarCodeCMD +=_T("^FO30,68^XGOUTSTR01,1,1^FS");
	//========================================================================



	for (int j = 0; j < 1; j++)
	{
		CString outStrSN = "";
		CString ProductSN = "";
		CString ProductMAC = "";
		CString strCoordinateY=_T("");        //�����ı�SN/MAC����Y��λ��


		//SN 1
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("SN:")+pdata->ProductSNMAC[0].strSNNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 0);
		sBarCodeCMD +=_T("^FO00,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductSN=Str2SubA(pdata->ProductSNMAC[0].strSNNum);
		sBarCodeCMD +=CreateZPLCode(0, 30,50,ProductSN,1.9);
		//SN 2
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("SN:")+pdata->ProductSNMAC[1].strSNNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 0);
		sBarCodeCMD +=_T("^FO400,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductSN=Str2SubA(pdata->ProductSNMAC[1].strSNNum);
		sBarCodeCMD +=CreateZPLCode(400, 30,50,ProductSN,1.9);
		//SN 3
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("SN:")+pdata->ProductSNMAC[2].strSNNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 0);
		sBarCodeCMD +=_T("^FO800,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductSN=Str2SubA(pdata->ProductSNMAC[2].strSNNum);
		sBarCodeCMD +=CreateZPLCode(800,30,50,ProductSN,1.9);

		// MAC 1
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("MAC:")+pdata->ProductSNMAC[0].strMACNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 80);
		sBarCodeCMD +=_T("^FO00,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductMAC=Str2SubA(pdata->ProductSNMAC[0].strMACNum);
		sBarCodeCMD +=CreateZPLCode(0, 110,50,ProductMAC,1.9);
		//MAC 2
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("MAC:")+pdata->ProductSNMAC[1].strMACNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 80);
		sBarCodeCMD +=_T("^FO400,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductMAC=Str2SubA(pdata->ProductSNMAC[1].strMACNum);
		sBarCodeCMD +=CreateZPLCode(400,110,50,ProductMAC,1.9);
		//MAC3
		outStrSN.Format("OUTSTR01%d", j);
		for(int i=0;i<20480;i++)
			new_Buffer+=" ";
		Getfonthex(_T("MAC:")+pdata->ProductSNMAC[2].strMACNum, _T("Arial"),0, 35 , 0, 1, 0, new_Buffer);
		new_Buffer.Replace(_T("OUTSTR01"), outStrSN);
		sBarCodeCMD +=new_Buffer;
		strCoordinateY.Format("%d", 80);
		sBarCodeCMD +=_T("^FO800,")+strCoordinateY+_T("^XG")+outStrSN+_T(",1,1^FS");

		ProductMAC=Str2SubA(pdata->ProductSNMAC[2].strMACNum);
		sBarCodeCMD +=CreateZPLCode(800,110,50,ProductMAC,1.9);
	}


	strfpDoc.Format(_T("^XA\n^LH%d,%d\n"), 100, 80);
	strfpDoc += sBarCodeCMD;

	//��ӡ������
	strfpDoc += _T("^PQ1\n^XZ\n");

	for (int i = 0; i <1; i++)
	{
		if (0 != SendZPL2Printer(strfpDoc))
		{
			AfxMessageBox(_T("��ӡ������ֽʧ�ܣ�����"));

			return FALSE;
		}
	}

	return true;
}

/*
*	��ӡջ����ֽ
*/
BOOL CPrintBarcode::PrintEntrancePallet(PALLETDATA *data)
{
	CString new_Buffer=_T("");
	CString sBarCodeCMD=_T("");
	CString strfpDoc=_T("");
	int iNum=0;
	int numENSN=0;
	if(data->strProductName == _T("") || data->strModel == _T("") || data->strZTEMaterialCode == _T("")
		|| data->strProductionBatch == _T("") || data->strProductionDate == _T("") || data->strPalletNum == _T(""))
		return false;

	//�����ǹ��ڴ�ӡ���ֵĺ���

	HINSTANCE m_Handle;
	m_Handle=LoadLibrary(_T("./Fnthex32.dll"));
	if(!m_Handle)
	{
		AfxMessageBox(_T("Load FntHex32.dll fail!"));
		return FALSE;
	}
	int (__stdcall * Getfonthex)(CString,CString,int,int,int,int,int,CString);
	Getfonthex=(int (__stdcall *) (CString,CString,int,int,int,int,int,CString))GetProcAddress(m_Handle,"GETFONTHEX");
	//========================================================================

	//��Ʒ����
	for(int i=0;i<6000;i++)
		new_Buffer+=" ";
	Getfonthex(_T("��Ʒ����:  ")+data->strProductName, _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR01"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO22,68^XGOUTSTR01,1,1^FS");

	//����ͺ�
	for(int i=0;i<800;i++)
		new_Buffer+=" ";
	Getfonthex(_T("����ͺ�:  ")+data->strModel, _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR02"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO22,132^XGOUTSTR02,1,1^FS");

	//ZTE���ϱ���
	for(int i=0;i<256;i++)
		new_Buffer+=" ";
	Getfonthex(_T("ZTE���ϱ���:  ")+data->strZTEMaterialCode, _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR03"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO22,196^XGOUTSTR03,1,1^FS");

	//��������
	for(int i=0;i<800;i++)
		new_Buffer+=" ";
	Getfonthex(_T("��������:  ")+data->strProductionBatch, _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR04"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO22,260^XGOUTSTR04,1,1^FS");

	//��������
	for(int i=0;i<800;i++)
		new_Buffer+=" ";
	Getfonthex(_T("��������:  ")+data->strProductionDate, _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR05"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO22,324^XGOUTSTR05,1,1^FS");

	//=========================================================================

	//ջ������

	CString strCN=_T("");
	int iCodeY = 0;
	CString strCNCoordinateY=_T("");
	CString strCoordinateY = "";
	int iCNCoordinateY=0;
	strCN=data->strPalletNum;
	strCNCoordinateY = "400";
	strCoordinateY = "435";
	iCodeY = 392;

	for(int i=0;i<1000;i++)
		new_Buffer+=" ";
	Getfonthex(_T("ջ������:"), _T("����"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR09"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO212,")+strCNCoordinateY+_T("^XGOUTSTR06,1,1^FS");

	for(int i=0;i<1000;i++)
		new_Buffer+=" ";
	Getfonthex(_T("EN:")+strCN, _T("Arial"),0, 40 , 0, 0, 0, new_Buffer);
	new_Buffer.Replace(_T("OUTSTR01"), _T("OUTSTR06"));
	sBarCodeCMD +=new_Buffer;
	sBarCodeCMD +=_T("^FO440,")+strCoordinateY+_T("^XGOUTSTR06,1,1^FS");

	strCN=Str2SubA(strCN);
	sBarCodeCMD +=CreateZPLCode(440,iCodeY,55,strCN,3.0);

	//========================================================================

	strfpDoc.Format(_T("^XA\n^LH%d,%d\n"), 50, 20);
	strfpDoc += sBarCodeCMD;

	//��ӡ������
	strfpDoc += _T("^PQ1\n^XZ\n");

	for (int i = 0; i <1; i++)
	{
		if (0 != SendZPL2Printer(strfpDoc))
		{
			AfxMessageBox(_T("��ӡջ����ֽʧ�ܣ�����"));

			return FALSE;
		}
	}

	return true;
}

//��ӵĴ�ӡ����Ĵ���

