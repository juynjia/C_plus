// ASESUpload.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ASESUpload dialog
#include "0204Set.h"

class ASESUpload : public CDialog
{
	static LPCTSTR strBOOL(BOOL bFlag) {
		return bFlag ? _T("TRUE") : _T("FALSE");
	}
// Construction
public:
	short m_iActive;
	C0204ApplySet  * m_p0204ApplySet;
	C0204RecordSet * m_p0204RecordSet;
	CDatabase *m_pDB; //PRS_CCS.mdb
	CRecordset *m_pRS; //0204派工登記表
	CRecordset *m_pRS1; //0204業務紀錄
	BOOL m_bDeleteFlag;
	BOOL m_bChangeFlag;
	BOOL OnInitDialog();
	ASESUpload(CWnd* pParent = NULL);   // standard constructor
	static CString strVARIANT(const COleVariant& var);

// Dialog Data
	//{{AFX_DATA(ASESUpload)
	enum { IDD = IDD_ASES_UPLOAD };
	CProgressCtrl	m_cProgress;
	CString	m_str0204num;
	CString	m_new0204num;
	CString	m_strStatus;
	int		m_BARID;
	int		m_LOCKPID;
	int		m_STATUS;
	CString	m_TX_NUM;
	BOOL	m_check_delete;
	int		m_ANNID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ASESUpload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ASESUpload)
	afx_msg void OnBeginUpload();
	afx_msg void OnGetMdbdata();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
