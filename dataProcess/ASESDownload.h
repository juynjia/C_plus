#if !defined(AFX_ASESDOWNLOAD_H__4B3E0709_1C2B_11D5_8FAD_00E018002562__INCLUDED_)
#define AFX_ASESDOWNLOAD_H__4B3E0709_1C2B_11D5_8FAD_00E018002562__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ASESDownload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ASESDownload dialog

class ASESDownload : public CDialog
{
// Construction
public:
	ASESDownload(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ASESDownload)
	enum { IDD = IDD_ASES_DOWNLOAD };
	CProgressCtrl	m_cProgress;
	CString	m_str0204num;
	CString	m_strStatus;
	int		m_BARID;
	int		m_LOCKPID;
	int		m_STATUS;
	CString	m_TX_NUM;
	CString	m_TX_NUM10;
	int		m_STATUS10;
	int		m_BARID10;
	int		m_LOCKPID10;
	int		m_ANNID;
	int		m_ANNID10;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ASESDownload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ASESDownload)
	afx_msg void OnBeginDownload();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeTxNum10();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASESDOWNLOAD_H__4B3E0709_1C2B_11D5_8FAD_00E018002562__INCLUDED_)
