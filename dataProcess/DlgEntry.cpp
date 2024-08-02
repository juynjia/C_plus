// DlgEntry.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "DlgEntry.h"
#include "DlgPasswd.h"
#include "DlgConfig.h"
#include "DlgColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogEntry dialog


CDialogEntry::CDialogEntry(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogEntry::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogEntry)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDialogEntry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogEntry)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogEntry, CDialog)
	//{{AFX_MSG_MAP(CDialogEntry)
	ON_BN_CLICKED(IDC_DLGENTRY_CONFIGURE, OnDlgentryConfigure)
	ON_BN_CLICKED(IDC_DLGENTRY_DISPATCH, OnDlgentryDispatch)
	ON_BN_CLICKED(IDC_DLGENTRY_PRINT, OnDlgentryPrint)
	ON_BN_CLICKED(IDC_DLGENTRY_COLOR, OnDlgentryColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogEntry message handlers

BOOL CDialogEntry::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    typedef struct 
    {
        UINT control;
        UINT bitmap;
    } BITMAP_BUTTON;

    static BITMAP_BUTTON buttons[] = 
    {
        { IDC_DLGENTRY_CONFIGURE, IDB_SYS_CONFIG   },
        { IDC_DLGENTRY_DISPATCH,  IDB_SYS_DISPATCH },
        { IDC_DLGENTRY_PRINT,     IDB_SYS_PRINT    },
        { IDC_DLGENTRY_COLOR,     IDB_SYS_COLOR    },
        { ID_APP_EXIT,            IDB_SYS_EXIT     }
    };

    for (int i=0; i<(sizeof(buttons)/sizeof(BITMAP_BUTTON)); i++)
    {
	    CButton *pButton = (CButton*)GetDlgItem(buttons[i].control);
        ASSERT(pButton != NULL);
	    pButton->SetBitmap(::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(buttons[i].bitmap)));
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogEntry::OnDlgentryConfigure() 
{
	CDialogConfigure dlgConfig;
    CDialogPassword  dlgPassword;
	
	if (dlgPassword.DoModal() == IDOK)
	    dlgConfig.DoModal();
}

void CDialogEntry::OnDlgentryDispatch() 
{
    CDialog::OnOK();
    AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_OPEN, 0);
}

void CDialogEntry::OnDlgentryPrint() 
{
}

void CDialogEntry::OnDlgentryColor() 
{
    CDialogColor dlgColor;
    dlgColor.DoModal();
}
