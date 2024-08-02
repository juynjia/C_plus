// DlgColor.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "DlgColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef struct 
{
    LPCSTR lpText;
    UINT CSetting::*lpColor;
} COLOR_COMBO;

static COLOR_COMBO items[] = {
    { "對話方塊", &CSetting::m_nColorDlg  },
    { "0204業務", &CSetting::m_nColor0204 }
};

/////////////////////////////////////////////////////////////////////////////
// CDialogColor dialog

CDialogColor::CDialogColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogColor)
	//}}AFX_DATA_INIT
}

void CDialogColor::DoDataExchange(CDataExchange* pDX)
{
	TRACE("CDialogColor::DoDataExchange()---->\n");
    CSetting *pSetting = AfxGetSetting();

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogColor)
	DDX_Control(pDX, IDC_DLGCOLOR_ITEM, m_hComboItem);
	//}}AFX_DATA_MAP
    ASSERT(!(m_hComboItem.GetStyle() & CBS_SORT));

	DDX_Radio(pDX, IDC_DLGCOLOR_DEFAULT, pSetting->m_nColorType);

    if (pDX->m_bSaveAndValidate)
    {
        if (pSetting->m_nColorType == COLOR_CUSTOM)
        {
            int nCount = m_hComboItem.GetCount();
            ASSERT(nCount == (sizeof(items)/sizeof(COLOR_COMBO)));
            for (int nItem=0; nItem<nCount; nItem++)
                pSetting->*(items[nItem].lpColor) = m_hComboItem.GetItemData(nItem);
        }
    }
    else
    {
        for (int nItem=0; nItem<(sizeof(items)/sizeof(COLOR_COMBO)); nItem++)
        {
            int nIndex = m_hComboItem.AddString(items[nItem].lpText);
            if (nIndex != CB_ERR)
                m_hComboItem.SetItemData(nIndex, pSetting->*(items[nItem].lpColor));
        }
        m_hComboItem.SetCurSel(0);
        OnSelchangeDlgcolorItem();
        OnDlgcolorRadio(pSetting->m_nColorType?IDC_DLGCOLOR_CUSTOM:IDC_DLGCOLOR_DEFAULT);
    }
}

HBRUSH CDialogColor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_DLGCOLOR_COLOR)
        hbr = (HBRUSH)m_hBrush;
	return hbr;
}

BEGIN_MESSAGE_MAP(CDialogColor, CDialog)
	//{{AFX_MSG_MAP(CDialogColor)
	ON_CBN_SELCHANGE(IDC_DLGCOLOR_ITEM, OnSelchangeDlgcolorItem)
	ON_BN_CLICKED(IDC_DLGCOLOR_CHOOSE, OnDlgcolorChoose)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_DLGCOLOR_DEFAULT, IDC_DLGCOLOR_CUSTOM, OnDlgcolorRadio)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogColor message handlers

void CDialogColor::OnDlgcolorRadio(UINT nID) 
{
    BOOL bEnable = (nID == IDC_DLGCOLOR_CUSTOM);
    GetDlgItem(IDC_DLGCOLOR_ITEM)->EnableWindow(bEnable);
    GetDlgItem(IDC_DLGCOLOR_CHOOSE)->EnableWindow(bEnable);
}

void CDialogColor::OnSelchangeDlgcolorItem() 
{
    m_hBrush.DeleteObject();
    m_hBrush.CreateSolidBrush(m_hComboItem.GetItemData(m_hComboItem.GetCurSel()));
    GetDlgItem(IDC_DLGCOLOR_COLOR)->InvalidateRect(NULL);
}

void CDialogColor::OnDlgcolorChoose() 
{
	CColorDialog dlg;

	if (dlg.DoModal() == IDOK)
    {
        int nIndex = m_hComboItem.GetCurSel();
        ASSERT(nIndex != CB_ERR);
        m_hComboItem.SetItemData(nIndex, dlg.GetColor());
        OnSelchangeDlgcolorItem();
    }
}

void CDialogColor::OnOK() 
{
	AfxGetSetting()->SaveToRegistry();
	CDialog::OnOK();
    AfxMessageBox(IDS_MESSAGE_RESTART);
}
