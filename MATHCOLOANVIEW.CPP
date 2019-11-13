// MathcoLoanView.cpp : implementation of the CMathcoLoanView class
//

#include "stdafx.h"
#include "MathcoLoan.h"

#include "SchedForm.h"
#include "MathcoLoanDoc.h"
#include "MathcoLoanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanView

IMPLEMENT_SERIAL(CMathcoLoanView, CFormView, VERSIONABLE_SCHEMA | 2)

BEGIN_MESSAGE_MAP(CMathcoLoanView, CFormView)
	//{{AFX_MSG_MAP(CMathcoLoanView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_AMT, OnBtnAmt)
	ON_BN_CLICKED(IDC_BTN_PMT, OnBtnPmt)
	ON_EN_KILLFOCUS(IDC_AMT, OnKillfocusAmt)
	ON_EN_KILLFOCUS(IDC_PER, OnKillfocusPer)
	ON_EN_KILLFOCUS(IDC_PMT, OnKillfocusPmt)
	ON_EN_KILLFOCUS(IDC_RATE, OnKillfocusRate)
	ON_EN_CHANGE(IDC_AMT, OnChangeAmt)
	ON_EN_CHANGE(IDC_PER, OnChangePer)
	ON_EN_CHANGE(IDC_PMT, OnChangePmt)
	ON_EN_CHANGE(IDC_RATE, OnChangeRate)
	ON_EN_CHANGE(IDC_BLN, OnChangeBln)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_BN_CLICKED(IDC_BTNSCHED, OnBtnSchedule)
	ON_BN_CLICKED(IDC_BTN_PER, OnBtnPer)
	ON_BN_CLICKED(IDC_BTN_RATE, OnBtnRate)
	ON_CBN_SELENDOK(IDC_CMB_PER, OnSelendokCmbPer)
	ON_BN_CLICKED(IDC_BTN_CALC, OnBtnCalc)
	ON_BN_CLICKED(IDC_AMT_DTL, OnAmtDtl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanView construction/destruction

CMathcoLoanView::CMathcoLoanView()
	: CFormView(CMathcoLoanView::IDD)
{
	//{{AFX_DATA_INIT(CMathcoLoanView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	m_pLoanObj = new CLoanCalcs();
	m_AmountDlg = new CAmntDetailDlg;

	//m_hWnd = AfxGetMainWnd()->m_hWnd;

}

CMathcoLoanView::~CMathcoLoanView()
{
	delete m_pLoanObj;
	delete m_AmountDlg;
}

void CMathcoLoanView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMathcoLoanView)
	DDX_Control(pDX, IDC_AMT_DTL, m_btnAmtDtl);
	DDX_Control(pDX, IDC_CMB_PER, m_cmbPer);
	DDX_Control(pDX, IDC_RATE, m_edRate);
	DDX_Control(pDX, IDC_PMT, m_edPmnt);
	DDX_Control(pDX, IDC_PER, m_edPer);
	DDX_Control(pDX, IDC_AMT, m_edAmount);
	DDX_Control(pDX, IDC_BTN_RATE, m_btnRate);
	DDX_Control(pDX, IDC_BTN_PER, m_btnPer);
	DDX_Control(pDX, IDC_BTN_PMT, m_btnPmnt);
	DDX_Control(pDX, IDC_BTN_AMT, m_btnAmount);
	//}}AFX_DATA_MAP
}

BOOL CMathcoLoanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanView diagnostics

#ifdef _DEBUG
void CMathcoLoanView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMathcoLoanView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMathcoLoanDoc* CMathcoLoanView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMathcoLoanDoc)));
	return (CMathcoLoanDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanView message handlers
int CMathcoLoanView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	int iResult = CFormView::OnCreate(lpCreateStruct);

	if(iResult == 0)
		//AfxGetMainWnd()->ShowDoneButton(TRUE);
		CWnd::ShowDoneButton(TRUE);
		
	return iResult;
}

void CMathcoLoanView::OnDestroy()
{
	//::SHSipPreference(m_hWnd, SIP_FORCEDOWN);
	CFormView::OnDestroy();
}



void CMathcoLoanView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	// Checkbox
	COLORREF	crBtnColor, crBtnColor2;
	
	//crBtnColor = ::GetSysColor(COLOR_BTNFACE) + RGB(30, 30, 30);
	crBtnColor = RGB(192, 192, 192);
	crBtnColor2 = RGB(255, 255, 255);

	m_btnAmount.SetFont(GetFont());
	m_btnAmount.SetIcon(IDI_LEDON, CSize(16, 16), IDI_LEDOFF, CSize(16, 16));
	m_btnAmount.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, crBtnColor2);
	m_btnAmount.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, crBtnColor2);
	m_btnAmount.DrawBorder(FALSE);
	m_btnAmount.SetAlign(CCeButtonST::ST_ALIGN_HORIZ_RIGHT);

	m_btnPmnt.SetFont(GetFont());
	m_btnPmnt.SetIcon(IDI_LEDON, CSize(16, 16), IDI_LEDOFF, CSize(16, 16));
	m_btnPmnt.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, crBtnColor2);
	m_btnPmnt.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, crBtnColor2);
	m_btnPmnt.DrawBorder(FALSE);
	m_btnPmnt.SetAlign(CCeButtonST::ST_ALIGN_HORIZ_RIGHT);

	m_btnRate.ShowWindow(SW_HIDE);
	m_btnRate.SetFont(GetFont());
	m_btnRate.SetIcon(IDI_LEDON, CSize(16, 16), IDI_LEDOFF, CSize(16, 16));
	m_btnRate.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, crBtnColor2);
	m_btnRate.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, crBtnColor2);
	m_btnRate.DrawBorder(FALSE);
	m_btnRate.SetAlign(CCeButtonST::ST_ALIGN_HORIZ_RIGHT);

	m_btnPer.ShowWindow(SW_HIDE);
	m_btnPer.SetFont(GetFont());
	m_btnPer.SetIcon(IDI_LEDON, CSize(16, 16), IDI_LEDOFF, CSize(16, 16));
	m_btnPer.SetColor(CCeButtonST::BTNST_COLOR_BK_IN, crBtnColor2);
	m_btnPer.SetColor(CCeButtonST::BTNST_COLOR_BK_OUT, crBtnColor2);
	m_btnPer.DrawBorder(FALSE);
	m_btnPer.SetAlign(CCeButtonST::ST_ALIGN_HORIZ_RIGHT);

	m_btnAmtDtl.SetIcon(IDI_MAG, CSize(16, 16));
	m_btnAmtDtl.SetFlat(FALSE);

	//Populate period options
	strTemp.LoadString(IDS_MONTHLY);
	m_cmbPer.AddString(strTemp);
	strTemp.LoadString(IDS_ANNUALY);
	m_cmbPer.AddString(strTemp);
	
	//Restore Data From Document
	m_cmbPer.SetCurSel(pDoc->m_iPerType);
	m_edAmount.SetWindowText(pDoc->m_strAmount);
	m_edPer.SetWindowText(pDoc->m_strPer);
	m_edRate.SetWindowText(pDoc->m_strRate);
	m_edPmnt.SetWindowText(pDoc->m_strPmnt);
	m_pLoanObj->m_fAmnt = pDoc->m_fAmnt;
	m_pLoanObj->m_fBaloon = 0;
	m_pLoanObj->m_fDown = pDoc->m_fDown;
	m_pLoanObj->m_fPmnt = pDoc->m_fPmnt;
	m_pLoanObj->m_fRate = pDoc->m_fRate;
	m_pLoanObj->m_fTax = pDoc->m_fTax;
	m_pLoanObj->m_iPer = pDoc->m_iPer;
	m_pLoanObj->m_iPerType = pDoc->m_iPerType;
	m_pLoanObj->m_SolveFor = pDoc->m_SolveFor;
	m_AmountDlg->m_strAmount = pDoc->m_strAmount;
	m_AmountDlg->m_strDown = pDoc->m_strDown;
	m_AmountDlg->m_strTax = pDoc->m_strTax;
	m_AmountDlg->m_strTaxAmount = pDoc->m_strTaxAmount;
	m_AmountDlg->m_strTotal = pDoc->m_strTotal;
	m_AmountDlg->m_fAmount = pDoc->m_fPurchAmount;
	m_AmountDlg->m_fDown = pDoc->m_fDown;
	m_AmountDlg->m_fTaxAmount = pDoc->m_fTaxAmount;
	m_AmountDlg->m_fTaxRate = pDoc->m_fTaxRate;
	m_AmountDlg->m_fTotal = pDoc->m_fAmnt;


	//Set Calculate Payment to on
	strTemp.LoadString(IDS_CALCULATE);

	switch (pDoc->m_SolveFor)
	{
	case enPayment:
		m_edPmnt.SetWindowText(strTemp);
		m_edPmnt.EnableWindow(FALSE);
		m_btnPmnt.SetCheck(BST_CHECKED);
		break;
	case enAmount:
		m_edAmount.SetWindowText(strTemp);
		m_edAmount.EnableWindow(FALSE);
		m_btnAmount.SetCheck(BST_CHECKED);
		break;
	case enRate:
		m_edRate.SetWindowText(strTemp);
		m_edRate.EnableWindow(FALSE);
		break;
	case enPeriod:
		m_edPer.SetWindowText(strTemp);
		m_edPer.EnableWindow(FALSE);
		break;
	}

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();


}

BOOL CMathcoLoanView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CMathcoLoanView::OnBtnAmt() 
{
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	m_pLoanObj->m_SolveFor = enAmount;
	pDoc->m_SolveFor = enAmount;
	strTemp.LoadString(IDS_CALCULATE);
	m_edAmount.SetWindowText(strTemp);
	//reactivate all others
	m_edAmount.EnableWindow(FALSE);
	m_edPmnt.EnableWindow(TRUE);
	m_edRate.EnableWindow(TRUE);
	m_edPer.EnableWindow(TRUE);
	//handle radio button like x boxes
	m_btnAmount.SetCheck(BST_CHECKED);
	m_btnPmnt.SetCheck(BST_UNCHECKED);
	m_btnRate.SetCheck(BST_UNCHECKED);
	m_btnPer.SetCheck(BST_UNCHECKED);
	//reset the details dialog
	m_AmountDlg->ResetDetails(CString(TEXT("")));
	m_btnAmtDtl.EnableWindow(FALSE);

	return;
	
}


void CMathcoLoanView::OnBtnPmt() 
{
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	m_pLoanObj->m_SolveFor = enPayment;
	pDoc->m_SolveFor = enPayment;
	strTemp.LoadString(IDS_CALCULATE);
	m_edPmnt.SetWindowText(strTemp);
	//reactivate all others
	m_edPmnt.EnableWindow(FALSE);
	m_edAmount.EnableWindow(TRUE);
	m_edRate.EnableWindow(TRUE);
	m_edPer.EnableWindow(TRUE);
	//handle radio button like x boxes
	m_btnPmnt.SetCheck(BST_CHECKED);
	m_btnAmount.SetCheck(BST_UNCHECKED);
	m_btnRate.SetCheck(BST_UNCHECKED);
	m_btnPer.SetCheck(BST_UNCHECKED);
	//reset the details dialog
	m_btnAmtDtl.EnableWindow(TRUE);

	return;	
}

void CMathcoLoanView::OnBtnPer() 
{
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();


	m_pLoanObj->m_SolveFor = enPeriod;
	pDoc->m_SolveFor = enPeriod;
	strTemp.LoadString(IDS_CALCULATE);
	m_edPer.SetWindowText(strTemp);
	//reactivate all others
	m_edPer.EnableWindow(FALSE);
	m_edAmount.EnableWindow(TRUE);
	m_edRate.EnableWindow(TRUE);
	m_edPmnt.EnableWindow(TRUE);
	//handle radio button like x boxes
	m_btnPmnt.SetCheck(BST_UNCHECKED);
	m_btnAmount.SetCheck(BST_UNCHECKED);
	m_btnRate.SetCheck(BST_UNCHECKED);
	m_btnPer.SetCheck(BST_CHECKED);
	//reset the details dialog
	m_btnAmtDtl.EnableWindow(TRUE);

	return;	
}
	

void CMathcoLoanView::OnBtnRate() 
{
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	m_pLoanObj->m_SolveFor = enRate;
	pDoc->m_SolveFor = enRate;
	strTemp.LoadString(IDS_CALCULATE);
	m_edRate.SetWindowText(strTemp);
	//reactivate all others
	m_edRate.EnableWindow(FALSE);
	m_edAmount.EnableWindow(TRUE);
	m_edPmnt.EnableWindow(TRUE);
	m_edPer.EnableWindow(TRUE);
	//handle radio button like x boxes
	m_btnPmnt.SetCheck(BST_UNCHECKED);
	m_btnAmount.SetCheck(BST_UNCHECKED);
	m_btnRate.SetCheck(BST_CHECKED);
	m_btnPer.SetCheck(BST_UNCHECKED);
	//reset the details dialog
	m_btnAmtDtl.EnableWindow(TRUE);

	return;	
	
}

void CMathcoLoanView::OnKillfocusAmt() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	TCHAR szTmpString3[35];
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	//Reformat for the locale
	m_edAmount.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	m_pLoanObj->cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();

	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString2, NULL, szTmpString3, 35);
	m_edAmount.SetWindowText(CString(szTmpString3));

	//Recalculate the loan
	//m_pLoanObj->cleanFloat(pDoc->m_strAmount.GetBuffer(0), szTmpString2);
	m_pLoanObj->m_fAmnt = wcstod(szTmpString2,  &szTrash);

	//Save the formatted number
	pDoc->m_strAmount = CString(szTmpString3);
	pDoc->m_fAmnt = m_pLoanObj->m_fAmnt;
	
	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();
	
	pDoc->SetModifiedFlag();

	return;
}



void CMathcoLoanView::OnKillfocusPer() 
{
	TCHAR *szTrash;
	CMathcoLoanDoc* pDoc = GetDocument();

	//Reformat for the locale
	m_edPer.GetWindowText(pDoc->m_strPer);

	//Recalculate the loan
	m_pLoanObj->m_iPer = wcstol(pDoc->m_strPer,  &szTrash, 10);
	pDoc->m_iPer = m_pLoanObj->m_iPer;

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();

	pDoc->SetModifiedFlag();	

	return;
}

void CMathcoLoanView::OnKillfocusPmt() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	TCHAR szTmpString3[35];
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	//Reformat for the locale
	m_edPmnt.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	m_pLoanObj->cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();

	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString2, NULL, szTmpString3, 35);
	m_edPmnt.SetWindowText(CString(szTmpString3));

	//Recalculate the loan
	//m_pLoanObj->cleanFloat(pDoc->m_strPmnt.GetBuffer(0), szTmpString2);
	m_pLoanObj->m_fPmnt = wcstod(szTmpString2,  &szTrash);
	//Save the formatted number
	pDoc->m_strPmnt = CString(szTmpString3);
	pDoc->m_fPmnt = m_pLoanObj->m_fPmnt;

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();

	pDoc->SetModifiedFlag();

	return;
}


void CMathcoLoanView::OnKillfocusRate() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	CString strTemp;
	CMathcoLoanDoc* pDoc = GetDocument();

	//Reformat for the locale
	m_edRate.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	m_pLoanObj->cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();


	m_edRate.SetWindowText(CString(szTmpString2));

	//Recalculate the loan
	m_pLoanObj->m_fRate = (wcstod(szTmpString2,  &szTrash)/100);

	//Save the formatted number
	pDoc->m_strRate = CString(szTmpString2);
	pDoc->m_fRate = m_pLoanObj->m_fRate;

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();
	
	pDoc->SetModifiedFlag();

	return;
}



void CMathcoLoanView::OnSelendokCmbPer() 
{
	CMathcoLoanDoc* pDoc = GetDocument();

	//Store the current selection
	pDoc->m_iPerType = m_cmbPer.GetCurSel();

	//Recalculate the loan
	m_pLoanObj->m_iPerType = pDoc->m_iPerType;

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();
	
	pDoc->SetModifiedFlag();

	return;

}
void CMathcoLoanView::DisplayRecalc()
{
	TCHAR szTemp[255];
	TCHAR szTemp2[35];
	CMathcoLoanDoc* pDoc = GetDocument();

	switch(pDoc->m_SolveFor)
	{
	case enPayment:
		wsprintf(szTemp, TEXT("%f"), m_pLoanObj->m_fPmnt);
		GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTemp, NULL, szTemp2, 35);
		pDoc->m_strPmnt = CString(szTemp2);
		pDoc->m_fPmnt = m_pLoanObj->m_fPmnt;
		m_edPmnt.SetWindowText(pDoc->m_strPmnt);
		break;
	case enAmount:
		wsprintf(szTemp, TEXT("%f"), m_pLoanObj->m_fAmnt);
		GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTemp, NULL, szTemp2, 35);
		pDoc->m_strAmount = CString(szTemp2);
		pDoc->m_fAmnt = m_pLoanObj->m_fAmnt;
		m_edAmount.SetWindowText(pDoc->m_strAmount);
		break;

	}
	return;
}

void CMathcoLoanView::OnChangeAmt() 
{
	

}

void CMathcoLoanView::OnChangePer() 
{
}

void CMathcoLoanView::OnChangePmt() 
{
}

void CMathcoLoanView::OnChangeRate() 
{
}


void CMathcoLoanView::OnChangeBln() 
{
}



void CMathcoLoanView::OnEditCopy() 
{
	CWnd * pGetFocus = (CWnd*)this->GetFocus();
	pGetFocus->SendMessage(WM_COPY);
}

void CMathcoLoanView::OnEditCut() 
{
	CWnd * pGetFocus = (CWnd*)this->GetFocus();
	pGetFocus->SendMessage(WM_CUT);
	
}

void CMathcoLoanView::OnEditPaste() 
{
	CWnd * pGetFocus = (CWnd*)this->GetFocus();
	pGetFocus->SendMessage(WM_PASTE);
}

void CMathcoLoanView::OnBtnSchedule() 
{
	CSchedForm frmSchedule;
	if (m_pLoanObj->recalcLoan())
	{
		frmSchedule.fAmount = m_pLoanObj->m_fAmnt - m_pLoanObj->m_fDown + (m_pLoanObj->m_fAmnt * m_pLoanObj->m_fTax);
		frmSchedule.fRate = m_pLoanObj->m_fRate;
		frmSchedule.fPmnt = m_pLoanObj->m_fPmnt;
		if (m_pLoanObj->m_iPerType == 0)
			frmSchedule.iPer = m_pLoanObj->m_iPer;
		else
			frmSchedule.iPer = m_pLoanObj->m_iPer*12;
		frmSchedule.DoModal();
	}
	
}






void CMathcoLoanView::OnBtnCalc() 
{

	if (m_pLoanObj->recalcLoan())
		DisplayRecalc();
	else
	{
		CString str;
		str.LoadString(IDS_ERR_MOREDATA);
		MessageBox(str);
	}
}





void CMathcoLoanView::OnAmtDtl() 
{
	TCHAR szTmpString2[35];
	TCHAR* szTrash;
	CMathcoLoanDoc* pDoc = GetDocument();

	//Set the default value if there isn't one already
	if(m_AmountDlg->m_strTotal.IsEmpty() || m_AmountDlg->m_strTotal.Compare(TEXT("0")) == 0)
	{
		m_AmountDlg->ResetDetails(pDoc->m_strAmount);
	}
	//display the dialog
	if (m_AmountDlg->DoModal() == IDOK)
	{
		m_edAmount.SetWindowText(m_AmountDlg->m_strTotal);
		
		//Save new values to the document
		pDoc->m_strAmount = m_AmountDlg->m_strAmount;
		pDoc->m_strDown = m_AmountDlg->m_strDown;
		pDoc->m_strTax = m_AmountDlg->m_strTax;
		pDoc->m_strTaxAmount = m_AmountDlg->m_strTaxAmount ;
		pDoc->m_strTotal = m_AmountDlg->m_strTotal;
		pDoc->m_fPurchAmount = m_AmountDlg->m_fAmount;
		pDoc->m_fDown = m_AmountDlg->m_fDown;
		pDoc->m_fTaxAmount = m_AmountDlg->m_fTaxAmount;
		pDoc->m_fTaxRate = m_AmountDlg->m_fTaxRate;
		pDoc->m_fAmnt = m_AmountDlg->m_fTotal;

		//Recalculate the loan
		//m_pLoanObj->cleanFloat(m_strAmount.GetBuffer(0), szTmpString2);
		//m_pLoanObj->m_fAmnt = wcstod(szTmpString2,  &szTrash);
		m_pLoanObj->m_fAmnt = m_AmountDlg->m_fTotal;
		if (m_pLoanObj->recalcLoan())
			DisplayRecalc();
		
		pDoc->SetModifiedFlag();

	}

}
