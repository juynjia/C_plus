// 0204Doc.cpp : implementation of the C0204Doc class
//

#include "StdAfx.h"
#include "PRS.h"

#include "0204Doc.h"
#include "0204View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C0204Doc

IMPLEMENT_DYNCREATE(C0204Doc, CDocument)

BEGIN_MESSAGE_MAP(C0204Doc, CDocument)
	//{{AFX_MSG_MAP(C0204Doc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(IDC_RECORD_NEW, OnRecordNew)
	ON_UPDATE_COMMAND_UI(IDC_RECORD_NEW, OnUpdateRecordNew)
	ON_COMMAND(IDC_RECORD_DELETE, OnRecordDelete)
	ON_UPDATE_COMMAND_UI(IDC_RECORD_DELETE, OnUpdateRecordDelete)
	ON_COMMAND(IDC_RECORD_CANCEL, OnRecordCancel)
	ON_UPDATE_COMMAND_UI(IDC_RECORD_CANCEL, OnUpdateRecordCancel)
	ON_BN_CLICKED(IDC_0204_APPLY_NEW, On0204ApplyNew)
	ON_BN_CLICKED(IDC_0204_APPLY_DELETE, On0204ApplyDelete)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_RECORD_FIRST, ID_RECORD_PREV, OnRecordMove)
	ON_UPDATE_COMMAND_UI_RANGE(ID_RECORD_FIRST, ID_RECORD_PREV, OnUpdateRecordMove)
	ON_COMMAND_RANGE(IDC_0204_APPLY_FIRST, IDC_0204_APPLY_LAST, OnApplyMove)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C0204Doc construction/destruction

C0204Doc::C0204Doc()
    : m_h0204RecordSet(&m_hDatabase),
      m_h0204ApplySet(&m_hDatabase)
{
    m_nRecordIndex = 0;
    m_nRecordTotal = 0;
    m_nApplyIndex  = 0;
    m_nApplyTotal  = 0;
}

C0204Doc::~C0204Doc()
{
}


BOOL C0204Doc::Query(LPCSTR szSQL)
{
    ASSERT(m_hDatabase.IsOpen());

    // testing if record exists
    C0204RecordSet hSet(&m_hDatabase);
    hSet.Open(CRecordset::snapshot, szSQL);
    hSet.MoveLast();
    hSet.Close();

    // now really open
    ASSERT(m_h0204RecordSet.IsOpen());
    m_h0204RecordSet.Close();
    m_h0204RecordSet.Open(CRecordset::snapshot, szSQL);
    m_h0204RecordSet.MoveLast();
    m_nRecordIndex = 
    m_nRecordTotal = m_h0204RecordSet.GetRecordCount(); 

	return TRUE;
}

BOOL C0204Doc::OnNewDocument()
{
	CDocument::OnNewDocument();
	TRACE(_T("OnNewDocument()\n"));
    return OnOpenDocument(NULL);
}

BOOL C0204Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	TRACE("C0204Doc::OnOpenDocument()---->\n");
	TRACE("lpszPathName=%s\n", lpszPathName);
    // ignore parent call
    BOOL fResult = FALSE;
    try
    {
        CWaitCursor wait;
        ASSERT(!m_hDatabase.IsOpen());
        CSetting *pSetting = AfxGetSetting();
		//TRACE(_T("pSetting->m_szOMCDir=%s\n", (CString)pSetting->m_szOMCDir));
		//TRACE(_T("pSetting->m_szCSCDir=%s\n", CStrW2CStrT(pSetting->m_szCSCDir)));
		//TRACE(_T("DATABASE_NAME=%s\n", DATABASE_NAME));
		//TRACE(_T("DATABASE_NAME=%s\n", lpszPathName));
		//TRACE(_T("aaa: %s\n", const_cast<const char*>(pSetting->m_szOMCDir)));
        //m_hDatabase.Open(((pSetting->m_nVersion==VERSION_OMC)?pSetting->m_szOMCDir:pSetting->m_szCSCDir) + DATABASE_NAME);
		//m_hDatabase.Open(_T("rpcs_prs_ccs"));
        ASSERT(!m_h0204RecordSet.IsOpen());
        m_h0204RecordSet.Open();
        fResult = Query(NULL);
		//m_h0204RecordSet.Requery();
    }
    catch (CException *e)
    {
		TRACE(_T("C0204Doc::OnOpenDocument()-----> exception\n"));
		TCHAR   szCause[255];
		CString strFormatted;

		e->GetErrorMessage(szCause, 255);

		strFormatted = _T("Error : ");
		strFormatted += szCause;
		AfxMessageBox(strFormatted, MB_OK | MB_ICONSTOP);
		TRACE(_T("%s\n", strFormatted));
		//AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_OK|MB_ICONSTOP);
		//AfxMessageBox(e->GetErrorMessage, MB_OK | MB_ICONSTOP);
        e->Delete();
    }
	return fResult;
}

BOOL C0204Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	TRACE("C0204Doc::OnSaveDocument()---->\n");
	TRACE("lpszPathName()=%s\n", lpszPathName);
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	/*for(int  g=0;g<280;g++)
	{
     theApp->CountProgram();
	 Sleep(200);
	}*/
	
    BOOL bResult = FALSE;
	TRACE("yyyyyy\n");
	TRACE("IsModified()=%d\n", IsModified());
    if (IsModified() && GetView()->UpdateData())
    {
		TRACE("IsModified() && GetView()->UpdateData()---->\n");
        static CRecordset* pRecordSet[] = {
            &m_h0204RecordSet,
            &m_h0204ApplySet
        };
		TRACE("zzzzzzzz\n");
		
		GetView()->UpdateArrayFromView(); //added by erif
		//erif修改                                   
		ASSERT(&m_h0204RecordSet != NULL);
		ASSERT(m_h0204RecordSet.IsOpen());
		if (m_h0204RecordSet.GetEditMode() == m_h0204RecordSet.dbEditNone)
		{
			TRACE("m_h0204RecordSet.GetEditMode() == dbEditNone\n");
			m_h0204RecordSet.Edit();
		}
		m_h0204RecordSet.SetFieldDirty(NULL);
		m_h0204RecordSet.Update();

		ASSERT(&m_h0204ApplySet != NULL);
		ASSERT(m_h0204ApplySet.IsOpen());

		if (m_h0204ApplySet.GetEditMode() == m_h0204ApplySet.dbEditNone)
		{
			TRACE("m_h0204ApplySet.GetEditMode() == dbEditNone\n");
			m_h0204ApplySet.Edit();
		}
		m_h0204ApplySet.SetFieldDirty(NULL);
		m_h0204ApplySet.Update();
	bResult = TRUE;
    SetModifiedFlag(FALSE);						  
	}
		m_h0204ApplySet.Requery();
		ASSERT(m_h0204ApplySet.IsOpen());
		m_nApplyTotal = 0;
		if (!m_h0204ApplySet.IsEOF())
		{
			//先跑過一輪幫助算總數
			while (!m_h0204ApplySet.IsEOF()) {
				m_h0204ApplySet.MoveNext();
			}
			//移到最後一筆
			m_h0204ApplySet.MoveLast();
		
			m_nApplyTotal = m_h0204ApplySet.GetRecordCount();
			
			m_h0204ApplySet.MoveFirst();

			int tmp = m_nApplyIndex;
			tmp--;
			while (tmp > 0) {
				m_h0204ApplySet.MoveNext();
				tmp--;
			}



			//OnUpdateApplyMove();
			bResult = TRUE;
			SetModifiedFlag(FALSE);

			//m_nApplyIndex = 2;
			
			//m_h0204ApplySet.MoveFirst();
			//m_h0204ApplySet.MoveNext();
			//m_h0204ApplySet.MoveNext();

			/*m_nApplyIndex = 5;
			OnUpdateApplyMove();

			m_h0204ApplySet.MoveFirst();
			m_h0204ApplySet.MoveNext();
			m_h0204ApplySet.MoveNext();
			m_nApplyIndex = 2;*/
			
		}
		//OnUpdateApplyMove();


        
    
	
	GetView()->ReloadViewFromDB(); //added by erif
	TRACE("C0204Doc::OnSaveDocument()----> before return\n");
	TRACE("bResult=%d\n", bResult);
    return bResult;
}

void C0204Doc::OnCloseDocument() 
{
    // the DAO database and recordset destructor will close itself for us
	CDocument::OnCloseDocument();
}

BOOL C0204Doc::SaveModified() 
{
	TRACE("C0204Doc::SaveModified()\n");
	if (IsModified())
    {
		TRACE("C0204Doc::SaveModifi123545645656\n");
        switch (AfxMessageBox(IDS_PROMPT_SAVED, MB_YESNOCANCEL|MB_ICONQUESTION))
        {
        case IDYES:
            return OnSaveDocument(NULL);
        case IDNO:
            SetModifiedFlag(FALSE);
            break;
        case IDCANCEL:
            return FALSE;
        }
    }
    return TRUE;
}

void C0204Doc::SetTitle(LPCTSTR lpszTitle)
{
    CString szText;
    szText.LoadString(IDS_0204_TITLE);
    CDocument::SetTitle(szText);
}

void C0204Doc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
    // don't add name to MRU
	CDocument::SetPathName(lpszPathName, FALSE);
}

void C0204Doc::QueryApply (LPCSTR szNumber)
{
	TRACE("C0204Doc::QueryApply()---->\n");
	TRACE("szNumber=%s\n", szNumber);
    ASSERT(m_h0204RecordSet.IsOpen());
    m_h0204ApplySet.m_strFilter.Format("[節目號碼] = '%s'", szNumber);

    if (m_h0204ApplySet.IsOpen())
    {
        ASSERT(m_h0204ApplySet.CanRestart());
        m_h0204ApplySet.Requery();
    }
    else
        m_h0204ApplySet.Open();

    ASSERT(m_h0204ApplySet.IsOpen());
    m_nApplyIndex = m_nApplyTotal = 0;
    if (!m_h0204ApplySet.IsEOF())
    {
		//先跑過一輪幫助算總數
		while (!m_h0204ApplySet.IsEOF()) {
			m_h0204ApplySet.MoveNext();
		}
		//移到最後一筆
		m_h0204ApplySet.MoveLast();
        m_nApplyIndex =
        m_nApplyTotal = m_h0204ApplySet.GetRecordCount();
    }
    OnUpdateApplyMove();
}

void C0204Doc::OnRecordMove(UINT nIDMoveCommand) 
{
    if (SaveModified())
    {
        ASSERT(m_h0204RecordSet.IsOpen());
        switch (nIDMoveCommand)
        {
        case ID_RECORD_FIRST:
			TRACE("ID_RECORD_FIRST\n");
            ASSERT(!m_h0204RecordSet.IsBOF());
			m_h0204RecordSet.MoveFirst();
            m_nRecordIndex = 1;
            break;
        case ID_RECORD_PREV:
			TRACE("ID_RECORD_PREV\n");
            if (m_h0204RecordSet.IsBOF() || (m_nRecordIndex <= 1))
                return;
            m_h0204RecordSet.MovePrev();
            m_nRecordIndex--;
            break;
        case ID_RECORD_NEXT:
			TRACE("ID_RECORD_NEXT\n");
            if (m_h0204RecordSet.IsEOF() || (m_nRecordIndex >= m_nRecordTotal))
                return;
			m_h0204RecordSet.MoveNext();
            m_nRecordIndex++;
            break;
        case ID_RECORD_LAST:
			TRACE("ID_RECORD_LAST\n");
            ASSERT(!m_h0204RecordSet.IsEOF());
			TRACE("m_h0204RecordSet.GetRecordCount()1=%d\n", m_h0204RecordSet.GetRecordCount());
			m_h0204RecordSet.MoveFirst();
			while(!m_h0204RecordSet.IsEOF()){
				m_h0204RecordSet.MoveNext();
			}
			m_h0204RecordSet.MoveLast();
			TRACE("m_h0204RecordSet.GetRecordCount()2=%d\n", m_h0204RecordSet.GetRecordCount());
			m_nRecordTotal = m_h0204RecordSet.GetRecordCount();
			TRACE("m_nRecordIndex=%d\n", m_nRecordIndex);
            m_nRecordIndex = m_nRecordTotal;
			TRACE("m_nRecordTotal=%d\n", m_nRecordTotal);
            break;
        default:
			TRACE("default\n");
            ASSERT(0);
            break;
        }
		TRACE("qqqqq\n");
       QueryApply(CStrW2CStrT(m_h0204RecordSet.m_szNumber));
		TRACE("m_h0204ApplySet.GetRecordCount()=%d\n", m_h0204ApplySet.GetRecordCount());
        if (m_h0204ApplySet.GetRecordCount() == 0) // empty
        {
			TRACE("empty\n");
            AfxMessageBox(IDS_WARNING_NOAPPLY, MB_ICONEXCLAMATION);
            ASSERT(!IsModified());
            On0204ApplyNew();
        }
		else
		{
			TRACE(_T("else\n"));
			GetView()->UpdateData(FALSE);
		}
		TRACE(_T("eeee\n"));
        GetMainFrame()->UpdateCount(m_nRecordIndex, m_nRecordTotal);
		TRACE(_T("end\n"));
    }
}

void C0204Doc::OnApplyMove(UINT nIDMoveCommand) 
{
	TRACE("C0204Doc::OnApplyMove()---->\n");
    if (SaveModified())
    {
        ASSERT(m_h0204ApplySet.IsOpen());

        if (m_h0204ApplySet.GetEditMode() == m_h0204ApplySet.dbEditAdd)
        {
			TRACE("m_h0204ApplySet.GetEditMode() == dbEditAdd\n");
            m_h0204ApplySet.CancelUpdate();
            m_nApplyTotal--;
			TRACE("m_nApplyTotal=%d\n", m_nApplyTotal);
        }
		TRACE("m_nApplyIndex1=%d\n", m_nApplyIndex);
        switch (nIDMoveCommand)
        {
        case IDC_0204_APPLY_FIRST:
			TRACE("IDC_0204_APPLY_FIRST\n");
            ASSERT(!m_h0204ApplySet.IsBOF() && !m_h0204ApplySet.IsEOF());
			m_h0204ApplySet.MoveFirst();
            m_nApplyIndex = 1;
            break;
        case IDC_0204_APPLY_PREV:
			TRACE("IDC_0204_APPLY_PREV\n");
			if (m_h0204ApplySet.IsBOF()) {
				TRACE("m_h0204ApplySet.IsBOF()\n");
				return;
			}
			m_h0204ApplySet.MovePrev();
			m_nApplyIndex--;
			break;
        case IDC_0204_APPLY_NEXT:
			TRACE("IDC_0204_APPLY_NEXT\n");
            if (m_h0204ApplySet.IsEOF())
                return;
			m_h0204ApplySet.MoveNext();
            m_nApplyIndex++;  
            break;
        case IDC_0204_APPLY_LAST:
			TRACE("IDC_0204_APPLY_LAST\n");
            ASSERT(!m_h0204ApplySet.IsBOF() && !m_h0204ApplySet.IsEOF());
			m_h0204ApplySet.MoveLast();
            m_nApplyIndex = m_nApplyTotal;
            break;
        default:
			TRACE("default\n");
            ASSERT(0);
            break;
        }
		TRACE("m_nApplyIndex2=%d\n", m_nApplyIndex);
        OnUpdateApplyMove();
        GetView()->UpdateData(FALSE);
    }
}

/////////////////////////////////////////////////////////////////////////////
// C0204Doc serialization

void C0204Doc::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// C0204Doc diagnostics

#ifdef _DEBUG
void C0204Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C0204Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

CMainFrame* C0204Doc::GetMainFrame() const
{
    CWnd *pWnd = AfxGetMainWnd();
    ASSERT(pWnd != NULL);
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CMainFrame)));
    return (CMainFrame*)pWnd;
}

C0204View* C0204Doc::GetView() const
{
    POSITION pos = GetFirstViewPosition();
    ASSERT(pos != NULL);
    CView *pView = GetNextView(pos);
    ASSERT(pView != NULL);
    ASSERT(pos == NULL);
	ASSERT(pView->IsKindOf(RUNTIME_CLASS(C0204View)));
    return (C0204View*)pView;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C0204Doc commands

void C0204Doc::OnFileSave() 
{
	TRACE("C0204Doc::OnFileSave()----->\n");
    OnSaveDocument(NULL);
}

void C0204Doc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	//TRACE("C0204Doc::OnUpdateFileSave()----->\n");
    pCmdUI->Enable(IsModified());
}

void C0204Doc::OnRecordNew() 
{
	//TRACE("C0204Doc::OnRecordNew()----->\n");
    ASSERT(0);
}

void C0204Doc::OnUpdateRecordNew(CCmdUI* pCmdUI) 
{
	//TRACE("C0204Doc::OnUpdateRecordNew()----->\n");
    pCmdUI->Enable(FALSE);
}

void C0204Doc::OnRecordDelete() 
{
}

void C0204Doc::OnUpdateRecordDelete(CCmdUI* pCmdUI) 
{
	//TRACE("C0204Doc::OnUpdateRecordDelete()----->\n");
    //pCmdUI->Enable(m_nRecordIndex > 0 && m_nRecordIndex <= m_nRecordTotal);
    pCmdUI->Enable(FALSE);
}

void C0204Doc::OnRecordCancel() 
{
	//TRACE("C0204Doc::OnRecordCancel()----->\n");
    if (GetView()->UpdateData(FALSE))
        SetModifiedFlag(FALSE);
}

void C0204Doc::OnUpdateRecordCancel(CCmdUI* pCmdUI) 
{
	//TRACE("C0204Doc::OnUpdateRecordCancel()----->\n");
    pCmdUI->Enable(IsModified() &&
        m_h0204RecordSet.GetEditMode() != m_h0204RecordSet.dbEditAdd &&
        m_h0204ApplySet.GetEditMode() != m_h0204ApplySet.dbEditAdd);
}

void C0204Doc::OnUpdateRecordMove(CCmdUI* pCmdUI) 
{
	//TRACE("C0204Doc::OnUpdateRecordMove()----->\n");
    BOOL bEnabled = FALSE;
    switch (pCmdUI->m_nID)
    {
    case ID_RECORD_FIRST:
    case ID_RECORD_PREV:
        if (m_nRecordIndex > 1)
            bEnabled = TRUE;
        break;
    case ID_RECORD_NEXT:
    case ID_RECORD_LAST:
        if (m_nRecordIndex < m_nRecordTotal)
            bEnabled = TRUE;
        break;
    default:
        ASSERT(0);
        break;
    }
    pCmdUI->Enable(bEnabled);
}

void C0204Doc::OnUpdateApplyMove() 
{
	TRACE("C0204Doc::OnUpdateApplyMove()----->\n");
	TRACE("m_nApplyIndex=%d\n", m_nApplyIndex);
	TRACE("m_nApplyTotal=%d\n", m_nApplyTotal);
    ASSERT((m_nApplyIndex>0 && m_nApplyIndex<=m_nApplyTotal) ||
        (m_nApplyIndex==0 && m_nApplyTotal==0));
    UINT nIndex;
    for (nIndex=IDC_0204_APPLY_FIRST; nIndex<=IDC_0204_APPLY_PREV; nIndex++)
        GetView()->GetDlgItem(nIndex)->EnableWindow(m_nApplyIndex > 1);
    for (nIndex=IDC_0204_APPLY_NEXT; nIndex<=IDC_0204_APPLY_LAST; nIndex++)
        GetView()->GetDlgItem(nIndex)->EnableWindow(m_nApplyIndex < m_nApplyTotal);
}

void C0204Doc::On0204ApplyNew() 
{
	//TRACE("C0204Doc::On0204ApplyNew()----->\n");
    if (IsModified())
        AfxMessageBox(IDS_WARNING_SAVEFIRST);
    else
    {
        ASSERT(m_h0204ApplySet.GetEditMode() == m_h0204ApplySet.dbEditNone);
        ASSERT(m_h0204ApplySet.CanAppend());
        int nCount = 0;
        if (!m_h0204ApplySet.IsBOF() && !m_h0204ApplySet.IsEOF())
        {
            m_h0204ApplySet.MoveLast();
            nCount = m_h0204ApplySet.m_nCount + 1;
        }
        m_h0204ApplySet.AddNew();
        //m_h0204ApplySet.SetBookmark(m_h0204ApplySet.GetLastModifiedBookmark()); // make record current  //erif先移掉
        //m_h0204ApplySet.SetDefaultValue();  //erif先移掉
        m_h0204ApplySet.m_szNumber = m_h0204RecordSet.m_szNumber;
        m_h0204ApplySet.m_nCount   = nCount;
        m_nApplyIndex = ++m_nApplyTotal;
        SetModifiedFlag();
        OnUpdateApplyMove();
        GetView()->UpdateData(FALSE);
    }
}

void C0204Doc::On0204ApplyDelete() 
{
	//TRACE("C0204Doc::On0204ApplyDelete()----->\n");
    if (AfxMessageBox(IDS_PROMPT_DELETEAPPLY, MB_YESNO|MB_ICONQUESTION) == IDYES)
    {
        if (m_nApplyTotal == 1)
        {
            ASSERT(m_h0204ApplySet.GetRecordCount() <= 1); // may be zero for AddNew()
            AfxMessageBox(IDS_WARNING_LASTAPPLY, MB_ICONEXCLAMATION);
            return;
        }
        else if (m_h0204ApplySet.GetEditMode() == m_h0204ApplySet.dbEditAdd)
            m_h0204ApplySet.CancelUpdate();
        else
            m_h0204ApplySet.Delete();

        ASSERT(m_nApplyTotal > 1);
        OnApplyMove(m_h0204ApplySet.IsBOF()?IDC_0204_APPLY_FIRST:IDC_0204_APPLY_PREV);
        m_nApplyTotal--;
        ASSERT((m_nApplyIndex>0 && m_nApplyIndex<=m_nApplyTotal) ||
            (m_nApplyIndex==0 && m_nApplyTotal==0));
        OnUpdateApplyMove();
    }
}
