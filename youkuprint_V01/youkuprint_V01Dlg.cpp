
// youkuprint_V01Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "youkuprint_V01.h"
#include "youkuprint_V01Dlg.h"
#include "afxdialogex.h"
#include "Ping.h"
#include "WinSpool.h"
#include "PrintBarcode.h"
#include "afxwin.h"

#include "MInputClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
MInputClass dlg;

int print_flag = 1;
CPrintBarcode myBoxcode;
CPrintBarcode BoxData;
DATA ProductBoxData;
DATA PrintAginData;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cyoukuprint_V01Dlg 对话框




Cyoukuprint_V01Dlg::Cyoukuprint_V01Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cyoukuprint_V01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cyoukuprint_V01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_STATIC_SN1, m_sn);
	//DDX_Control(pDX, IDC_STATIC_MAC1, m_mac);
}

BEGIN_MESSAGE_MAP(Cyoukuprint_V01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDOK, &Cyoukuprint_V01Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cyoukuprint_V01Dlg 消息处理程序
HBRUSH Cyoukuprint_V01Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID() == IDC_STATIC_TITLE)
	{
		pDC->SelectObject(&m_font);
	}

	/*画链接状态背景颜色*/
	if(pWnd->GetDlgCtrlID() == IDC_LINK1)
	{
		if(m_thread_params[1].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[1].link_stat == 1 || m_thread_params[1].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[1].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
		}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK2)
	{
		if(m_thread_params[2].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[2].link_stat == 1 || m_thread_params[2].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[2].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK3)
	{
		if(m_thread_params[3].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[3].link_stat == 1 || m_thread_params[3].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[3].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK4)
	{
		if(m_thread_params[4].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[4].link_stat == 1 || m_thread_params[4].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[4].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK5)
	{
		if(m_thread_params[5].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[5].link_stat == 1 || m_thread_params[5].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[5].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK6)
	{
		if(m_thread_params[6].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[6].link_stat == 1 || m_thread_params[6].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[6].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK7)
	{
		if(m_thread_params[7].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[7].link_stat == 1 || m_thread_params[7].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[7].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_LINK8)
	{
		if(m_thread_params[8].link_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[8].link_stat == 1|| m_thread_params[8].link_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[8].link_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	

	/*测试背景颜色*/
	/*画链接状态背景颜色*/
	if(pWnd->GetDlgCtrlID() == IDC_TEST1)
	{
		if(m_thread_params[1].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[1].test_stat == 1 || m_thread_params[1].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[1].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST2)
	{
		if(m_thread_params[2].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[2].test_stat == 1 || m_thread_params[2].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[2].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST3)
	{
		if(m_thread_params[3].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[3].test_stat == 1 || m_thread_params[3].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[3].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST4)
	{
		if(m_thread_params[4].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[4].test_stat == 1 || m_thread_params[4].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[4].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST5)
	{
		if(m_thread_params[5].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[5].test_stat == 1 || m_thread_params[5].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[5].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST6)
	{
		if(m_thread_params[6].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[6].test_stat == 1 || m_thread_params[6].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[6].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST7)
	{
		if(m_thread_params[7].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[7].test_stat == 1 || m_thread_params[7].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[7].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	if(pWnd->GetDlgCtrlID() == IDC_TEST8)
	{
		if(m_thread_params[8].test_stat == 0){
			pDC->SetBkColor(RGB(0,0,0));
			hbr = m_Brush[0];
		}
		if(m_thread_params[8].test_stat == 1|| m_thread_params[8].test_stat == 3){
			pDC->SetBkColor(RGB(255,0,0));
			hbr = m_Brush[1];
		}
		if(m_thread_params[8].test_stat == 2){
			pDC->SetBkColor(RGB(0,255,0));
			hbr = m_Brush[2];
		}
	}	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


BOOL Cyoukuprint_V01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_font.CreatePointFont(150,"宋体");

	/*获取当前主对话框的坐标*/
	//GetWindowRect(&m_rect);

	/*启动8个工作线程、1个对话框线程*/
	start_thread(); 
	//读取配置文件
	ReadConfig(); 

	m_Brush[0] = (HBRUSH) CreateSolidBrush(RGB(0,0,0));
	m_Brush[1] = (HBRUSH) CreateSolidBrush(RGB(255,0,0));
	m_Brush[2] = (HBRUSH) CreateSolidBrush(RGB(0,255,0));

	AfxBeginThread(TestPing,(LPVOID)m_thread_params,0,0,THREAD_PRIORITY_NORMAL,NULL);  //多线程进入待测路由后ping线程不起作用 20140405fzj
		////AfxBeginThread(test_paint_threadresultall,(LPVOID)&(m_thread_params[i]),0,0,THREAD_PRIORITY_NORMAL,NULL);
	
	//((CButton*)GetDlgItem(IDC_EDIT_IPUTSN1))->SetFocus();
	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

/*写SN/MAC文件
供打印机使用
*/
void Cyoukuprint_V01Dlg::WriteLogFile(CString mac, CString sn)
{
	CString macSn;
	macSn = result_mac + "," + result_sn;

	CStdioFile logFile;
	if (logFile.Open(configPath + "MacSn.txt", CFile::modeWrite) == TRUE)
	{
		logFile.Close();
		DeleteFile(configPath + "MacSn.txt");
	}
	logFile.Open(configPath + "MacSn.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	logFile.SeekToEnd();
	logFile.WriteString(macSn);
	Sleep(500);
	logFile.Close();
}

bool Cyoukuprint_V01Dlg::OnPrint() 
{
	// TODO: Add your control notification handler code here	

	CString strLog;
	CString str;

	//ProductBoxData.num = 10;
	if(PrintAginData.num == 3){
		myBoxcode.PrintEntrance(&PrintAginData);
		//ProductBoxData.num = 0;
		for (int j = 0; j < PrintAginData.num; j++)
		{
			strLog.Format("%02d  ", j+1);
			strLog += ProductBoxData.ProductSNMAC[j].strSNNum + "  " + ProductBoxData.ProductSNMAC[j].strMACNum;
			////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(strLog);
		}
		PrintAginData.num = 0;
	}
	return true;
}
void Cyoukuprint_V01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cyoukuprint_V01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


//读取配置文件
bool Cyoukuprint_V01Dlg::ReadConfig()
{
	char buff[200];

	char pFileName[MAX_PATH];  /*获取全路径缓冲区*/
	CString configpath;
	int cutnum;

	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, pFileName, MAX_PATH));
	configpath = pFileName;
	cutnum = configpath.ReverseFind('\\');
	configpath = configpath.Mid(0, cutnum);
	allfilepath = configpath;
	configpath += "\\config.ini";

	/*获取基本参数信息*/
/******************************************************************************************/
	CString csFullPath;	
	CString FilePath;		
	CString Filepath_Po;
	int str_num = 0;
	CString Station;
	CString User;
	CString flowline;
	VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, pFileName, MAX_PATH));
		csFullPath = pFileName;
		/*if(nPos < 0)
			MessageBox("获取目录失败", ERROR);*/
		str_num = csFullPath.Find("po");
		Filepath_Po = csFullPath.Mid(str_num, strlen(csFullPath));
		//str_num = Filepath_Po.Find('\\');
		csFullPath = Filepath_Po.Mid(Filepath_Po.Find('\\') + 1, strlen(Filepath_Po));
		Filepath_Po = csFullPath.Mid(0, csFullPath.Find('\\'));  //获取PO号
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		Station = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取站位名称
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		User = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取员工号
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		flowline = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取流水线号
		GetDlgItem(IDC_PO_TEXT)->SetWindowText(Filepath_Po);
		GetDlgItem(IDC_PRA_TEXT)->SetWindowText(Station);
		GetDlgItem(IDC_USER_TEXT)->SetWindowText(User);
		GetDlgItem(IDC_LINE_TEXT)->SetWindowText(flowline);
		
		/*20150403Fzj*/
/*****************************************************************************************************/

	/*KINGSIN  对切换模式配置提取*/
	/*SQL服务器*/
	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("SQL_IP", "sql_ip", NULL, buff, 20, configpath);
	sql_ip=buff;
	sql_port=::GetPrivateProfileInt("SQL_PORT", "sql_port", 0, configpath);

	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("SQL_DBNAME", "sql_dbname", NULL, buff,20, configpath);
	sql_dbname = buff;

	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("SQL_TABLE", "sqltable_name", NULL, buff,20, configpath);
	sqltable_name = buff;
	
	/*待测路由*/
	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("ROUTER", "router_ip1", NULL, buff, 20, configpath);
	m_thread_params[1].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip2", NULL, buff, 20, configpath);
	m_thread_params[2].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip3", NULL, buff, 20, configpath);
	m_thread_params[3].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip4", NULL, buff, 20, configpath);
	m_thread_params[4].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip5", NULL, buff, 20, configpath);
	m_thread_params[5].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip6", NULL, buff, 20, configpath);
	m_thread_params[6].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip7", NULL, buff, 20, configpath);
	m_thread_params[7].routerIP = buff;
	::GetPrivateProfileString("ROUTER", "router_ip8", NULL, buff, 20, configpath);
	m_thread_params[8].routerIP = buff;
	
	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("ROUTER", "router_name", NULL, buff, 20, configpath);
	for(int i = 1; i < 9; i++){
		m_thread_params[i].router_name = buff;
	}

	ZeroMemory(buff, sizeof(buff));
	::GetPrivateProfileString("ROUTER", "router_key", NULL, buff, 20, configpath);
	for(int i = 1; i < 9; i++){
		m_thread_params[i].router_key = buff;
	}

	///*获取打印机相关参数*/
	//ZeroMemory(buff, sizeof(buff));
	//::GetPrivateProfileString("BARCODE_WINDOW_CLASS", "barcode_window_class", NULL, buff, sizeof(buff), configpath);
	//barcodeWindowClass = buff;
	//ZeroMemory(buff, sizeof(buff));
	//::GetPrivateProfileString("BARCODE_WINDOW_NAME", "barcode_window_name", NULL, buff, sizeof(buff), configpath);
	//barcodeWindowName = buff;
	//ZeroMemory(buff, sizeof(buff));
	//::GetPrivateProfileString("PRINT_WINDOW_CLASS", "print_window_class", NULL, buff, sizeof(buff), configpath);
	//printWindowClass = buff;
	//ZeroMemory(buff, sizeof(buff));
	//::GetPrivateProfileString("PRINT_WINDOW_NAME", "print_window_name", NULL, buff, sizeof(buff), configpath);
	//printWindowName = buff;

	return true;
}

UINT __cdecl Cyoukuprint_V01Dlg::TestPing(LPVOID info)
{
		
	thread_Params *mptr = (thread_Params*)info;

	Cyoukuprint_V01Dlg *ptr=(Cyoukuprint_V01Dlg *)mptr[1].pDlg;
	
	////CString router_ip = "192.168.11.1";
	////Cyoukuprint_V01Dlg *ptr=(Cyoukuprint_V01Dlg *)info;
	//CPing ping((LPSTR)(LPCTSTR)ptr->router_ip);   /*设定ping对应的IP地址*/
	//CPing ping((LPSTR)(LPCTSTR)mptr->routerIP);
	CString oldinfo="";
	bool nicstatus=false;//是否插入网卡 
	int i=0;
	//ping.SetScoket();
	CString inf;

	while(true)
	{	
		for(int j = 1; j < 9; j++){
		CPing ping((LPSTR)(LPCTSTR)mptr[j].routerIP);
		ping.SetScoket();
		ptr->GetDlgItem(mptr[j].ipID)->SetWindowText(mptr[j].routerIP);
		ping.Ping(inf);
		////ptr->m_ping.GetWindowText(oldinfo);
		////oldinfo=oldinfo+inf+"\r\n";
		////if (oldinfo.GetLength()>800)
		////{
			////oldinfo=oldinfo.Mid(oldinfo.GetLength()-600,oldinfo.GetLength());
		////}
		////ptr->m_ping.SetWindowText(oldinfo);
		////ptr->m_ping.LineScroll(ptr->m_ping.GetLineCount());
		if (inf.Find("Destination host")>-1 ||inf.Find("Request timed out.")>-1)
		{
			mptr[j].link_stat = 3;
			
			// add by WYK
			mptr[j].test_work = 0;
			mptr[j].test_stat = 0;
			ptr->GetDlgItem(mptr[j].testID)->SetWindowText("启动...");
			
			if(mptr[j].scal == 1)
			{
				ptr->GetDlgItem(IDC_LINK1)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 2)
			{
				ptr->GetDlgItem(IDC_LINK2)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 3)
			{
				ptr->GetDlgItem(IDC_LINK3)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 4)
			{
				ptr->GetDlgItem(IDC_LINK4)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 5)
			{
				ptr->GetDlgItem(IDC_LINK5)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 6)
			{
				ptr->GetDlgItem(IDC_LINK6)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 7)
			{
				ptr->GetDlgItem(IDC_LINK7)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 8)
			{
				ptr->GetDlgItem(IDC_LINK8)->SetWindowText("连接失败");
			}
			
			print_flag = 1;
			nicstatus=false;
			
			//ptr->UpdateWindow();
		}
		if (inf.Find("Reply from "+mptr[j].routerIP)>-1)
		{
			mptr[j].link_stat = 2;
			if(mptr[j].scal == 1)
			{
				ptr->GetDlgItem(IDC_LINK1)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 2)
			{
				ptr->GetDlgItem(IDC_LINK2)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 3)
			{
				ptr->GetDlgItem(IDC_LINK3)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 4)
			{
				ptr->GetDlgItem(IDC_LINK4)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 5)
			{
				ptr->GetDlgItem(IDC_LINK5)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 6)
			{
				ptr->GetDlgItem(IDC_LINK6)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 7)
			{
				ptr->GetDlgItem(IDC_LINK7)->SetWindowText("链接成功");
			}
			if(mptr[j].scal == 8)
			{
				ptr->GetDlgItem(IDC_LINK8)->SetWindowText("链接成功");
			}

			//ptr->UpdateWindow();
		}
		else
		{
			mptr[j].link_stat = 3;

			// add by WYK
			mptr[j].test_work = 0;
			mptr[j].test_stat = 0;
			ptr->GetDlgItem(mptr[j].testID)->SetWindowText("启动...");

			if(mptr[j].scal == 1)
			{
				ptr->GetDlgItem(IDC_LINK1)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 2)
			{
				ptr->GetDlgItem(IDC_LINK2)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 3)
			{
				ptr->GetDlgItem(IDC_LINK3)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 4)
			{
				ptr->GetDlgItem(IDC_LINK4)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 5)
			{
				ptr->GetDlgItem(IDC_LINK5)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 6)
			{
				ptr->GetDlgItem(IDC_LINK6)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 7)
			{
				ptr->GetDlgItem(IDC_LINK7)->SetWindowText("连接失败");
			}
			if(mptr[j].scal == 8)
			{
				ptr->GetDlgItem(IDC_LINK8)->SetWindowText("连接失败");
			}
			i=0;
			
		}
		////ptr->test_paint(mptr[j].link_flag, mptr[j].scal, mptr[j].link_stat);  /*初始化总链接灯*/
		}
	}
	
	return 1;
}

//bool Cyoukuprint_V01Dlg::Begin()
//{ 
//	CString sn = "";
//	GetDlgItem(IDC_EDIT_IPUTSN1)->GetWindowText(sn);
//	GetDlgItem(IDC_EDIT_IPUTSN1)->SetWindowText("");
//
//	/*首先登陆telnet*/
//	//if(GetOn() == false)
//	//{
//	//	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("Telnet FAIL!");
//	//	////log +=router_ip + " =fail\r\n";
//	//	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(log);
//	//	return false;
//	//}
//	//else
//		////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("TELNET SUCCESS！");
//		//Sleep(2000);  //offer to kingsin
//		;
//	//////if(GetMacSn() == false)
//	//////{
//	//////	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("Get SN/MAC FAIL!");
//	//////	log += router_ip + " fail\r\n";
//	//////	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(log);
//	//////	return false;
//	//////}
//	//////else
//		////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("MAC/SN SUCCESS！");
//		//Sleep(2000);  //offer to kingsin
//	/*与数据库做校验*/
//	//if(MyCheckout() == false)
//	//{
//	//	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("设备SN/MAC获取失败！");
//	//	log = "SN/MAC校验失败";
//	//	log += " fail\r\n";
//	//	////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(log);
//	//	return false; 
//	//}
//	//else
//		////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("设备SN/MAC获取成功！");
///*
//	if(OnPrint() == false)
//	{
//		GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("产品在线打印失败！");
//		return false;
//	}
//	else
//		GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("产品在线打印成功！");
//*/
//	 if(MyUpdata() == false)
//	 {
//		////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("数据库更新失败！");
//		return false;
//	}
//	else
//	{
//		////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("数据库更新成功！");
//	}
//
//	return true;
//}

/*
函数名： GetOn
功能：打开Telnet
*/
bool Cyoukuprint_V01Dlg::GetOn(SOCKET *router_socket,UINT scal)
{
	char recvBuff[2000];
	CString recvStr;
	WORD wVersionRequested;
	WSADATA wsaData;
	int posmacstr = 0;
	SOCKET clientconn;
	wVersionRequested=MAKEWORD(2,2);
	m_thread_params[scal].link_flag = 1;  //链接中  20140405 kingsin

	if (WSAStartup(wVersionRequested,&wsaData)!=0)
	{
		MessageBox("初始化网络版本!","错误",MB_ICONERROR);
		WSACleanup();
		return false;
	}
	clientconn = socket(AF_INET,SOCK_STREAM,0);
	if (clientconn==-1)
	{
		closesocket(clientconn);
		return false;
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family=AF_INET;
	char *ipchar=m_thread_params[scal].routerIP.GetBuffer(m_thread_params[scal].routerIP.GetLength());
	addrSrv.sin_addr.s_addr=inet_addr(ipchar);
	addrSrv.sin_port=htons(23);
	int recvsend=1024*256;
	setsockopt(clientconn, SOL_SOCKET, SO_RCVBUF, (char*)&recvsend, sizeof(int));
	if (connect(clientconn, (SOCKADDR *)&addrSrv,sizeof(addrSrv)) == SOCKET_ERROR) 	{
		WSACleanup(); 
		//////MessageBox("链接失败!","错误",MB_ICONERROR);
		return false;
	}

	Sleep(800);
	CString commandStr;
	commandStr.Empty();
	char *commandChar=NULL;

#if 0   /*开启陪测DMZ成功时不启用*/
	commandStr="admin\r";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
	{
		closesocket(clientconn);
		WSACleanup();
		//////MessageBox("发送登录名失败!","错误",MB_ICONERROR);
		return false;
	}
	Sleep(800);
	commandStr.Empty();
	commandStr="admin\r";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
	{
		closesocket(clientconn);
		WSACleanup();
		//////MessageBox("发送登录密码失败!","错误",MB_ICONERROR);
		return false;
	}
	Sleep(800);
	commandStr.Empty();
	commandStr="\r";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
	{
		closesocket(clientconn);
		WSACleanup();
		//////MessageBox("发送登录密码失败!","错误",MB_ICONERROR);
		return false;
	}
	Sleep(800);
	ZeroMemory(recvBuff,sizeof(recvBuff));
	recv(clientconn,recvBuff,sizeof(recvBuff),0);
	recvStr=recvBuff;
	//	MessageBox(recvStr);
	if (recvStr.Find("BusyBox")==-1)
	{
		closesocket(clientconn);
		WSACleanup();
		/////MessageBox("登录失败!","错误",MB_ICONERROR);
		print_flag = 1;  //校验程序从新从Begin()开始
		/*		GetDlgItem(IDC_LABEL2)->SetWindowText("测试失败");*/
		return false;
	}
#endif 

	////if(flag == 0){
			/*跳转登陆*/
		Sleep(800);
		commandStr.Empty();
		commandChar=NULL;
		commandStr=m_thread_params[scal].router_name+"\r";
		commandChar=(LPSTR)(LPCTSTR)commandStr;
		if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
		{
			closesocket(clientconn);
			WSACleanup();
			//////MessageBox("发送登录名失败!","错误",MB_ICONERROR);
			return false;
		}
		Sleep(800);
		commandStr.Empty();
		commandStr=m_thread_params[scal].router_key+"\r";
		commandChar=(LPSTR)(LPCTSTR)commandStr;
		if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
		{
			closesocket(clientconn);
			WSACleanup();
			/////MessageBox("发送登录密码失败!","错误",MB_ICONERROR);
			return false;
		}
		Sleep(800);
		commandStr.Empty();
		commandStr="\r";
		commandChar=(LPSTR)(LPCTSTR)commandStr;
		if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
		{
			closesocket(clientconn);
			WSACleanup();
			//////MessageBox("发送登录密码失败!","错误",MB_ICONERROR);
			return false;
		}
		Sleep(800);
		ZeroMemory(recvBuff,sizeof(recvBuff));
		recv(clientconn,recvBuff,sizeof(recvBuff),0);
		recvStr=recvBuff;
		//	MessageBox(recvStr);
		if (recvStr.Find("[root@Youku-router]")==-1)
		{
			closesocket(clientconn);
			WSACleanup();
			//////MessageBox("登录失败!","错误",MB_ICONERROR);
			print_flag = 1;  //校验程序从新从Begin()开始
			m_thread_params[scal].link_flag = 3;
			/*		GetDlgItem(IDC_LABEL2)->SetWindowText("测试失败");*/
			return false;
		}
		m_thread_params[scal].link_flag = 2;
	////}
	/*供守护线程调用，通过ping判断相应槽位的待测路由的连通性 20140405/1426*/
	////else if(flag == 1){
	////	Sleep(800);
	////	commandStr.Empty();
	////	commandStr="ping 192.168.11.1 -c 2\r";
	////	commandChar=(LPSTR)(LPCTSTR)commandStr;
	////	if (send(clientconn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
	////	{
	////		closesocket(clientconn);
	////		WSACleanup();
	////		MessageBox("发送ping失败!","错误",MB_ICONERROR);
	////		return false;
	////	}
	////	Sleep(1000);  //等1s未收到就报失败
	////	ZeroMemory(recvBuff,sizeof(recvBuff));
	////	recv(clientconn,recvBuff,sizeof(recvBuff),0);
	////	recvStr=recvBuff;
	////	//	MessageBox(recvStr);
	////	if(recvStr.Find("bytes from") == -1)
	////	{
	////		closesocket(clientconn);
	////		WSACleanup();
	////		MessageBox("链接失败!","错误",MB_ICONERROR);
	////		//print_flag = 1;  //校验程序从新从Begin()开始
	////		/*		GetDlgItem(IDC_LABEL2)->SetWindowText("测试失败");*/
	////		m_thread_params[scal].link_stat = 3;
	////		return false;
	////	}
	////	else
	////		m_thread_params[scal].link_stat = 2;
	////}

	*router_socket = clientconn;
	return true;
}

/*未用线程函数*/
UINT __cdecl Cyoukuprint_V01Dlg::test_paint_threadresultall(LPVOID info)
{
	thread_Params *mptr = (thread_Params*)info;
	Cyoukuprint_V01Dlg *ptr=(Cyoukuprint_V01Dlg *)mptr->pDlg;
	//while(true){
		////ptr->GetOn(&(mptr->router_socket), mptr->scal, 1);  //0表示测试中；1表示测试前

		ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat);  /*初始化总链接灯*/
		ptr->test_paint(mptr->test_flag, mptr->scal, mptr->test_stat); /*初始化总测试灯*/
	//}
	return 0;
}

/************************************************************************/
/* 该注释并非出自原作者，请谨慎参考，若有错误，注释者不负任何责任。
   test_stat: 2-测试成功      3-测试失败
   link_stat: 2-Ping成功
   test_work: 2-测试完成      3-测试失败    */
/************************************************************************/
UINT __cdecl Cyoukuprint_V01Dlg::test_paint_threadresult1(LPVOID info)
{
	thread_Params *mptr = (thread_Params*)info;
	Cyoukuprint_V01Dlg *ptr=(Cyoukuprint_V01Dlg *)mptr->pDlg;
	mptr->test_stat = 1;
	while(true){
		
		if(false == mptr->router_sn.IsEmpty() && mptr->test_work == 1){

			ptr->GetDlgItem(mptr->snID)->SetWindowText(mptr->router_sn);
			ptr->GetDlgItem(mptr->ipID)->SetWindowText(mptr->routerIP);
			////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat);  /*初始化总链接灯*/
			////ptr->test_paint(mptr->test_flag, mptr->scal, mptr->test_stat); /*初始化总测试灯*/
			
			if(mptr->link_stat == 2 && mptr->test_stat == 2){
				//mptr->resultflag = 1;
				ptr->GetDlgItem(mptr->resultID)->SetWindowText("测试通过");
				mptr->test_work = 2;
				//return false;
			
			} else {
				//mptr->test_work = 0;

				/*telnet测试*/
				if(ptr->GetOn(&(mptr->router_socket), mptr->scal) != true){   //DZM未成功时加了一个判断标志位，0表示测试中(输入SN后的检测)；1表示测试前(输入SN前连通性)
					ptr->GetDlgItem(mptr->resultID)->SetWindowText("telnet登陆失败");
					ptr->GetDlgItem(mptr->testID)->SetWindowText("测试失败");
					mptr->m_failnum += 1;  //统计失败次数
					mptr->test_stat = 3;
					mptr->test_work = 3;
					goto END;
					////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat);  /*初始化总链接灯*/
					//return false;
				}
				ptr->GetDlgItem(mptr->resultID)->SetWindowText("telnet成功");
				ptr->GetDlgItem(mptr->testID)->SetWindowText("测试中...");
				mptr->test_stat = 1;
				////mptr->link_stat = 2;
				////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat);  /*链接灯*/

				/*链接数据库*/
				if(mptr->db_socket.ConnectServer(ptr->sql_ip, ptr->sql_port) == false){
					ptr->GetDlgItem(mptr->resultID)->SetWindowText("数据库链接失败");
					ptr->GetDlgItem(mptr->testID)->SetWindowText("测试失败");
					mptr->m_failnum += 1;  //统计失败次数
					mptr->test_stat = 3;
					mptr->test_work = 3;
					goto END;
					////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat);  /*初始化总链接灯*/
					//return false;
				}
				ptr->GetDlgItem(mptr->resultID)->SetWindowText("数据库链接成功");
				ptr->GetDlgItem(mptr->testID)->SetWindowText("测试中...");
				mptr->test_stat = 1;
				////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat); 

				/*防PO并检测SN/MAC是否非法*/
				if(ptr->MyCheckout(mptr->db_socket, mptr->scal) != true){
					ptr->GetDlgItem(mptr->resultID)->SetWindowText("数据库校验失败");
					ptr->GetDlgItem(mptr->testID)->SetWindowText("测试失败");
					mptr->m_failnum += 1;    //统计失败次数
					mptr->test_stat = 3;
					mptr->test_work = 3;
					goto END;
					//return false;
				}
				ptr->GetDlgItem(mptr->macID)->SetWindowText(mptr->router_mac);
				ptr->GetDlgItem(mptr->resultID)->SetWindowText("从数据库验证sn查询mac成功");
				ptr->GetDlgItem(mptr->testID)->SetWindowText("测试中...");
				mptr->test_stat = 1;
				////ptr->test_paint(mptr->test_flag, mptr->scal, mptr->test_stat); /*初始化总测试灯*/

				/*从路由查询SN/MAC*/
				if(ptr->GetMacSn(mptr->router_socket, mptr->scal) != true){
					ptr->GetDlgItem(mptr->resultID)->SetWindowText("路由获取SN/MAC失败");
					ptr->GetDlgItem(mptr->testID)->SetWindowText("测试失败");
					mptr->m_failnum += 1;   //统计失败次数
					mptr->test_stat = 3;
					mptr->test_work = 3;
					goto END;
					////ptr->test_paint(mptr->test_flag, mptr->scal, mptr->test_stat); /*初始化总测试灯*/
					//return false;
				}

				ptr->GetDlgItem(mptr->resultID)->SetWindowText("SN/MAC校验合法");
				ptr->GetDlgItem(mptr->testID)->SetWindowText("测试成功");
				mptr->test_stat = 2;
				mptr->test_work = 2;
				ptr->GetDlgItem(mptr->testID)->SetWindowText("测试成功");
				////ptr->test_paint(mptr->link_flag, mptr->scal, mptr->link_stat); 

				/*关闭telnet*/
			}
		}
END:
		Sleep(400);
	}
	return 0;
}

UINT __cdecl Cyoukuprint_V01Dlg::Dilog_thread(LPVOID info)
{
	thread_Params *param = (thread_Params *)info;
	Cyoukuprint_V01Dlg *pDlg = (Cyoukuprint_V01Dlg *)param[0].pDlg;

	int index = 0;

	while (1) {
		index = 0;
		for (index = 1; index < 9; index++) {
			if (param[index].link_stat == 2 && (param[index].test_work == 0 || param[index].test_work == 3)) {
				MInputClass m_inputclass;
				m_inputclass.DoModal(param[index].scal, param[index].m_failnum);
				param[index].router_sn = m_inputclass.GetData();
				param[index].test_work = 1;  //1允许进入测试流程
			}
		}
		Sleep(400);
	}
}

void Cyoukuprint_V01Dlg::test_paint(int mode, int scal, int stat)
{
	CClientDC pDC(this);
	CRect rect;
	GetWindowRect(rect);
	int width = rect.Width();
	int heigh = rect.Height();
	/*CString mm;
	mm.Format("%d",width);
	MessageBox(mm);
	mm.Format("%d",heigh);
	MessageBox(mm);*/
	int j = 0;  /*控制排数*/
	int k = 0;  /*设定灯的类型：1链接状态灯；2测试信息灯*/
	
	CBrush brush, *oldbrush = NULL;
	if(mode == 2)
		k = 25;
	if(scal < 3)
		j = 0;
	else if(scal < 6){
		j = 1;
		scal = scal - 3;
	}
	else{
		j = 2;
		scal = scal - 6;
	}
		if(stat == 1 ||stat ==3){
		brush.CreateSolidBrush(RGB(255, 0, 0));
		oldbrush = pDC.SelectObject(&brush);
		pDC.Ellipse(width/10*(scal*3+2)+80, heigh/10*(j*3+1)+k, width/10*(scal*3+2)+100, heigh/10*(j*3+1)+k+20);
		pDC.SelectObject(oldbrush);
		brush.DeleteObject();
		Sleep(10);
		}
		
		if(stat == 0){
		brush.CreateSolidBrush(RGB(0,0,0));   //对话框默认的背景RGB值236,233,216
		oldbrush = pDC.SelectObject(&brush);
		pDC.Ellipse(width/10*(scal*3+2)+80, heigh/10*(j*3+1)+k, width/10*(scal*3+2)+100, heigh/10*(j*3+1)+k+20);
		pDC.SelectObject(oldbrush);
		brush.DeleteObject();
		Sleep(10);
		}
		if(stat == 2){
			brush.CreateSolidBrush(RGB(0,255,0));   //对话框默认的背景RGB值236,233,216
			oldbrush = pDC.SelectObject(&brush);
			pDC.Ellipse(width/10*(scal*3+2)+80, heigh/10*(j*3+1)+k, width/10*(scal*3+2)+100, heigh/10*(j*3+1)+k+20);
			pDC.SelectObject(oldbrush);
			brush.DeleteObject();
			Sleep(10);
		}
}

bool Cyoukuprint_V01Dlg::GetMacSn(SOCKET conn, UINT scal)
{
	CString	commandStr;
	char recvBuff[2000];
	CString recvStr;
	char *commandChar=NULL;
	CString tempmacsn;
	int str_cur = 0;
	CString rfsn;   //从路由获取sn
	CString rfmac;  //从路由获取mac

	/*发送指令前的回车清除指令*/
	commandStr.Empty();
	commandStr="\r";  
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	if (send(conn,commandChar,strlen(commandChar),0)==SOCKET_ERROR)
	{
		closesocket(conn);
		WSACleanup();
		/*MessageBox("发送失败!","错误",MB_ICONERROR);*/
		return false;
	}

	Sleep(500);
	ZeroMemory(recvBuff,sizeof(recvBuff));
	recv(conn,recvBuff,sizeof(recvBuff),0);
	recvStr=recvBuff;
	if (recvStr.Find("[root@Youku-router]")==-1)
	{
		closesocket(conn);
		WSACleanup();
		/*MessageBox("接收错误[软件复位]","错误",MB_ICONERROR);*/
		return false;
	}

	/*获取sn*/
	commandStr.Empty();
	rfsn.Empty();
	result_sn.Empty();
	memset(recvBuff, 0, sizeof(recvBuff));
	commandStr = "iwpriv ra0 e2p 110\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		//////MessageBox("查询SN出错 1","错误",MB_ICONERROR);	
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfsn = tempmacsn.Mid(str_cur + 3, 2);
	rfsn += tempmacsn.Mid(str_cur + 1, 2);

	commandStr = "iwpriv ra0 e2p 112\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		//////MessageBox("查询SN出错 2","错误",MB_ICONERROR);	
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfsn += tempmacsn.Mid(str_cur + 3, 2);
	rfsn += tempmacsn.Mid(str_cur + 1, 2);

	commandStr = "iwpriv ra0 e2p 114\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		//////MessageBox("查询SN出错 3","错误",MB_ICONERROR);	
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfsn += tempmacsn.Mid(str_cur + 3, 2);
	rfsn += tempmacsn.Mid(str_cur + 1, 2);

	commandStr = "iwpriv ra0 e2p 116\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		//////MessageBox("查询SN出错 4","错误",MB_ICONERROR);	
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfsn += tempmacsn.Mid(str_cur + 3, 2);
	rfsn += tempmacsn.Mid(str_cur + 1, 2);
	result_sn = rfsn;
	if(m_thread_params[scal].router_sn != rfsn)
	{
		//////MessageBox("查询SN与路由所获SN不匹配");
		return false;
	}
	/*GetDlgItem(IDC_STATIC_SN1)->SetWindowText(rfsn);*/

	/*获取mac*/
	commandStr.Empty();
	rfmac.Empty();
	result_mac.Empty();
	memset(recvBuff, 0, sizeof(recvBuff));
	/*commandStr = "iwpriv ra0 e2p 4\r\n";*/
	commandStr = "iwpriv ra0 e2p 28\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		/*MessageBox("查询Mac出错 1","错误",MB_ICONERROR);	*/
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfmac = tempmacsn.Mid(str_cur + 3, 2);
	rfmac += tempmacsn.Mid(str_cur + 1, 2);

	/*commandStr = "iwpriv ra0 e2p 6\r\n";*/
	commandStr = "iwpriv ra0 e2p 2a\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		/*MessageBox("查询Mac出错 2","错误",MB_ICONERROR);	*/
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	//MessageBox(tempmacsn);
	str_cur = tempmacsn.ReverseFind('x');
	rfmac += tempmacsn.Mid(str_cur + 3, 2);
	rfmac += tempmacsn.Mid(str_cur + 1, 2);

	/*commandStr = "iwpriv ra0 e2p 8\r\n";*/
	commandStr = "iwpriv ra0 e2p 2c\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	ZeroMemory(recvBuff, sizeof(recvBuff));
	Sleep(500);
	recv(conn, recvBuff, sizeof(recvBuff), 0);
	if(recvBuff == NULL || recvBuff == "")
	{
		closesocket(conn);
		WSACleanup();
		/*MessageBox("查询Mac出错 3","错误",MB_ICONERROR);	*/
		return false;
	}
	tempmacsn.Format("%s", recvBuff);
	str_cur = tempmacsn.ReverseFind('x');
	rfmac += tempmacsn.Mid(str_cur + 3, 2);
	rfmac += tempmacsn.Mid(str_cur + 1, 2);
	result_mac = rfmac;
	if(m_thread_params[scal].router_mac != rfmac)
	{
		/*MessageBox("路由MAC与数据库不匹配","错误",MB_ICONERROR);	*/
		return false;
	}
	/*GetDlgItem(IDC_STATIC_MAC1)->SetWindowText(result_mac);*/

	//关闭telnetfzj
	commandStr = "oper_telnet 0\r\n";
	commandChar=(LPSTR)(LPCTSTR)commandStr;
	send(conn,commandChar,strlen(commandChar),0);
	
	return true;
}

/*
函数名称：MyCheckout
传入参数：
传出参数：true/false
功能：将从路由指令获取的mac/sn与在数据库中查找是否存在并合法
Edtor： kingsin
时间：2015-04-01
*/
bool Cyoukuprint_V01Dlg::MyCheckout(ClientSocket dbclilent, UINT scal)
{
	/*if (clientSocket.ConnectServer(sql_ip, sql_port))
	{*/
		CString Test_PrepFlag;
		CString Test_SQL;
		CString csFullPath;    /*当前程序全路径*/
		int str_num;		   /*字符截取辅助符*/
		char pFileName[MAX_PATH];  /*获取全路径缓冲区*/
		int nPos;				/*程序全路径总字节*/

		CString temp_mac;
		CString temp_sn;

		/**********************************************************************************************************
		*                                                                                                         *
		*                      增加防PO功能 2015.03.23Fzj                                                      *
		*																										  *
		***********************************************************************************************************/
		Test_SQL.Empty();
		CString SN = m_thread_params[scal].router_sn;
		Test_SQL = "select MTNPO from tempPoInfo where SN = '"+SN+"';";//"select MTNPO from tempPoInfo where SN = '"+SN+"';"; 
		dbclilent.mySocketSend(sql_dbname, Test_SQL, "0x00020002", 0);
		Test_PrepFlag = dbclilent.mySocketReceive();
		//nPos = GetCurrentDirectory(MAX_PATH, pFileName);

		VERIFY(::GetModuleFileName(AfxGetApp()->m_hInstance, pFileName, MAX_PATH));
		csFullPath = pFileName;
		/*if(nPos < 0)
			MessageBox("获取目录失败", ERROR);*/
		str_num = csFullPath.Find("po");
		//if(str_num < 0){
		//	//MessageBox("可执行程序路径异常");
		//	return false;
		//}
		Filepath_Po = csFullPath.Mid(str_num, strlen(csFullPath));
		//str_num = Filepath_Po.Find('\\');
		csFullPath = Filepath_Po.Mid(Filepath_Po.Find('\\') + 1, strlen(Filepath_Po));
		Filepath_Po = csFullPath.Mid(0, csFullPath.Find('\\'));  //获取PO号
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		Station = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取站位名称
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		User = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取员工号
		csFullPath = csFullPath.Mid(csFullPath.Find('\\') + 1, strlen(csFullPath));
		flowline = csFullPath.Mid(0, csFullPath.Find('\\'));      //获取流水线号
		////MessageBox("POhao"+Filepath_Po);
		////MessageBox("Test"+Test_PrepFlag);
		if(Filepath_Po != Test_PrepFlag){
			//MessageBox("PO号不匹配！！！", ERROR);
			GetDlgItem(m_thread_params[scal].resultID)->SetWindowText("PO号不匹配");
			Sleep(2000);
			return false;
		}


		/*增加防漏侧功能 Fzj*/  ///////////////////
		temp_mac.Empty();
		Test_SQL = "select FLAG from tempPoInfo where SN='"+m_thread_params[scal].router_sn+"';";
		dbclilent.mySocketSend(sql_dbname, Test_SQL, "0x00020002", 0);
		temp_mac = dbclilent.mySocketReceive();
		if("ERROR" == temp_mac)
		{
			//MessageBox("数据库错误");
			return false;
		}
		if("NULL"== temp_mac||"null"==temp_mac||""==temp_mac)
		{
			//MessageBox("数据库查询MAC错误");
			return false;
		}
		if(temp_mac != "1"){
			////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("待打印设备MAC与数据库记录MAC不匹配");
			//MessageBox("上一站写MAC失败，请重测");
			return false;
		}

		/*Select MAC*/
		temp_mac.Empty();
		Test_SQL = "select MAC from tempPoInfo where SN='"+m_thread_params[scal].router_sn+"';";
		dbclilent.mySocketSend(sql_dbname, Test_SQL, "0x00020002", 0);
		temp_mac = dbclilent.mySocketReceive();
		if("ERROR" == temp_mac)
		{
			//////MessageBox("数据库错误");
			return false;
		}
		if("NULL"== temp_mac||"null"==temp_mac||""==temp_mac)
		{
			/////MessageBox("数据库查询MAC错误");
			return false;
		}
		m_thread_params[scal].router_mac = temp_mac;
		//if(temp_mac != m_thread_params[scal].router_mac){
			////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText("待打印设备MAC与数据库记录MAC不匹配");
			//return false;
		//}
		/*Select SN*/
		temp_sn.Empty();
		Test_SQL = "select SN from tempPoInfo where MAC ='"+m_thread_params[scal].router_mac+"';";
		dbclilent.mySocketSend(sql_dbname, Test_SQL, "0x00020002", 0);
		temp_sn	= dbclilent.mySocketReceive();
		if ("ERROR" == temp_sn)
		{
			//////MessageBox("数据库错误");
			return false;
		}
		if("NULL"== temp_sn||"null"==temp_sn||""==temp_sn)
		{
			//////MessageBox("数据库查询SN错误");
			return	false;
		}
		if(temp_sn != m_thread_params[scal].router_sn){
			return false;
		}
			////GetDlgItem(IDC_STATIC_RESULT)->SetWindowText(temp_mac + "\r\n");
			//PrintAginData.num++;
			////PrintAginData.ProductSNMAC[PrintAginData.num - 1].strMACNum = result_mac;
			////PrintAginData.ProductSNMAC[PrintAginData.num - 1].strSNNum = result_sn;
		return true;
}

bool Cyoukuprint_V01Dlg::UpdateCheck(ClientSocket dbclilent, UINT scal)
{
	;
	return true;
}


bool Cyoukuprint_V01Dlg::MyUpdata()
{
	return true;
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cyoukuprint_V01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cyoukuprint_V01Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	return ;
}

/*启动线程函数*/
void Cyoukuprint_V01Dlg::start_thread()
{	
	
	/*dlg.DoModal(m_thread_params[1].scal, m_thread_params[1].m_failnum);
	m_thread_params[1].router_sn = dlg.GetData();
	MessageBox(m_thread_params[1].router_sn);*/

	for(int j = 1; j < 9; j++){
		m_thread_params[j].m_failnum = 0;
		m_thread_params[j].scal = j;
		m_thread_params[j].pDlg = this;
		m_thread_params[j].test_stat = 0;
		m_thread_params[j].link_flag = 0;
		m_thread_params[j].link_stat = 0;
		m_thread_params[j].test_work = 0;
		m_thread_params[j].test_flag = 2;  //固定值
	}
	
	/*槽位1线程*/
	m_thread_params[1].sn_inputID = IDC_SN_INPUT1;
	m_thread_params[1].snID = IDC_SN_OUT1;
	m_thread_params[1].macID= IDC_MAC_OUT1;
	m_thread_params[1].resultID = IDC_RESULT1;
	m_thread_params[1].ipID = IDC_IP1;			//IP状态显示
	m_thread_params[1].testID = IDC_TEST1;	    //test状态显示
	GetDlgItem(m_thread_params[1].testID)->SetWindowText("启动...");
	
	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[1]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	/*槽位2线程*/
	m_thread_params[2].sn_inputID = IDC_SN_INPUT2;
	m_thread_params[2].snID = IDC_SN_OUT2;
	m_thread_params[2].macID = IDC_MAC_OUT2;
	m_thread_params[2].resultID = IDC_RESULT2;
	m_thread_params[2].ipID = IDC_IP2;
	m_thread_params[2].testID = IDC_TEST2;
	GetDlgItem(m_thread_params[2].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[2]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	/*槽位3线程*/
	m_thread_params[3].sn_inputID	 = IDC_SN_INPUT3;
	m_thread_params[3].snID = IDC_SN_OUT3;
	m_thread_params[3].macID = IDC_MAC_OUT3;
	m_thread_params[3].resultID = IDC_RESULT3;
	m_thread_params[3].ipID = IDC_IP3;
	m_thread_params[3].testID = IDC_TEST3;
	GetDlgItem(m_thread_params[3].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[3]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	/*槽位4线程*/
	m_thread_params[4].sn_inputID	 = IDC_SN_INPUT4;
	m_thread_params[4].snID = IDC_SN_OUT4;
	m_thread_params[4].macID = IDC_MAC_OUT4;
	m_thread_params[4].resultID = IDC_RESULT4;
	m_thread_params[4].ipID = IDC_IP4;
	m_thread_params[4].testID = IDC_TEST4;
	GetDlgItem(m_thread_params[4].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[4]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	/*槽位5线程*/
	
	m_thread_params[5].sn_inputID	 = IDC_SN_INPUT5;
	m_thread_params[5].snID = IDC_SN_OUT5;
	m_thread_params[5].macID	= IDC_MAC_OUT5;
	m_thread_params[5].resultID = IDC_RESULT5;
	m_thread_params[5].ipID = IDC_IP5;
	m_thread_params[5].testID = IDC_TEST5;
	GetDlgItem(m_thread_params[5].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[5]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	/*槽位6线程*/
	m_thread_params[6].sn_inputID	 = IDC_SN_INPUT6;
	m_thread_params[6].snID = IDC_SN_OUT6;
	m_thread_params[6].macID	= IDC_MAC_OUT6;
	m_thread_params[6].resultID = IDC_RESULT6;
	m_thread_params[6].ipID = IDC_IP6;
	m_thread_params[6].testID = IDC_TEST6;
	GetDlgItem(m_thread_params[6].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[6]), 0, 0,THREAD_PRIORITY_IDLE, NULL);
	
	/*槽位7线程*/
	m_thread_params[7].sn_inputID	 = IDC_SN_INPUT7;
	m_thread_params[7].snID = IDC_SN_OUT7;
	m_thread_params[7].macID	= IDC_MAC_OUT7;
	m_thread_params[7].resultID = IDC_RESULT7;
	m_thread_params[7].ipID = IDC_IP7;
	m_thread_params[7].testID = IDC_TEST7;
	GetDlgItem(m_thread_params[7].testID)->SetWindowText("启动...");

	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[7]), 0, 0,THREAD_PRIORITY_IDLE, NULL);
		
	/*槽位8线程*/
	m_thread_params[8].sn_inputID	 = IDC_SN_INPUT8;
	m_thread_params[8].snID = IDC_SN_OUT8;
	m_thread_params[8].macID	= IDC_MAC_OUT8;
	m_thread_params[8].resultID = IDC_RESULT8;
	m_thread_params[8].ipID = IDC_IP8;
	m_thread_params[8].testID = IDC_TEST8;
	GetDlgItem(m_thread_params[8].testID)->SetWindowText("启动...");
	
	AfxBeginThread(test_paint_threadresult1, (LPVOID)&(m_thread_params[8]), 0, 0,THREAD_PRIORITY_IDLE, NULL);

	AfxBeginThread(Dilog_thread,(LPVOID)m_thread_params,0,0,THREAD_PRIORITY_NORMAL,NULL);  //输入对话框线程
}

BOOL Cyoukuprint_V01Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_KEYDOWN   ==   pMsg-> message && 13   ==   pMsg-> wParam)
	{
		switch( GetFocus()->GetDlgCtrlID())
		{
		//case IDC_SN_INPUT1:
		////	/*m_thread_params[1].m_failnum = 0;
		////	dlg.DoModal(m_thread_params[1].scal, m_thread_params[1].m_failnum);
		////	m_thread_params[1].router_sn = dlg.GetData();
		////	MessageBox(m_thread_params[1].router_sn);*/
		//	GetDlgItem(IDC_SN_INPUT1)->GetWindowText(m_thread_params[1].router_sn);
		//	GetDlgItem(IDC_SN_INPUT1)->SetWindowText("");
		//	if(m_thread_params[1].router_sn.IsEmpty())
		//	{
		//		//////MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[1].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT2:
		//	GetDlgItem(IDC_SN_INPUT2)->GetWindowText(m_thread_params[2].router_sn);
		//	GetDlgItem(IDC_SN_INPUT2)->SetWindowText("");
		//	if(m_thread_params[2].router_sn.IsEmpty())
		//	{
		//		/////MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[2].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT3:
		//	GetDlgItem(IDC_SN_INPUT3)->GetWindowText(m_thread_params[3].router_sn);
		//	GetDlgItem(IDC_SN_INPUT3)->SetWindowText("");
		//	if(m_thread_params[3].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[3].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT4:
		//	GetDlgItem(IDC_SN_INPUT4)->GetWindowText(m_thread_params[4].router_sn);
		//	GetDlgItem(IDC_SN_INPUT4)->SetWindowText("");
		//	if(m_thread_params[4].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[4].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT5:
		//	GetDlgItem(IDC_SN_INPUT5)->GetWindowText(m_thread_params[5].router_sn);
		//	GetDlgItem(IDC_SN_INPUT5)->SetWindowText("");
		//	if(m_thread_params[5].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[5].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT6:
		//	GetDlgItem(IDC_SN_INPUT6)->GetWindowText(m_thread_params[6].router_sn);
		//	GetDlgItem(IDC_SN_INPUT6)->SetWindowText("");
		//	if(m_thread_params[6].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[6].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT7:
		//	GetDlgItem(IDC_SN_INPUT7)->GetWindowText(m_thread_params[7].router_sn);
		//	GetDlgItem(IDC_SN_INPUT7)->SetWindowText("");
		//	if(m_thread_params[7].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[7].test_work = 1;
		//	return FALSE;
		//	break;
		//case IDC_SN_INPUT8:
		//	GetDlgItem(IDC_SN_INPUT8)->GetWindowText(m_thread_params[8].router_sn);
		//	GetDlgItem(IDC_SN_INPUT8)->SetWindowText("");
		//	if(m_thread_params[8].router_sn.IsEmpty())
		//	{
		//		MessageBox("SN不能为空!");
		//		break;
		//	}
		//	m_thread_params[8].test_work = 1;
		//	return FALSE;
		//	break;

		default:
			break;
		}
		return TRUE;				
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
