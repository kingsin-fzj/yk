#pragma once

typedef struct _SN_MAC
{
	CString strMACNum;			//ZTE名称
	CString strSNNum;			//产品名称
	//CString strISN;
} SN_MAC ;

typedef struct _DATA
{
	SN_MAC ProductSNMAC[3];
	int num;
} DATA ;

typedef struct _PalletDATA
{
	CString strProductName;          //产品名称
	CString strModel;                //规格型号
	CString strZTEMaterialCode;      //物料编码
	CString strProductionBatch;      //生产批次
	CString strProductionDate;		 //生产日期
	CString strPalletNum;			 //栈板号
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

