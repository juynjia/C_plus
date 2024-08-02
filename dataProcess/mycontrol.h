// MyControl.h : header file
//

#if !defined(AFX_MYCONTROL_H__FF8D02E1_0AFE_11D5_A242_444553540001__INCLUDED_)
#define AFX_MYCONTROL_H__FF8D02E1_0AFE_11D5_A242_444553540001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyButton window

class CMyButton : public CButton
{
private:
    UINT m_nFlags;
    BOOL m_bDown;
    BOOL m_bCapture;
    CRgn m_hRgnUpdate;
    BOOL m_bDrawing;
    BOOL m_bErasing;

    void DrawSurface(CDC&, const CString&, const CRect&);
    void DrawSurface(CDC&, CBitmap*, const CRect&);

public:
    BOOL m_bTransparent; // default TRUE

// Construction
public:
	CMyButton();
	virtual ~CMyButton();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyTab window

class CMyTab : public CTabCtrl
{
private:
    CRgn m_hRgnUpdate;
    BOOL m_bErasing;

public:
    BOOL m_bTransparent; // default TRUE

// Construction
public:
	CMyTab();
	virtual ~CMyTab();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTab)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

    // Generated message map functions
protected:
	//{{AFX_MSG(CMyTab)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyCombo window

class CMyCombo : public CComboBox
{
public:
    BOOL m_bTransparent; // default TRUE

// Construction
public:
	CMyCombo();
	virtual ~CMyCombo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCombo)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyCombo)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CMyEdit window

class CMyEdit : public CEdit
{
// Construction
public:
	CMyEdit();
	virtual ~CMyEdit();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCONTROL_H__FF8D02E1_0AFE_11D5_A242_444553540001__INCLUDED_)
