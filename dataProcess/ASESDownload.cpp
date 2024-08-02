// ASESDownload.cpp : implementation file
//

#include "stdafx.h"
#include "PRS.h"
#include "ASESDownload.h"
#include "SVC_TBLSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ASESDownload dialog


ASESDownload::ASESDownload(CWnd* pParent /*=NULL*/)
	: CDialog(ASESDownload::IDD, pParent)
{
	//{{AFX_DATA_INIT(ASESDownload)
	m_str0204num = _T("0204-");
	m_strStatus = _T("");
	m_BARID = 0;
	m_LOCKPID = 0;
	m_STATUS = 0;
	m_TX_NUM = _T("");
	m_TX_NUM10 = _T("");
	m_STATUS10 = 0;
	m_BARID10 = 0;
	m_LOCKPID10 = 0;
	m_ANNID = 0;
	m_ANNID10 = 0;
	//}}AFX_DATA_INIT
}


void ASESDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ASESDownload)
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress);
	DDX_Text(pDX, IDC_0204NUMBER, m_str0204num);
	DDV_MaxChars(pDX, m_str0204num, 10);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_BARID, m_BARID);
	DDX_Text(pDX, IDC_LOCKPID, m_LOCKPID);
	DDX_Text(pDX, IDC_STATUS, m_STATUS);
	DDX_Text(pDX, IDC_TX_NUM, m_TX_NUM);
	DDX_Text(pDX, IDC_TX_NUM10, m_TX_NUM10);
	DDX_Text(pDX, IDC_STATUS10, m_STATUS10);
	DDX_Text(pDX, IDC_BARID10, m_BARID10);
	DDX_Text(pDX, IDC_LOCKPID10, m_LOCKPID10);
	DDX_Text(pDX, IDC_ANNID, m_ANNID);
	DDX_Text(pDX, IDC_ANNID10, m_ANNID10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ASESDownload, CDialog)
	//{{AFX_MSG_MAP(ASESDownload)
	ON_BN_CLICKED(ID_BEGIN_DOWNLOAD, OnBeginDownload)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_TX_NUM10, &ASESDownload::OnEnChangeTxNum10)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ASESDownload message handlers

void ASESDownload::OnBeginDownload() 
{
	UpdateData(TRUE);

	CDatabase* ases_db;
	try
	{
		m_strStatus.Format("%s 號碼查詢中，請稍候...",m_str0204num);
		BeginWaitCursor();
		UpdateData(FALSE);
		
		ases_db = new CDatabase();
		ases_db->OpenEx(("DSN=IN4_ESMS"));//嘉:DSN=IN4_SMS_EN  東:DSN=IN4_ESMS
		SVC_TBLSet *plan = new SVC_TBLSet(ases_db);

		
		CButton	*pButton=(CButton*)GetDlgItem(ID_BEGIN_DOWNLOAD);
		pButton->EnableWindow(FALSE);
		m_strStatus = "資料下載中，請稍候...";
		UpdateData(FALSE);
		m_cProgress.SetPos(30);
		CString num="204"+m_str0204num.Right(5);

		
		if (plan->Find0204Num(num))
		{
			m_TX_NUM=plan->A;
			//m_STATUS=plan->m_STATUS;
			//m_BARID=plan->m_BARID;
			//m_LOCKPID=plan->m_LOCKPID;
			//m_ANNID=plan->m_ANNID;
			
			m_STATUS = atoi((plan->B).Left(1));
			m_BARID = atoi((plan->B).Mid(1,1));
			m_LOCKPID = atoi((plan->B).Right(1));
			m_ANNID = plan-> C;
			m_cProgress.SetPos(100);
			m_strStatus = "SMP資料下載完成！";
		}
		else
			m_strStatus = "*** SMP查無資料！***";
		
		
		
		
		
		UpdateData(FALSE);
		 /*if (plan10->Find0204Num(num))    JIA碼掉0826
		{
			m_TX_NUM10=plan10->m_TX_NUM;
			m_STATUS10=plan10->m_STATUS;
			m_BARID10=plan10->m_BARID;
			m_LOCKPID10=plan10->m_LOCKPID;
			m_ANNID10=plan10->m_ANNID;
			m_cProgress.SetPos(100);
			m_strStatus = "SCP10資料下載完成！";
		}
		else
			m_strStatus = "*** SCP10查無資料！***";
			*/
		UpdateData(FALSE);
		EndWaitCursor();
		plan->Close();
		//plan10->Close();
		ases_db->Close();
		//ases_db10.Close();
	}
	catch(CDBException *e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}	
}


void ASESDownload::OnEnChangeTxNum10()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialog::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}
