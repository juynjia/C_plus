// 0204View.h : interface of the C0204View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_0204VIEW_H__4C213441_0930_11D5_A465_00485455D12D__INCLUDED_)
#define AFX_0204VIEW_H__4C213441_0930_11D5_A465_00485455D12D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyPicture.h"
#include "MyControl.h"
#include "0204Set.h"

#define COMBO_TOTAL     (IDC_0204_COMBO_END-IDC_0204_COMBO_BEGIN+1)
#define BUTTON_TOTAL    (IDC_0204_BUTTON_END-IDC_0204_BUTTON_BEGIN+1)
#define EDIT_TOTAL      (IDC_0204_EDIT_END-IDC_0204_EDIT_BEGIN+1)

class C0204View : public CFormView
{
private:
    CMyPicture m_hBackground;
    CToolBar m_wndApplyBar;
    static void CALLBACK EXPORT PRSTranBMSPollingTimerProc(
	   HWND hWnd,      // handle of CWnd that called SetTimer
	   UINT nMsg,      // WM_TIMER
	   UINT nIDEvent,   // timer identification
	   DWORD dwTime    // system time
	);
	static void CALLBACK EXPORT AutoUploadSCPPollingTimerProc(
	   HWND hWnd,      // handle of CWnd that called SetTimer
	   UINT nMsg,      // WM_TIMER
	   UINT nIDEvent,   // timer identification
	   DWORD dwTime    // system time
   );
    static int CALLBACK SortFunc(LPARAM, LPARAM, LPARAM);
    void AFXAPI DDX_Content(CDataExchange*, int, CString&);

protected: // create from serialization only
	C0204View();
	DECLARE_DYNCREATE(C0204View)

public:
	CMyCombo  m_hCombo[COMBO_TOTAL];
    CMyButton m_hButton[BUTTON_TOTAL];

	//{{AFX_DATA(C0204View)
	enum { IDD = IDD_0204_FORM };
	CListCtrl	m_hApplyContent;
	C0204RecordSet *m_p0204RecordSet;
    C0204ApplySet  *m_p0204ApplySet;
	//}}AFX_DATA

// Attributes
public:
	C0204Doc* GetDocument();
	CFtpClient m_ftp;
	CFtpServer m_ftps;
	void OnSessionAction();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C0204View)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void UpdateArrayFromView();
	virtual void ReloadViewFromDB();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C0204View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C0204View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnListCtrlItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnControlClicked();
	afx_msg void OnReplyBtnClicked();
	afx_msg void OnAsesUpload();
	afx_msg void OnAsesDownload();
	afx_msg void OnUpdateAsesUpload(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAsesDownload(CCmdUI* pCmdUI);
	afx_msg void On0204Query1();
	afx_msg void On0204Query2();
	afx_msg void OnAcceptFtpserver();
	afx_msg void OnListFtpserver(BSTR FAR* UserName);
	afx_msg void OnLoginFtpserver(short FAR* Connection, BSTR FAR* UserName, BSTR FAR* IPAddress);
	afx_msg void OnQueryFtpserver();
	afx_msg void OnActionProfile();
	afx_msg void OnFtpSet();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnControlChange(UINT nID);
    afx_msg void OnControlDataClicked(UINT nID);
    afx_msg void OnControlButtonClicked(UINT nID);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 0204View.cpp
inline C0204Doc* C0204View::GetDocument()
   { return (C0204Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0204VIEW_H__4C213441_0930_11D5_A465_00485455D12D__INCLUDED_)
