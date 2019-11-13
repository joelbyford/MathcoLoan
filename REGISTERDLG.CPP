// RegisterDlg.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg dialog


CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegisterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegisterDlg)
	m_szCompany = _T("");
	m_szCode = _T("");
	m_szName = _T("");
	//}}AFX_DATA_INIT
}


void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegisterDlg)
	DDX_Text(pDX, IDC_TXTCO, m_szCompany);
	DDV_MaxChars(pDX, m_szCompany, 35);
	DDX_Text(pDX, IDC_TXTCODE, m_szCode);
	DDV_MaxChars(pDX, m_szCode, 35);
	DDX_Text(pDX, IDC_TXTNAME, m_szName);
	DDV_MaxChars(pDX, m_szName, 35);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegisterDlg, CDialog)
	//{{AFX_MSG_MAP(CRegisterDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterDlg message handlers

BOOL CRegisterDlg::isRegistered()
{
	if(GetFromRegistry() == ERROR_SUCCESS)
		return(CheckRegCode(m_szCode));
	else
		return FALSE;
}

DWORD CRegisterDlg::encrToday()
{
	DWORD dwRetVal = 0;
	SYSTEMTIME systime;
	GetSystemTime(&systime);

	dwRetVal = (systime.wYear+2365)+((systime.wDay+22)*10000)+((systime.wMonth+74)*1000000);
	
	return dwRetVal;
}

void CRegisterDlg::decrDate(DWORD dwDate, int *iDay, int *iMonth, int *iYear)
{
	int iRawMonth = 0;
	int iRawDay = 0;

	//Figure out the month portion
	iRawMonth = dwDate/1000000;
	*iMonth = iRawMonth - 74;

	//Figure the day portion
	iRawDay = (dwDate - (iRawMonth*1000000))/10000;
	*iDay = iRawDay - 22;

	//Figure the year portion
	*iYear = (dwDate - (iRawMonth*1000000) - (iRawDay*10000)) - 2365;
	return;

}

DWORD CRegisterDlg::getInstallDate()
{
	HKEY    hKey;
	DWORD   dwSize, dwType, dwValue;
	long    hRes1, hRes2;
	TCHAR	szTrash[35];

    dwValue = 0;
	dwSize = sizeof(DWORD);

	hRes1 = RegOpenKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, KEY_ALL_ACCESS, &hKey);
	hRes2 = RegQueryValueExW(hKey, szRegValue4, 0, &dwType, (LPBYTE)&dwValue, &dwSize);
	//if the key or value doesn't exist create it
	if (hRes1 !=ERROR_SUCCESS || hRes2 !=ERROR_SUCCESS)
	{
		dwValue = encrToday();
		SetToRegistry(szTrash, 4, dwValue);	
	}
	RegCloseKey(hKey);
    
    return dwValue;
}

int CRegisterDlg::daysInMonth(int iMonth)
{
	int iDays = 0;

	switch(iMonth)
	{
	case 1:
		iDays = 31;
		break;
	case 2:
		iDays = 59;
		break;
	case 3:
		iDays = 90;
		break;
	case 4:
		iDays = 120;
		break;
	case 5:
		iDays = 151;
		break;
	case 6:
		iDays = 181;
		break;
	case 7:
		iDays = 212;
		break;
	case 8:
		iDays = 243;
		break;
	case 9:
		iDays = 273;
		break;
	case 10:
		iDays = 304;
		break;
	case 11:
		iDays = 334;
		break;
	case 12:
		iDays = 365;
		break;
	default:
		iDays = 0;
		break;
	}
	return iDays;

}

int CRegisterDlg::daysLeft()
{
	DWORD dwInstDate = 0;
	SYSTEMTIME systime;
	int iDay, iMonth, iYear;
	int iCurDay, iInstDay;
	int iYrPart;

	//Get the current date
	GetSystemTime(&systime);

	//Get the install date
	dwInstDate = getInstallDate();
	decrDate(dwInstDate, &iDay, &iMonth, &iYear);

	//Figure out what day of the year each is
	iCurDay = daysInMonth(systime.wMonth) + systime.wDay;
	iInstDay = daysInMonth(iMonth) + iDay;
	
	//Create a multiplier from the year diff
	iYrPart = (systime.wYear - iYear) * 365;

	//Diff the two dates and return the results
	return (EVAL_PERIOD - (iCurDay + iYrPart - iInstDay));

}

BOOL CRegisterDlg::CheckRegCode(CString szCode)
{
	//put code validation in here.
	if (wcscmp(szCode, szAppRegCode)==0)
		return true;
	else
		return false;

}

HRESULT CRegisterDlg::GetFromRegistry()
{
	HKEY    hKey;
	DWORD    dwSize, dwType;
	long    hRes;

    hRes = RegOpenKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, KEY_ALL_ACCESS, &hKey);
    if (hRes != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return hRes;
        }

    dwSize = sizeof(TCHAR[35]);
    
	//store the values 
	hRes = RegQueryValueExW(hKey, szRegValue1, 0, &dwType, (LPBYTE)m_szCode.GetBuffer(35), &dwSize);
	hRes = RegQueryValueExW(hKey, szRegValue2, 0, &dwType, (LPBYTE)m_szCompany.GetBuffer(35), &dwSize);
	hRes = RegQueryValueExW(hKey, szRegValue3, 0, &dwType, (LPBYTE)m_szName.GetBuffer(35), &dwSize);
	
	//Release the buffer locks
	m_szCode.ReleaseBuffer();
	m_szCompany.ReleaseBuffer();
	m_szName.ReleaseBuffer();

    
	//close the key
	RegCloseKey(hKey);
    
	//return success or not
    return hRes;

}

HRESULT CRegisterDlg::SetToRegistry(TCHAR *pPos, int iValType, DWORD dwDateVal)
{
	HKEY    hKey;
	DWORD    Disp;
	HRESULT hRes;

    hRes = RegCreateKeyExW(HKEY_CURRENT_USER, szRegistryKey, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &Disp);
    if (hRes != ERROR_SUCCESS) {
		RegCloseKey(hKey);
        return hRes;
        }
	switch (iValType)
	{
	case eCODE:
		hRes = RegSetValueExW(hKey, szRegValue1,0,REG_SZ, (LPBYTE)pPos, sizeof(TCHAR[35]));
		break;
	case eCOMPANY:
		hRes = RegSetValueExW(hKey, szRegValue2,0,REG_SZ, (LPBYTE)pPos, sizeof(TCHAR[35]));
		break;
	case eUSER:
		hRes = RegSetValueExW(hKey, szRegValue3,0,REG_SZ, (LPBYTE)pPos, sizeof(TCHAR[35]));
		break;
	case eDATE:
		hRes = RegSetValueExW(hKey, szRegValue4,0,REG_DWORD, (LPBYTE)&dwDateVal, sizeof(DWORD));
		break;
	}
    RegCloseKey(hKey);                    

    return hRes;
}

BOOL CRegisterDlg::RegisterSoft()
{
	BOOL bRetVal = FALSE;
	TCHAR szText[255];		// place to store some text
	int i=0, iBadFlag=0;
	CString str1, str2;

	if (!CheckRegCode(m_szCode))
	{
		//invalid registration
		str1.LoadString(IDS_SHAREW_BADCODE);
		str2.LoadString(IDS_SHAREW);
		MessageBox(str1, str2);
		bRetVal = FALSE;
	}
	else
	{
		//Good Registratoin
		//invalid registration
		str1.LoadString(IDS_SHAREW_THANKS);
		str2.LoadString(IDS_SHAREW);
		MessageBox(str1, str2);
		if (SetToRegistry(m_szCode.GetBuffer(35), 1, 0) != ERROR_SUCCESS)
		{
			wsprintf(szText, TEXT("Unable to save code in registry."));
			MessageBox(szText, MB_OK);
		}
		else 
		{
			if (SetToRegistry(m_szCompany.GetBuffer(35), 2, 0) != ERROR_SUCCESS)
			{
				wsprintf(szText, TEXT("Unable to save company in registry."));
				MessageBox(szText, TEXT("Error"), MB_OK);
			}
			else 
			{
				if (SetToRegistry(m_szName.GetBuffer(35), 3, 0) != ERROR_SUCCESS)
				{
					wsprintf(szText, TEXT("Unable to save user in registry."));
					MessageBox(szText, TEXT("Error"), MB_OK);
				}
				
			}
		}


		bRetVal = TRUE;
	}


	m_szCode.ReleaseBuffer();
	m_szName.ReleaseBuffer();
	m_szCompany.ReleaseBuffer();

	return bRetVal;
}


