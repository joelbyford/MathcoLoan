// LoanCalcs.cpp: implementation of the CLoanCalcs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathcoLoan.h"
#include "LoanCalcs.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoanCalcs::CLoanCalcs()
{
	m_fAmnt = 0;
	m_fTax = 0;
	m_fDown = 0;
	m_fPmnt = 0;
	m_fRate = 0;
	m_iPer = 0;
	m_SolveFor = enPayment;
	m_iPerType=0;
}

CLoanCalcs::~CLoanCalcs()
{

}

//-----------------
// cleanFloat()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
void CLoanCalcs::cleanFloat(TCHAR szInput[], TCHAR szOutput[])
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
// cleanInt()
// ----------------
// Remove non-numeric values from a string (such as letters and special characters)
// and return the cleaned string. 
void CLoanCalcs::cleanInt(TCHAR szInput[], TCHAR szOutput[])
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

double CLoanCalcs::getPayment()
{
	long iMonths;
	//get the correct monthly pct rate
	double fMoRate = m_fRate/12;
	//calcualte the number of months
	if (m_iPerType == 0)
		iMonths = m_iPer;
	else
		iMonths = m_iPer*12;

	return((m_fLoanAmnt/((1-(1/pow((1+fMoRate),(float)iMonths)))/fMoRate)));
}

//Calculate rate
double CLoanCalcs::getRate()
{
	//figure this out someday
	return((double)0.0);
}


//Calculate loan amount if other factors are known
double CLoanCalcs::getAmount()
{
	long iMonths;
	//calcualte the number of months
	if (m_iPerType == 0)
		iMonths = m_iPer;
	else
		iMonths = m_iPer*12;

	//get the correct monthly pct rate
	double fMoRate = m_fRate/12;

	return((m_fPmnt*((1-(1/pow((1+fMoRate),(double)iMonths)))/fMoRate)));
}


BOOL CLoanCalcs::recalcLoan(double fAmnt, double fRate, UINT iPer, double fPmnt, SolveFor iSF)
{
	m_fAmnt = fAmnt;
	m_fRate = fRate;
	m_iPer = iPer;
	m_fPmnt = fPmnt;
	m_SolveFor = iSF;
	m_iPerType = 0;

	return recalcLoan();
}

BOOL CLoanCalcs::recalcLoan()
{
	//declared
	BOOL bRetVal= FALSE;
	int iReady=0;
	double fMoRate = 0;
	
	if(m_fRate !=0)
		iReady ++;

	if(m_fAmnt !=0)
		iReady ++;

	if(m_iPer !=0)
		iReady ++;

	if(m_fPmnt !=0)
		iReady ++;

	//solve if 3 or more vars available 
	if(iReady >2)
	{
		m_fLoanAmnt = m_fAmnt;

		if(m_fTax > 0)
		{
			m_fLoanAmnt += (m_fAmnt * m_fTax);
		}
		//solve for...
		switch (m_SolveFor)
		{
		case enPayment:
			//Adjust loan amount for down amount
			if (m_fDown > m_fAmnt)
				m_fDown = m_fAmnt;
			m_fLoanAmnt -= m_fDown;
			m_fPmnt = getPayment();
			break;
		case enAmount:
			m_fAmnt = getAmount();
			break;
		}
		bRetVal = TRUE;
	}
	else
		bRetVal = FALSE;
	
	return (bRetVal);
}