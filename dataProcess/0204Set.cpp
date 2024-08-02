// 0204Set.cpp : implementation file
//

#include "StdAfx.h"
#include "PRS.h"
#include "0204Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C0204RecordSet

IMPLEMENT_DYNAMIC(C0204RecordSet, CRecordset)

C0204RecordSet::C0204RecordSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(C0204RecordSet)
	//}}AFX_FIELD_INIT
	mode = dbEditNone;
	m_szNumber = _T("");
	m_szStatus = _T("受理中");
	m_iActive = 1;  //現用狀態,預設為1:使用中
	m_nFields = 3;
	m_nDefaultType = snapshot;
	//m_nDefaultType = dbOpenDynaset;
}


CString C0204RecordSet::GetDefaultDBName()
{
	return DATABASE_NAME;
}

CString C0204RecordSet::GetDefaultConnect()
{
	return _T("DSN=rpcs_prs_ccs;SERVER=127.0.0.1;UID=rpcs;PWD=rpcs;DATABASE=prs_ccs;PORT=3306");
}

CString C0204RecordSet::GetDefaultSQL()
{
    CString sql; sql.Format("[%s]", TABLE_0204_DISPATCH); return sql;
}

void C0204RecordSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// 如 RFX_Text() 和 RFX_Int() 等巨集是和
// 成員變數的類型相依，而非資料庫中欄位的類型。
// ODBC 將會嘗試自動將資料行值轉換成要求的類型
	RFX_Text(pFX, _T("[0204號碼]"), m_szNumber);
	RFX_Text(pFX, _T("[建構狀態]"), m_szStatus);
	RFX_Long(pFX, _T("[現用狀態]"), m_iActive);
}

void C0204RecordSet::AddNew()
{
	mode = dbEditAdd;
	CRecordset::AddNew();
}

BOOL C0204RecordSet::Update()
{
	mode = dbEditNone;
	return CRecordset::Update();
}

void C0204RecordSet::Edit()
{
	mode = dbEditInProgress;
	return CRecordset::Edit();
}

int C0204RecordSet::GetEditMode()
{
	return mode;
}

/////////////////////////////////////////////////////////////////////////////
// C0204RecordSet diagnostics

#ifdef _DEBUG
void C0204RecordSet::AssertValid() const
{
	CRecordset::AssertValid();

}

void C0204RecordSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C0204ApplySet

IMPLEMENT_DYNAMIC(C0204ApplySet, CRecordset)

C0204ApplySet::C0204ApplySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(C0204ApplySet)
	//}}AFX_FIELD_INIT
	mode = dbEditNone;
	m_szApplyNumber = L"";
	m_szNumber = L"";
	m_szApplyContent = _T("20");
	m_dateExpect;
	m_szName = L"";
	m_szSort = _T("1");
	m_nChargeType = 1;
	m_nCharge = 20;
	m_szInfoProvider = L"";
	m_szInfoPhone = L"";
	m_szLicense = L"";
	m_szLock = _T("0");
	m_szOverride = _T("0");
	m_szNewNumber = L"";
	m_szPrelude = L"";
	m_nType = 1;
	m_nCount = 0;
	m_dateOMCDisp;
	m_dateFinish;
	m_dateOMCTake;
	m_szOMCConstructor = L"";
	m_nOMCConstructorID = 0;
	m_szOMCChecker = L"";
	m_dateOMCSMS;
	m_dateReply;
	m_timeReply;
	m_dateOMCBS;
	m_szNote = L"";
	m_szDestination = L"";
	m_szCallbar = _T("0");
	m_dateApply;
	m_szPlace = _T("92");
	m_szReply = _T("0");
	m_nFields = 33;
	m_nDefaultType = snapshot;
    m_strSort      = _T("[次數]"); 
}


CString C0204ApplySet::GetDefaultDBName()
{
	return DATABASE_NAME;
}

//#error 安全性問題: 連接字串可能包含密碼
// 下列的連接字串可能包含純文字密碼和 (或) 其他機密的資訊。針對任何安全性
// 問題檢視連接字串後，請將 #error 移除。您需要以其他形式儲存密碼
// 或使用不同的使用者驗證。
CString C0204ApplySet::GetDefaultConnect()
{
	return _T("DSN=rpcs_prs_ccs");
}

CString C0204ApplySet::GetDefaultSQL()
{
    CString sql; sql.Format("[%s]", TABLE_0204_APPLY); return sql;
}

void C0204ApplySet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// 如 RFX_Text() 和 RFX_Int() 等巨集是和
	// 成員變數的類型相依，而非資料庫中欄位的類型。
	// ODBC 將會嘗試自動將資料行值轉換成要求的類型
	RFX_Text(pFX, _T("[聯單編號]"), m_szApplyNumber);
	RFX_Text(pFX, _T("[節目號碼]"), m_szNumber);
	RFX_Text(pFX, _T("[異動事項]"), m_szApplyContent);
	RFX_Date(pFX, _T("[預定生效日期]"), m_dateExpect);
	RFX_Text(pFX, _T("[節目名稱]"), m_szName);
	RFX_Text(pFX, _T("[節目類別]"), m_szSort);
	RFX_Long(pFX, _T("[資費種類]"), m_nChargeType);
	RFX_Long(pFX, _T("[資費]"), m_nCharge);
	RFX_Text(pFX, _T("[資訊提供者]"), m_szInfoProvider);
	RFX_Text(pFX, _T("[資訊提供者連絡電話]"), m_szInfoPhone);
	RFX_Text(pFX, _T("[經營者證號]"), m_szLicense);
	RFX_Text(pFX, _T("[鎖碼節目]"), m_szLock);
	RFX_Text(pFX, _T("[超載服務]"), m_szOverride);
	RFX_Text(pFX, _T("[新節目號碼]"), m_szNewNumber);
	RFX_Text(pFX, _T("[前言]"), m_szPrelude);
	RFX_Long(pFX, _T("[0204業務種類]"), m_nType);
	RFX_Long(pFX, _T("[次數]"), m_nCount);
	RFX_Date(pFX, _T("[派工日期]"), m_dateOMCDisp);
	RFX_Date(pFX, _T("[完成日期]"), m_dateFinish);
	RFX_Date(pFX, _T("[OMC受理日期]"), m_dateOMCTake);
	RFX_Text(pFX, _T("[OMC建構人]"), m_szOMCConstructor);
	RFX_Long(pFX, _T("[OMC建構人員工代號]"), m_nOMCConstructorID);
	RFX_Text(pFX, _T("[OMC審核人]"), m_szOMCChecker);
	RFX_Date(pFX, _T("[SMS上線日期]"), m_dateOMCSMS);
	RFX_Date(pFX, _T("[回竣日期]"), m_dateReply);
	RFX_Date(pFX, _T("[回竣時間]"), m_timeReply);
	RFX_Date(pFX, _T("[BS啟動日期]"), m_dateOMCBS);
	RFX_Text(pFX, _T("[備註]"), m_szNote);
	RFX_Text(pFX, _T("[實體號碼]"), m_szDestination);
	RFX_Text(pFX, _T("[CallBar種類]"), m_szCallbar);
	RFX_Date(pFX, _T("[申請日期]"), m_dateApply);
	RFX_Text(pFX, _T("[受理單位]"), m_szPlace);
	RFX_Text(pFX, _T("[是否需要SMS報竣]"), m_szReply);
}

void C0204ApplySet::AddNew()
{
	mode = dbEditAdd;
	CRecordset::AddNew();
}

BOOL C0204ApplySet::Update()
{
	mode = dbEditNone;
	return CRecordset::Update();
}

void C0204ApplySet::Edit()
{
	mode = dbEditInProgress;
	return CRecordset::Edit();
}

int C0204ApplySet::GetEditMode()
{
	return mode;
}

/////////////////////////////////////////////////////////////////////////////
// C0204ApplySet diagnostics

#ifdef _DEBUG
void C0204ApplySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void C0204ApplySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

