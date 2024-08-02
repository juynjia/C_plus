// ASESUpload.cpp : implementation file
//

#include "stdafx.h"
#include "PRS.h"
#include "ASESUpload.h"
#include "SVC_TBLSet.h"

#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ASESUpload dialog


ASESUpload::ASESUpload(CWnd* pParent /*=NULL*/)
	: CDialog(ASESUpload::IDD, pParent)
{
	//{{AFX_DATA_INIT(ASESUpload)
	m_str0204num = _T("0204-"); 
	m_new0204num = _T("0204-"); 
	m_strStatus = _T("");
	m_BARID = 0;
	m_LOCKPID = 0;
	m_STATUS = 0;
	m_TX_NUM = _T("");
	m_check_delete = FALSE;
	m_p0204RecordSet = NULL;
	m_p0204ApplySet  = NULL;
	m_bDeleteFlag = FALSE;
	m_bChangeFlag = FALSE;
	m_iActive=1;  //現用狀態,預設為1:使用中
	m_ANNID = 0;
	//}}AFX_DATA_INIT
}

void ASESUpload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ASESUpload)
	DDX_Control(pDX, IDC_PROGRESS1, m_cProgress);
	DDX_Text(pDX, IDC_0204NUMBER, m_str0204num);
	DDV_MaxChars(pDX, m_str0204num, 10);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_strStatus);
	DDX_Text(pDX, IDC_BARID, m_BARID);
	DDX_Text(pDX, IDC_LOCKPID, m_LOCKPID);
	DDX_Text(pDX, IDC_STATUS, m_STATUS);
	DDX_Text(pDX, IDC_TX_NUM, m_TX_NUM);
	//DDX_Check(pDX, IDC_CHECK_DELETE, m_check_delete);
	DDX_Text(pDX, IDC_ANNID, m_ANNID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ASESUpload, CDialog)
	//{{AFX_MSG_MAP(ASESUpload)
	ON_BN_CLICKED(ID_BEGIN_UPLOAD, OnBeginUpload)
	ON_BN_CLICKED(IDC_GET_MDBDATA, OnGetMdbdata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ASESUpload message handlers
void ASESUpload::OnBeginUpload() //上載至Oracle
{
	UpdateData(TRUE);

	if (m_str0204num.GetLength() != 10)
	{
		m_strStatus = "0204號碼不完整，請重新輸入！";
		UpdateData(FALSE);
		return;
	}
	if (m_p0204RecordSet->m_szStatus != "處理中")
	{
		m_strStatus = "plan建構狀態為\"處理中\"，才能上載！";
		UpdateData(FALSE);
		return;
	}

	/*
    //shyrong add,2001/05/07
	int c_d(0);
	if(m_check_delete)
	{
      m_bDeleteFlag=TRUE;
	  c_d=1;
	  if(AfxMessageBox("你確定要將 PLAN 暫時從SCP刪除 嗎?",MB_YESNO)== IDNO)
		  return;
	}
	*/

	CDatabase* ases_db;
	try
	{
		ases_db = new CDatabase();
		ases_db->OpenEx(("DSN=IN4_ESMS"));
		SVC_TBLSet *plan = new SVC_TBLSet(ases_db);
		m_strStatus.Format("%s 號碼查詢中，請稍候...",m_str0204num);
		UpdateData(FALSE);
		
		CButton	*pButton=(CButton*)GetDlgItem(ID_BEGIN_UPLOAD);
		pButton->EnableWindow(FALSE);
		m_strStatus = "資料上載至SMP，請稍候...";
		UpdateData(FALSE);
		BeginWaitCursor();
		m_cProgress.SetPos(30);
		CString num="204"+m_str0204num.Right(5);
/*		if (m_bChangeFlag)
		{
			CString new_0204num="204"+m_new0204num.Right(5);
			CString new_TXnum=m_TX_NUM.Left(6)+m_new0204num.Right(5);
			ok=plan->SavePlan(new_0204num,new_TXnum,m_STATUS,m_BARID,m_LOCKPID);
			ok=plan->DeletePlan(num);
		}
		else */
		/*if (m_bDeleteFlag)
		{
			ok=plan->DeletePlan(num);
			m_strStatus = "資料上載至SCP10，請稍候...";
			m_cProgress.SetPos(70);
			UpdateData(FALSE);
			
		}
		else
		{*/
		CString field_3;
		field_3.Format("%d%d%d", m_STATUS, m_BARID, m_LOCKPID);

		CString field_4;
		field_4.Format("%d", m_ANNID);

		try
		{
			if (plan->Find0204Num(num))
			{   
				if (m_bDeleteFlag == TRUE)
				{
					ases_db->ExecuteSQL(_T(_T("DELETE FROM SMS_SH.SH_AFP_TABLE_1 WHERE FIELD_1='" + num + "'")));
					m_strStatus = "資料刪除中，請稍候...";
					m_cProgress.SetPos(70);
					UpdateData(FALSE);
				}
				else
				{
					ases_db->ExecuteSQL(_T(_T("UPDATE SMS_SH.SH_AFP_TABLE_1 SET FIELD_2='" + m_TX_NUM + "',FIELD_3='" + field_3 + "',FIELD_4='" + field_4 + "' WHERE FIELD_1='" + num + "'")));
					m_strStatus = "資料更新至SMP，請稍候...";
					m_cProgress.SetPos(70);
					UpdateData(FALSE);
				}
			}
			else
			{
				ases_db->ExecuteSQL(_T(_T("INSERT INTO SMS_SH.SH_AFP_TABLE_1 (FIELD_1,FIELD_2,FIELD_3,FIELD_4) VALUES ('" + num + "','" + m_TX_NUM + "','" + field_3 + "','" + field_4 + "')")));
				m_strStatus = "資料上載至SMP，請稍候...";
				m_cProgress.SetPos(70);
				UpdateData(FALSE);
			}
			
			
			m_cProgress.SetPos(100);
			m_strStatus = "資料上載完成！";
		
		}
		catch (CDBException *e) {
			m_strStatus = "資料上載失敗！請稍後重新上載。";
		}

		

		UpdateData(FALSE);
		EndWaitCursor();
		plan->Close();
		ases_db->Close();
	}
	catch(CDBException *e)
	{
		AfxMessageBox(e->m_strError);
		e->Delete();
	}
}



/*void ASESUpload::OnBeginUpload()
{
	/*
	CDatabase* pMySQLDB;
	pMySQLDB = new CDatabase();
	pMySQLDB->OpenEx("DSN=rpcs_prs_ccs;SERVER=127.0.0.1;UID=rpcs;PWD=rpcs;DATABASE=prs_ccs;PORT=3306");
	C0204ApplySet* p;
	p = new C0204ApplySet(pMySQLDB);

	p->m_strFilter = "節目號碼='" + m_str0204num + "'";
	p->Open();

	if (!p->IsEOF())
	{
		m_TX_NUM = p->m_szDestination;

		if (CStrW2CStrT(p->m_szApplyContent).Find("31") >= 0 || CStrW2CStrT(p->m_szApplyContent).Find("33") >= 0 || CStrW2CStrT(p->m_szApplyContent).Find("34") >= 0 || CStrW2CStrT(p->m_szApplyContent).Find("35") >= 0 || CStrW2CStrT(p->m_szApplyContent).Find("36") >= 0)
			m_STATUS = 0;
		else
			m_STATUS = 1;

		m_LOCKPID = atoi(CStrW2CStrT(p->m_szLock));
		m_BARID = atoi(CStrW2CStrT(p->m_szCallbar));


		CString temp;
		if (p->m_nChargeType == 1)
		{
			if (p->m_nCharge <= 9)
				temp.Format("200%d", p->m_nCharge);
			else if (p->m_nCharge <= 99)
				temp.Format("20%d", p->m_nCharge);
			else
				temp.Format("2%d", p->m_nCharge);
		}
		else
		{
			if (p->m_nCharge == 10)
				temp.Format("2100");
			else
				temp.Format("2200");
		}

		m_ANNID = atoi(temp);
	}
	else
		return;// 沒找到就??
	

	CDatabase* m_oracleDB;
	m_oracleDB = new CDatabase();
	m_oracleDB->OpenEx(("DSN=IN4_ESMS"));
	SVC_TBLSet *plan = new SVC_TBLSet(m_oracleDB);
	m_strStatus.Format("%s 號碼查詢中，請稍候...", m_str0204num);
	UpdateData(FALSE);

	CButton	*pButton = (CButton*)GetDlgItem(ID_BEGIN_UPLOAD);
	pButton->EnableWindow(FALSE);
	m_strStatus = "資料上載至SCP9，請稍候...";
	UpdateData(FALSE);
	BeginWaitCursor();
	m_cProgress.SetPos(30);
	BOOL ok;
	CString num = "204" + m_str0204num.Right(5);

	if (plan->Find0204Num(num))
	{   
		plan->Edit();
		plan->A = m_TX_NUM;

		CString cs;
		cs.Format("%d%d%d", m_STATUS, m_BARID, m_LOCKPID);
		plan->B = cs;
		plan->C = m_ANNID;
	}
	else
	{
		plan->AddNew();//新增一行
		
		plan->m_CD_NUM = num;
		plan->A = m_TX_NUM;

		CString cs;
		cs.Format("%d%d%d", m_STATUS, m_BARID, m_LOCKPID);
		plan->B = cs;
		plan->C = m_ANNID;
	}



}*/


BOOL ASESUpload::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_str0204num=m_p0204RecordSet->m_szNumber;
	m_cProgress.SetRange( 0, 100 );
	m_cProgress.SetPos( 0 );
	m_strStatus = "請按\"擷取資料\"鍵，以轉換資料提供上載";
	UpdateData(FALSE);
	OnGetMdbdata();
	return TRUE;
}

void ASESUpload::OnGetMdbdata() //從MySQL撈資料 顯現在UI上
{	
	UpdateData(TRUE);
	if (m_str0204num.GetLength()!=10)
	{
		m_strStatus = "0204號碼不完整，請重新輸入！";
		UpdateData(FALSE);
		return;
	}
	if (m_p0204RecordSet->m_szStatus!="處理中")
	{
		m_strStatus = "plan建構狀態為\"處理中\"，才能上載！";
		UpdateData(FALSE);
		return;
	}
	
	m_TX_NUM = m_p0204ApplySet->m_szDestination;//實體號碼
	m_LOCKPID = atoi(CStrW2CStrT(m_p0204ApplySet->m_szLock));//鎖碼
	m_BARID = atoi(CStrW2CStrT(m_p0204ApplySet->m_szCallbar));//CallBar

	CString temp;
	if (m_p0204ApplySet->m_nChargeType == 1)
	{
		if (m_p0204ApplySet->m_nCharge <= 9)
			temp.Format("200%d", m_p0204ApplySet->m_nCharge);
		else if (m_p0204ApplySet->m_nCharge <= 99)
			temp.Format("20%d", m_p0204ApplySet->m_nCharge);
		else
			temp.Format("2%d", m_p0204ApplySet->m_nCharge);
	}
	else
	{
		if (m_p0204ApplySet->m_nCharge == 10)
			temp.Format("2100");
		else
			temp.Format("2200");
	}
	m_ANNID = atoi(temp);//ANNID

	m_STATUS = 1; //default value,啟動  狀態
	m_bDeleteFlag = FALSE;
	CString str;
	str = CStrW2CStrT(m_p0204ApplySet->m_szApplyContent);//從異動事項判別狀態 

//	if (var==2) //異動
	//{
/*		if (str.Find("23")!=-1) //更節目號碼
		{
			m_bChangeFlag = TRUE;
			m_new0204num = m_p0204ApplySet->m_szNewNumber;
		}*/
	if (str.Find("23") != -1 || str.Find("21") != -1 || str.Find("32") != -1 || str.Find("51") != -1) //更節目號碼,退租,拆機,違規終租
	{ 
		m_bDeleteFlag = TRUE;
		m_STATUS = 0; //停用
	}
	if (str.Find("27") != -1 || str.Find("31") != -1 || str.Find("32") != -1 || str.Find("33") != -1 || str.Find("34") != -1 || str.Find("35") != -1 || str.Find("36") != -1 || str.Find("52") != -1) //停話
		m_STATUS = 0; //停用
		
	if (str.Find("21") != -1 || str.Find("23") != -1 || str.Find("32") != -1 || str.Find("51") != -1 || str.Find("52") != -1) //停用
		m_iActive = 0; //停用中
	//}
	
	CButton	*pButton=(CButton*)GetDlgItem(ID_BEGIN_UPLOAD);
	pButton->EnableWindow(TRUE);
	m_strStatus = "請按\"開始上載\"鍵，以進行資料上載至SMP";
	UpdateData(FALSE);
}

/*CString ASESUpload::strVARIANT(const COleVariant& var)
{
	CString strRet;
	//strRet = _T("Fish");
	switch(var.vt){
		case VT_EMPTY:
		case VT_NULL:
			strRet = _T("NULL");
			break;
		case VT_I2:
			strRet.Format(_T("%hd"),V_I2(&var));
			break;
		case VT_I4:
			strRet.Format(_T("%d"),V_I4(&var));
			break;
		case VT_R4:
			strRet.Format(_T("%e"),(double)V_R4(&var));
			break;
		case VT_R8:
			strRet.Format(_T("%e"),V_R8(&var));
			break;
		case VT_CY:
			strRet = COleCurrency(var).Format();
			break;
		case VT_DATE:
			strRet = COleDateTime(var).Format(_T("%m %d %Y"));
			break;
		case VT_BSTR:
			strRet = V_BSTRT(&var);
			break;
		case VT_DISPATCH:
			strRet = _T("VT_DISPATCH");
			break;
		case VT_ERROR:
			strRet = _T("VT_ERROR");
			break;
		case VT_BOOL:
			return strBOOL(V_BOOL(&var));
		case VT_VARIANT:
			strRet = _T("VT_VARIANT");
			break;
		case VT_UNKNOWN:
			strRet = _T("VT_UNKNOWN");
			break;
		case VT_I1:
			strRet = _T("VT_I1");
			break;
		case VT_UI1:
			strRet.Format(_T("0x%02hX"),(unsigned short)V_UI1(&var));
			break;
		case VT_UI2:
			strRet = _T("VT_UI2");
			break;
		case VT_UI4:
			strRet = _T("VT_UI4");
			break;
		case VT_I8:
			strRet = _T("VT_I8");
			break;
		case VT_UI8:
			strRet = _T("VT_UI8");
			break;
		case VT_INT:
			strRet = _T("VT_INT");
			break;
		case VT_UINT:
			strRet = _T("VT_UINT");
			break;
		case VT_VOID:
			strRet = _T("VT_VOID");
			break;
		case VT_HRESULT:
			strRet = _T("VT_HRESULT");
			break;
		case VT_PTR:
			strRet = _T("VT_PTR");
			break;
		case VT_SAFEARRAY:
			strRet = _T("VT_SAFEARRAY");
			break;
		case VT_CARRAY:
			strRet = _T("VT_CARRAY");
			break;
		case VT_USERDEFINED:
			strRet = _T("VT_USERDEFINED");
			break;
		case VT_LPSTR:
			strRet = _T("VT_LPSTR");
			break;
		case VT_LPWSTR:
			strRet = _T("VT_LPWSTR");
			break;
		case VT_FILETIME:
			strRet = _T("VT_FILETIME");
			break;
		case VT_BLOB:
			strRet = _T("VT_BLOB");
			break;
		case VT_STREAM:
			strRet = _T("VT_STREAM");
			break;
		case VT_STORAGE:
			strRet = _T("VT_STORAGE");
			break;
		case VT_STREAMED_OBJECT:
			strRet = _T("VT_STREAMED_OBJECT");
			break;
		case VT_STORED_OBJECT:
			strRet = _T("VT_STORED_OBJECT");
			break;
		case VT_BLOB_OBJECT:
			strRet = _T("VT_BLOB_OBJECT");
			break;
		case VT_CF:
			strRet = _T("VT_CF");
			break;
		case VT_CLSID:
			strRet = _T("VT_CLSID");
			break;
	}
	WORD vt = var.vt;
	if(vt & VT_ARRAY){
		vt = vt & ~VT_ARRAY;
		strRet = _T("Array of ");
	}
	if(vt & VT_BYREF){
		vt = vt & ~VT_BYREF;
		strRet += _T("Pointer to ");
	}
	if(vt != var.vt){
		switch(vt){
			case VT_EMPTY:
				strRet += _T("VT_EMPTY");
				break;
			case VT_NULL:
				strRet += _T("VT_NULL");
				break;
			case VT_I2:
				strRet += _T("VT_I2");
				break;
			case VT_I4:
				strRet += _T("VT_I4");
				break;
			case VT_R4:
				strRet += _T("VT_R4");
				break;
			case VT_R8:
				strRet += _T("VT_R8");
				break;
			case VT_CY:
				strRet += _T("VT_CY");
				break;
			case VT_DATE:
				strRet += _T("VT_DATE");
				break;
			case VT_BSTR:
				strRet += _T("VT_BSTR");
				break;
			case VT_DISPATCH:
				strRet += _T("VT_DISPATCH");
				break;
			case VT_ERROR:
				strRet += _T("VT_ERROR");
				break;
			case VT_BOOL:
				strRet += _T("VT_BOOL");
				break;
			case VT_VARIANT:
				strRet += _T("VT_VARIANT");
				break;
			case VT_UNKNOWN:
				strRet += _T("VT_UNKNOWN");
				break;
			case VT_I1:
				strRet += _T("VT_I1");
				break;
			case VT_UI1:
				strRet += _T("VT_UI1");
				break;
			case VT_UI2:
				strRet += _T("VT_UI2");
				break;
			case VT_UI4:
				strRet += _T("VT_UI4");
				break;
			case VT_I8:
				strRet += _T("VT_I8");
				break;
			case VT_UI8:
				strRet += _T("VT_UI8");
				break;
			case VT_INT:
				strRet += _T("VT_INT");
				break;
			case VT_UINT:
				strRet += _T("VT_UINT");
				break;
			case VT_VOID:
				strRet += _T("VT_VOID");
				break;
			case VT_HRESULT:
				strRet += _T("VT_HRESULT");
				break;
			case VT_PTR:
				strRet += _T("VT_PTR");
				break;
			case VT_SAFEARRAY:
				strRet += _T("VT_SAFEARRAY");
				break;
			case VT_CARRAY:
				strRet += _T("VT_CARRAY");
				break;
			case VT_USERDEFINED:
				strRet += _T("VT_USERDEFINED");
				break;
			case VT_LPSTR:
				strRet += _T("VT_LPSTR");
				break;
			case VT_LPWSTR:
				strRet += _T("VT_LPWSTR");
				break;
			case VT_FILETIME:
				strRet += _T("VT_FILETIME");
				break;
			case VT_BLOB:
				strRet += _T("VT_BLOB");
				break;
			case VT_STREAM:
				strRet += _T("VT_STREAM");
				break;
			case VT_STORAGE:
				strRet += _T("VT_STORAGE");
				break;
			case VT_STREAMED_OBJECT:
				strRet += _T("VT_STREAMED_OBJECT");
				break;
			case VT_STORED_OBJECT:
				strRet += _T("VT_STORED_OBJECT");
				break;
			case VT_BLOB_OBJECT:
				strRet += _T("VT_BLOB_OBJECT");
				break;
			case VT_CF:
				strRet += _T("VT_CF");
				break;
			case VT_CLSID:
				strRet += _T("VT_CLSID");
				break;
		}
	}
	return strRet;
}*/ //JIA


void ASESUpload::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}
