// MathcoLoanDoc.cpp : implementation of the CMathcoLoanDoc class
//

#include "stdafx.h"
#include "MathcoLoan.h"

#include "MathcoLoanDoc.h"
#include "MathcoLoanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanDoc

IMPLEMENT_SERIAL(CMathcoLoanDoc, CDocument, VERSIONABLE_SCHEMA | 2)

BEGIN_MESSAGE_MAP(CMathcoLoanDoc, CDocument)
	//{{AFX_MSG_MAP(CMathcoLoanDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanDoc construction/destruction

CMathcoLoanDoc::CMathcoLoanDoc()
{
	// TODO: add one-time construction code here

}

CMathcoLoanDoc::~CMathcoLoanDoc()
{
}

BOOL CMathcoLoanDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_SolveFor = 0;
	m_strAmount = TEXT("0");
	m_strPer = TEXT("0");
	m_strRate = TEXT("0");
	m_strPmnt = TEXT("0");
	m_iPerType = 0;
	//default the calc object values
	m_fAmnt = 0;
	m_fPmnt = 0;
	m_fRate = 0;
	m_iPer = 0;
	//Default Amount Dialog Values
	m_strTotal = TEXT("0");
	m_strTax = TEXT("0");
	m_strDown = TEXT("0");
	m_strTaxAmount = TEXT("0");
	m_fPurchAmount = 0;
	m_fTaxAmount = 0;
	m_fTaxRate = 0;

	SetModifiedFlag(FALSE);

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanDoc serialization

void CMathcoLoanDoc::Serialize(CArchive& ar)
{
	//pView->m_AmountDlg->Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_strAmount;
		ar << m_strPer;
		ar << m_strRate;
		ar << m_strPmnt;
		ar << m_SolveFor;
		ar << m_iPerType;
		ar << m_fAmnt;
		ar << m_fPmnt;
		ar << m_fRate;
		ar << m_iPer;
		ar << m_strTotal;
		ar << m_strTax;
		ar << m_strDown;
		ar << m_strTaxAmount;
		ar << m_fPurchAmount;
		ar << m_fTaxAmount;
		ar << m_fTaxRate;
		
	}
	else
	{
		ar >> m_strAmount;
		ar >> m_strPer;
		ar >> m_strRate;
		ar >> m_strPmnt;
		ar >> m_SolveFor;
		ar >> m_iPerType;
		ar >> m_fAmnt;
		ar >> m_fPmnt;
		ar >> m_fRate;
		ar >> m_iPer;
		ar >> m_strTotal;
		ar >> m_strTax;
		ar >> m_strDown;
		ar >> m_strTaxAmount;
		ar >> m_fPurchAmount;
		ar >> m_fTaxAmount;
		ar >> m_fTaxRate;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanDoc diagnostics

#ifdef _DEBUG
void CMathcoLoanDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMathcoLoanDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanDoc commands
