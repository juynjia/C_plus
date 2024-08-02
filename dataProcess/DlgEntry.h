// DlgEntry.h : header file
//

#if !defined(AFX_DLGENTRY_H__6972D863_24BA_11D5_8175_0050BA130582__INCLUDED_)
#define AFX_DLGENTRY_H__6972D863_24BA_11D5_8175_0050BA130582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogEntry dialog

class CDialogEntry : public CDialog
{
// Construction
public:
	CDialogEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogEntry)
	enum { IDD = IDD_DIALOG_ENTRY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogEntry)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogEntry)
	virtual BOOL OnInitDialog();
	afx_msg void OnDlgentryConfigure();
	afx_msg void OnDlgentryDispatch();
	afx_msg void OnDlgentryPrint();
	afx_msg void OnDlgentryColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGENTRY_H__6972D863_24BA_11D5_8175_0050BA130582__INCLUDED_)
