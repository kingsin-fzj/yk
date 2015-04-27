
// youkuprint_V01Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"

#include "LinkServer.h"

//typedef struct DlgCtrl {
//	UINT ID_out;
//	UINT ID_write;
//};

typedef struct thread_Params {
	LPVOID pDlg;
	CString routerIP;
	UINT sn_inputID;	// sn 输入框控件ID
	UINT snID;		// sn 打印、状态控件ID
	CString router_mac;
	CString router_sn;
	UINT macID;	// mac打印、状态控件ID
	UINT resultID;	// 整个过程执行结果输出控件ID
	UINT testID;  //记录测试状态
	UINT ipID;
	UINT m_failnum; //记录失败次数
	ClientSocket db_socket;
	SOCKET		 router_socket;
	
	UINT scal;
	UINT test_flag;	//固定值为2
	UINT test_stat; 
	UINT link_flag;  
	UINT link_stat;
	UINT test_work;
	//UINT mode_flag;   //模式标志
	CString router_name;
	CString router_key;
	//UINT resultflag;  /*测试总结果标志位1表示成功，0表示失败*/
};

/*记录主对话框的坐标，用于确定SN输入对话框的位置*/
//CRect m_rect;
// Cyoukuprint_V01Dlg 对话框
class Cyoukuprint_V01Dlg : public CDialogEx
{
// 构造
public:
	Cyoukuprint_V01Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_YOUKUPRINT_V01_DIALOG };
	CBrush m_brush;
	CFont m_font;
	static UINT __cdecl TestPing(LPVOID info);  //模拟DOS ping显示功能
	static UINT __cdecl test_paint_threadresultall(LPVOID info);   //测试总结果
	static UINT __cdecl test_paint_threadresult1(LPVOID info);   //关闭Telnet线程
	static UINT __cdecl Dilog_thread(LPVOID info);   //关闭Telnet线程
		
	//static UINT __cdecl Begin(LPVOID info);
	bool ReadConfig();
	bool Begin();
	bool GetOn(SOCKET *conn,UINT scal);
	bool GetMacSn(SOCKET conn, UINT scal);
	bool MyCheckout(ClientSocket dbclilent, UINT scal);
	bool UpdateCheck(ClientSocket dbclilent, UINT scal);
	bool OnPrint();   //打印条码
	bool MyUpdata();		  //更新数据库
	void start_thread();

	HBRUSH m_Brush[3];
//Dialog Data
	CEdit m_ping;
	CString allfilepath;     //执行程序完全路径存储变量
	/*数据库参数*/
	CString sql_ip;
	int sql_port;
	CString sql_dbname;
	CString sqltable_name;
	/*配置文件中的打印参数*/
	CString barcodeWindowName;
	CString barcodeWindowClass;
	CString printWindowName;
	CString printWindowClass;
	CString configPath;

	/*待测路由参数*/
	CString router_ip;
	CString router_name;
	CString router_key;
	/*从路由器获取SN/MAC*/
	CString result_mac;
	CString rfmac;  //从路由获取mac
	CString temp_mac;  //校验mac临时变量
	CString result_sn;
	CString rfsn;   //从路由获取sn
	CString temp_sn;  //校验sn临时变量

	/*
	点灯函数 第一个参数为连通性/测试状态 对应参数值：0、1、2、3；
	第二个参数为设备号（1-8）；
	第三个参数为相应灯状态，0未执行，1执行过程中，2成功，3失败
	*/
	void test_paint(int mode, int scal, int stat);
	ClientSocket clientSocket;

	CString log;

	//从文件路径获取生产相关信息
	CString Filepath_Po;   //PO号
	CString Station;   //站位
	CString User;   //用户号
	CString flowline;  //流水线
//telnet
	//SOCKET clientconn;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	int     runMessageFlag;             // 运行信息标识：            1（PASS），    -1（FAIL），    0（初始状态）
	int     testResultFlag;             // 测试结果标识：            1（PASS），    -1（FAIL），    0（初始状态）
	bool    printFlag;    // 为真，表示打印成功
	void WriteLogFile(CString mac, CString sn);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);  //按键监听处理函数
	//afx_msg void OnCbnSelchangeCombo1();
	//afx_msg void OnCbnSelchangeCombo2();
	CStatic m_result;
	CStatic m_sn;
	CStatic m_mac;
	CStatic test_light1;
protected:
public:
	void OnOk();
	//afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	thread_Params m_thread_params[9];
};
