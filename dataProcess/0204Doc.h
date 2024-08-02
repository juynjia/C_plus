// 0204Doc.h : interface of the C0204Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_0204DOC_H__4C21343F_0930_11D5_A465_00485455D12D__INCLUDED_)
#define AFX_0204DOC_H__4C21343F_0930_11D5_A465_00485455D12D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "0204Set.h"
#include "MainFrm.h"

class C0204View;

class C0204Doc : public CDocument
{
private:
    void UpdateCount();
    void QueryApply(LPCSTR);

protected: // create from serialization only
	C0204Doc();
	DECLARE_DYNCREATE(C0204Doc)

    UINT m_nRecordIndex;
    UINT m_nRecordTotal;
    UINT m_nApplyIndex;
    UINT m_nApplyTotal;

// Attributes
public:
    CDatabase m_hDatabase;
	C0204RecordSet m_h0204RecordSet;
    C0204ApplySet  m_h0204ApplySet;

// Operations
public:
    inline UINT GetRecordIndex() { return m_nRecordIndex; }
    inline UINT GetRecordTotal() { return m_nRecordTotal; }
    inline UINT GetApplyIndex() { return m_nApplyIndex; }
    inline UINT GetApplyTotal() { return m_nApplyTotal; }

    BOOL Query(LPCSTR szSQL);

	void OnRecordMove(UINT nIDMoveCommand);
	void OnApplyMove(UINT nIDMoveCommand);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C0204Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
    virtual void SetTitle(LPCTSTR lpszTitle);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C0204Doc();

    CMainFrame* GetMainFrame() const;
	C0204View* GetView() const;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C0204Doc)
	afx_msg void OnFileSave();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordCancel();
	afx_msg void OnUpdateRecordCancel(CCmdUI* pCmdUI);
	afx_msg void On0204ApplyNew();
	afx_msg void On0204ApplyDelete();
	//}}AFX_MSG
	afx_msg void OnUpdateRecordMove(CCmdUI* pCmdUI);
    void OnUpdateApplyMove();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 0204Doc.cpp
inline CMainFrame* C0204Doc::GetMainFrame() const
   { return (CMainFrame*)AfxGetMainWnd(); }
inline C0204View* C0204Doc::GetView() const
   { POSITION pos = GetFirstViewPosition(); return (C0204View*)GetNextView(pos); }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0204DOC_H__4C21343F_0930_11D5_A465_00485455D12D__INCLUDED_)
