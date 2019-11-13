#if !defined(AFX_AMNTDETAILDLG_H__7DA52E8E_2C7A_4803_B842_3BF3E3465D42__INCLUDED_)
#define AFX_AMNTDETAILDLG_H__7DA52E8E_2C7A_4803_B842_3BF3E3465D42__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AmntDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAmntDetailDlg dialog

class CAmntDetailDlg : public CDialog
{
// Construction
public:
	void ResetDetails(CString strAmount);
	CAmntDetailDlg(CWnd* pParent = NULL);   // standard constructor
	double m_fTotal;
	double m_fAmount;
	double m_fDown;
	double m_fTaxRate;
	double m_fTaxAmount;
	

// Dialog Data
	//{{AFX_DATA(CAmntDetailDlg)
	enum { IDD = IDD_AMNT_DTL };
	CStatic	m_staticTaxAmnt;
	CEdit m_edAmount;
	CEdit m_edTax;
	CEdit m_edDown;
	CString m_strTotal;
	CString m_strAmount;
	CString m_strTax;
	CString m_strDown;
	CStatic m_staticTotal;
	CString	m_strTaxAmount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAmntDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void cleanFloat(TCHAR szInput[], TCHAR szOutput[]);
	CString cleanFloat(CString strInput);
	void cleanInt(TCHAR szInput[], TCHAR szOutput[]);
	void DisplayRecalc();

protected:

	// Generated message map functions
	//{{AFX_MSG(CAmntDetailDlg)
	afx_msg void OnKillfocusAmnt();
	afx_msg void OnKillfocusDwn();
	afx_msg void OnKillfocusTax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AMNTDETAILDLG_H__7DA52E8E_2C7A_4803_B842_3BF3E3465D42__INCLUDED_)
