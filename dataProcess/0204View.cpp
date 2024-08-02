// 0204View.cpp : implementation of the C0204View class
//

#include "StdAfx.h"
#include "PRS.h"
#include "MainFrm.h"

#include "0204Doc.h"
#include "0204View.h"

#include "ASESUpload.h"	//cjshen add
#include "ASESDownload.h"	//cjshen add
#include "FTPSetting.h"
#include "Rpcs_Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// hack:
#define STATEIMAGE_CHECK    0x2000 

#define REPLY_NO            0
#define REPLY_YES           1

#define LOCK_NO             0
#define LOCK_YES            1

#define CHARGING_PER_TIME   0
#define CHARGING_PER_MIN    1

#define OVERRIDE_NONE       0
#define OVERRIDE_CHT        1
#define OVERRIDE_CUSTOMER   2
#define OVERRIDE_RECEDE     3

#define PLACE_NCSC          92 //北客
#define PLACE_CCSC          94 //中客
#define PLACE_SCSC          97 //南客
#define PLACE_LDM           9  //長通  改成 北分
#define PLACE_OTHER         8  //其他

#define CALLBAR_NONE        0 //不限制
#define CALLBAR_PRIVATE     1 //民營
#define CALLBAR_MOBILE      2 //所有行動

#define APPLY_CREATE        1
#define APPLY_MODIFY        2
#define APPLY_READD         3

static int REPLY_FIELDVALUE[] = 
{
    REPLY_NO,
    REPLY_YES
};

static int LOCK_FIELDVALUE[] = 
{
    LOCK_NO,
    LOCK_YES
};

static int CHARGING_FIELDVALUE[] = 
{
    CHARGING_PER_TIME,
    CHARGING_PER_MIN
};

static int OVERRIDE_FIELDVALUE[] = 
{
    OVERRIDE_NONE,
    OVERRIDE_CHT,
    OVERRIDE_CUSTOMER,
    OVERRIDE_RECEDE
};

static LPCSTR PLACE_FIELDNAME[] =
{
    "北客",
    "中客",
    "南客",
    "北分",
	"其他"
};

static int PLACE_FIELDVALUE[] = 
{
    PLACE_NCSC,
    PLACE_CCSC,
    PLACE_SCSC,
    PLACE_LDM,
	PLACE_OTHER
};

static LPCSTR CALLBAR_FIELDNAME[] = 
{
    "不限制",
    "民營",
    "所有行動"
};

static int CALLBAR_FIELDVALUE[] = 
{
    CALLBAR_NONE,
    CALLBAR_PRIVATE,
    CALLBAR_MOBILE
};

static LPCSTR APPLY_FIELDNAME[] =
{
    "Error", // dummy
    "新增",
    "異動",
    "新增(補)"
};

/////////////////////////////////////////////////////////////////////////////
// C0204View

IMPLEMENT_DYNCREATE(C0204View, CFormView)

BEGIN_MESSAGE_MAP(C0204View, CFormView)
	//{{AFX_MSG_MAP(C0204View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_0204_APPLY_CONTENT, OnListCtrlItemchanged)
	ON_BN_CLICKED(IDC_0204_REPLY_BTN, OnReplyBtnClicked)
	ON_COMMAND(ID_ASES_UPLOAD, OnAsesUpload)
	ON_COMMAND(ID_ASES_DOWNLOAD, OnAsesDownload)
	ON_UPDATE_COMMAND_UI(ID_ASES_UPLOAD, OnUpdateAsesUpload)
	ON_UPDATE_COMMAND_UI(ID_ASES_DOWNLOAD, OnUpdateAsesDownload)
	ON_BN_CLICKED(IDC_0204_QUERY1, On0204Query1)
	ON_BN_CLICKED(IDC_0204_QUERY2, On0204Query2)
	ON_COMMAND(ID_ACTION_PROFILE, OnActionProfile)
	ON_COMMAND(IDM_FTP_SET, OnFtpSet)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_0204_EDIT_BEGIN, IDC_0204_EDIT_END, OnControlChange)
	ON_CONTROL_RANGE(CBN_EDITCHANGE, IDC_0204_COMBO_BEGIN, IDC_0204_COMBO_END, OnControlChange)
	ON_CONTROL_RANGE(CBN_SELCHANGE, IDC_0204_COMBO_BEGIN, IDC_0204_COMBO_END, OnControlChange)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_0204_BUTTON_BEGIN, IDC_0204_BUTTON_END, OnControlDataClicked)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_0204_REPLY, IDC_0204_REPLY, OnControlButtonClicked)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_0204_LOCK, IDC_0204_LOCK, OnControlButtonClicked)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_0204_ONETIME, IDC_0204_ONEMIN, OnControlButtonClicked)
    ON_CONTROL_RANGE(BN_CLICKED, IDC_0204_OVERRIDE_NONE, IDC_0204_OVERRIDE_RECEDE, OnControlButtonClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C0204View construction/destruction

C0204View::C0204View()
	: CFormView(C0204View::IDD)
{
	//{{AFX_DATA_INIT(C0204View)
	m_p0204RecordSet = NULL;
	m_p0204ApplySet  = NULL;
	//}}AFX_DATA_INIT
}

C0204View::~C0204View()
{
}

int CALLBACK C0204View::SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CListCtrl *pListCtrl = (CListCtrl*)lParamSort;
    ASSERT(pListCtrl != NULL);

    BOOL bCheck1 = HIWORD(lParam1), bCheck2 = HIWORD(lParam2);
    WORD wValue1 = LOWORD(lParam1), wValue2 = LOWORD(lParam2);

    if (bCheck1 && !bCheck2)
        return -1;
    else if (!bCheck1 && bCheck2)
        return 1;
    return (wValue1<wValue2)?-1:((wValue1>wValue2)?1:0);
}

void AFXAPI C0204View::DDX_Content(CDataExchange *pDX, int nIDC, CString& value)
{
    pDX->PrepareCtrl(nIDC);

    CString szData;
    int nItem;
    DWORD nIndex;
    if (pDX->m_bSaveAndValidate)
    {
        value = "";
        for (nItem=0; nItem<m_hApplyContent.GetItemCount(); nItem++)
            if (m_hApplyContent.GetCheck(nItem))
            {
                szData.Format("%d", LOWORD(m_hApplyContent.GetItemData(nItem)));
                if (value.IsEmpty())
                    value = szData;
                else
                    value += "," + szData;
            }
        if (value.IsEmpty())
        {
            AfxMessageBox(IDS_WARNING_NOCONTENT, MB_ICONEXCLAMATION);
    		pDX->Fail();
        }
    }
    else
    {
        for (nItem=0; nItem<m_hApplyContent.GetItemCount(); nItem++)
        {
            m_hApplyContent.SetCheck(nItem, FALSE);
            m_hApplyContent.SetItemState(nItem, 0, LVIS_SELECTED|LVIS_FOCUSED);
            m_hApplyContent.SetItemData(nItem, LOWORD(m_hApplyContent.GetItemData(nItem)));
        }

        szData = value;
        char *lpData = szData.GetBuffer(szData.GetLength()), *lpStart = lpData;
        BOOL bContinue = TRUE;
        while (bContinue)
        {
            switch (*lpData)
            {
            case '\0':
                bContinue = FALSE;
                // fall through
            case ',':
                *lpData = '\0';
                nIndex = atol(lpStart); 
                for (nItem=0; nItem<m_hApplyContent.GetItemCount(); nItem++)
                    if (m_hApplyContent.GetItemData(nItem) == nIndex)
                    {
                        m_hApplyContent.SetCheck(nItem, TRUE);
                        m_hApplyContent.SetItemData(nItem, MAKELONG(WORD(nIndex), STATEIMAGE_CHECK));
                    }
                lpStart = lpData + 1;
                break;
            }
            lpData++;
        }
        m_hApplyContent.SortItems(SortFunc, (DWORD)&m_hApplyContent);
        m_hApplyContent.EnsureVisible(0, FALSE);
    }
}

void C0204View::DoDataExchange(CDataExchange* pDX)
{
	TRACE("剛加入  %s\n", CStrW2CStrT(m_p0204ApplySet->m_szName));
	TRACE("(C0204View::DoDataExchange()---->\n");
    UINT nIndex;
    BOOL bModified = GetDocument()->IsModified();
	//TRACE("IDC_0204_COMBO_BEGIN = %d\n", IDC_0204_COMBO_BEGIN);
	//TRACE("IDC_0204_COMBO_END = %d\n", IDC_0204_COMBO_END);
	for (nIndex = IDC_0204_COMBO_BEGIN; nIndex <= IDC_0204_COMBO_END; nIndex++) {
		DDX_Control(pDX, nIndex, m_hCombo[nIndex - IDC_0204_COMBO_BEGIN]);
	}
	//TRACE("IDC_0204_BUTTON_BEGIN = %d\n", IDC_0204_BUTTON_BEGIN);
	//TRACE("IDC_0204_BUTTON_END = %d\n", IDC_0204_BUTTON_END);
	for (nIndex = IDC_0204_BUTTON_BEGIN; nIndex <= IDC_0204_BUTTON_END; nIndex++) {
		DDX_Control(pDX, nIndex, m_hButton[nIndex - IDC_0204_BUTTON_BEGIN]);
	}
    CFormView::DoDataExchange(pDX);
	CString nullString = "";
	TRACE("(33\n");
	//{{AFX_DATA_MAP(C0204View)
	DDX_Control(pDX, IDC_0204_APPLY_CONTENT, m_hApplyContent);
	TRACE("0204號碼(m_p0204RecordSet->m_szNumber)=%s\n", CStrW2CStrT(m_p0204RecordSet->m_szNumber));
	//TRACE("m_p0204RecordSet->IsOpen()=%d\n", m_p0204RecordSet->IsOpen());
	DDX_Text(pDX, IDC_0204_NUMBER, CStrW2CStrT(m_p0204RecordSet->m_szNumber));
	//DDX_FieldText(pDX, IDC_0204_NUMBER, CStrW2CStrT(m_p0204RecordSet->m_szNumber), m_p0204RecordSet);
	TRACE("建構狀態1(m_p0204RecordSet->m_szStatus)=%s\n", CStrW2CStrT(m_p0204RecordSet->m_szStatus));
	DDX_Text(pDX, IDC_0204_STATUS, CStrW2CStrT(m_p0204RecordSet->m_szStatus));
	TRACE("建構狀態2(m_p0204RecordSet->m_szStatus)=%s\n", CStrW2CStrT(m_p0204RecordSet->m_szStatus));
	//DDX_FieldText(pDX, IDC_0204_STATUS, CStrW2CStrT(m_p0204RecordSet->m_szStatus), m_p0204RecordSet);
	//DDX_FieldCBStringExact(pDX, IDC_0204_STATUS, CStrW2CStrT(m_p0204RecordSet->m_szStatus), m_p0204RecordSet);
//	DDX_Control(pDX, IDC_FTPSERVER, m_ftps);
//	DDX_Control(pDX, IDC_FTPCLIENT, m_ftp);
	//}}AFX_DATA_MAP
    ASSERT(m_p0204ApplySet->IsOpen());
    ASSERT(m_p0204ApplySet->m_szNumber == m_p0204RecordSet->m_szNumber);
    // custom DDXs
	TRACE("是否需要SMS報竣(m_p0204ApplySet->m_szReply)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szReply));
    DDX_CheckBox(pDX, IDC_0204_REPLY, CStrW2CStrT(m_p0204ApplySet->m_szReply), REPLY_FIELDVALUE);
	TRACE("鎖碼節目(m_p0204ApplySet->m_szLock)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szLock));
    DDX_CheckBox(pDX, IDC_0204_LOCK, CStrW2CStrT(m_p0204ApplySet->m_szLock), LOCK_FIELDVALUE);
	TRACE("資費種類(m_p0204ApplySet->m_nChargeType)=%d\n", (m_p0204ApplySet->m_nChargeType));
    DDX_RadioGroup(pDX, IDC_0204_ONETIME, m_p0204ApplySet->m_nChargeType, CHARGING_FIELDVALUE, sizeof(CHARGING_FIELDVALUE)/sizeof(int));
	TRACE("超載服務(m_p0204ApplySet->m_szOverride)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szOverride));
    DDX_RadioGroup(pDX, IDC_0204_OVERRIDE_NONE, CStrW2CStrT(m_p0204ApplySet->m_szOverride), OVERRIDE_FIELDVALUE, sizeof(OVERRIDE_FIELDVALUE)/sizeof(int));
	TRACE("受理單位(m_p0204ApplySet->m_szPlace)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szPlace));
    DDX_ComboBox(pDX, IDC_0204_PLACE, CStrW2CStrT(m_p0204ApplySet->m_szPlace));
	TRACE("CallBar種類(m_p0204ApplySet->m_szCallbar)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szCallbar));
    DDX_ComboBox(pDX, IDC_0204_CALLBAR, CStrW2CStrT(m_p0204ApplySet->m_szCallbar));
	TRACE("節目類別(m_p0204ApplySet->m_szSort)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szSort));
    DDX_ComboBoxByte(pDX, IDC_0204_SORT, CStrW2CStrT(m_p0204ApplySet->m_szSort));
	TRACE("異動事項(m_p0204ApplySet->m_szApplyContent)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szApplyContent));
    DDX_Content(pDX, IDC_0204_APPLY_CONTENT, CStrW2CStrT(m_p0204ApplySet->m_szApplyContent));
	
    // normal DDXs
	TRACE("經營者證號(m_p0204ApplySet->m_szLicense)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szLicense));
	DDX_Text(pDX, IDC_0204_LICENSE, CStrW2CStrT(m_p0204ApplySet->m_szLicense));
	//DDX_FieldText(pDX, IDC_0204_LICENSE, CStrW2CStrT(m_p0204ApplySet->m_szLicense), m_p0204ApplySet);
	TRACE("新節目號碼(m_p0204ApplySet->m_szNewNumber)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szNewNumber));
	DDX_Text(pDX, IDC_0204_NEWNUM, CStrW2CStrT(m_p0204ApplySet->m_szNewNumber));
	//DDX_FieldText(pDX, IDC_0204_NEWNUM, CStrW2CStrT(m_p0204ApplySet->m_szNewNumber), m_p0204ApplySet);
	TRACE("次數(m_p0204ApplySet->m_nCount)=%d\n", m_p0204ApplySet->m_nCount);
	DDX_Text(pDX, IDC_0204_APPLY_COUNT, m_p0204ApplySet->m_nCount);
	//DDX_FieldText(pDX, IDC_0204_APPLY_COUNT, m_p0204ApplySet->m_nCount, m_p0204ApplySet);
	TRACE("聯單編號(m_p0204ApplySet->m_szApplyNumber)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber));
	DDX_Text(pDX, IDC_0204_APPLY_NUMBER, CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber));
	//DDX_FieldText(pDX, IDC_0204_APPLY_NUMBER, CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber), m_p0204ApplySet);
	DDV_MinMaxChars(pDX, CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber), 1, 10);
	//DDX_FieldText(pDX, IDC_0204_APPLY_DATE, m_p0204ApplySet->m_dateApply, m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_EXPECT_DATE, m_p0204ApplySet->m_dateExpect, m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_REPLY_DATE, m_p0204ApplySet->m_dateReply, m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_REPLY_TIME, m_p0204ApplySet->m_timeReply, m_p0204ApplySet);
	if (m_p0204ApplySet->m_dateApply == NULL) {
		//TRACE("申請日期為空\n");
		DDX_Text(pDX, IDC_0204_APPLY_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt1 = (m_p0204ApplySet->m_dateApply).GetTime();
		DDX_Text(pDX, IDC_0204_APPLY_DATE, cdt1); //用DDX_Text取代DDX_FieldText
		CString cs1 = (m_p0204ApplySet->m_dateApply).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("申請日期(m_p0204ApplySet->m_dateApply)=%s\n", cs1);
	}
	if (m_p0204ApplySet->m_dateExpect == NULL) {
		//TRACE("預定生效為空\n");
		DDX_Text(pDX, IDC_0204_EXPECT_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt2 = (m_p0204ApplySet->m_dateExpect).GetTime();
		DDX_Text(pDX, IDC_0204_EXPECT_DATE, cdt2); //用DDX_Text取代DDX_FieldText
		CString cs2 = (m_p0204ApplySet->m_dateExpect).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("預定生效日期(m_p0204ApplySet->m_dateExpect)=%s\n", cs2);
	}
	if (m_p0204ApplySet->m_dateReply == NULL) {
		//TRACE("回竣日期為空\n");
		DDX_Text(pDX, IDC_0204_REPLY_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt3 = (m_p0204ApplySet->m_dateReply).GetTime();
		DDX_Text(pDX, IDC_0204_REPLY_DATE, cdt3); //用DDX_Text取代DDX_FieldText
		CString cs3 = (m_p0204ApplySet->m_dateReply).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("回竣日期(m_p0204ApplySet->m_dateReply)=%s\n", cs3);
	}
	
	if (m_p0204ApplySet->m_timeReply == NULL) {
		//TRACE("回竣時間為空\n");
		DDX_Text(pDX, IDC_0204_REPLY_TIME, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt4 = (m_p0204ApplySet->m_timeReply).GetTime();
		CString cs4;
		cs4.Format(_T("%02d:%02d:%02d"), cdt4.GetHour(), cdt4.GetMinute(), cdt4.GetSecond());
		DDX_Text(pDX, IDC_0204_REPLY_TIME, cs4); //用DDX_Text取代DDX_FieldText
		//TRACE("回竣時間(m_p0204ApplySet->m_timeReply)=%s\n", cs4);
	}
	//DDX_MonthCalCtrl(pDX, IDC_0204_APPLY_DATE, m_p0204ApplySet->m_dateApply); //另一種寫法可過
	//DDX_MonthCalCtrl(pDX, IDC_0204_EXPECT_DATE, m_p0204ApplySet->m_dateExpect); //另一種寫法可過
	//DDX_MonthCalCtrl(pDX, IDC_0204_REPLY_DATE, m_p0204ApplySet->m_dateReply); //另一種寫法可過
	//DDX_MonthCalCtrl(pDX, IDC_0204_REPLY_TIME, m_p0204ApplySet->m_timeReply); //另一種寫法可過
	TRACE("實體號碼(m_p0204ApplySet->m_szDestination)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szDestination));
	DDX_Text(pDX, IDC_0204_DESTINATION, CStrW2CStrT(m_p0204ApplySet->m_szDestination));
	//DDX_FieldText(pDX, IDC_0204_DESTINATION, CStrW2CStrT(m_p0204ApplySet->m_szDestination), m_p0204ApplySet);
	TRACE("節目名稱(m_p0204ApplySet->m_szName)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szName));
	DDX_Text(pDX, IDC_0204_NAME, CStrW2CStrT(m_p0204ApplySet->m_szName));
	//DDX_FieldText(pDX, IDC_0204_NAME, CStrW2CStrT(m_p0204ApplySet->m_szName), m_p0204ApplySet);
	TRACE("資訊提供者(m_p0204ApplySet->m_szInfoProvider)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szInfoProvider));
	DDX_Text(pDX, IDC_0204_INFO_PROVIDER, CStrW2CStrT(m_p0204ApplySet->m_szInfoProvider));
	//DDX_FieldText(pDX, IDC_0204_INFO_PROVIDER, CStrW2CStrT(m_p0204ApplySet->m_szInfoProvider), m_p0204ApplySet);
	TRACE("資訊提供者連絡電話(m_p0204ApplySet->m_szInfoPhone)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szInfoPhone));
	DDX_Text(pDX, IDC_0204_INFO_PHONE, CStrW2CStrT(m_p0204ApplySet->m_szInfoPhone));
	//DDX_FieldText(pDX, IDC_0204_INFO_PHONE, CStrW2CStrT(m_p0204ApplySet->m_szInfoPhone), m_p0204ApplySet);
	TRACE("資費1(m_p0204ApplySet->m_nCharge)=%d\n", m_p0204ApplySet->m_nCharge);
	DDX_Text(pDX, IDC_0204_CHARGE, m_p0204ApplySet->m_nCharge);
	TRACE("資費2(m_p0204ApplySet->m_nCharge)=%d\n", m_p0204ApplySet->m_nCharge);
	//DDX_FieldText(pDX, IDC_0204_CHARGE, m_p0204ApplySet->m_nCharge, m_p0204ApplySet);
	TRACE("前言(m_p0204ApplySet->m_szPrelude)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szPrelude));
	DDX_Text(pDX, IDC_0204_PRELUDE, CStrW2CStrT(m_p0204ApplySet->m_szPrelude));
	//DDX_FieldText(pDX, IDC_0204_PRELUDE, CStrW2CStrT(m_p0204ApplySet->m_szPrelude), m_p0204ApplySet);
    //DDX_FieldText(pDX, IDC_0204_OMC_TAKE_DATE, m_p0204ApplySet->m_dateOMCTake, m_p0204ApplySet);
    //DDX_FieldText(pDX, IDC_0204_OMC_DISP_DATE, m_p0204ApplySet->m_dateOMCDisp, m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_OMC_SMS_DATE, m_p0204ApplySet->m_dateOMCSMS, m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_OMC_BS_DATE, m_p0204ApplySet->m_dateOMCBS, m_p0204ApplySet);
	
	if (m_p0204ApplySet->m_dateOMCTake == NULL) {
		//TRACE("OMC受理日期為空\n");
		DDX_Text(pDX, IDC_0204_OMC_TAKE_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt5 = (m_p0204ApplySet->m_dateOMCTake).GetTime();
		DDX_Text(pDX, IDC_0204_OMC_TAKE_DATE, cdt5); //用DDX_Text取代DDX_FieldText
		CString cs5 = (m_p0204ApplySet->m_dateOMCTake).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("OMC受理日期(m_p0204ApplySet->m_dateOMCTake)=%s\n", cs5);
	}
	if (m_p0204ApplySet->m_dateOMCDisp == NULL) {
		//TRACE("派工日期為空\n");
		DDX_Text(pDX, IDC_0204_OMC_DISP_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt6 = (m_p0204ApplySet->m_dateOMCDisp).GetTime();
		DDX_Text(pDX, IDC_0204_OMC_DISP_DATE, cdt6); //用DDX_Text取代DDX_FieldText
		CString cs6 = (m_p0204ApplySet->m_dateOMCDisp).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("派工日期(m_p0204ApplySet->m_dateOMCDisp)=%s\n", cs6);
	}
	if (m_p0204ApplySet->m_dateOMCSMS == NULL) {
		//TRACE("SMS上線日期為空\n");
		DDX_Text(pDX, IDC_0204_OMC_SMS_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt7 = (m_p0204ApplySet->m_dateOMCSMS).GetTime();
		DDX_Text(pDX, IDC_0204_OMC_SMS_DATE, cdt7); //用DDX_Text取代DDX_FieldText
		CString cs7 = (m_p0204ApplySet->m_dateOMCSMS).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("SMS上線日期(m_p0204ApplySet->m_dateOMCSMS)=%s\n", cs7);
	}
	if (m_p0204ApplySet->m_dateOMCBS == NULL) {
		//TRACE("BS啟動日期為空\n");
		DDX_Text(pDX, IDC_0204_OMC_BS_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt8 = (m_p0204ApplySet->m_dateOMCBS).GetTime();
		DDX_Text(pDX, IDC_0204_OMC_BS_DATE, cdt8); //用DDX_Text取代DDX_FieldText
		CString cs8 = (m_p0204ApplySet->m_dateOMCBS).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("BS啟動日期(m_p0204ApplySet->m_dateOMCBS)=%s\n", cs8);
	}
	TRACE("OMC建構人(m_p0204ApplySet->m_szOMCConstructor)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szOMCConstructor));
	DDX_Text(pDX, IDC_0204_OMC_CONSTRUCTOR, CStrW2CStrT(m_p0204ApplySet->m_szOMCConstructor));
	//DDX_FieldText(pDX, IDC_0204_OMC_CONSTRUCTOR, CStrW2CStrT(m_p0204ApplySet->m_szOMCConstructor), m_p0204ApplySet);
	TRACE("OMC審核人(m_p0204ApplySet->m_szOMCChecker)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szOMCChecker));
	DDX_Text(pDX, IDC_0204_OMC_CHECKER, CStrW2CStrT(m_p0204ApplySet->m_szOMCChecker));
	//DDX_FieldText(pDX, IDC_0204_OMC_CHECKER, CStrW2CStrT(m_p0204ApplySet->m_szOMCChecker), m_p0204ApplySet);
	//DDX_FieldText(pDX, IDC_0204_FINISH_DATE, m_p0204ApplySet->m_dateFinish, m_p0204ApplySet);
	if (m_p0204ApplySet->m_dateFinish == NULL) {
		//TRACE("完成日期為空\n");
		DDX_Text(pDX, IDC_0204_FINISH_DATE, nullString); //用DDX_Text取代DDX_FieldText
	}
	else {
		COleDateTime cdt9 = (m_p0204ApplySet->m_dateFinish).GetTime();
		DDX_Text(pDX, IDC_0204_FINISH_DATE, cdt9); //用DDX_Text取代DDX_FieldText
		CString cs9 = (m_p0204ApplySet->m_dateFinish).Format("'%Y-%m-%d %H:%M:%S'");
		//TRACE("完成日期(m_p0204ApplySet->m_dateFinish)=%s\n", cs9);
	}
	TRACE("備註(m_p0204ApplySet->m_szNote)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szNote));
	DDX_Text(pDX, IDC_0204_NOTE, CStrW2CStrT(m_p0204ApplySet->m_szNote));
	//DDX_FieldText(pDX, IDC_0204_NOTE, CStrW2CStrT(m_p0204ApplySet->m_szNote), m_p0204ApplySet);
}

//added by erif
CString list[13][2];// by JIA
int temp[40];//by JIA
void C0204View::UpdateArrayFromView()
{   
	CString a, b;
	if (temp[0] != 0)
	{
		a.Format("%d", temp[0]);
		int i = 1;
		while (temp[i] != 0)
		{
			b.Format("%d", temp[i]);
			a = a + "," + b;
			++i;
		};
		m_p0204ApplySet->m_szApplyContent = a;

	}
//異動事項 JIA 
	TRACE("!!!!!!!!!!!!!!C0204View::UpdateArrayFromView()------>\n");
	CEdit *pEdit;
	pEdit = (CEdit*)GetDlgItem(IDC_0204_STATUS);
	CString csContent;
	pEdit->GetWindowText(csContent);
	TRACE("建構狀態2(csContent=%s\n", CStrW2CStrT(m_p0204RecordSet->m_szStatus));
	m_p0204RecordSet->m_szStatus = _T((LPCTSTR &)csContent); //建構狀態
	TRACE("建構狀態3(csContent=%s\n", CStrW2CStrT(m_p0204RecordSet->m_szStatus));

	pEdit = (CEdit*)GetDlgItem(IDC_0204_PRELUDE);
	pEdit->GetWindowText(csContent);
	TRACE("前言2(csContent=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szPrelude));
	m_p0204ApplySet->m_szPrelude = _T((LPCTSTR &)csContent); //前言
	TRACE("前言3(csContent=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szPrelude));

	pEdit = (CEdit*)GetDlgItem(IDC_0204_NOTE);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szNote = _T((LPCTSTR &)csContent); //備註

	pEdit = (CEdit*)GetDlgItem(IDC_0204_NEWNUM);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szNewNumber = _T((LPCTSTR &)csContent); //新節目號碼

	pEdit = (CEdit*)GetDlgItem(IDC_0204_LICENSE);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szLicense = _T((LPCTSTR &)csContent); //經營者證號

	pEdit = (CEdit*)GetDlgItem(IDC_0204_APPLY_NUMBER);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szApplyNumber = _T((LPCTSTR &)csContent); //聯單編號


	pEdit = (CEdit*)GetDlgItem(IDC_0204_NAME);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szName = _T((LPCTSTR &)csContent); //節目名稱 by JIA

	pEdit = (CEdit*)GetDlgItem(IDC_0204_APPLY_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateApply = NULL;
	else
		m_p0204ApplySet->m_dateApply = Rpcs_Util::getMysqlTime(csContent); //申請日期 by JIA 

	pEdit = (CEdit*)GetDlgItem(IDC_0204_EXPECT_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateExpect = NULL;
	else
		m_p0204ApplySet->m_dateExpect = Rpcs_Util::getMysqlTime(csContent); //預定生效日期 by JIA 

	pEdit = (CEdit*)GetDlgItem(IDC_0204_FINISH_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateFinish = NULL;
	else
		m_p0204ApplySet->m_dateFinish = Rpcs_Util::getMysqlTime(csContent); //完成日期 by JIA 
														  
    pEdit = (CEdit*)GetDlgItem(IDC_0204_SORT);                              //節目類別 by JIA
	pEdit->GetWindowText(csContent);
	for (int i = 0; i <= 12; i++)                                           
	{ 
		if (list[i][0] == _T(csContent)) 
		m_p0204ApplySet->m_szSort = _T((LPCTSTR &)list[i][1]);
		
	}

	pEdit = (CEdit*)GetDlgItem(IDC_0204_PLACE);                    //受理單位 by JIA
    pEdit->GetWindowText(csContent);
	CString k;
	for (int i = 0; i <= 4; i++) {
		if (PLACE_FIELDNAME[i] == csContent)
		{
			k.Format(_T("%d"), PLACE_FIELDVALUE[i]);
			m_p0204ApplySet->m_szPlace = _T((LPCTSTR &)k);
		}
	}
    
	//if (PLACE_FIELDNAME[4] == csContent)
	

	pEdit = (CEdit*)GetDlgItem(IDC_0204_CALLBAR);                    //發話限制 by JIA
	pEdit->GetWindowText(csContent);
	CString j;
	for (int i = 0; i <= 2; i++) {
		if (CALLBAR_FIELDNAME[i] == csContent)
		{
			j.Format(_T("%d"), CALLBAR_FIELDVALUE[i]);
			m_p0204ApplySet->m_szCallbar = _T((LPCTSTR &)j);
		}
	}


	pEdit = (CEdit*)GetDlgItem(IDC_0204_INFO_PROVIDER);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szInfoProvider = _T((LPCTSTR &)csContent); //資訊提供者 by JIA

	pEdit = (CEdit*)GetDlgItem(IDC_0204_INFO_PHONE);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szInfoPhone = _T((LPCTSTR &)csContent); //資訊提供者連絡電話 by JIA


	CButton* radio_none = (CButton*)GetDlgItem(IDC_0204_OVERRIDE_NONE);
	CButton* radio_cht = (CButton*)GetDlgItem(IDC_0204_OVERRIDE_CHT);
	CButton* radio_customer = (CButton*)GetDlgItem(IDC_0204_OVERRIDE_CUSTOMER);
	CButton* radio_recede = (CButton*)GetDlgItem(IDC_0204_OVERRIDE_RECEDE);

	if (radio_none->GetCheck()) {
		m_p0204ApplySet->m_szOverride = "0";
	}
	if (radio_cht->GetCheck()) {
		m_p0204ApplySet->m_szOverride = "1";
	}
	if (radio_customer->GetCheck()) {
		m_p0204ApplySet->m_szOverride = "2";
	}
	if (radio_recede->GetCheck()) {
		m_p0204ApplySet->m_szOverride = "3";
	}
	TRACE("超載服務(m_p0204ApplySet->m_szOverride)=%s\n", CStrW2CStrT(m_p0204ApplySet->m_szOverride));

    
	CButton* check_reply= (CButton*)GetDlgItem(IDC_0204_REPLY);
	CButton* check_lock = (CButton*)GetDlgItem(IDC_0204_LOCK);
	if (check_reply->GetCheck())
		m_p0204ApplySet->m_szReply = "1";
	else
		m_p0204ApplySet->m_szReply = "0";

	if (check_lock->GetCheck())
		m_p0204ApplySet->m_szLock = "1";
	else
		m_p0204ApplySet->m_szLock = "0";

	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_TAKE_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateOMCTake = NULL;
	else
		m_p0204ApplySet->m_dateOMCTake = Rpcs_Util::getMysqlTime(csContent); //OMC受理日期 by JIA 

	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_DISP_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateOMCDisp = NULL;
	else
		m_p0204ApplySet->m_dateOMCDisp = Rpcs_Util::getMysqlTime(csContent); //OMC派工日期 by JIA */


	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_SMS_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateOMCSMS = NULL;
	else 
		m_p0204ApplySet->m_dateOMCSMS = Rpcs_Util::getMysqlTime(csContent); //SMS上線日期 by JIA */


	
	
	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_BS_DATE);
	pEdit->GetWindowText(csContent);
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateOMCBS = NULL;
	else
		m_p0204ApplySet->m_dateOMCBS = Rpcs_Util::getMysqlTime(csContent); //BS啟動日期 by JIA */
	
	
	pEdit = (CEdit*)GetDlgItem(IDC_0204_REPLY_DATE);
	pEdit->GetWindowText(csContent);
	//CString temp1 = csContent;

	//pEdit = (CEdit*)GetDlgItem(IDC_0204_REPLY_TIME);
	//pEdit->GetWindowText(csContent);
	//csContent = temp1 +" "+ csContent;

	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_dateReply = NULL;
	else
		m_p0204ApplySet->m_dateReply = Rpcs_Util::getMysqlTime(csContent); //回竣日期 by JIA 


	pEdit = (CEdit*)GetDlgItem(IDC_0204_REPLY_TIME);
	pEdit->GetWindowText(csContent);
	csContent = "10/11/2018 "+ csContent;
	if ((csContent == "") || (csContent == "NULL"))
		m_p0204ApplySet->m_timeReply = NULL;
	else
		m_p0204ApplySet->m_timeReply = Rpcs_Util::getMysqlTime(csContent); //回竣時間 by JIA 
	


	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_CONSTRUCTOR);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szOMCConstructor = _T((LPCTSTR &)csContent);//OMC建構人 by JIA

	pEdit = (CEdit*)GetDlgItem(IDC_0204_OMC_CHECKER);
	pEdit->GetWindowText(csContent);
	m_p0204ApplySet->m_szOMCChecker = _T((LPCTSTR &)csContent);//OMC審核人 by JIA
	UpdateData(FALSE);

	TRACE("aaa剛加入  %s\n", (m_p0204ApplySet->m_nChargeType));
	
	//實體號碼 by JIA
	if ((m_p0204ApplySet->m_szPlace == "92" || m_p0204ApplySet->m_szPlace == "9") && m_p0204ApplySet->m_szOverride == "0")
		m_p0204ApplySet->m_szDestination = "021224" + CStrW2CStrT(m_p0204RecordSet->m_szNumber).Right(5);

	if ((m_p0204ApplySet->m_szPlace == "92" || m_p0204ApplySet->m_szPlace == "9") && m_p0204ApplySet->m_szOverride == "1")
		m_p0204ApplySet->m_szDestination = "021294" + CStrW2CStrT(m_p0204RecordSet->m_szNumber).Right(5);

	if ((m_p0204ApplySet->m_szPlace == "92" || m_p0204ApplySet->m_szPlace == "9") && m_p0204ApplySet->m_szOverride == "2")
		m_p0204ApplySet->m_szDestination = "021204" + CStrW2CStrT(m_p0204RecordSet->m_szNumber).Right(5);

	if (m_p0204ApplySet->m_szPlace == "94")
		m_p0204ApplySet->m_szDestination = "021414" + CStrW2CStrT(m_p0204RecordSet->m_szNumber).Right(5);

	if (m_p0204ApplySet->m_szPlace == "97")
		m_p0204ApplySet->m_szDestination = "021714" + CStrW2CStrT(m_p0204RecordSet->m_szNumber).Right(5);



}

//added by erif
void C0204View::ReloadViewFromDB()
{
	TRACE("!!!!!!!!!!!!!!C0204View::ReloadViewFromDB()------>\n");



}

BOOL C0204View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void C0204View::OnInitialUpdate() 
{
	TRACE(_T("C0204View::OnInitialUpdate()----->\n"));
    CComboBox *pCombo;
    UINT nIndex;
    int nItem;

    SetDlgItemText(IDC_0204_QUERY_NUMBER, "0204-%");

    /////////////////////////////////////////////////////////////////////
    // Load bitmap
	TRACE(_T("Load bitmap\n"));
    for (nIndex=IDC_0204_APPLY_FIRST; nIndex<=IDC_0204_APPLY_LAST; nIndex++)
        ((CButton*)GetDlgItem(nIndex))->SetIcon(
            ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_TOOL_FIRST+nIndex-IDC_0204_APPLY_FIRST)));

    /////////////////////////////////////////////////////////////////////
    // Name and values into combo box
    typedef struct 
    {
        UINT    nID;
        int     nCount;
        LPCSTR *lpNames;
        int    *lpValues;
    } CC_STRUCT;

    static CC_STRUCT CC_PAIR[] =
    {
        { IDC_0204_CALLBAR, sizeof(CALLBAR_FIELDNAME)/sizeof(LPCSTR), CALLBAR_FIELDNAME, CALLBAR_FIELDVALUE },
        { IDC_0204_PLACE, sizeof(PLACE_FIELDNAME)/sizeof(LPCSTR), PLACE_FIELDNAME, PLACE_FIELDVALUE }
    };

    for (nIndex=0; nIndex<(sizeof(CC_PAIR)/sizeof(CC_STRUCT)); nIndex++)
    {
        pCombo = (CComboBox*)GetDlgItem(CC_PAIR[nIndex].nID);
        ASSERT(pCombo != NULL);
        for (int i=0; i<CC_PAIR[nIndex].nCount; i++)
        {
            nItem = pCombo->AddString(CC_PAIR[nIndex].lpNames[i]);
            ASSERT(nItem != CB_ERR);
            pCombo->SetItemData(nItem, CC_PAIR[nIndex].lpValues[i]);
        }
        pCombo->SetCurSel(0);
    }

    // Load database data into control
    CRecordset rs(&GetDocument()->m_hDatabase);
	//CRecordset *rs;
	//rs= new CRecordset(&GetDocument()->m_hDatabase);
	CDBVariant varName2, varNum2;
	//CString temp1, temp2;
    try
    {
        /////////////////////////////////////////////////////////////////////
        // Modify name into check listbox
        CString szSQL;
        szSQL.Format("Select * From [%s]", TABLE_0204_CONTENT);
		TRACE("szSQL=%s\n", szSQL);
        rs.Open(CRecordset::snapshot, szSQL);
        if (rs.IsOpen())
        { 
            CListCtrl *pListCtrl = static_cast<CListCtrl*>(GetDlgItem(IDC_0204_APPLY_CONTENT));
            ASSERT(pListCtrl != NULL);
            pListCtrl->SetExtendedStyle(pListCtrl->GetExtendedStyle()|LVS_EX_CHECKBOXES);
            while (!rs.IsEOF())
            {
				rs.GetFieldValue(_T("異動事項"), varName2);
				rs.GetFieldValue(_T("代碼"), varNum2);
				if ((varName2.m_dwType == DBVT_WSTRING) && (varNum2.m_dwType == DBVT_WSTRING))
				{
					CString temp1, temp2;
					temp1 = *varName2.m_pstringW;
					temp2 = *varNum2.m_pstringW;
					TRACE("temp1=%s\n", temp1);
					TRACE("temp2=%s\n", temp2);
					nItem = pListCtrl->InsertItem(0, (LPCTSTR)temp1);
					TRACE("nItem=%d\n", nItem);
					ASSERT(nItem != -1);
					ASSERT(atol((LPCTSTR)temp2) != 0);
					pListCtrl->SetItemData(nItem, atol((LPCTSTR)temp2));

				}
                rs.MoveNext();
            }
            rs.Close();
        }
		TRACE(_T("------\n"));
        /////////////////////////////////////////////////////////////////////
        // Misc data into combo box
        typedef struct
        {
            UINT   nID;
            LPCSTR szTable;
        } DC_STRUCT;
        static DC_STRUCT DC_PAIR[] =
        {
            { IDC_0204_STATUS,          TABLE_0204_STATUS     },
            { IDC_0204_SORT,            TABLE_0204_SORT       },
            { IDC_0204_OMC_CONSTRUCTOR, TABLE_OMC_CONSTRUCTOR },
            { IDC_0204_OMC_CHECKER,     TABLE_OMC_CHECKER     },
            { IDC_0204_NOTE,            TABLE_NOTE            },
            { IDC_0204_QUERY_STATUS,      TABLE_0204_STATUS     },
            { IDC_0204_QUERY_CONSTRUCTOR, TABLE_OMC_CONSTRUCTOR },
            { IDC_0204_QUERY_CHECKER,     TABLE_OMC_CHECKER     }
        };
		//TRACE("(sizeof(DC_PAIR)/sizeof(DC_STRUCT))=%u\n", (sizeof(DC_PAIR) / sizeof(DC_STRUCT)));
        for (nIndex=0; nIndex<(sizeof(DC_PAIR)/sizeof(DC_STRUCT)); nIndex++)
        {
			//TRACE("nIndex=%d\n", nIndex);
            CString szSQL;
			//TRACE("DC_PAIR[nIndex].szTable=%s\n", DC_PAIR[nIndex].szTable);
            szSQL.Format("Select * From [%s]", DC_PAIR[nIndex].szTable);
            rs.Open(CRecordset::snapshot, szSQL);
			//TRACE("szSQL=%s\n", szSQL);
            if (rs.IsOpen())
            { 
                pCombo = (CComboBox*)GetDlgItem(DC_PAIR[nIndex].nID);
				//TRACE("DC_PAIR[nIndex].nID=%d\n", DC_PAIR[nIndex].nID);
                ASSERT(pCombo != NULL);
				int i = 0;//by JIA
                while (!rs.IsEOF())
                {
                    // special case 
                    if (DC_PAIR[nIndex].nID == IDC_0204_SORT)
                    {
						//TRACE("DC_PAIR[nIndex].nID == IDC_0204_SORT\n");
                        rs.GetFieldValue(_T("節目類別"), varName2);
                        rs.GetFieldValue(_T("代碼"), varNum2);
						//TRACE("varName2.m_dwType=%d\n", varName2.m_dwType);
						//TRACE("varNum2.m_dwType=%d\n", varNum2.m_dwType);
						if ((varName2.m_dwType == DBVT_WSTRING) && (varNum2.m_dwType == DBVT_WSTRING))
						{
							CString temp1, temp2;
							temp1 = *varName2.m_pstringW;
							temp2 = *varNum2.m_pstringW;
							list[i][0] = temp1;//by JIA
							list[i][1] = temp2;//by JIA
							i++;               //by JIA
							//TRACE("varName2s=%s\n", temp1);
							//TRACE("varNum2=%s\n", temp2);

							nItem = pCombo->AddString((LPCTSTR)temp1);
							ASSERT(nItem != CB_ERR);
							ASSERT(((LPCTSTR)temp2)[1] == '\0'); // must be exactly one char
							pCombo->SetItemData(nItem, ((LPCTSTR)temp2)[0]);
						}
						
                    }
                    else
                    {
						//TRACE("else\n");

                        rs.GetFieldValue((short)0, varName2);
                        if (varName2.m_dwType == DBVT_WSTRING){
							CString temp1;
							temp1 = *varName2.m_pstringW;
							//TRACE("varName2s=%s\n", temp1);
							pCombo->AddString((LPCTSTR)temp1);
						}
                    }
                    rs.MoveNext();
                }

                // Hack: last byte is droplist style
				if ((pCombo->GetStyle() & 0xF) == CBS_DROPDOWNLIST) {
					//TRACE("CBS_DROPDOWNLIST\n");
					pCombo->SetCurSel(0);
				}
                rs.Close();
            }
        }
    }
    catch (CException *e)
    {
		TRACE("exception!!!!!\n");
		TCHAR   szCause[255];
		CString strFormatted;

		e->GetErrorMessage(szCause, 255);

		strFormatted = _T("Error: ");
		strFormatted += szCause;
		AfxMessageBox(strFormatted, MB_OK | MB_ICONSTOP);
        //AfxMessageBox(e->m_pErrorInfo->m_strDescription, MB_OK|MB_ICONSTOP);
		//AfxMessageBox(e->GetErrorMessage, MB_OK | MB_ICONSTOP);
        e->Delete();
        if (rs.IsOpen())
            rs.Close();
        return;
    }
	TRACE("55555\n");
	m_p0204RecordSet = &GetDocument()->m_h0204RecordSet;
    m_p0204ApplySet  = &GetDocument()->m_h0204ApplySet;
	TRACE("66666\n");
    GetDocument()->OnRecordMove(ID_RECORD_LAST);
	TRACE("77777\n");
	CFormView::OnInitialUpdate();
	TRACE("77777222222\n");
    CSetting *pSetting = AfxGetSetting();
    if (pSetting->m_nVersion == VERSION_OMC)
    {
        if (pSetting->m_nDevice == DEVICE_CLIENT)
        {
            static UINT omcCheck[] = {
                IDC_0204_REPLY, IDC_0204_LOCK
            };
            static UINT omcRadio[] = {
                IDC_0204_ONETIME,      IDC_0204_ONEMIN,            IDC_0204_OVERRIDE_NONE,
                IDC_0204_OVERRIDE_CHT, IDC_0204_OVERRIDE_CUSTOMER, IDC_0204_OVERRIDE_RECEDE
            };
            static UINT omcControl[] = {
                IDC_0204_NEWNUM,          IDC_0204_LICENSE,            IDC_0204_APPLY_NUMBER, 
                IDC_0204_APPLY_DATE,      IDC_0204_EXPECT_DATE,        IDC_0204_NAME,
                IDC_0204_INFO_PROVIDER,   IDC_0204_INFO_PHONE,         IDC_0204_CHARGE,
                IDC_0204_PRELUDE,         IDC_0204_OMC_TAKE_DATE,      IDC_0204_OMC_DISP_DATE,
                IDC_0204_REPLY_DATE,      IDC_0204_REPLY_TIME,         IDC_0204_PLACE,
                IDC_0204_APPLY_CONTENT,   IDC_0204_CALLBAR,            IDC_0204_SORT,
                IDC_0204_REPLY_BTN,       IDC_0204_OMC_TAKE_BTN,       IDC_0204_OMC_DISP_BTN,
                IDC_0204_OMC_CONSTRUCTOR, IDC_0204_OMC_CHECKER
            };

            for (nItem=0; nItem<(sizeof(omcCheck)/sizeof(UINT)); nItem++)
                ((CButton*)GetDlgItem(omcCheck[nItem]))->SetButtonStyle(BS_CHECKBOX);
            for (nItem=0; nItem<(sizeof(omcRadio)/sizeof(UINT)); nItem++)
                ((CButton*)GetDlgItem(omcRadio[nItem]))->SetButtonStyle(BS_RADIOBUTTON);
            for (nItem=0; nItem<(sizeof(omcControl)/sizeof(UINT)); nItem++)
                GetDlgItem(omcControl[nItem])->EnableWindow(FALSE);
        }

        static UINT omcCommon[] = {
            IDC_0204_APPLY_NEW, IDC_0204_APPLY_DELETE
        };

        for (nItem=0; nItem<(sizeof(omcCommon)/sizeof(UINT)); nItem++)
            GetDlgItem(omcCommon[nItem])->EnableWindow(FALSE);
    }
    else
    {
    }
	TRACE("88888\n");

//  removed by erif 因會報錯,之後要記得打開測
	if((pSetting->m_nVersion==VERSION_OMC)&&(pSetting->m_nDevice==DEVICE_SERVER)&&(pSetting->m_nFTPVer==1))
    {
		int re;
		//re=m_ftps.GetPort ();
		//TRACE("m_ftps.GetPort ()=%f\n", re);
		//re=m_ftps.Listen (m_ftps.GetPort ());
		//TRACE("m_ftps.Listen ()=%f\n", re);
		UINT uResult = SetTimer(9998,					
								16000,                
								(TIMERPROC) PRSTranBMSPollingTimerProc);
		TRACE("rrr\n");
		uResult = SetTimer(9988,					
								120000,                
								(TIMERPROC) AutoUploadSCPPollingTimerProc);
		TRACE("ppp\n");
		//uResult = SetTimer(9988,					
		//						20000,                
		//						(TIMERPROC) AutoUploadSCPPollingTimerProc);
		
	}

	TRACE("99999\n");
}

void C0204View::OnDraw(CDC* pDC) 
{
    CRect rectTotal(CPoint(0, 0), GetTotalSize());
    CRect rectClient;
    GetClientRect(rectClient);
    if (rectTotal.right < rectClient.right)
        rectTotal.right = rectClient.right;
    if (rectTotal.bottom < rectClient.bottom)
        rectTotal.bottom = rectClient.bottom;
    m_hBackground.Draw(pDC, &rectTotal);
}

/////////////////////////////////////////////////////////////////////////////
// C0204View printing

BOOL C0204View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void C0204View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void C0204View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void C0204View::OnPrint(CDC* pDC, CPrintInfo*)
{
}

/////////////////////////////////////////////////////////////////////////////
// C0204View diagnostics

#ifdef _DEBUG
void C0204View::AssertValid() const
{
	CFormView::AssertValid();
}

void C0204View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

C0204Doc* C0204View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C0204Doc)));
	return (C0204Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// C0204View database support

CRecordset* C0204View::OnGetRecordset()
{
    ASSERT(m_p0204RecordSet != NULL);
	return m_p0204RecordSet;
}

/////////////////////////////////////////////////////////////////////////////
// C0204View window message handlers

int C0204View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    CSetting *pSetting = AfxGetSetting();

	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

    // create background
    if (m_hBackground.Create(this) == FALSE)
        return -1;

    switch (pSetting->m_nColorType)
    {

    case COLOR_DEFAULT:
        m_hBackground.SetEnable(FALSE);
        break;
    case COLOR_CUSTOM:
        m_hBackground.SetColor(pSetting->m_nColor0204);
        break;
    }
/*
    m_hBackground.LoadFromResource(IMAGE_BITMAP, IDB_BACKGROUND_BITMAP2);
    m_hBackground.SetStyle(STYLE_CASCADE);
*/
	
	return 0;
}

void C0204View::OnDestroy() 
{
	CSetting *pSetting = AfxGetSetting();
	if((pSetting->m_nVersion==VERSION_OMC)&&(pSetting->m_nDevice==DEVICE_SERVER)&&(pSetting->m_nFTPVer==1))
	{
	 //m_ftps.Quit (); //removed by erif 因會報錯,之後要記得打開測
	}
    m_hBackground.Destroy();
	CFormView::OnDestroy(); 
    
	
}

HBRUSH C0204View::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hBrush = m_hBackground.OnControlColor(pDC, pWnd, nCtlColor);
    if (hBrush == NULL)
        return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
    else
        return hBrush;
}

/////////////////////////////////////////////////////////////////////////////
// C0204View control message handlers
class listnode
{
private:
	int data;
	listnode *next;

public:


};//JIA



void C0204View::OnListCtrlItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
	 NM_LISTVIEW *pNMListView = (NM_LISTVIEW*)pNMHDR;

    BOOL bCheckedOld = pNMListView->uOldState & STATEIMAGE_CHECK,
         bCheckedNew = pNMListView->uNewState & STATEIMAGE_CHECK;

    if (bCheckedOld != bCheckedNew)
    {
		TRACE("NNNNNNNN\n");
		for(int i=0;i<30;i++)
		{ 
			temp[i] = 0;
		};
        GetDocument()->SetModifiedFlag();
        int nItem = pNMListView->iItem;
        ASSERT(nItem != -1);
        // always selected first
		m_hApplyContent.SetItemState(nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
        // if clear check then uncheck
        if (!bCheckedNew)
            m_hApplyContent.SetItemState(nItem, 0, LVIS_SELECTED|LVIS_FOCUSED);
        m_hApplyContent.SetItemData(nItem, MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK) );
		//TRACE("MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK)= %d\n", (MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK) - 536870912));

		int j = 0;//JIA 
		for (int i = 0; i < 22; i++) {

			if (m_hApplyContent.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED || m_hApplyContent.GetCheck(i))
			{
				TRACE("MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK)= %d\n", (MAKELONG(LOWORD(m_hApplyContent.GetItemData(i)), pNMListView->uNewState & STATEIMAGE_CHECK) - 536870912));
				if ((MAKELONG(LOWORD(m_hApplyContent.GetItemData(i)), pNMListView->uNewState & STATEIMAGE_CHECK) - 536870912)>0)
				{
					temp[j] = (MAKELONG(LOWORD(m_hApplyContent.GetItemData(i)), pNMListView->uNewState & STATEIMAGE_CHECK) - 536870912);
					j++;
				}
				else
				{
					temp[j] = MAKELONG(LOWORD(m_hApplyContent.GetItemData(i)), pNMListView->uNewState & STATEIMAGE_CHECK);
					j++;
				}
				
			}
		}//JIA 

		for (int i = 0; i < 5; i++)
		{
			TRACE("temp=%d\n", temp[i]);
		}


















		/*if (MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK) > 1000)
		{
			index++;
			temp[index] = MAKELONG(LOWORD(m_hApplyContent.GetItemData(nItem)), pNMListView->uNewState & STATEIMAGE_CHECK) - 536870912;
			
		}
		else
		{
			temp[index] = 0;
			index--;
		} // by JIA */

		m_hApplyContent.SortItems(SortFunc, (DWORD)&m_hApplyContent);

		TRACE("33333\n");

    }
}

void C0204View::OnControlClicked() 
{
    GetDocument()->SetModifiedFlag();
}

void C0204View::OnReplyBtnClicked() 
{
    COleDateTime today = COleDateTime::GetCurrentTime();
    SetDlgItemText(IDC_0204_REPLY_DATE, today.Format(VAR_DATEVALUEONLY));
    SetDlgItemText(IDC_0204_REPLY_TIME, today.Format(VAR_TIMEVALUEONLY));
}

/*
void C0204View::OnEnterIndex() 
{
    if (m_h0204RecordSet->IsOpen())
    {
        CMainFrame *pMainWnd = (CMainFrame*)AfxGetMainWnd();
        ASSERT(pMainWnd != NULL);

        int nIndex = pMainWnd->m_wndDlgBar.GetDlgItemInt(IDC_RECORD_INDEX);
        int nCount = m_h0204RecordSet->GetRecordCount();

        // same index then return
        if ((UINT)nIndex == m_nRecordIndex)
            return;

        // not first or last
        if ((nIndex > 1) && (nIndex < nCount))
        {
            // copy from CFormView
            if (m_h0204RecordSet->CanUpdate())
	        {
		        m_h0204RecordSet->Edit();
		        if (UpdateData())
                {
		            if (m_h0204RecordSet->IsFieldDirty(NULL))
			            m_h0204RecordSet->Update();
		            else
			            m_h0204RecordSet->CancelUpdate();
                }
                m_h0204RecordSet->Move(nIndex - m_nRecordIndex);
                m_nRecordIndex = nIndex;
                m_nStatus     |= AFX_DAOVIEW_SCROLL_BACKWARD|AFX_DAOVIEW_SCROLL_NEXT|AFX_DAOVIEW_SCROLL_LAST;
                UpdateData(FALSE);
	        }
        }
        else if (nIndex == 1)
            OnMove(ID_RECORD_FIRST);
        else if (nIndex == nCount)
            OnMove(ID_RECORD_LAST);
        else
            AfxMessageBox(IDS_ERROR_NORECORD, MB_OK|MB_ICONSTOP);

        UpdateCount();            
    }
}
*/

void C0204View::OnControlChange(UINT nID) 
{
    GetDocument()->SetModifiedFlag();
}

void C0204View::OnControlDataClicked(UINT nID) 
{
	
	if(nID==1011)
	{
		m_p0204RecordSet = &GetDocument()->m_h0204RecordSet;
		m_p0204ApplySet  = &GetDocument()->m_h0204ApplySet;
		if (m_p0204RecordSet->m_szStatus!="上線中")
		{
         AfxMessageBox("plan建構狀態為[上線中]，才能啟動BS回竣！");
		 return;
		}
		COleDateTime cdt1 = (m_p0204ApplySet->m_dateFinish).GetTime();
        if (cdt1.m_status==2)
		{
         AfxMessageBox("plan的[完成日期]未填，確認後才能啟動BS回竣！");
		 return;
		}
		COleDateTime cdt2 = (m_p0204ApplySet->m_dateOMCSMS).GetTime();
		if (cdt2.m_status==2)
		{
         AfxMessageBox("plan的[SMS上線日期]未填，確認後才能啟動BS回竣！");
		 return;
		}
		
		if(IDOK==AfxMessageBox("你確定要[啟動BS]並[回竣]?",MB_OKCANCEL,0))
		{
         OnReplyBtnClicked();
		 CPRSApp  *pApp =  (CPRSApp *)AfxGetApp();
		 if(m_p0204ApplySet->m_szApplyNumber.Find('_')==-1)
		   pApp->PRSTranBMS(CStrW2CStrT(m_p0204ApplySet->m_szNumber), CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber));

		 //shyrong add,2001/05/10
			//帳務分列 處理

			CString str = m_p0204ApplySet->m_szApplyContent;
			if (str.Find("60")!=-1)
			{
			 COleDateTime pt1,pt4,pt5,pt6,pt7,pt8;
			 pt4=m_p0204ApplySet->m_dateOMCSMS.GetTime();
			 CTime t=CTime::GetCurrentTime();
			 CString date3 = t.Format(_T(" %Y/%m/%d"));
			 CString date4=  t.Format(_T("%H:%M:%S"));
			 pt8=m_p0204ApplySet->m_dateFinish.GetTime();
			 CString pt2,pt3;
			 pt1=m_p0204ApplySet->m_dateOMCDisp.GetTime();
			 pt2=m_p0204ApplySet->m_szOMCChecker;
			 pt3=m_p0204ApplySet->m_szOMCConstructor;
             //if(m_p0204ApplySet->m_szApplyNumber.Left(2)=="CP")
			//	 AfxMessageBox("此號碼為[一退一租],你已完成[退租]聯單,但尚有[新租]聯單須完成,完成後記得報竣!!");
            // if(m_p0204ApplySet->m_szApplyNumber.Left(2)=="NP")
			//	 AfxMessageBox("此號碼為[一退一租],你已完成[新租]聯單,但尚有[退租]聯單須完成,完成後記得報竣!!");
			 if(!m_p0204ApplySet->IsBOF())
			 {
			     m_p0204ApplySet->MovePrev();
				 if(CStrW2CStrT(m_p0204ApplySet->m_szApplyContent).Find("60")!=-1)
				 {
				  CString kk=m_p0204ApplySet->m_szApplyNumber;

				  m_p0204ApplySet->Edit();
                  m_p0204ApplySet->m_dateOMCDisp=pt1;
			      m_p0204ApplySet->m_szOMCChecker=pt2;
			      m_p0204ApplySet->m_szOMCConstructor=pt3;
				  m_p0204ApplySet->m_dateOMCSMS=pt4;
				  //m_p0204ApplySet->m_dateReply=pt5;
				  COleDateTime cdt1 = m_p0204ApplySet->m_dateReply.GetTime();
				  cdt1.ParseDateTime(date3, VAR_DATEVALUEONLY);
				  //m_p0204ApplySet->m_dateReply.ParseDateTime(date3, VAR_DATEVALUEONLY);
				  //m_p0204ApplySet->m_timeReply=pt6;
				  COleDateTime cdt2 = m_p0204ApplySet->m_timeReply.GetTime();
				  cdt2.ParseDateTime(date4, VAR_TIMEVALUEONLY);
				  //m_p0204ApplySet->m_timeReply.ParseDateTime(date4, VAR_TIMEVALUEONLY);
				  //m_p0204ApplySet->m_dateOMCBS=pt7;
				  COleDateTime cdt3 = m_p0204ApplySet->m_dateOMCBS.GetTime();
				  cdt3.ParseDateTime(date3, VAR_DATEVALUEONLY);
				  //m_p0204ApplySet->m_dateOMCBS.ParseDateTime(date3, VAR_DATEVALUEONLY);
				  m_p0204ApplySet->m_dateFinish=pt8;
				  m_p0204ApplySet->Update();
				  if(m_p0204ApplySet->m_szApplyNumber.Find('_')==-1)
		             pApp->PRSTranBMS(CStrW2CStrT(m_p0204ApplySet->m_szNumber),kk);
				 }
				 m_p0204ApplySet->MoveNext();
			 }
			}

		}
		else
			return;
         

	}
    COleDateTime today = COleDateTime::GetCurrentTime();
    // this really need tricks
    CWnd *pWnd = GetDlgItem(IDC_0204_EDIT_BEGIN + nID - IDC_0204_BUTTON_BEGIN);
    ASSERT(pWnd != NULL);
    pWnd->SetWindowText(today.Format(VAR_DATEVALUEONLY));
	if(nID==1011)
	{
	  
      //UpdateData(FALSE);
      GetDocument()->OnSaveDocument(NULL);
	  m_p0204RecordSet->Edit();
	  m_p0204RecordSet->m_szStatus="竣工";
	  m_p0204RecordSet->Update();
	  UpdateData(FALSE);
	}
}

void C0204View::OnControlButtonClicked(UINT nID)
{
    UINT nStyle = ((CButton*)GetDlgItem(nID))->GetButtonStyle();
    if ((nStyle != BS_RADIOBUTTON) && (nStyle != BS_CHECKBOX))
        GetDocument()->SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////
// C0204View command message handlers

void C0204View::OnAsesUpload() 
{
	ASESUpload	dlg;
	dlg.m_str0204num=m_p0204RecordSet->m_szNumber;
	dlg.m_p0204RecordSet=m_p0204RecordSet;
	dlg.m_p0204ApplySet=m_p0204ApplySet;
	dlg.DoModal();
//	m_p0204RecordSet->Requery();
//	m_p0204RecordSet->Close();
//	m_p0204RecordSet->Open();
	//	UpdateData(FALSE);
	//C0204Doc *p_Doc=GetDocument();
	//p_Doc->UpdateAllViews(NULL);
}

void C0204View::OnAsesDownload() 
{
	ASESDownload	dlg;
	dlg.m_str0204num=m_p0204RecordSet->m_szNumber;
	dlg.DoModal();
	
}

void C0204View::OnUpdateAsesUpload(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(AfxGetSetting()->m_nVersion == VERSION_OMC);
}

void C0204View::OnUpdateAsesDownload(CCmdUI* pCmdUI) 
{
    OnUpdateAsesUpload(pCmdUI);
}

void C0204View::On0204Query1() 
{
#define TABLE_0204_TEMP     _T("0204暫存")
#define FIELD_0204_NUMBER   _T("號碼")
#define FIELD_0204_MAXAPPLY _T("最大次")

	TRACE("C0204View::On0204Query1()---->\n");
    C0204Doc *pDoc = GetDocument();

    if (pDoc->SaveModified())
    {
        UpdateData(FALSE);

        CString sql="", query="", subquery="", status, conter, checker;
        GetDlgItemText(IDC_0204_QUERY_STATUS, status);
        GetDlgItemText(IDC_0204_QUERY_CONSTRUCTOR, conter);
        GetDlgItemText(IDC_0204_QUERY_CHECKER, checker);

        if (!conter.IsEmpty())
            query.Format("[%s].[OMC建構人] = '%s'", TABLE_0204_APPLY, conter);

        if (!checker.IsEmpty())
        {
            if (!query.IsEmpty())
                query += " And ";
            subquery.Format("[%s].[OMC審核人] = '%s'", TABLE_0204_APPLY, checker);
            query += subquery;
        }

        // construct sub-table
        if (!query.IsEmpty())
        {
            ASSERT(pDoc->m_hDatabase.IsOpen());

            subquery.Format("DELETE FROM %s", TABLE_0204_TEMP);
            try {
                // always delete first and never care about if the table exists
                pDoc->m_hDatabase.ExecuteSQL(subquery);
            }
            catch (CException *e) {
                e->Delete();
            }

            subquery.Format("INSERT INTO %s SELECT %s.節目號碼, Max(次數) AS %s FROM %s GROUP BY 節目號碼",
                TABLE_0204_TEMP, TABLE_0204_APPLY, FIELD_0204_MAXAPPLY, TABLE_0204_APPLY);
            pDoc->m_hDatabase.ExecuteSQL(subquery);

            // finally
			TRACE("%s\n", query);
            subquery.Format("[0204號碼] In (Select [%s].[節目號碼] From [%s] Inner Join [%s] On [%s].[節目號碼] = [%s].[節目號碼] And [%s].[次數] = [%s].[%s] Where %s)",
                TABLE_0204_TEMP, TABLE_0204_TEMP, TABLE_0204_APPLY, TABLE_0204_APPLY, TABLE_0204_TEMP, TABLE_0204_APPLY, TABLE_0204_TEMP, FIELD_0204_MAXAPPLY, query);
			TRACE("[0204號碼] In (Select [%s].[節目號碼] From [%s] Inner Join [%s] On [%s].[節目號碼] = [%s].[節目號碼] And [%s].[次數] = [%s].[%s] Where %s)",
				TABLE_0204_TEMP, TABLE_0204_TEMP, TABLE_0204_APPLY, TABLE_0204_APPLY, TABLE_0204_TEMP, TABLE_0204_APPLY, TABLE_0204_TEMP, FIELD_0204_MAXAPPLY, query);
            query = "";
			
        }

        if (!status.IsEmpty())
		{
            //shyrong Modify,2001/05/07
			if(status=="未竣工")
              query.Format("[建構狀態] <> '%s'", "竣工");
			else
              query.Format("[建構狀態] = '%s'", status);
		}

        if (!subquery.IsEmpty())
        {
            if (!query.IsEmpty())
                query += " And ";
            query += subquery;
        }

        sql.Format("Select * From [%s]", TABLE_0204_DISPATCH);
		TRACE("C0204View::On0204Query1()--->sql=%s\n", sql);
        if (!query.IsEmpty())
            sql += " Where " + query;
		TRACE("%s", sql);
        pDoc->Query(sql);
        pDoc->OnRecordMove(ID_RECORD_LAST);
    }
}

void C0204View::On0204Query2() 
{
	TRACE("C0204View::On0204Query2()---->\n");
	/*CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	for(int  i=0;i<450;i++)
	{
     theApp->AutoASESUpload();
	 Sleep(1000);
	 if((100<i)&&(i<200))
		 Sleep(1000);
	 if((200<i)&&(i<300))
		 Sleep(1500);
	 if((300<i)&&(i<400))
		 Sleep(2000);
	 if(i>400)
		 Sleep(1000);

	}*/
	/*CString strText;
	strText=" i want test #";
	char test[128];
	strcpy(test, strText);
	strText="";
	strText=test;*/
    //strcpy(strText, test);
	//return;
    C0204Doc *pDoc = GetDocument();

    if (pDoc->SaveModified())
    {
        UpdateData(FALSE);

        CString sql="", query="", subquery="", number, appnum;
        GetDlgItemText(IDC_0204_QUERY_NUMBER, number);
        GetDlgItemText(IDC_0204_QUERY_APPLYNUMBER, appnum);

        if (!number.IsEmpty())
            query.Format("[0204號碼] Like \"%s\"", number);

        if (!appnum.IsEmpty())
        {
            if (!query.IsEmpty())
                query += " AND ";
            subquery.Format("[0204號碼] In (Select [節目號碼] From %s Where [聯單編號] = '%s' Group By [節目號碼])", TABLE_0204_APPLY, appnum);
            query += subquery;
        }

        sql.Format("Select * From [%s]", TABLE_0204_DISPATCH);
        if (!query.IsEmpty())
            sql += " Where " + query;
		TRACE("sql=%s\n", sql);
        pDoc->Query(sql);
        pDoc->OnRecordMove(ID_RECORD_LAST);

        if (!appnum.IsEmpty())
        {
            ASSERT(m_p0204RecordSet->GetRecordCount() == 1);
            LockWindowUpdate();
            while (TRUE)
            {
                if (CStrW2CStrT(m_p0204ApplySet->m_szApplyNumber) == appnum)
                    break;
                else if (pDoc->GetApplyIndex() == 1)
                    break;
                pDoc->OnApplyMove(IDC_0204_APPLY_PREV);
            }
            UnlockWindowUpdate();
            Invalidate(NULL);
        }
    }
}


BEGIN_EVENTSINK_MAP(C0204View, CFormView)
    //{{AFX_EVENTSINK_MAP(C0204View)
//	ON_EVENT(C0204View, IDC_FTPSERVER, 1 /* OnAccept */, OnAcceptFtpserver, VTS_NONE)
//	ON_EVENT(C0204View, IDC_FTPSERVER, 6 /* OnList */, OnListFtpserver, VTS_PBSTR)
//	ON_EVENT(C0204View, IDC_FTPSERVER, 9 /* OnLogin */, OnLoginFtpserver, VTS_PI2 VTS_PBSTR VTS_PBSTR)
//	ON_EVENT(C0204View, IDC_FTPSERVER, 11 /* OnQuery */, OnQueryFtpserver, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void C0204View::OnAcceptFtpserver() 
{
	m_ftps.Accept ();
	
}

void C0204View::OnListFtpserver(BSTR FAR* UserName) 
{
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	// user listing
    CString Display(*UserName);
    theApp->profileDlg->m_userlist.AddString(Display);
	
}

void C0204View::OnLoginFtpserver(short FAR* Connection, BSTR FAR* UserName, BSTR FAR* IPAddress) 
{
	int i=m_ftps.GetSessions ()	;
	
}

void C0204View::OnQueryFtpserver() 
{
		CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	int count;

    // update information pertaining to user
    theApp->profileDlg->m_passwd.SetWindowText (m_ftps.GetPassword ());
    theApp->profileDlg->m_defaultdir.SetWindowText (m_ftps.GetDefaultDir ());
    if ((count = m_ftps.GetDirectoryCount ()) == 0) return;
    for (int i = 0; i < count; i++)
    {
        theApp->profileDlg->m_dir.AddString (m_ftps.GetDirectory(i));
        theApp->profileDlg->m_export.AddString (m_ftps.GetExportName(i));
        
        // keep copy of directory info for user
        theApp->profileDlg->DirInfo[i].Directory = m_ftps.GetDirectory(i);
        theApp->profileDlg->DirInfo[i].Export = m_ftps.GetExportName(i);
        theApp->profileDlg->DirInfo[i].Read = m_ftps.GetReadPermission(i);
        theApp->profileDlg->DirInfo[i].Write = m_ftps.GetWritePermission(i);
        theApp->profileDlg->DirInfo[i].List = m_ftps.GetListPermission(i);
        theApp->profileDlg->DirInfo[i].Del = m_ftps.GetDeletePermission(i);
    }

    // update number of directories for user
    theApp->profileDlg->DirIndex = count;

    // update information related to first directory entry of first user
    theApp->profileDlg->m_dir.SetCurSel (0);
    theApp->profileDlg->m_export.SetCurSel (0);
    theApp->profileDlg->m_read.SetCheck (m_ftps.GetReadPermission (0));
    theApp->profileDlg->m_write.SetCheck (m_ftps.GetWritePermission (0));
    theApp->profileDlg->m_list.SetCheck (m_ftps.GetListPermission (0));
    theApp->profileDlg->m_delete.SetCheck (m_ftps.GetDeletePermission (0));
	
}

void C0204View::OnActionProfile() 
{
	CSetting *pSetting = AfxGetSetting();
	if((pSetting->m_nVersion==VERSION_CSC)||(pSetting->m_nDevice==DEVICE_CLIENT))
	{
      AfxMessageBox("無此權限執行此功能!!");
	  return;
	}
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
   // int re;
  // re=m_ftps.GetPort ();
//	re=m_ftps.Listen (m_ftps.GetPort ());
	theApp->profileDlg = new CFtpsProfile (this);
    theApp->profileDlg->DoModal();
    delete theApp->profileDlg;
	
}
void C0204View::OnSessionAction()
{
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	int re;
  m_ftp.SetPassive (FALSE);
  re=m_ftp.Connect ("10.144.27.65", "guest", "guest", 
                "");
  CString Dir = m_ftp.GetCurrentDir();
  re=m_ftp.ChangeDir("test");
  re=m_ftp.FileMode();
  re=m_ftp.PutFile("config.txt","config3.txt");
  if ((m_ftp.GetLastResult()) == FTP_OK)
        {
            CString Message = "File transferred successfully";
			AfxMessageBox(Message);
            //MessageBox(Message, "FTP Client Sample", MB_OK | MB_ICONASTERISK);  
        }
        else
        {
            CString Message = "Unable to transfer file";
			CString filename="Prs_serverlog.txt";
			FILE *file;
			CTime t = CTime::GetCurrentTime();
			CString temp   =t.Format("%Y/%m/%d")+"-"+t.Format("%H:%M:%S");
			if( (file = fopen( filename, "a+" )) != NULL )
			{
					fputs("\n"+temp+" "+Message, file);	   
			}
			CreateDirectory("\\", NULL);
			fclose(file);
			//AfxMessageBox(Message);
            //MessageBox(Message, "FTP Client Sample", MB_OK | MB_ICONASTERISK);  
        }
  m_ftp.Disconnect();
}

void C0204View::OnFtpSet() 
{
	CSetting *pSetting = AfxGetSetting();
	if((pSetting->m_nVersion==VERSION_CSC)||(pSetting->m_nDevice==DEVICE_CLIENT))
	{
      AfxMessageBox("無此權限執行此功能!!");
	  return;
	}
	FTPSetting dlg;
	dlg.DoModal();
	
}

void CALLBACK EXPORT C0204View::PRSTranBMSPollingTimerProc(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
)
{
	CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
//	C0204View *pView = (C0204View *) GetDocument()->GetActiveView();
		theApp->OnSessionAction();
	

}

void CALLBACK EXPORT C0204View::AutoUploadSCPPollingTimerProc(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
)
{
	/*CPRSApp  *theApp =  (CPRSApp *)AfxGetApp();
	theApp->AutoASESUpload();
	*/ //JIA碼掉
}
