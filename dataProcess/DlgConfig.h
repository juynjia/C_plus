// DlgConfig.h : header file
//

#if !defined(AFX_DLGCONFIG_H__6972D866_24BA_11D5_8175_0050BA130582__INCLUDED_)
#define AFX_DLGCONFIG_H__6972D866_24BA_11D5_8175_0050BA130582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogConfigure dialog

class CDialogConfigure : public CDialog
{
// Construction
public:
	CDialogConfigure(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogConfigure)
	enum { IDD = IDD_DIALOG_CONFIG };
	CComboBox	m_hDevice;
	CComboBox	m_hVersion;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogConfigure)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogConfigure)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDlgconfigVersion();
	//}}AFX_MSG
	afx_msg void OnDlgconfigbtn(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONFIG_H__6972D866_24BA_11D5_8175_0050BA130582__INCLUDED_)
