// DlgPasswd.h : header file
//

#ifndef __DLGPASSWD_H__
#define __DLGPASSWD_H__

/////////////////////////////////////////////////////////////////////////////
// CDialogPassword dialog

class CDialogPassword : public CDialog
{
// Construction
public:
	CDialogPassword(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogPassword)
	enum { IDD = IDD_DIALOG_PASSWORD };
	CString	m_strPassword;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogPassword)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Encrypt(LPCSTR lpsz1, CString& strOut);
	void SetPrompt();

	BOOL m_bConfirmMode;
	CString m_strConfirming;

	// Generated message map functions
	//{{AFX_MSG(CDialogPassword)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif