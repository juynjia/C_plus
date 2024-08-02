// DispatchTable.cpp : implementation file
//

#include "stdafx.h"
#include "PRS.h"
#include "DispatchTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DispatchTable

IMPLEMENT_DYNAMIC(DispatchTable, CRecordset)

DispatchTable::DispatchTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(DispatchTable)
	m_0204_num = _T("");
	m_con_type = _T("");
	m_iActive=0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString DispatchTable::GetDefaultDBName()
{
	CSetting *pSetting = AfxGetSetting();
    CString dirT;
    if(pSetting->m_nVersion==VERSION_OMC)
		dirT=pSetting->m_szOMCDir;
	else
	    dirT=pSetting->m_szCSCDir;
	return _T(dirT+"PRS_CCS.mdb");
	//return _T(dirT+"PRS_CCS.accdb");
}

CString DispatchTable::GetDefaultSQL()
{
	return _T("[0204派工登記表]");
}

void DispatchTable::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DispatchTable)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[0204號碼]"), m_0204_num);
	RFX_Text(pFX, _T("[建構狀態]"), m_con_type);
	RFX_Long(pFX, _T("[現用狀態]"), m_iActive);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DispatchTable diagnostics

#ifdef _DEBUG
void DispatchTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void DispatchTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
