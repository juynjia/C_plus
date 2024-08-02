// DlgColor.h : header file
//
#if !defined(AFX_DLGCOLOR_H__D3862583_289D_11D5_8176_0050BA130582__INCLUDED_)
#define AFX_DLGCOLOR_H__D3862583_289D_11D5_8176_0050BA130582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogColor dialog

class CDialogColor : public CDialog
{
private:
    CBrush m_hBrush;

// Construction
public:
	CDialogColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogColor)
	enum { IDD = IDD_DIALOG_COLOR };
	CComboBox	m_hComboItem;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDialogColor)
	afx_msg void OnSelchangeDlgcolorItem();
	afx_msg void OnDlgcolorChoose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg void OnDlgcolorRadio(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOLOR_H__D3862583_289D_11D5_8176_0050BA130582__INCLUDED_)
