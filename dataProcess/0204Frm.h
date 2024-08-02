// 0204Frm.h : interface of the C0204Frame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_0204FRM_H__4C21343D_0930_11D5_A465_00485455D12D__INCLUDED_)
#define AFX_0204FRM_H__4C21343D_0930_11D5_A465_00485455D12D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class C0204Frame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(C0204Frame)

public:
	C0204Frame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C0204Frame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C0204Frame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(C0204Frame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0204FRM_H__4C21343D_0930_11D5_A465_00485455D12D__INCLUDED_)
