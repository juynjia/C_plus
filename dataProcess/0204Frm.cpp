// 0204Frm.cpp : implementation of the C0204Frame class
//

#include "StdAfx.h"
#include "PRS.h"

#include "0204Frm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C0204Frame

IMPLEMENT_DYNCREATE(C0204Frame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(C0204Frame, CMDIChildWnd)
	//{{AFX_MSG_MAP(C0204Frame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C0204Frame construction/destruction

C0204Frame::C0204Frame()
{
}

C0204Frame::~C0204Frame()
{
}

BOOL C0204Frame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style |= WS_MAXIMIZE;
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// C0204Frame diagnostics

#ifdef _DEBUG
void C0204Frame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void C0204Frame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C0204Frame message handlers

void C0204Frame::ActivateFrame(int nCmdShow) 
{
    nCmdShow = SW_MAXIMIZE;	
	CMDIChildWnd::ActivateFrame(nCmdShow);
}
