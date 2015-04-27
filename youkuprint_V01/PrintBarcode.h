#pragma once

typedef struct _SN_MAC
{
	CString strMACNum;			//ZTE����
	CString strSNNum;			//��Ʒ����
	//CString strISN;
} SN_MAC ;

typedef struct _DATA
{
	SN_MAC ProductSNMAC[3];
	int num;
} DATA ;

typedef struct _PalletDATA
{
	CString strProductName;          //��Ʒ����
	CString strModel;                //����ͺ�
	CString strZTEMaterialCode;      //���ϱ���
	CString strProductionBatch;      //��������
	CString strProductionDate;		 //��������
	CString strPalletNum;			 //ջ���
} PALLETDATA ;

class CPrintBarcode
{
public:
	CPrintBarcode(void);
	virtual ~CPrintBarcode(void);
public:
	int SendZPL2Printer(CString strDoc1);
	CString Str2SubA(CString str);
	CString CreateZPLText(int iStartX,
		int iStartY,
		int iHeight,
		int iWidth,
		CString strText);
	CString CreateZPLCode(int iStartX,
		int iStartY,
		int iHeight,
		CString strCode,
		int iWeight);
	BOOL PrintEntrance(DATA *pdata);
	BOOL PrintEntrancePallet(PALLETDATA *data);
};

