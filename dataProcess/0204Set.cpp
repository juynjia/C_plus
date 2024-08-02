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
	m_szStatus = _T("���z��");
	m_iActive = 1;  //�{�Ϊ��A,�w�]��1:�ϥΤ�
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
// �p RFX_Text() �M RFX_Int() �������O�M
// �����ܼƪ������̡ۨA�ӫD��Ʈw����쪺�����C
// ODBC �N�|���զ۰ʱN��Ʀ���ഫ���n�D������
	RFX_Text(pFX, _T("[0204���X]"), m_szNumber);
	RFX_Text(pFX, _T("[�غc���A]"), m_szStatus);
	RFX_Long(pFX, _T("[�{�Ϊ��A]"), m_iActive);
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
    m_strSort      = _T("[����]"); 
}


CString C0204ApplySet::GetDefaultDBName()
{
	return DATABASE_NAME;
}

//#error �w���ʰ��D: �s���r��i��]�t�K�X
// �U�C���s���r��i��]�t�¤�r�K�X�M (��) ��L���K����T�C�w�����w����
// ���D�˵��s���r���A�бN #error �����C�z�ݭn�H��L�Φ��x�s�K�X
// �ΨϥΤ��P���ϥΪ����ҡC
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
	// �p RFX_Text() �M RFX_Int() �������O�M
	// �����ܼƪ������̡ۨA�ӫD��Ʈw����쪺�����C
	// ODBC �N�|���զ۰ʱN��Ʀ���ഫ���n�D������
	RFX_Text(pFX, _T("[�p��s��]"), m_szApplyNumber);
	RFX_Text(pFX, _T("[�`�ظ��X]"), m_szNumber);
	RFX_Text(pFX, _T("[���ʨƶ�]"), m_szApplyContent);
	RFX_Date(pFX, _T("[�w�w�ͮĤ��]"), m_dateExpect);
	RFX_Text(pFX, _T("[�`�ئW��]"), m_szName);
	RFX_Text(pFX, _T("[�`�����O]"), m_szSort);
	RFX_Long(pFX, _T("[��O����]"), m_nChargeType);
	RFX_Long(pFX, _T("[��O]"), m_nCharge);
	RFX_Text(pFX, _T("[��T���Ѫ�]"), m_szInfoProvider);
	RFX_Text(pFX, _T("[��T���Ѫ̳s���q��]"), m_szInfoPhone);
	RFX_Text(pFX, _T("[�g����Ҹ�]"), m_szLicense);
	RFX_Text(pFX, _T("[��X�`��]"), m_szLock);
	RFX_Text(pFX, _T("[�W���A��]"), m_szOverride);
	RFX_Text(pFX, _T("[�s�`�ظ��X]"), m_szNewNumber);
	RFX_Text(pFX, _T("[�e��]"), m_szPrelude);
	RFX_Long(pFX, _T("[0204�~�Ⱥ���]"), m_nType);
	RFX_Long(pFX, _T("[����]"), m_nCount);
	RFX_Date(pFX, _T("[���u���]"), m_dateOMCDisp);
	RFX_Date(pFX, _T("[�������]"), m_dateFinish);
	RFX_Date(pFX, _T("[OMC���z���]"), m_dateOMCTake);
	RFX_Text(pFX, _T("[OMC�غc�H]"), m_szOMCConstructor);
	RFX_Long(pFX, _T("[OMC�غc�H���u�N��]"), m_nOMCConstructorID);
	RFX_Text(pFX, _T("[OMC�f�֤H]"), m_szOMCChecker);
	RFX_Date(pFX, _T("[SMS�W�u���]"), m_dateOMCSMS);
	RFX_Date(pFX, _T("[�^�����]"), m_dateReply);
	RFX_Date(pFX, _T("[�^���ɶ�]"), m_timeReply);
	RFX_Date(pFX, _T("[BS�Ұʤ��]"), m_dateOMCBS);
	RFX_Text(pFX, _T("[�Ƶ�]"), m_szNote);
	RFX_Text(pFX, _T("[���鸹�X]"), m_szDestination);
	RFX_Text(pFX, _T("[CallBar����]"), m_szCallbar);
	RFX_Date(pFX, _T("[�ӽФ��]"), m_dateApply);
	RFX_Text(pFX, _T("[���z���]"), m_szPlace);
	RFX_Text(pFX, _T("[�O�_�ݭnSMS����]"), m_szReply);
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

