// MInputClass.cpp : 实现文件
//

#include "stdafx.h"
#include "youkuprint_V01.h"
#include "MInputClass.h"
#include "afxdialogex.h"

#include "youkuprint_V01Dlg.h"

// MInputClass 对话框

IMPLEMENT_DYNAMIC(MInputClass, CDialog)

MInputClass::MInputClass(CWnd* pParent /*=NULL*/)
	: CDialog(MInputClass::IDD, pParent)
{

}

MInputClass::~MInputClass()
{
}

void MInputClass::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MInputClass, CDialog)
	ON_BN_CLICKED(IDOK, &MInputClass::OnBnClickedOk)
END_MESSAGE_MAP()


// MInputClass 消息处理程序

INT_PTR MInputClass::DoModal(UINT scal, UINT failnum)
{
	m_scal = scal;
	m_fail = failnum;
	return CDialog::DoModal();
}

BOOL MInputClass::OnInitDialog()
{
	MoveWindow(210, 90, 310, 200);
	CString temp;
	CDialog::OnInitDialog();
	if(m_scal > 0){
		temp.Format("%d", m_scal);
		GetDlgItem(IDC_SCAL)->SetWindowText(temp);
	}
	
	if(m_fail > 0){
		temp.Empty();
		temp.Format("%d", m_fail);
		GetDlgItem(IDC_NUM)->SetWindowText(temp);
	}
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return FALSE;
}

void MInputClass::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//Cyoukuprint_V01Dlg *ptr = (Cyoukuprint_V01Dlg*)AfxGetApp()->m_pMainWnd;
	 
	GetDlgItem(IDC_EDIT1)->GetWindowText(m_sn);
	if(!m_sn.IsEmpty()){
		//ptr->m_thread_params[m_scal].router_sn = m_sn;
		CDialog::OnOK();
	}
	else{
		MessageBox("请输入正确SN");
	}
}
