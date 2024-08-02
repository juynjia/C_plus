// DlgOpen.h : header file
//

#if !defined(AFX_DLGOPEN_H__781B4EC1_0E91_11D5_A242_444553540001__INCLUDED_)
#define AFX_DLGOPEN_H__781B4EC1_0E91_11D5_A242_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum
{
    DLGOPEN_TYPE_NEW=0,
    DLGOPEN_TYPE_OPEN,
    DLGOPEN_TYPE_TOTAL
};

enum
{
    DLGOPEN_0204_NEW=0,
    DLGOPEN_0204_CHANGE,
    DLGOPEN_0204_OPEN,
    DLGOPEN_TOTAL
};

/////////////////////////////////////////////////////////////////////////////
// CDialogOpen dialog

class CDialogOpen : public CDialog
{
public:
    int m_nOpenType;
    int m_nOpenResult;
    CImageList m_hImageList;

// Construction
public:
	CDialogOpen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogOpen)
	enum { IDD = IDD_DIALOG_OPEN };
	CStatic	m_hHelp;
	CButton	m_hOK;
	CListCtrl	m_hList;
	CTabCtrl	m_hTab;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogOpen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogOpen)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListctrl(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPEN_H__781B4EC1_0E91_11D5_A242_444553540001__INCLUDED_)
