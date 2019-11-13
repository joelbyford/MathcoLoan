#if !defined(AFX_REGISTERDLG_H__C45A3263_2C3F_4E24_9692_11144F240CA6__INCLUDED_)
#define AFX_REGISTERDLG_H__C45A3263_2C3F_4E24_9692_11144F240CA6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RegisterDlg.h : header file
//

#define EVAL_PERIOD 15
//Registry key and value
static const TCHAR szRegistryKey[] =    TEXT("Software\\Mathco\\Loan");
static const TCHAR szRegValue1[] =       TEXT("RegCD");
static const TCHAR szRegValue2[] =       TEXT("Company");
static const TCHAR szRegValue3[] =       TEXT("User");
static const TCHAR szRegValue4[] =       TEXT("Prefs");
static const TCHAR szAppRegCode[] =	     TEXT("MCL-JD89-ZQ7B-2PUU");

enum eRegEntry
{
	eCODE = 1,
	eCOMPANY = 2,
	eUSER = 3,
	eDATE = 4
};

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog

class CRegisterDlg : public CDialog
{
// Construction
public:
	BOOL SharewareCheck(void);
	BOOL RegisterSoft(void);
	BOOL CheckRegCode(CString szCode);
	int daysLeft(void);
	BOOL isRegistered(void);
	CRegisterDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegisterDlg)
	enum { IDD = IDD_REGISTER };
	CString	m_szCompany;
	CString	m_szCode;
	CString	m_szName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegisterDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HRESULT SetToRegistry(TCHAR* pPos, int iValType, DWORD dwDateVal);
	HRESULT GetFromRegistry();
	DWORD getInstallDate(void);
	void decrDate(DWORD dwDate, int* iDay, int* iMonth, int* iYear);
	DWORD encrToday(void);
	int daysInMonth(int iMonth);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERDLG_H__C45A3263_2C3F_4E24_9692_11144F240CA6__INCLUDED_)
