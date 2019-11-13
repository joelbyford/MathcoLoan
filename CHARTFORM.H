#if !defined(AFX_CHARTFORM_H__9B7366A3_ACCB_47F4_8849_7702C4E48A6D__INCLUDED_)
#define AFX_CHARTFORM_H__9B7366A3_ACCB_47F4_8849_7702C4E48A6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "LineGraph.h"

// ChartForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartForm dialog

class CChartForm : public CDialog
{
// Construction
public:
	CChartForm(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CChartForm)
	enum { IDD = IDD_CHART };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartForm)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CLineGraph m_LineGraph;
	CArray<int, int> m_Columns;
	CArray<CString, CString> m_strColumns;
	COLORREF m_LineColors[10];
	CString m_strGraphLabel;
	CString m_strXAxisLabel;
	CString m_strYAxisLabel;
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartForm)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTFORM_H__9B7366A3_ACCB_47F4_8849_7702C4E48A6D__INCLUDED_)
