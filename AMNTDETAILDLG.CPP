// AmntDetailDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "AmntDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmntDetailDlg dialog

CAmntDetailDlg::CAmntDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAmntDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAmntDetailDlg)
	m_strTotal = _T("");
	m_strAmount = _T("");
	m_strTax = _T("");
	m_strDown = _T("");
	m_strTaxAmount = _T("");
	//}}AFX_DATA_INIT
	m_fAmount = 0;
	m_fDown = 0;
	m_fTaxRate = 0;
	m_fTaxAmount = 0;

}


void CAmntDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmntDetailDlg)
	DDX_Control(pDX, IDC_TAX_AMT, m_staticTaxAmnt);
	DDX_Control(pDX, IDC_AMNT, m_edAmount);
	DDX_Control(pDX, IDC_TAX, m_edTax);
	DDX_Control(pDX, IDC_DWN, m_edDown);
	DDX_Text(pDX, IDC_TOTAL, m_strTotal);
	DDX_Text(pDX, IDC_AMNT, m_strAmount);
	DDX_Text(pDX, IDC_TAX, m_strTax);
	DDX_Text(pDX, IDC_DWN, m_strDown);
	DDX_Control(pDX, IDC_TOTAL, m_staticTotal);
	DDX_Text(pDX, IDC_TAX_AMT, m_strTaxAmount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmntDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CAmntDetailDlg)
	ON_EN_KILLFOCUS(IDC_AMNT, OnKillfocusAmnt)
	ON_EN_KILLFOCUS(IDC_DWN, OnKillfocusDwn)
	ON_EN_KILLFOCUS(IDC_TAX, OnKillfocusTax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAmntDetailDlg message handlers

void CAmntDetailDlg::OnKillfocusDwn() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	TCHAR szTmpString3[35];
	CString strTemp;
	
	//Reformat for the locale
	m_edDown.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();

	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString2, NULL, szTmpString3, 35);
	m_edDown.SetWindowText(CString(szTmpString3));
	//Save the formatted number
	m_strDown = CString(szTmpString3);

	//Recalculate the total
	m_fDown = wcstod(szTmpString2,  &szTrash);
	DisplayRecalc();

	return;
}

void CAmntDetailDlg::OnKillfocusTax() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	CString strTemp;
	
	//Reformat for the locale
	m_edTax.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();

	//GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString2, NULL, szTmpString3, 35);
	m_edTax.SetWindowText(CString(szTmpString2));
	//Save the formatted number
	m_strTax = CString(szTmpString2);

	//Recalculate the total
	m_fTaxRate = wcstod(szTmpString2,  &szTrash)/100;
	
	
	DisplayRecalc();

	return;
}
void CAmntDetailDlg::OnKillfocusAmnt() 
{
	TCHAR *szTrash;
	TCHAR *szTmpString;
	TCHAR szTmpString2[35];
	TCHAR szTmpString3[35];
	CString strTemp;
	
	//Reformat for the locale
	m_edAmount.GetWindowText(strTemp);
	szTmpString = strTemp.GetBuffer(0);
	//clean the floats
	cleanFloat(szTmpString, szTmpString2);
	strTemp.ReleaseBuffer();

	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString2, NULL, szTmpString3, 35);
	m_edAmount.SetWindowText(CString(szTmpString3));
	//Save the formatted number
	m_strAmount = CString(szTmpString3);

	//Recalculate the total
	m_fAmount = wcstod(szTmpString2,  &szTrash);
	DisplayRecalc();
}


//-----------------
// cleanFloat()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
void CAmntDetailDlg::cleanFloat(TCHAR szInput[], TCHAR szOutput[])
{
	int i, iStrSize;
	TCHAR szTemp[2];
	TCHAR szDecimal[2];
	TCHAR szValidChars[] = TEXT("1234567890");

	//find out what the decimal figure is for this locale
	GetLocaleInfo(GetUserDefaultLCID(), LOCALE_SDECIMAL, szDecimal, 2);

	//initialize the output buffer
	wcscpy(szOutput, TEXT(""));
	
	iStrSize = wcslen(szInput);
	for (i=0;i<iStrSize;i++)
	{
		if (wcschr(szValidChars, szInput[i]))
		{
			wsprintf(szTemp, TEXT("%c"), szInput[i]);
			wcscat(szOutput, szTemp);
		}
		else if(wcschr(szDecimal, szInput[i]))
		{
			wsprintf(szTemp, TEXT("."), szInput[i]);
			wcscat(szOutput, szTemp);
		}

	}
	return;
}

//-----------------
// cleanFloat()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
CString CAmntDetailDlg::cleanFloat(CString strInput)
{
	int i, iStrSize;
	CString strOutput;
	TCHAR szDecimal[2];
	TCHAR szValidChars[] = TEXT("1234567890");

	//find out what the decimal figure is for this locale
	GetLocaleInfo(GetUserDefaultLCID(), LOCALE_SDECIMAL, szDecimal, 2);

	iStrSize = strInput.GetLength();
	for (i=0;i<iStrSize;i++)
	{
		if (wcschr(szValidChars, strInput[i]))
		{
			strOutput += strInput[i];
		}
		else if(wcschr(szDecimal, strInput[i]))
		{
			strOutput += strInput[i];
		}

	}
	return (strOutput);
}

//-----------------
// cleanInt()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
void CAmntDetailDlg::cleanInt(TCHAR szInput[], TCHAR szOutput[])
{
	int i, iStrSize;
	TCHAR szTemp[2];
	TCHAR szValidChars[] = TEXT("1234567890");

	//initialize the output buffer
	wcscpy(szOutput, TEXT(""));
	
	iStrSize = wcslen(szInput);
	for (i=0;i<iStrSize;i++)
	{
		if (wcschr(szValidChars, szInput[i]))
		{
			wsprintf(szTemp, TEXT("%c"), szInput[i]);
			wcscat(szOutput, szTemp);
		}
	}
	return;
}

void CAmntDetailDlg::DisplayRecalc()
{
	CString oldStr;
	TCHAR newStr[35];
	TCHAR* szTmpString;

	//Recalc Tax amount
	m_fTaxAmount = m_fTaxRate * m_fAmount;

	//Display the tax amount
	oldStr.Format(TEXT("%f"), m_fTaxAmount);
	szTmpString = oldStr.GetBuffer(0);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szTmpString, NULL, newStr, 35);
	oldStr.ReleaseBuffer();
	m_strTaxAmount = CString(newStr);
	m_staticTaxAmnt.SetWindowText(m_strTaxAmount);

	//Recalc the total
	m_fTotal = m_fAmount - m_fDown + m_fTaxAmount;
	
	//Display the total amount
	oldStr.Format(TEXT("%f"), m_fTotal);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, oldStr, NULL, newStr, 35);
	m_staticTotal.SetWindowText(newStr);

	return;
}


void CAmntDetailDlg::ResetDetails(CString strAmount)
{
	TCHAR* szTrash;
	m_strDown.Empty();
	m_strTax.Empty();
	m_strTaxAmount = TEXT("0");
	m_fDown = 0;
	m_fTaxAmount = 0;
	m_fTaxRate = 0;

	m_strAmount = strAmount;
	m_strTotal = strAmount;
	m_fAmount = wcstod(cleanFloat(m_strAmount),  &szTrash);
	m_fTotal = m_fAmount;

}


