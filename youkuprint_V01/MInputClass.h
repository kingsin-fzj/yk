#pragma once


// MInputClass �Ի���

class MInputClass : public CDialog
{
	DECLARE_DYNAMIC(MInputClass)

public:
	MInputClass(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MInputClass();
	CString GetData(){return m_sn;};
// �Ի�������
	enum { IDD = IDD_INPUTBOX };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CString m_sn;	 // �������ȡSN
	UINT	m_fail;  //ʧ�ܴ���
	UINT m_scal;  //��λ��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	virtual INT_PTR DoModal(UINT scal, UINT failnum);  //�Զ���DoModal
	virtual BOOL OnInitDialog();			//��ʼ����ر���
};
