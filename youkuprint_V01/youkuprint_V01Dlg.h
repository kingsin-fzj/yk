
// youkuprint_V01Dlg.h : ͷ�ļ�
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
	UINT sn_inputID;	// sn �����ؼ�ID
	UINT snID;		// sn ��ӡ��״̬�ؼ�ID
	CString router_mac;
	CString router_sn;
	UINT macID;	// mac��ӡ��״̬�ؼ�ID
	UINT resultID;	// ��������ִ�н������ؼ�ID
	UINT testID;  //��¼����״̬
	UINT ipID;
	UINT m_failnum; //��¼ʧ�ܴ���
	ClientSocket db_socket;
	SOCKET		 router_socket;
	
	UINT scal;
	UINT test_flag;	//�̶�ֵΪ2
	UINT test_stat; 
	UINT link_flag;  
	UINT link_stat;
	UINT test_work;
	//UINT mode_flag;   //ģʽ��־
	CString router_name;
	CString router_key;
	//UINT resultflag;  /*�����ܽ����־λ1��ʾ�ɹ���0��ʾʧ��*/
};

/*��¼���Ի�������꣬����ȷ��SN����Ի����λ��*/
//CRect m_rect;
// Cyoukuprint_V01Dlg �Ի���
class Cyoukuprint_V01Dlg : public CDialogEx
{
// ����
public:
	Cyoukuprint_V01Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_YOUKUPRINT_V01_DIALOG };
	CBrush m_brush;
	CFont m_font;
	static UINT __cdecl TestPing(LPVOID info);  //ģ��DOS ping��ʾ����
	static UINT __cdecl test_paint_threadresultall(LPVOID info);   //�����ܽ��
	static UINT __cdecl test_paint_threadresult1(LPVOID info);   //�ر�Telnet�߳�
	static UINT __cdecl Dilog_thread(LPVOID info);   //�ر�Telnet�߳�
		
	//static UINT __cdecl Begin(LPVOID info);
	bool ReadConfig();
	bool Begin();
	bool GetOn(SOCKET *conn,UINT scal);
	bool GetMacSn(SOCKET conn, UINT scal);
	bool MyCheckout(ClientSocket dbclilent, UINT scal);
	bool UpdateCheck(ClientSocket dbclilent, UINT scal);
	bool OnPrint();   //��ӡ����
	bool MyUpdata();		  //�������ݿ�
	void start_thread();

	HBRUSH m_Brush[3];
//Dialog Data
	CEdit m_ping;
	CString allfilepath;     //ִ�г�����ȫ·���洢����
	/*���ݿ����*/
	CString sql_ip;
	int sql_port;
	CString sql_dbname;
	CString sqltable_name;
	/*�����ļ��еĴ�ӡ����*/
	CString barcodeWindowName;
	CString barcodeWindowClass;
	CString printWindowName;
	CString printWindowClass;
	CString configPath;

	/*����·�ɲ���*/
	CString router_ip;
	CString router_name;
	CString router_key;
	/*��·������ȡSN/MAC*/
	CString result_mac;
	CString rfmac;  //��·�ɻ�ȡmac
	CString temp_mac;  //У��mac��ʱ����
	CString result_sn;
	CString rfsn;   //��·�ɻ�ȡsn
	CString temp_sn;  //У��sn��ʱ����

	/*
	��ƺ��� ��һ������Ϊ��ͨ��/����״̬ ��Ӧ����ֵ��0��1��2��3��
	�ڶ�������Ϊ�豸�ţ�1-8����
	����������Ϊ��Ӧ��״̬��0δִ�У�1ִ�й����У�2�ɹ���3ʧ��
	*/
	void test_paint(int mode, int scal, int stat);
	ClientSocket clientSocket;

	CString log;

	//���ļ�·����ȡ���������Ϣ
	CString Filepath_Po;   //PO��
	CString Station;   //վλ
	CString User;   //�û���
	CString flowline;  //��ˮ��
//telnet
	//SOCKET clientconn;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	int     runMessageFlag;             // ������Ϣ��ʶ��            1��PASS����    -1��FAIL����    0����ʼ״̬��
	int     testResultFlag;             // ���Խ����ʶ��            1��PASS����    -1��FAIL����    0����ʼ״̬��
	bool    printFlag;    // Ϊ�棬��ʾ��ӡ�ɹ�
	void WriteLogFile(CString mac, CString sn);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);  //��������������
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
