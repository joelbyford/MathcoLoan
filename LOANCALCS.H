// LoanCalcs.h: interface for the CLoanCalcs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOANCALCS_H__D396FAC5_40C2_4B12_9564_0465D56705A3__INCLUDED_)
#define AFX_LOANCALCS_H__D396FAC5_40C2_4B12_9564_0465D56705A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
enum SolveFor
{
	enPayment,
	enAmount,
	enRate,
	enPeriod
};

enum LoanType
{
	enCompMonth,
	enCompAnnual,
	enCompDay,
	enCompCMonth,
	enCompCAnnual,
	enCompCDay,
	enSimple
};

class CLoanCalcs  
{
public:
	HWND m_hWnd;
	double m_fBaloon;
	double m_fDown;
	double m_fAmnt;
	double m_fLoanAmnt;
	double m_fRate;
	double m_fTax;
	double m_fPmnt;
	int m_SolveFor;
	int m_iPerType;
	UINT m_iPer;
	void cleanInt(TCHAR szInput[], TCHAR szOutput[]);
	void cleanFloat(TCHAR szInput[], TCHAR szOutput[]);
	double getPayment();
	double getRate();
	double getAmount();
	BOOL recalcLoan(double fAmnt, double fRate, UINT iPer, double fPmnt, SolveFor iSF);
	BOOL recalcLoan();
	CLoanCalcs();
	virtual ~CLoanCalcs();

};



#endif // !defined(AFX_LOANCALCS_H__D396FAC5_40C2_4B12_9564_0465D56705A3__INCLUDED_)
