// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PRS.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIClientWnd

CMDIClientWnd::CMDIClientWnd()
{
}

CMDIClientWnd::~CMDIClientWnd()
{
}

BEGIN_MESSAGE_MAP(CMDIClientWnd, CWnd)
	//{{AFX_MSG_MAP(CMDIClientWnd)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIClientWnd message handlers

BOOL CMDIClientWnd::OnEraseBkgnd(CDC* pDC) 
{
    return TRUE;
}

void CMDIClientWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    RECT rect;
    GetClientRect(&rect);
    m_hBackground.Draw(&dc, &rect);
}

void CMDIClientWnd::PreSubclassWindow() 
{
    m_hBackground.LoadFromResource(IMAGE_BITMAP, IDB_BACKGROUND_BITMAP1);
    m_hBackground.SetStyle(STYLE_CASCADE);
	CWnd::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOVE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditGeneral)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditGeneral)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	ON_COMMAND_EX(ID_VIEW_RECORD, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RECORD, OnUpdateControlBarMenu)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    CRect rect, rectBorder(0, 2, 0, 2);

    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

    // subclass MDI client window
    if (m_wndMDIClient.SubclassWindow(m_hWndMDIClient) == FALSE)
    {
		TRACE("Failed to subclass MDI client window!\n");
        return -1;
    }
    
    DWORD dwCtrlStyle = TBSTYLE_FLAT;
    DWORD dwStyle = WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC;

    // create toolbar
	if (!m_wndToolBar.CreateEx(this, dwCtrlStyle, dwStyle, rectBorder) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

    // create record toolbar
    if (!m_wndRecordBar.CreateEx(this, dwCtrlStyle, dwStyle, rectBorder, ID_VIEW_RECORD) ||
        !m_wndRecordBar.LoadToolBar(IDR_RECORD))
	{
		TRACE0("Failed to create record toolbar\n");
		return -1;      // fail to create
	}

    // create edit and static control on record toolbar
#define RECORD_BORDER  3
#define RECORD_EDIT_INDEX   6
#define RECORD_EDTT_WIDTH   60
#define RECORD_TOTAL_INDEX  9   
#define RECORD_TOTAL_WIDTH  60

	m_wndRecordBar.SetButtonInfo(RECORD_EDIT_INDEX, IDC_RECORD_INDEX, TBBS_SEPARATOR, RECORD_EDTT_WIDTH);
	m_wndRecordBar.GetItemRect(RECORD_EDIT_INDEX, rect);
    rect.top    += 2;
    rect.bottom -= 2;
    rect.left  += RECORD_BORDER;
    rect.right -= RECORD_BORDER;
	if (!m_hEdit.Create(WS_VISIBLE|WS_CHILD|WS_BORDER|ES_NUMBER|ES_RIGHT|ES_AUTOHSCROLL,
			rect, &m_wndRecordBar, IDC_RECORD_INDEX))
	{
		TRACE0("Failed to create edit control\n");
		return -1;
	}

	m_wndRecordBar.SetButtonInfo(RECORD_TOTAL_INDEX, IDC_RECORD_TOTAL, TBBS_SEPARATOR, RECORD_TOTAL_WIDTH);
	m_wndRecordBar.GetItemRect(RECORD_TOTAL_INDEX, rect);
    rect.top    += 2;
    rect.bottom -= 2;
    rect.left  += RECORD_BORDER;
    rect.right -= RECORD_BORDER;
	if (!m_hStatic.Create("", WS_VISIBLE|WS_CHILD|SS_CENTERIMAGE, rect, &m_wndRecordBar, IDC_RECORD_TOTAL))
	{
		TRACE0("Failed to create static control\n");
		return -1;
	}

	m_hEdit.SetFont(m_wndRecordBar.GetFont());
	m_hStatic.SetFont(m_wndRecordBar.GetFont());

    // create status bar
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// docking toolbars
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndRecordBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

    rect.SetRect(0, 0, 600, 600);
    ClientToScreen(&rect);
	DockControlBar(&m_wndRecordBar, (UINT)0, rect);
	DockControlBar(&m_wndToolBar, (UINT)0, rect);

    // setup title
    CString szTitle;
    szTitle.LoadString(IDS_TOOLBAR_TITLE);
    m_wndToolBar.SetWindowText(szTitle);
    szTitle.LoadString(IDS_RECORD_TITLE);
    m_wndRecordBar.SetWindowText(szTitle);

    return 0;
}

void CMainFrame::OnDestroy() 
{
	CMDIFrameWnd::OnDestroy();
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    CSetting *pSetting = AfxGetSetting();

    // Reload window position and size
    POINT point = { (int)pSetting->m_nWndPos>>16, (int)pSetting->m_nWndPos&0xFFFF };
    SIZE  size  = { (int)pSetting->m_nWndSize>>16, (int)pSetting->m_nWndSize&0xFFFF };

    int cx, cy;
    if (size.cx > (cx = ::GetSystemMetrics(SM_CXMAXIMIZED))) size.cx = cx;
    if (size.cy > (cy = ::GetSystemMetrics(SM_CYSCREEN)))    size.cy = cy;
    if (point.x > (cx = ::GetSystemMetrics(SM_CXSCREEN)))    point.x = 0;
    if (point.y > cy)                                        point.y = 0;

    CRect rect(point, size);
    if (rect.right < 0) rect.OffsetRect(-rect.left, 0);
    if (rect.bottom < 0) rect.OffsetRect(0, -rect.top);

    cs.x  = rect.left;    cs.y  = rect.top;
    cs.cx = rect.Width(); cs.cy = rect.Height();
   
	return CMDIFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::UpdateCount(int nIndex, int nTotal)
{
    ASSERT((nIndex>0 && nIndex<=nTotal) || (nIndex==0 && nTotal==0));
    
    CString szFormat, szText;
    szFormat.LoadString(IDS_FORMAT_TOTAL);
    szText.Format(szFormat, nTotal);
    m_wndRecordBar.SetDlgItemInt(IDC_RECORD_INDEX, nIndex);
    m_wndRecordBar.SetDlgItemText(IDC_RECORD_TOTAL, szText);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnMove(int x, int y) 
{
	CMDIFrameWnd::OnMove(x, y);
    if (!IsIconic() && !IsZoomed())
    {
        RECT rect;
        GetWindowRect(&rect);
        AfxGetSetting()->m_nWndPos = ((WORD)rect.left<<16) | ((WORD)rect.top&0xFFFF);
    }
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
    AfxGetSetting()->m_nWndFlag = 0;
    switch (nType)
    {
    case SIZE_RESTORED:
        {
            CRect rect;
            GetWindowRect(rect);
            AfxGetSetting()->m_nWndSize = ((WORD)rect.Width()<<16) | ((WORD)rect.Height()&0xFFFF);
        }
        break;
    case SIZE_MAXIMIZED:
        AfxGetSetting()->m_nWndFlag = 1;
        break;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame command message handlers

BOOL IsEditClass(CWnd *pWnd)
{
    BOOL bResult=FALSE;
    if (pWnd)
    {
        char classname[16];
        int len = ::GetClassName(pWnd->m_hWnd, classname, 15);
        if (len > 0)
        {
            CString name(classname, len);
            bResult = (name.CompareNoCase("Edit") == 0);
        }
    }
    return bResult;
}

void CMainFrame::OnEditUndo() 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    if (IsEditClass(pEdit) && pEdit->CanUndo())
        pEdit->Undo();
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    pCmdUI->Enable(IsEditClass(pEdit) && pEdit->CanUndo());
}

void CMainFrame::OnEditCut() 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    if (IsEditClass(pEdit)) pEdit->Cut();
}

void CMainFrame::OnEditCopy() 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    if (IsEditClass(pEdit)) pEdit->Copy();
}

void CMainFrame::OnUpdateEditGeneral(CCmdUI* pCmdUI) 
{
    DWORD value = 0;
    CEdit *pEdit = (CEdit*)GetFocus();
    if (IsEditClass(pEdit))
        value = pEdit->GetSel();
    pCmdUI->Enable(HIWORD(value) != LOWORD(value));
}

void CMainFrame::OnEditPaste() 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    if (IsEditClass(pEdit)) pEdit->Paste();
}

void CMainFrame::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    CEdit *pEdit = (CEdit*)GetFocus();
    pCmdUI->Enable(IsEditClass(pEdit) && ::IsClipboardFormatAvailable(CF_TEXT));
}