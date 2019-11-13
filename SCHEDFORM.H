#if !defined(AFX_SCHEDFORM_H__A67BBCEF_DB19_4172_A1C1_A8CFF62116AD__INCLUDED_)
#define AFX_SCHEDFORM_H__A67BBCEF_DB19_4172_A1C1_A8CFF62116AD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SchedForm.h : header file
//
#include "PXLWriter.h"
#include "ChartForm.h"
#include "CeBtnST.h"

/////////////////////////////////////////////////////////////////////////////
// CSchedForm dialog

class CSchedForm : public CDialog
{
// Construction
public:
	double fPmnt;
	long iPer;
	double fAmount;
	double fRate;
	CSchedForm(CWnd* pParent = NULL);   // standard constructor
	BOOL BuildSched();
	BOOL BuildQtrPoint();
	CCeButtonST	m_btnExport;
	CCeButtonST	m_btnChart;

// Dialog Data
	//{{AFX_DATA(CSchedForm)
	enum { IDD = IDD_SCHED };
	CButton	m_edTotalBox;
	CComboBox	m_cmbType;
	CStatic	m_edTotal1;
	CStatic	m_edTotal2;
	CStatic	m_edTotal3;
	CStatic	m_edTotal4;
	CStatic	m_edTotal5;
	CStatic	m_edText1;
	CStatic	m_edText2;
	CStatic	m_edText3;
	CStatic	m_edText4;
	CStatic	m_edText5;
	CComboBox	m_cmbView;
	CStatic	m_edTotPay;
	CStatic	m_edTotInt;
	CListCtrl	m_lstSched;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSchedForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSchedForm)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendokCmbview();
	afx_msg void OnBtnExport();
	afx_msg void OnBtnChart();
	afx_msg void OnSelendokCmbtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPXLWriter *m_pPXL;
	CChartForm *m_pChartForm;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDFORM_H__A67BBCEF_DB19_4172_A1C1_A8CFF62116AD__INCLUDED_)
