// DlgPasswd.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "dlgpasswd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_PASS 250

/////////////////////////////////////////////////////////////////////////////
// CDialogPassword dialog

CDialogPassword::CDialogPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPassword)
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}

void CDialogPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPassword)
	DDX_Text(pDX, IDC_DLGPASSWD_PASSWORD, m_strPassword);
	DDV_MaxChars(pDX, m_strPassword, MAX_PASS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDialogPassword, CDialog)
	//{{AFX_MSG_MAP(CDialogPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogPassword Helper routines

void CDialogPassword::Encrypt(LPCTSTR lpsz1, CString& strOut)
{
	srand(5234);
	LPTSTR lpsz2 = strOut.GetBufferSetLength(MAX_PASS+1);
	int nLen = _tcslen(lpsz1);
    ASSERT(nLen != 0);
	if (nLen != 0)
	{
		int nSpace = MAX_PASS / nLen;
		int j = 0;
		for (int i = MAX_PASS; i>0; i--)
		{
			if (i % nSpace == 0)
				lpsz2[i] = (TCHAR) (33 + (lpsz1[j++]<<1+1) % 93);
			else
				lpsz2[i] = (TCHAR) (32 + (rand() % 94)); 
		}
		lpsz2[0] = _T('x');
	}
    strOut.ReleaseBuffer(MAX_PASS+1);
}

void CDialogPassword::SetPrompt()
{
	CString strPrompt;
    strPrompt.LoadString(m_bConfirmMode?IDS_DLGPASSWD_CONFIRM:IDS_DLGPASSWD_ENTRY);
	SetDlgItemText(IDC_DLGPASSWD_MESSAGE, strPrompt);
}

/////////////////////////////////////////////////////////////////////////////
// CDialogPassword message handlers

BOOL CDialogPassword::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText(AfxGetAppName());
	m_bConfirmMode = FALSE;
    SetPrompt();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogPassword::OnOK() 
{
	UpdateData(TRUE);

    if (m_strPassword.IsEmpty())
		return;

	CString strUserData, strFileData;
	Encrypt(m_strPassword, strUserData);
    strFileData = AfxGetSetting()->m_szPassword;

	if (strFileData == _T("password"))
	{
		if (m_bConfirmMode == TRUE)
		{
			if (m_strConfirming != m_strPassword)
			{
				m_bConfirmMode = FALSE;
				m_strPassword = m_strConfirming;
				m_strConfirming.Empty();
				SetPrompt();
				UpdateData(FALSE);
				AfxMessageBox(IDC_DLGPASSWD_MISMATCH, MB_OK);
				return;
			}

            EndDialog(IDOK);
            AfxGetSetting()->m_szPassword = strUserData;
            AfxGetSetting()->SaveToRegistry();
			return;
		}
		else if (AfxMessageBox(IDS_DLGPASSWD_CREATE, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			// No password found
			m_bConfirmMode = TRUE;
			m_strConfirming = m_strPassword;
			m_strPassword.Empty();
			SetPrompt();
			UpdateData(FALSE);
			return;
		}
	}

	if (strUserData == strFileData)
		EndDialog(IDOK);
	else
		AfxMessageBox(IDS_DLGPASSWD_ERROR, MB_OK|MB_ICONSTOP);
}

void CDialogPassword::OnCancel()
{
	if (m_bConfirmMode)
	{
		m_bConfirmMode = FALSE;
		SetPrompt();
		return;
	}
	else
		EndDialog(IDCANCEL);
}

