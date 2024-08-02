// DlgConfig.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "DlgConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogConfigure dialog

CDialogConfigure::CDialogConfigure(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogConfigure::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogConfigure)
	//}}AFX_DATA_INIT
}

void CDialogConfigure::DoDataExchange(CDataExchange* pDX)
{
    CSetting *pSetting = AfxGetSetting();

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogConfigure)
	DDX_Control(pDX, IDC_DLGCONFIG_DEVICE, m_hDevice);
	DDX_Control(pDX, IDC_DLGCONFIG_VERSION, m_hVersion);
	//}}AFX_DATA_MAP

    DDX_ComboBox(pDX, IDC_DLGCONFIG_VERSION, pSetting->m_nVersion);
    DDX_ComboBox(pDX, IDC_DLGCONFIG_DEVICE, pSetting->m_nDevice);
	DDX_Text(pDX, IDC_DLGCONFIG_OFFICE, pSetting->m_szOffice);
	DDX_Text(pDX, IDC_DLGCONFIG_AGENT, pSetting->m_szAgent);
	DDX_Text(pDX, IDC_DLGCONFIG_CSCDIR, pSetting->m_szCSCDir);
	DDX_Text(pDX, IDC_DLGCONFIG_OMCDIR, pSetting->m_szOMCDir);

    if (pDX->m_bSaveAndValidate)
    {
        CString *lpStrings[2];
        lpStrings[0] = &pSetting->m_szCSCDir;
        lpStrings[1] = &pSetting->m_szOMCDir;
        for (int i=0; i<2; i++)
        {
            if (!lpStrings[i]->IsEmpty() && (lpStrings[i]->GetAt(lpStrings[i]->GetLength()-1) != '\\'))
                *lpStrings[i] += '\\';
        }
    }
}

void CDialogConfigure::OnOK()
{
    CDialog::OnOK();
    AfxGetSetting()->SaveToRegistry();
}

BEGIN_MESSAGE_MAP(CDialogConfigure, CDialog)
	//{{AFX_MSG_MAP(CDialogConfigure)
	ON_CBN_SELCHANGE(IDC_DLGCONFIG_VERSION, OnSelchangeDlgconfigVersion)
	//}}AFX_MSG_MAP
    ON_CONTROL_RANGE(BN_CLICKED, IDC_DLGCONFIG_CSCBTN, IDC_DLGCONFIG_CSCBTN, OnDlgconfigbtn)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_DLGCONFIG_OMCBTN, IDC_DLGCONFIG_OMCBTN, OnDlgconfigbtn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogConfigure message handlers

BOOL CDialogConfigure::OnInitDialog() 
{
    typedef struct 
    {
        LPCSTR text;
        UINT   value;
    } SELECT_COMBO;

    static UINT controls[2] = 
    {
        IDC_DLGCONFIG_VERSION,
        IDC_DLGCONFIG_DEVICE
    };

    static SELECT_COMBO combos[2][2] = 
    { { { "OMC", VERSION_OMC }, { "CSC", VERSION_CSC } },
      { { "CLIENT", DEVICE_CLIENT }, { "SERVER", DEVICE_SERVER } }
    };

    for (int i=0; i<2; i++)
    {
        CComboBox *pCombo = (CComboBox*)GetDlgItem(controls[i]);
        ASSERT(pCombo != NULL);
        for (int j=0; j<2; j++)
        {
            int nIndex = pCombo->AddString(combos[i][j].text);
            ASSERT(nIndex != -1);
            pCombo->SetItemData(nIndex, combos[i][j].value);
        }
        pCombo->SetCurSel(0);
    }
	
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogConfigure::OnSelchangeDlgconfigVersion() 
{
    int nIndex = m_hVersion.GetCurSel();
    ASSERT(nIndex != -1);
    BOOL bOMC=FALSE, bCSC=FALSE;
    switch (m_hVersion.GetItemData(nIndex))
    {
    case VERSION_OMC:
        bOMC = TRUE;
        break;
    case VERSION_CSC:
        bCSC = TRUE;
        break;
    default:
        ASSERT(0);
        break;
    }
    GetDlgItem(IDC_DLGCONFIG_CSCDIR)->EnableWindow(bCSC);
    GetDlgItem(IDC_DLGCONFIG_OMCDIR)->EnableWindow(bOMC);
}

void CDialogConfigure::OnDlgconfigbtn(UINT nID) 
{
    CString text;
    GetDlgItemText((nID==IDC_DLGCONFIG_CSCBTN)?IDC_DLGCONFIG_CSCLABEL:IDC_DLGCONFIG_OMCLABEL, text);

    BROWSEINFO bInfo;
    memset(&bInfo, 0, sizeof(BROWSEINFO));
    bInfo.hwndOwner = m_hWnd;
    bInfo.lpszTitle = text;
    bInfo.ulFlags   = BIF_RETURNONLYFSDIRS|BIF_DONTGOBELOWDOMAIN;

    LPITEMIDLIST lpItem = ::SHBrowseForFolder(&bInfo);
    if (lpItem != NULL)
    {
        LPMALLOC lpMalloc;
        if (SHGetMalloc(&lpMalloc) == NOERROR)
        {
            // retrieve path
            LPSHELLFOLDER lpShell;
            if (SHGetDesktopFolder(&lpShell) == NOERROR)
            {
                STRRET ret;
                if (lpShell->GetDisplayNameOf(lpItem, SHGDN_NORMAL|SHGDN_FORPARSING, &ret) == NOERROR)
                {
                    ASSERT(ret.uType == STRRET_WSTR);
                    if (ret.uType == STRRET_WSTR)
                    {
                        text = ret.pOleStr;
                        if (text.GetAt(text.GetLength()-1) != '\\')
                            text += '\\';
                        SetDlgItemText((nID==IDC_DLGCONFIG_CSCBTN)?IDC_DLGCONFIG_CSCDIR:IDC_DLGCONFIG_OMCDIR, text);
                        lpMalloc->Free(ret.pOleStr);
                    }
                }
                lpShell->Release();
            }

            // free folder
            lpMalloc->Free(lpItem);
        }
    }
}
