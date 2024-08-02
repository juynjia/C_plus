// 0204Set.h : header file
//

#if !defined(AFX_0204SET_H__13F551B5_0B82_11D5_A466_00485455D12D__INCLUDED_)
#define AFX_0204SET_H__13F551B5_0B82_11D5_A466_00485455D12D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// C0204RecordSet DAO recordset

class C0204RecordSet : public CRecordset
{

public:
	C0204RecordSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(C0204RecordSet)

// Field/Param Data
	//{{AFX_FIELD(C0204RecordSet, CDaoRecordset)
	CStringW	m_szNumber;
	CStringW	m_szStatus;
	long m_iActive;
	int mode;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C0204RecordSet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultConnect();	// �w�]�s���r��
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	virtual void AddNew();
	virtual BOOL Update();
	virtual void Edit();
	typedef enum EditModeEnum
	{
		dbEditNone = 0,
		dbEditInProgress = 1,
		dbEditAdd = 2,
		dbEditChanged = 4,
		dbEditDeleted = 8,
		dbEditNew = 16
	}	EditModeEnum;

	virtual int GetEditMode();

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// C0204ApplySet DAO recordset

class C0204ApplySet : public CRecordset
{

public:
	C0204ApplySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(C0204ApplySet)

	// ���/�ѼƸ��

	// �U�C���r������ (�p�G��) �ϬM ANSI ��������� CStringA �M Unicode ���
	// ������ CStringW ��Ʈw��쪺����������C�o�O���F�w�� ODBC �X��
	// �{������D���n���ഫ�C�z�]�i�H�N�o�Ǧ����ܧ� CString �����AODBC 
	// �X�ʵ{���N����Ҧ����n���ഫ�C
	// (�`�N: �z�����ϥ� ODBC �X�ʵ{�� 3.5 ���Χ�s�������~��P�ɤ䴩
	// Unicode �M�o���ഫ)�C

	CStringW	m_szApplyNumber;
	CStringW	m_szNumber;
	CStringW	m_szApplyContent;
	CTime	m_dateExpect;
	CStringW	m_szName;
	CStringW	m_szSort;
	long	m_nChargeType;
	long	m_nCharge;
	CStringW	m_szInfoProvider;
	CStringW	m_szInfoPhone;
	CStringW	m_szLicense;
	CStringW	m_szLock;
	CStringW	m_szOverride;
	CStringW	m_szNewNumber;
	CStringW	m_szPrelude;
	long	m_nType;
	long	m_nCount;
	CTime	m_dateOMCDisp;
	CTime	m_dateFinish;
	CTime	m_dateOMCTake;
	CStringW	m_szOMCConstructor;
	long	m_nOMCConstructorID;
	CStringW	m_szOMCChecker;
	CTime	m_dateOMCSMS;
	CTime	m_dateReply;
	CTime	m_timeReply;
	CTime	m_dateOMCBS;
	CStringW	m_szNote;
	CStringW	m_szDestination;
	CStringW	m_szCallbar;
	CTime	m_dateApply;
	CStringW	m_szPlace;
	CStringW	m_szReply;
	int mode;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C0204ApplySet)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultConnect();	// �w�]�s���r��
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	virtual void AddNew();
	virtual BOOL Update();
	virtual void Edit();
	typedef enum EditModeEnum
	{
		dbEditNone = 0,
		dbEditInProgress = 1,
		dbEditAdd = 2,
		dbEditChanged = 4,
		dbEditDeleted = 8,
		dbEditNew = 16
	}	EditModeEnum;

	virtual int GetEditMode();

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_0204SET_H__13F551B5_0B82_11D5_A466_00485455D12D__INCLUDED_)
