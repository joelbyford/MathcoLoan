// MathcoLoan.h : main header file for the MATHCOLOAN application
//

#if !defined(AFX_MATHCOLOAN_H__3257B53F_AC97_4F44_99DF_D974BD0E2DAA__INCLUDED_)
#define AFX_MATHCOLOAN_H__3257B53F_AC97_4F44_99DF_D974BD0E2DAA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMathcoLoanApp:
// See MathcoLoan.cpp for the implementation of this class
//

class CMathcoLoanApp : public CWinApp
{
public:
	CMathcoLoanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoLoanApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMathcoLoanApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCOLOAN_H__3257B53F_AC97_4F44_99DF_D974BD0E2DAA__INCLUDED_)
