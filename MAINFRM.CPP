// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MathcoLoan.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define PSPC_TOOLBAR_HEIGHT 24

const DWORD dwAdornmentFlags = 0; // exit button

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDM_HELP_HELP, OnHelpHelp)
	ON_COMMAND(IDM_TOOLS_REG, OnToolsReg)
	//}}AFX_MSG_MAP
	ON_NOTIFY(DLN_CE_CREATE, AFXCE_ID_DOCLIST, OnCreateDocList)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_pRegDialog = new CRegisterDlg();
	
}

CMainFrame::~CMainFrame()
{
	delete m_pRegDialog;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_wndCommandBar.m_bShowSharedNewButton = FALSE;
	m_ToolTipsTable[0] = MakeString(IDS_FILE);
	m_ToolTipsTable[1] = MakeString(IDS_MHELP);
	m_ToolTipsTable[2] = MakeString(IDS_CUT);
	m_ToolTipsTable[3] = MakeString(IDS_COPY);
	m_ToolTipsTable[4] = MakeString(IDS_PASTE);

	if(!m_wndCommandBar.Create(this) ||
	   !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	   !m_wndCommandBar.AddAdornments() ||
	   !m_wndCommandBar.LoadToolBar(IDR_MAINFRAME)  ||
		!m_wndCommandBar.SendMessage(TB_SETTOOLTIPS, (WPARAM)(7), (LPARAM)(m_ToolTipsTable)))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return TRUE;
}


void CMainFrame::OnCreateDocList(DLNHDR* pNotifyStruct, LRESULT* result)
{
	CCeDocList* pDocList = (CCeDocList*)FromHandle(pNotifyStruct->nmhdr.hwndFrom);
	ASSERT_KINDOF(CCeDocList, pDocList);

	CCeCommandBar* pDocListCB = pDocList->GetCommandBar();
	ASSERT(pDocListCB != NULL);

	pDocListCB->InsertMenuBar(IDM_DOCLIST);
	pDocListCB->SendMessage(TB_SETTOOLTIPS, (WPARAM)(1), (LPARAM)(m_ToolTipsTable));
	CFrameWnd::OnCreateDocList(pNotifyStruct, result);	

	SharewareCheck();
}


void CMainFrame::OnDestroy()
{
	for(int i = 0; i < NUM_TOOL_TIPS; i++)
		delete m_ToolTipsTable[i];

	CFrameWnd::OnDestroy();
}

LPTSTR CMainFrame::MakeString(UINT stringID)
{
	TCHAR buffer[255];
	TCHAR* theString;

	::LoadString(AfxGetInstanceHandle(), stringID, buffer, 255);
	theString = new TCHAR[lstrlen(buffer) + 1];
	lstrcpy(theString, buffer);
	return theString;
}   

 
/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnHelpHelp() 
{
	PROCESS_INFORMATION p;

	CreateProcess(_T("peghelp.exe"), _T("file:\\Windows\\LoanHelp.htc"), NULL, NULL, FALSE, 0, NULL, NULL, NULL, &p);
	CloseHandle(p.hProcess);
	CloseHandle(p.hThread);
}

void CMainFrame::SharewareCheck()
{
	int iDaysLeft;
	CString str1, str2;

	//Shareware check
	if (!m_pRegDialog->isRegistered())
	{
		iDaysLeft = m_pRegDialog->daysLeft();
		if (iDaysLeft <= 0)
		{
			str1.LoadString(IDS_SHAREW_OVER);
			str2.LoadString(IDS_SHAREW);
			MessageBox(str1, str2, MB_OK);

			//Show them the register dialog
			if(m_pRegDialog->DoModal() == IDOK)
			{
				m_pRegDialog->RegisterSoft();
			}
			//if they could not register and this trial is expired, kick them out
			if (!m_pRegDialog->isRegistered())
			{
				//MessageBox(TEXT("The trial period has ended.  Please register to continue using this software."), TEXT("Shareware"), MB_OK);
				//close the application
				//SendMessage(WM_COMMAND, MAKEWPARAM(ID_APP_EXIT, 0), 0);
				::AfxAbort();
				return;

			}
			
		}
		else
		{
			str2.LoadString(IDS_SHAREW);
			str1.Format(IDS_SHAREW_WARN, iDaysLeft);
			//wsprintf(szTmpString, TEXT(""), iDaysLeft);
			MessageBox(str1, str2);
		}
	}
	else
	{
		//Delete the menu reference to register because its already registered
		//hwndMenu = SHGetMenu(hwndCB)
		CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
		CMenu* pToolsMenu = pTopMenu->GetSubMenu(0);
		pToolsMenu->DeleteMenu(IDM_TOOLS_REG, MF_BYCOMMAND); 
		//this->DrawMenuBar();
	}

}

void CMainFrame::OnToolsReg() 
{
	if(m_pRegDialog->DoModal() == IDOK)
	{
		m_pRegDialog->RegisterSoft();
	}
	
}
