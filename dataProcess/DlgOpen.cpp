// DlgOpen.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "DlgOpen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT labels[DLGOPEN_TYPE_TOTAL] = 
{
    IDS_DLGOPEN_NEW,
    IDS_DLGOPEN_OPEN
};

typedef struct
{
    UINT nStringID;
    UINT nImageID;
    int  nResult;
} DLGOPEN_ITEM;

static DLGOPEN_ITEM items_add[] = 
{
    //{ IDS_DLGOPEN_0204_NEW,    0, DLGOPEN_0204_NEW    },
    //{ IDS_DLGOPEN_0204_CHANGE, 0, DLGOPEN_0204_CHANGE },
    { 0, 0, 0 }
};

static DLGOPEN_ITEM items_open[] = 
{
    { IDS_DLGOPEN_0204_OPEN, 1, DLGOPEN_0204_OPEN },
    { 0, 0, 0 }
};

static DLGOPEN_ITEM* items[DLGOPEN_TYPE_TOTAL] = { items_add, items_open };

/////////////////////////////////////////////////////////////////////////////
// CDialogOpen dialog

CDialogOpen::CDialogOpen(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOpen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOpen)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_nOpenType   = DLGOPEN_TYPE_NEW;
    m_nOpenResult = -1;
}

void CDialogOpen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOpen)
	DDX_Control(pDX, IDC_DLGOPEN_HELP, m_hHelp);
	DDX_Control(pDX, IDOK, m_hOK);
	DDX_Control(pDX, IDC_DLGOPEN_LISTCTRL, m_hList);
	DDX_Control(pDX, IDC_DLGOPEN_TAB, m_hTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogOpen, CDialog)
	//{{AFX_MSG_MAP(CDialogOpen)
	ON_NOTIFY(TCN_SELCHANGE, IDC_DLGOPEN_TAB, OnSelchangeTab)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_DLGOPEN_LISTCTRL, OnItemchangedListctrl)
	ON_NOTIFY(NM_DBLCLK, IDC_DLGOPEN_LISTCTRL, OnDblclkListctrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOpen message handlers

BOOL CDialogOpen::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_hImageList.Create(IDB_IMAGELIST, 32, 0, RGB(0, 128, 128));
    m_hList.SetImageList(&m_hImageList, LVSIL_NORMAL);
    m_hList.InsertColumn(0, "");
    m_hList.InsertColumn(0, "");

    for (int nIndex=0; nIndex<DLGOPEN_TYPE_TOTAL; nIndex++)
    {
        CString szText;
        szText.LoadString(labels[nIndex]);

        TCITEM tcItem;
        tcItem.mask    = TCIF_PARAM|TCIF_TEXT;
        tcItem.pszText = (LPSTR)(LPCSTR)szText;
        tcItem.lParam  = nIndex;
        m_hTab.InsertItem(nIndex, &tcItem);
    }
	
    if ((m_nOpenType < 0) || (m_nOpenType >= DLGOPEN_TYPE_TOTAL))
        m_nOpenType = 0;
    m_hTab.SetCurSel(m_nOpenType);

    LRESULT lResult;
    OnSelchangeTab(NULL, &lResult);

    return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogOpen::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
    DLGOPEN_ITEM *pItems;
    TCITEM tcItem;
    tcItem.mask = TCIF_PARAM;
   
    int i;
    int nIndex = m_hTab.GetCurSel();

    if ((nIndex != -1) && m_hTab.GetItem(nIndex, &tcItem))
    {
        m_hList.DeleteAllItems();
        m_hOK.EnableWindow(FALSE);
        m_hHelp.SetWindowText("");
        m_nOpenResult = -1;

        switch (tcItem.lParam)
        {
        case DLGOPEN_TYPE_NEW:
        case DLGOPEN_TYPE_OPEN:
            pItems = items[tcItem.lParam];
            ASSERT(pItems != NULL);
            for (i=0; pItems[i].nStringID != 0; i++)
            {
                CString szText;
                if (szText.LoadString(pItems[i].nStringID))
                {
                    int nLength = szText.GetLength()+1;
                    char *pHelp = szText.GetBuffer(nLength),
                         *pText = strchr(pHelp, '\n');
                    ASSERT((pText != NULL) && (pHelp != NULL));
                    pHelp[nLength] = '\0';
                    *pText++       = '\0';

                    nIndex = m_hList.InsertItem(i, pText, pItems[i].nImageID);
                    if (nIndex != -1)
                    {
                        m_hList.SetItemText(nIndex, 1, pHelp);
                        m_hList.SetItemData(nIndex, pItems[i].nResult);
                    }

                    szText.ReleaseBuffer(0);
                }
            }
            break;

        default:
            ASSERT(0);
            break;
        }
    }

	*pResult = 0;
}

void CDialogOpen::OnItemchangedListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if (pNMListView->uChanged & LVIF_STATE)
    {
        CString szHelp("");
        int nResult = -1;
        int nEnable = FALSE;

        if (m_hList.GetSelectedCount() == 1)
        {
            int nIndex = m_hList.GetNextItem(-1, LVNI_SELECTED);
            ASSERT(nIndex != -1);
            szHelp  = m_hList.GetItemText(nIndex, 1);
            nResult = m_hList.GetItemData(nIndex);
            nEnable = TRUE;
        }

        m_nOpenResult = nResult;
        m_hOK.EnableWindow(nEnable);
        m_hHelp.SetWindowText(szHelp);
    }

	*pResult = 0;
}

void CDialogOpen::OnDblclkListctrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (m_hList.GetSelectedCount() == 1)
    {
		TRACE("DB selected\n");
        int nIndex = m_hList.GetNextItem(-1, LVNI_SELECTED);
		TRACE("nIndex=%d\n", nIndex);
        ASSERT(nIndex != -1);
        m_nOpenResult = m_hList.GetItemData(nIndex);
		TRACE("m_nOpenResult=%d\n", m_nOpenResult);
        EndDialog(IDOK);
    }
	
	*pResult = 0;
}
