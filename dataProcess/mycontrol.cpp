// MyControl.cpp : implementation file
//

#include "StdAfx.h"
#include "prs.h"
#include "MyControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUTTON_UP       0x0001
#define BUTTON_DOWN     0x0002
#define BUTTON_SWITCH   (0x0001<<16)

/////////////////////////////////////////////////////////////////////////////
// CMyButton

CMyButton::CMyButton()
{
    m_nFlags       = 0;
    m_bDown        = FALSE;
    m_bCapture     = FALSE;
    m_bDrawing     = FALSE;
    m_bErasing     = FALSE;
    m_bTransparent = TRUE;

    m_hRgnUpdate.CreateRectRgn(0, 0, 0, 0);
}

CMyButton::~CMyButton()
{
    m_hRgnUpdate.DeleteObject();
}

void CMyButton::DrawSurface(CDC& dc, const CString& text, const CRect& rect)
{
    UINT nStyle = GetStyle();
    UINT nFormat = 0;
    CRect bound = rect;

    // horizontal
    if (nStyle & BS_LEFT) nFormat |= DT_LEFT;
    else if (nStyle & BS_RIGHT) nFormat |= DT_RIGHT;
    else nFormat |= DT_CENTER;

    // vertical
    dc.SetTextAlign(dc.GetTextAlign() & ~TA_UPDATECP);

    if (nStyle & BS_MULTILINE)
    {
        nFormat |= DT_WORDBREAK;
        // bound rect will be modified
        dc.DrawText(text, bound, nFormat|DT_CALCRECT);
        int w = bound.Width(), h = bound.Height();
        bound.top    = rect.top + (rect.Height() - h) / 2;
        bound.bottom = bound.top + h;
        bound.left   = rect.left + (rect.Width() - w) / 2; 
        bound.right  = bound.left + w;
    }
    else
    {
        nFormat |= DT_SINGLELINE;
        if (nStyle & BS_TOP) nFormat |= DT_TOP;
        else if (nStyle & BS_BOTTOM) nFormat |= DT_BOTTOM;
        else nFormat |= DT_VCENTER;
    }

    dc.DrawText(text, bound, nFormat);
}

void CMyButton::DrawSurface(CDC& dc, CBitmap *pBitmap, const CRect& rect)
{
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap *pOldBitmap = memDC.SelectObject(pBitmap);

	dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
}

BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(CMyButton)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyButton message handlers

void CMyButton::PreSubclassWindow() 
{
    //ASSERT((GetButtonStyle() == BS_PUSHBUTTON) || (GetButtonStyle() == BS_OWNERDRAW));
    SetButtonStyle(BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

LRESULT CMyButton::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    LRESULT lResult;
	switch (message)
    {
    case WM_ERASEBKGND:
        if (!(lResult = m_bErasing))
        {
            m_bErasing = TRUE;
            lResult = CButton::WindowProc(message, wParam, lParam);
            m_bErasing = FALSE;
        }
        break;
    case WM_PAINT:
        if (lResult = !m_bDrawing)
        {
            m_bDrawing = TRUE;
            GetUpdateRgn(&m_hRgnUpdate);
            lResult = CButton::WindowProc(message, wParam, lParam);
            m_bDrawing = FALSE;
        }
        break;
    default:
	    lResult = CButton::WindowProc(message, wParam, lParam);
        break;
    }
    return lResult;
}

BOOL CMyButton::OnEraseBkgnd(CDC* pDC) 
{
    if (m_bTransparent)
    {
        CRect rect;
        GetWindowRect(rect);
        POINT org = rect.TopLeft();
        CWnd *pWnd = GetParent();
        ASSERT(pWnd != NULL);
        pWnd->ScreenToClient(&org);
        m_hRgnUpdate.OffsetRgn(org);
        //pWnd->RedrawWindow(NULL, &m_hRgnUpdate, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_NOCHILDREN);
        pWnd->RedrawWindow(NULL, &m_hRgnUpdate, RDW_ERASE|RDW_INVALIDATE|RDW_UPDATENOW|RDW_NOCHILDREN);
        m_hRgnUpdate.SetRectRgn(0, 0, 0, 0);
        return TRUE;
    }
    return CButton::OnEraseBkgnd(pDC);
}

HBRUSH CMyButton::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    if (m_bTransparent)
    {
        pDC->SetBkMode(TRANSPARENT);
        return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
    }
    return NULL; // pass to parent
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

    CDC dc;
    if (dc.Attach(lpDrawItemStruct->hDC))
    {
        CRect rect = lpDrawItemStruct->rcItem;

        // draw button edge
        if (m_nFlags & (BUTTON_DOWN|BUTTON_UP))
            dc.DrawEdge(rect, (m_nFlags&BUTTON_DOWN)?BDR_SUNKENOUTER:BDR_RAISEDINNER, BF_RECT);

        if (m_bDown)
            rect.OffsetRect(2, 2);

        // draw surface
        if (GetStyle() & BS_BITMAP)
            DrawSurface(dc, CBitmap::FromHandle(GetBitmap()), rect);
        else
        {
            CString text;
            GetWindowText(text);
            DrawSurface(dc, text, rect);
        }

        dc.Detach();
    }
}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (IsWindowEnabled())
    {
        if (m_bCapture)
        {
            m_bCapture = FALSE;
            ReleaseCapture();
        }

        if (!m_bDown)
        {
            m_bDown  = TRUE;
            m_nFlags |= BUTTON_SWITCH;
            OnMouseMove(nFlags, point);
        }
    }

    // default will capture the mouse, and send a WM_PAINT without erase
    // the background, so it should be called last
    CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CButton::OnLButtonUp(nFlags, point);

    if (IsWindowEnabled())
    {
        if (m_bDown)
        {
            m_bDown   = FALSE;
            m_nFlags |= BUTTON_SWITCH;
            OnMouseMove(nFlags, point);
        }	
    }
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point) 
{
    static UINT flags[2][2] = { 0, BUTTON_UP, BUTTON_UP, BUTTON_DOWN };

	if (IsWindowEnabled())
    {
        CRect rect;
        GetClientRect(rect);
        int nInside = rect.PtInRect(point)?1:0;

        if (m_bDown == FALSE)
        {
            if (nInside)
            {
                if (!m_bCapture)
                {
                    m_bCapture = TRUE;
                    SetCapture();
                }
            }
            else if (m_bCapture)
            {
                m_bCapture = FALSE;
                ReleaseCapture();
            }
        }

        UINT nFlag = flags[nInside][m_bDown?1:0];
        if ((m_nFlags&0xF) != nFlag)
        {
            CRect rect;
            GetClientRect(rect);
            m_hRgnUpdate.SetRectRgn(rect);

            if (!(m_nFlags & BUTTON_SWITCH))
            {
                int nCx = (::GetSystemMetrics(SM_CXEDGE)+1) / 2;
                int nCy = (::GetSystemMetrics(SM_CYEDGE)+1) / 2;
                rect.DeflateRect(nCx, nCy);
                CRgn rgn;
                rgn.CreateRectRgnIndirect(rect);
                m_hRgnUpdate.CombineRgn(&m_hRgnUpdate, &rgn, RGN_DIFF);
            }

            m_nFlags = nFlag;
            Invalidate();
        }
    }

	CButton::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CMyTab

CMyTab::CMyTab()
{
    m_bErasing     = FALSE;
    m_bTransparent = TRUE;
    m_hRgnUpdate.CreateRectRgn(0, 0, 0, 0);
}

CMyTab::~CMyTab()
{
}

BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTab)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTab message handlers

LRESULT CMyTab::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    LRESULT lResult;
	switch (message)
    {
    case WM_ERASEBKGND:
        if (!(lResult = m_bErasing))
        {
            m_bErasing = TRUE;
            lResult = CTabCtrl::WindowProc(message, wParam, lParam);
            m_bErasing = FALSE;
        }
        break;
    case WM_PAINT:
        GetUpdateRgn(&m_hRgnUpdate);
        // fall through
    default:
	    lResult = CTabCtrl::WindowProc(message, wParam, lParam);
        break;
    }
    return lResult;
}

BOOL CMyTab::OnEraseBkgnd(CDC* pDC) 
{
    if (m_bTransparent)
    {
        CRect rect;
        GetWindowRect(rect);
        POINT org = rect.TopLeft();
        CWnd *pWnd = GetParent();
        ASSERT(pWnd != NULL);
        pWnd->ScreenToClient(&org);
        m_hRgnUpdate.OffsetRgn(org);
        pWnd->RedrawWindow(NULL, &m_hRgnUpdate, RDW_INVALIDATE|RDW_NOERASE|RDW_UPDATENOW|RDW_NOCHILDREN);
        m_hRgnUpdate.SetRectRgn(0, 0, 0, 0);
        return TRUE;
    }
    return CTabCtrl::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMyCombo

CMyCombo::CMyCombo()
{
    m_bTransparent = TRUE;
}

CMyCombo::~CMyCombo()
{
}

BEGIN_MESSAGE_MAP(CMyCombo, CComboBox)
	//{{AFX_MSG_MAP(CMyCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCombo message handlers

LRESULT CMyCombo::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // Hack: use our hwnd instead of child's hwnd
    switch (message)
    {
    case WM_CTLCOLORMSGBOX:
    case WM_CTLCOLOREDIT:
    case WM_CTLCOLORLISTBOX:
    case WM_CTLCOLORBTN:
    case WM_CTLCOLORDLG:
    case WM_CTLCOLORSCROLLBAR:
    case WM_CTLCOLORSTATIC:
        return DefWindowProc(message, wParam, (LPARAM)m_hWnd);
    }
	return CComboBox::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMyEdit window

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) 
{
    switch (pMsg->message)
    {
    case WM_KEYDOWN:
        ASSERT(GetParent());
        // tricky
        if (pMsg->wParam == VK_RETURN)
            GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetWindowLong(m_hWnd, GWL_ID), EN_VSCROLL), (LPARAM)m_hWnd);
        break;
    }
	return CEdit::PreTranslateMessage(pMsg);
}

