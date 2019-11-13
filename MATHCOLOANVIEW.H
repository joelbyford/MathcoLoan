// MathcoLoanView.h : interface of the CMathcoLoanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHCOLOANVIEW_H__B9F34751_FB6C_4A74_A631_8A5D554A0147__INCLUDED_)
#define AFX_MATHCOLOANVIEW_H__B9F34751_FB6C_4A74_A631_8A5D554A0147__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "AmntDetailDlg.h"
#include "LoanCalcs.h"
#include "CeBtnST.h"


class CMathcoLoanView : public CFormView
{
protected: // create from serialization only
	CMathcoLoanView();
	DECLARE_SERIAL(CMathcoLoanView)

public:
	//{{AFX_DATA(CMathcoLoanView)
	enum { IDD = IDD_MATHCOLOAN_FORM };
	
	CComboBox	m_cmbPer;
	CEdit	m_edRate;
	CEdit	m_edPmnt;
	CEdit	m_edPer;
	CEdit	m_edAmount;
	//}}AFX_DATA
	CCeButtonST	m_btnPmnt;
	CCeButtonST	m_btnAmount;
	CCeButtonST	m_btnRate;
	CCeButtonST	m_btnPer;
	CCeButtonST	m_btnAmtDtl;
// Attributes
public:
	CMathcoLoanDoc* GetDocument();
	CLoanCalcs* m_pLoanObj;
	CAmntDetailDlg* m_AmountDlg;

	//CString m_strAmount;
	//CString m_strPer;
	//CString m_strRate;
	//CString m_strPmnt;
	//int m_iPerType;
	//int m_SolveFor;

private:
	void DisplayRecalc();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMathcoLoanView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMathcoLoanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMathcoLoanView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnBtnAmt();
	afx_msg void OnBtnPmt();
	afx_msg void OnKillfocusAmt();
	afx_msg void OnKillfocusPer();
	afx_msg void OnKillfocusPmt();
	afx_msg void OnKillfocusRate();
	afx_msg void OnChangeAmt();
	afx_msg void OnChangePer();
	afx_msg void OnChangePmt();
	afx_msg void OnChangeRate();
	afx_msg void OnChangeBln();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnBtnSchedule();
	afx_msg void OnBtnPer();
	afx_msg void OnBtnRate();
	afx_msg void OnSelendokCmbPer();
	afx_msg void OnBtnCalc();
	afx_msg void OnKillfocusDwn();
	afx_msg void OnKillfocusTax();
	afx_msg void OnAmtDtl();
	//}}AFX_MSG
	//afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	//afx_msg void OnSetFocus( CWnd* pOldWnd );
	//afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MathcoLoanView.cpp
inline CMathcoLoanDoc* CMathcoLoanView::GetDocument()
   { return (CMathcoLoanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATHCOLOANVIEW_H__B9F34751_FB6C_4A74_A631_8A5D554A0147__INCLUDED_)
