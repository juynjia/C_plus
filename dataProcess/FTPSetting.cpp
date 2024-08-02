// FTPSetting.cpp : implementation file
//

#include "stdafx.h"
#include "prs.h"
#include "FTPSetting.h"

#include "0204Doc.h"
#include "0204View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FTPSetting dialog


FTPSetting::FTPSetting(CWnd* pParent /*=NULL*/)
	: CDialog(FTPSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(FTPSetting)
	m_exportname = _T("");
	m_ip = _T("");
	m_username = _T("");
	m_userpassword = _T("");
	m_port = _T("21");
	m_check_ftp = FALSE;
	//}}AFX_DATA_INIT
}


void FTPSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FTPSetting)
	DDX_Text(pDX, IDC_EDIT_EXPORTNAME, m_exportname);
	DDX_Text(pDX, IDC_EDIT_IP, m_ip);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_username);
	DDX_Text(pDX, IDC_EDIT_USERPASSWORD, m_userpassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_Check(pDX, IDC_CHECK_FTP, m_check_ftp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FTPSetting, CDialog)
	//{{AFX_MSG_MAP(FTPSetting)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FTPSetting message handlers

void FTPSetting::OnOK() 
{
	UpdateData(TRUE);
	AfxGetSetting()->m_fIP=m_ip;
	AfxGetSetting()->m_fPort=m_port;
	AfxGetSetting()->m_fUser=m_username;
	AfxGetSetting()->m_fPassword=m_userpassword;
	AfxGetSetting()->m_fExport=m_exportname;
	AfxGetSetting()->m_nFTPVer=m_check_ftp;
	AfxGetSetting()->SaveToRegistry();
	
	//CDialog::OnOK();
}



BOOL FTPSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	AfxGetSetting()->LoadFromRegistry();
	m_ip=AfxGetSetting()->m_fIP;
	m_port=AfxGetSetting()->m_fPort;
	m_username=AfxGetSetting()->m_fUser;
	m_userpassword=AfxGetSetting()->m_fPassword;
	m_exportname=AfxGetSetting()->m_fExport;
	m_check_ftp=AfxGetSetting()->m_nFTPVer;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void FTPSetting::OnButtonConnect() 
{
	CMDIFrameWnd *pFrame = 
            (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	CMDIChildWnd *pChild = 
				 (CMDIChildWnd *) pFrame->GetActiveFrame();
	C0204View *pView = (C0204View *) pChild->GetActiveView();
	UpdateData(TRUE);
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	int re;
	re=pView->m_ftp.GetPort();
	pView->m_ftp.SetPort(atoi(m_port));
    pView->m_ftp.SetPassive (FALSE);
    re=pView->m_ftp.Connect (m_ip, m_username, m_userpassword, 
                "");
	   if (re == 1)
        {
            CString Message = "Connect to FTP Server successfully";
			AfxMessageBox(Message);
        }
        else
        {
            CString Message = "Unable to Connect FTP Server";
			AfxMessageBox(Message);
        }
	pView->m_ftp.Disconnect();
}
