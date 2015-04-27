#pragma once


// MInputClass 对话框

class MInputClass : public CDialog
{
	DECLARE_DYNAMIC(MInputClass)

public:
	MInputClass(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MInputClass();
	CString GetData(){return m_sn;};
// 对话框数据
	enum { IDD = IDD_INPUTBOX };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString m_sn;	 // 弹出框获取SN
	UINT	m_fail;  //失败次数
	UINT m_scal;  //槽位号
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	virtual INT_PTR DoModal(UINT scal, UINT failnum);  //自定义DoModal
	virtual BOOL OnInitDialog();			//初始化相关变量
};
