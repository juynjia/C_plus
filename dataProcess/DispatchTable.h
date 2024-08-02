#if !defined(AFX_DISPATCHTABLE_H__32675EA3_1D9B_11D5_B1F0_00E018002677__INCLUDED_)
#define AFX_DISPATCHTABLE_H__32675EA3_1D9B_11D5_B1F0_00E018002677__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DispatchTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DispatchTable DAO recordset

class DispatchTable : public CRecordset
{
public:
	DispatchTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(DispatchTable)

// Field/Param Data
	//{{AFX_FIELD(DispatchTable, CDaoRecordset)
	long  m_iActive;
	CStringW	m_0204_num;
	CStringW	m_con_type;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DispatchTable)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPATCHTABLE_H__32675EA3_1D9B_11D5_B1F0_00E018002677__INCLUDED_)
