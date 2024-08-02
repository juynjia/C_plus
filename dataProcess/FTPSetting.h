#if !defined(AFX_FTPSETTING_H__F0F6DFA6_3205_11D5_B1F6_00E018002677__INCLUDED_)
#define AFX_FTPSETTING_H__F0F6DFA6_3205_11D5_B1F6_00E018002677__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FTPSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FTPSetting dialog

class FTPSetting : public CDialog
{
// Construction
public:
	FTPSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FTPSetting)
	enum { IDD = IDD_DIALOG_FTP_SET };
	CString	m_exportname;
	CString	m_ip;
	CString	m_username;
	CString	m_userpassword;
	CString	m_port;
	BOOL	m_check_ftp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FTPSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FTPSetting)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonConnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FTPSETTING_H__F0F6DFA6_3205_11D5_B1F6_00E018002677__INCLUDED_)
