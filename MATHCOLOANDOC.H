// MathcoLoanDoc.h : interface of the CMathcoLoanDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHCOLOANDOC_H__78B1098C_2BFE_496F_8C9B_8828BFD2A46A__INCLUDED_)
#define AFX_MATHCOLOANDOC_H__78B1098C_2BFE_496F_8C9B_8828BFD2A46A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CMathcoLoanDoc : public CDocument
{
protected: // create from serialization only
	CMathcoLoanDoc();
	DECLARE_SERIAL(CMathcoLoanDoc)

// Attributes
public:
	CString m_strAmount;
	CString m_strPer;
	CString m_strRate;
	CString m_strPmnt;
	int m_SolveFor;
	int m_iPerType;

	//calc object values
	//double m_fBaloon;
	double m_fDown;
	double m_fAmnt;
	double m_fLoanAmnt;
	double m_fRate;
	double m_fTax;
	double m_fPmnt;
	UINT m_iPer;

	//Amount Dialog Values
	CString m_strTotal;
	CString m_strTax;
	CString m_strDown;
	CString	m_strTaxAmount;
	double m_fPurchAmount;
	double m_fTaxAmount;
	double m_fTaxRate;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoLoanDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathcoLoanDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathcoLoanDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCOLOANDOC_H__78B1098C_2BFE_496F_8C9B_8828BFD2A46A__INCLUDED_)
