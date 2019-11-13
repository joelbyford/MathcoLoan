// SchedForm.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "SchedForm.h"
#include "ChartForm.h"
#include "LineGraph.h"
#include "LoanCalcs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSchedForm dialog


CSchedForm::CSchedForm(CWnd* pParent /*=NULL*/)
	: CDialog(CSchedForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSchedForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSchedForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchedForm)
	DDX_Control(pDX, IDC_TOTALBOX, m_edTotalBox);
	DDX_Control(pDX, IDC_CMBTYPE, m_cmbType);
	DDX_Control(pDX, IDC_TOTAL1, m_edTotal1);
	DDX_Control(pDX, IDC_TOTAL2, m_edTotal2);
	DDX_Control(pDX, IDC_TOTAL3, m_edTotal3);
	DDX_Control(pDX, IDC_TOTAL4, m_edTotal4);
	DDX_Control(pDX, IDC_TOTAL5, m_edTotal5);
	DDX_Control(pDX, IDC_TEXT1, m_edText1);
	DDX_Control(pDX, IDC_TEXT2, m_edText2);
	DDX_Control(pDX, IDC_TEXT3, m_edText3);
	DDX_Control(pDX, IDC_TEXT4, m_edText4);
	DDX_Control(pDX, IDC_TEXT5, m_edText5);
	DDX_Control(pDX, IDC_CMBVIEW, m_cmbView);
	DDX_Control(pDX, IDC_LIST1, m_lstSched);
	DDX_Control(pDX, IDC_BTN_EXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BTN_CHART, m_btnChart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSchedForm, CDialog)
	//{{AFX_MSG_MAP(CSchedForm)
	ON_CBN_SELENDOK(IDC_CMBVIEW, OnSelendokCmbview)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_BN_CLICKED(IDC_BTN_CHART, OnBtnChart)
	ON_CBN_SELENDOK(IDC_CMBTYPE, OnSelendokCmbtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSchedForm message handlers

BOOL CSchedForm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strTemp;

	//Initialize the buttons
	m_btnExport.SetIcon(IDI_XLS, CSize(16, 16));
	m_btnExport.SetFlat(FALSE);
	m_btnChart.SetIcon(IDI_GRAPH, CSize(16,16));
	m_btnChart.SetFlat(FALSE);

	//Populate the Views
	strTemp.LoadString(IDS_ANNUALY);
	m_cmbView.AddString(strTemp);
	strTemp.LoadString(IDS_MONTHLY);
	m_cmbView.AddString(strTemp);

	strTemp.LoadString(IDS_SCHED);
	m_cmbType.AddString(strTemp);
	strTemp.LoadString(IDS_POINTS_PAID);
	m_cmbType.AddString(strTemp);

	m_cmbView.SetCurSel(0);
	m_cmbType.SetCurSel(0);

	//Create the schedule
	if (!BuildSched())
		MessageBox(TEXT("Problem displaying schedule, please contact customer support."));



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL  CSchedForm::BuildSched()
{
	CRect rect;	
	LVITEM lvI;				// list view item structure
	int index = 0;
	int index2 = 0;
	TCHAR szText[80];
	TCHAR szOut[35];
	TCHAR szIn[35];
	double fMoRate = fRate/12;
	double fInterest = 0;
	double fBalance = fAmount;
	double fPrinciple = 0;
	double fISubTot = 0;
	double fPSubTot = 0;

	//grand totals
	double fTotInt = 0;
	double fTotPay = 0;
	double fTotPcp = 0;

	//Delete all columns
	int nColumnCount = m_lstSched.GetHeaderCtrl()->GetItemCount();

	for (int i=0;i < nColumnCount;i++)
	{
		m_lstSched.DeleteColumn(0);
	}
	//Make list columns
	m_lstSched.GetClientRect(&rect);
	int nColInterval = (rect.Width()-20)/3;
	m_lstSched.InsertColumn(0, _T("Per"), LVCFMT_LEFT, 20);
	m_lstSched.InsertColumn(1, _T("Interest"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(2, _T("Principle"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(3, _T("Balance"), LVCFMT_LEFT, nColInterval);


	// Finally, add the actual items to the control.
	lvI.mask = LVIF_TEXT |  LVIF_STATE;  //LVIF_PARAM |
	lvI.state = 0;
	lvI.stateMask = 0;

	for (index = 0; index < iPer; index++)
	{
		//Calculate the stuff for this line
		fInterest = fBalance * fMoRate;
		fPrinciple = fPmnt - fInterest;
		fBalance = fBalance - fPrinciple;
		//subtotals
		fISubTot += fInterest;
		fPSubTot += fPrinciple;
		//Grand Totals
		fTotInt += fInterest;
		fTotPcp += fPrinciple;
		fTotPay += fPmnt;

		if (m_cmbView.GetCurSel() == 1) //Months
		{
			lvI.iItem = index;
			lvI.iSubItem = 0;
			// The parent window is responsible for storing the text.
			// The list view control will send an LVN_GETDISPINFO
			// when it needs the text to display.
			wsprintf(szText, TEXT("Error"));
			lvI.pszText = szText;
			lvI.cchTextMax = 80;
			//lvI.lParam = (LPARAM)&rgHouseInfo[index];

			if (m_lstSched.InsertItem(&lvI)== -1)
				return FALSE;
			//Add the month
			wsprintf(szText, TEXT("%i"), index + 1);
			m_lstSched.SetItemText(index, 0, szText);
			//Interest
			wsprintf(szText, TEXT("%.2f"), fInterest);
			m_lstSched.SetItemText( index, 1, szText);
			//Principle
			wsprintf(szText, TEXT("%.2f"), fPrinciple);
			m_lstSched.SetItemText( index, 2, szText);
			//Balance
			wsprintf(szText, TEXT("%.2f"), fBalance);
			m_lstSched.SetItemText(index, 3, szText);
		}
		else if ((index+1)%12 == 0 //Years
					|| index == iPer-1)
		{
			lvI.iItem = index2;
			lvI.iSubItem = 0;
			wsprintf(szText, TEXT("Error"));
			lvI.pszText = szText;
			lvI.cchTextMax = 80;
			//lvI.lParam = (LPARAM)&rgHouseInfo[index];
			if (m_lstSched.InsertItem(&lvI) == -1)
				return FALSE;
			//Add the month
			wsprintf(szText, TEXT("%i"), index2+1);
			m_lstSched.SetItemText( index2, 0, szText);
			//Interest
			wsprintf(szText, TEXT("%.2f"), fISubTot);
			m_lstSched.SetItemText( index2, 1, szText);
			//Principle
			wsprintf(szText, TEXT("%.2f"), fPSubTot);
			m_lstSched.SetItemText( index2, 2, szText);
			//Balance
			wsprintf(szText, TEXT("%.2f"), fBalance);
			m_lstSched.SetItemText( index2, 3, szText);
			//incriment the other index
			index2 ++;
			fISubTot = 0;
			fPSubTot = 0;
		}

	}

	//show totals
	CString strTemp;
	strTemp.LoadString(IDS_TOTALS);
	m_edTotalBox.SetWindowText(strTemp);

	strTemp.LoadString(IDS_PRINCIPLE);
	m_edText1.SetWindowText(strTemp);

	strTemp.LoadString(IDS_INTEREST);
	m_edText2.SetWindowText(strTemp);

	strTemp.LoadString(IDS_PAYMENT);
	m_edText3.SetWindowText(strTemp);

	m_edText4.SetWindowText(TEXT(" "));
	m_edText5.SetWindowText(TEXT(" "));
	m_edTotal4.SetWindowText(TEXT(" "));
	m_edTotal5.SetWindowText(TEXT(" "));

	wsprintf(szIn, TEXT("%.3f"), fTotPay);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal3.SetWindowText(CString(szOut));

	wsprintf(szIn, TEXT("%.3f"), fTotInt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal2.SetWindowText(CString(szOut));

	wsprintf(szIn, TEXT("%.3f"), fTotPcp);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal1.SetWindowText(CString(szOut));

	return TRUE;
}

BOOL  CSchedForm::BuildQtrPoint()
{
	CRect rect;
	CLoanCalcs oCalcs;
	LVITEM lvI;				// list view item structure
	int index = 0;
	int index2 = 0;
	TCHAR szText[80];
	TCHAR szOut[35];
	TCHAR szIn[35];


	double fMoRate = fRate/12;
	double fInterest = 0;
	double fBalance = fAmount;
	double fPrinciple = 0;
	double fISubTot = 0;
	double fPSubTot = 0;

	oCalcs.m_fAmnt = fAmount;
	oCalcs.m_fLoanAmnt = fAmount;
	oCalcs.m_fRate = (fRate-.0025);
	oCalcs.m_iPer = iPer;
	double f25Pmnt = oCalcs.getPayment();
	double f25MoRate = (fRate-.0025)/12;
	double f25Interest = 0;
	double f25Balance = fAmount;
	double f25Principle = 0;
	double f25ISubTot = 0;
	double f25PSubTot = 0;

	oCalcs.m_fAmnt = fAmount;
	oCalcs.m_fLoanAmnt = fAmount;
	oCalcs.m_fRate = (fRate-.005);
	oCalcs.m_iPer = iPer;
	double f50Pmnt = oCalcs.getPayment();
	double f50MoRate = (fRate-.005)/12;
	double f50Interest = 0;
	double f50Balance = fAmount;
	double f50Principle = 0;
	double f50ISubTot = 0;
	double f50PSubTot = 0;

	oCalcs.m_fAmnt = fAmount;
	oCalcs.m_fLoanAmnt = fAmount;
	oCalcs.m_fRate = (fRate-.01);
	oCalcs.m_iPer = iPer;
	double f1Pmnt = oCalcs.getPayment();
	double f1MoRate = (fRate-.01)/12;
	double f1Interest = 0;
	double f1Balance = fAmount;
	double f1Principle = 0;
	double f1ISubTot = 0;
	double f1PSubTot = 0;

	oCalcs.m_fAmnt = fAmount;
	oCalcs.m_fLoanAmnt = fAmount;
	oCalcs.m_fRate = (fRate-.02);
	oCalcs.m_iPer = iPer;
	double f2Pmnt = oCalcs.getPayment();
	double f2MoRate = (fRate-.02)/12;
	double f2Interest = 0;
	double f2Balance = fAmount;
	double f2Principle = 0;
	double f2ISubTot = 0;
	double f2PSubTot = 0;

	oCalcs.m_fAmnt = fAmount;
	oCalcs.m_fLoanAmnt = fAmount;
	oCalcs.m_fRate = (fRate-.03);
	oCalcs.m_iPer = iPer;

	//Delete all columns
	int nColumnCount = m_lstSched.GetHeaderCtrl()->GetItemCount();

	for (int i=0;i < nColumnCount;i++)
	{
		m_lstSched.DeleteColumn(0);
	}
	//Make list columns
	m_lstSched.GetClientRect(&rect);
	int nColInterval = 60;
	m_lstSched.InsertColumn(0, _T("Per"), LVCFMT_LEFT, 20);
	m_lstSched.InsertColumn(1, _T("0-Intr"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(2, _T("1/4-Intr"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(3, _T("1/2-Intr"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(4, _T("1-Intr"), LVCFMT_LEFT, nColInterval);
	m_lstSched.InsertColumn(5, _T("2-Intr"), LVCFMT_LEFT, nColInterval);


	// Finally, add the actual items to the control.
	lvI.mask = LVIF_TEXT |  LVIF_STATE;  //LVIF_PARAM |
	lvI.state = 0;
	lvI.stateMask = 0;

	for (index = 0; index < iPer; index++)
	{
		//Calculate the stuff for this line
		fInterest = fBalance * fMoRate;
		fPrinciple = fPmnt - fInterest;
		fBalance = fBalance - fPrinciple;
		//subtotals
		fISubTot += fInterest;
		fPSubTot += fPmnt;

		//Calculate the stuff for this line
		f25Interest = f25Balance * f25MoRate;
		f25Principle = f25Pmnt - f25Interest;
		f25Balance = f25Balance - f25Principle;
		//subtotals
		f25ISubTot += f25Interest;
		f25PSubTot += f25Pmnt;

		//Calculate the stuff for this line
		f50Interest = f50Balance * f50MoRate;
		f50Principle = f50Pmnt - f50Interest;
		f50Balance = f50Balance - f50Principle;
		//subtotals
		f50ISubTot += f50Interest;
		f50PSubTot += f50Pmnt;

		//Calculate the stuff for this line
		f1Interest = f1Balance * f1MoRate;
		f1Principle = f1Pmnt - f1Interest;
		f1Balance = f1Balance - f1Principle;
		//subtotals
		f1ISubTot += f1Interest;
		f1PSubTot += f1Pmnt;

		//Calculate the stuff for this line
		f2Interest = f2Balance * f2MoRate;
		f2Principle = f2Pmnt - f2Interest;
		f2Balance = f2Balance - f2Principle;
		//subtotals
		f2ISubTot += f2Interest;
		f2PSubTot += f2Pmnt;

		if (m_cmbView.GetCurSel() == 1) //Months
		{
			lvI.iItem = index;
			lvI.iSubItem = 0;
			// The parent window is responsible for storing the text.
			// The list view control will send an LVN_GETDISPINFO
			// when it needs the text to display.
			wsprintf(szText, TEXT("Error"));
			lvI.pszText = szText;
			lvI.cchTextMax = 80;
			//lvI.lParam = (LPARAM)&rgHouseInfo[index];

			if (m_lstSched.InsertItem(&lvI)== -1)
				return FALSE;
			//Add the month
			wsprintf(szText, TEXT("%i"), index + 1);
			m_lstSched.SetItemText(index, 0, szText);

			//Baseline (0 paid)
			wsprintf(szText, TEXT("%.2f"), fInterest);
			m_lstSched.SetItemText( index, 1, szText);

			//1/4 Point Paid down
			wsprintf(szText, TEXT("%.2f"), f25Interest);
			m_lstSched.SetItemText( index, 2, szText);
			//1/2 Point Paid down
			wsprintf(szText, TEXT("%.2f"), f50Interest);
			m_lstSched.SetItemText( index, 3, szText);
			//1 Point Paid down
			wsprintf(szText, TEXT("%.2f"), f1Interest);
			m_lstSched.SetItemText( index, 4, szText);
			//2 Point Paid down
			wsprintf(szText, TEXT("%.2f"), f2Interest);
			m_lstSched.SetItemText( index, 5, szText);

		}
		else if ((index+1)%12 == 0 //Years
					|| index == iPer-1)
		{
			lvI.iItem = index2;
			lvI.iSubItem = 0;
			wsprintf(szText, TEXT("Error"));
			lvI.pszText = szText;
			lvI.cchTextMax = 80;
			//lvI.lParam = (LPARAM)&rgHouseInfo[index];
			if (m_lstSched.InsertItem(&lvI) == -1)
				return FALSE;
			//Add the month
			wsprintf(szText, TEXT("%i"), index2+1);
			m_lstSched.SetItemText( index2, 0, szText);

			//Baseline 0 Paid
			wsprintf(szText, TEXT("%.2f"), fISubTot);
			m_lstSched.SetItemText( index2, 1, szText);

			//1/4 Point
			wsprintf(szText, TEXT("%.2f"), f25ISubTot);
			m_lstSched.SetItemText( index2, 2, szText);

			//1/2 Point
			wsprintf(szText, TEXT("%.2f"), f50ISubTot);
			m_lstSched.SetItemText( index2, 3, szText);
			//1 Point
			wsprintf(szText, TEXT("%.2f"), f1ISubTot);
			m_lstSched.SetItemText( index2, 4, szText);
			//2 Point
			wsprintf(szText, TEXT("%.2f"), f2ISubTot);
			m_lstSched.SetItemText( index2, 5, szText);

			//incriment the other index
			index2 ++;
			fISubTot = 0;
			fPSubTot = 0;
			f25ISubTot = 0;
			f25PSubTot = 0;
			f50ISubTot = 0;
			f50PSubTot = 0;
			f1ISubTot = 0;
			f1PSubTot = 0;
			f2ISubTot = 0;
			f2PSubTot = 0;


		}


	}

	//show totals
	CString strTemp;
	strTemp.LoadString(IDS_PAYMENTS);
	m_edTotalBox.SetWindowText(strTemp);

	strTemp.LoadString(IDS_NOPTSPMT);
	m_edText1.SetWindowText(strTemp);

	strTemp.LoadString(IDS_NOPTSPMT25);
	m_edText2.SetWindowText(strTemp);

	strTemp.LoadString(IDS_NOPTSPMT50);
	m_edText3.SetWindowText(strTemp);

	strTemp.LoadString(IDS_NOPTSPMT1);
	m_edText4.SetWindowText(strTemp);
	
	strTemp.LoadString(IDS_NOPTSPMT2);
	m_edText5.SetWindowText(strTemp);
	

	wsprintf(szIn, TEXT("%.3f"), fPmnt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal1.SetWindowText(CString(szOut));

	wsprintf(szIn, TEXT("%.3f"), f25Pmnt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal2.SetWindowText(CString(szOut));

	wsprintf(szIn, TEXT("%.3f"), f50Pmnt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal3.SetWindowText(CString(szOut));	

	wsprintf(szIn, TEXT("%.3f"), f1Pmnt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal4.SetWindowText(CString(szOut));

	wsprintf(szIn, TEXT("%.3f"), f2Pmnt);
	GetNumberFormat(LOCALE_USER_DEFAULT, 0, szIn, NULL, szOut, 35);
	m_edTotal5.SetWindowText(CString(szOut));
	
	return TRUE;

}

void CSchedForm::OnSelendokCmbview() 
{
	m_lstSched.DeleteAllItems();
	if (m_cmbType.GetCurSel() == 1)
	{
		//Create the .25 Points comparison
		if (!BuildQtrPoint())
			MessageBox(TEXT("Problem displaying schedule, please contact customer support."));
	}
	else
	{
		//Create the schedule
		if (!BuildSched())
			MessageBox(TEXT("Problem displaying schedule, please contact customer support."));
	}

}

void CSchedForm::OnSelendokCmbtype() 
{
	m_lstSched.DeleteAllItems();
	if (m_cmbType.GetCurSel() == 1)
	{
		//Create the .25 Points comparison
		if (!BuildQtrPoint())
			MessageBox(TEXT("Problem displaying schedule, please contact customer support."));
	}
	else
	{
		//Create the schedule
		if (!BuildSched())
			MessageBox(TEXT("Problem displaying schedule, please contact customer support."));
	}	
}
void CSchedForm::OnBtnExport() 
{
	//Declaraions
	CString szTmpString;
	int lineindex = 0;
	int pmntCounter = 0;
	double fMoRate = fRate/12;
	double fInterest = 0;
	double fBalance = fAmount;
	double fPrinciple = 0;
	double fISubTot = 0;
	double fPSubTot = 0;
	double fIntTot = 0;
	double fPmtTot = 0;
	PROCESS_INFORMATION p;

	//Get the file name
	CFileDialog pFileDlg(FALSE, SZ_DEFEXT, NULL, NULL, SZ_FILEFILTER);
	if (pFileDlg.DoModal()==IDOK)
	{
		m_pPXL = new CPXLWriter();

		m_pPXL->CreatePXLFile(pFileDlg.GetPathName().LockBuffer());
		//loop through entire table and write out data.
		//Check what type of data we are displaying first
		//to format it right in Excel.
		if (m_cmbView.GetCurSel() == 0 || m_cmbView.GetCurSel() == 1) //Standard Month & Year Views
		{
			//Header
			szTmpString.LoadString(IDS_PERIOD);
			m_pPXL->WriteLabel(0,0,szTmpString.LockBuffer(), 0);
			szTmpString.LoadString(IDS_PAYMENT);
			m_pPXL->WriteLabel(0,1,szTmpString.LockBuffer(), 0);
			szTmpString.LoadString(IDS_INTEREST);
			m_pPXL->WriteLabel(0,2,szTmpString.LockBuffer(), 0);
			szTmpString.LoadString(IDS_PRINCIPLE);
			m_pPXL->WriteLabel(0,3,szTmpString.LockBuffer(), 0);
			szTmpString.LoadString(IDS_BALANCE);
			m_pPXL->WriteLabel(0,4,szTmpString.LockBuffer(), 0);
	
			//Details
			lineindex = 0;
			pmntCounter = 0;
			//for (index = 1; index <= iPer; index++)
			while (pmntCounter < iPer)
			{
				//incriment the counters
				lineindex++;
				pmntCounter++;
				//Calculate the stuff for this line
				fInterest = fBalance * fMoRate;
				fPrinciple = fPmnt - fInterest;
				fBalance = fBalance - fPrinciple;
				//subtotals
				fISubTot += fInterest;
				fPSubTot += fPrinciple;
				//totals
				fIntTot += fInterest;
				fPmtTot += fPmnt;


				//Add the month
				m_pPXL->WriteDouble(lineindex, 0, pmntCounter, 1);
				//Payment
				m_pPXL->WriteDouble(lineindex, 1, fPmnt, 0);
				//Interest
				m_pPXL->WriteDouble(lineindex, 2, fInterest, 0);
				//Principle
				m_pPXL->WriteDouble(lineindex, 3, fPrinciple, 0);
				//Balance
				m_pPXL->WriteDouble(lineindex, 4, fBalance, 0);

				//Subtotal each year
				if (pmntCounter%12 == 0 || pmntCounter == iPer)
				{
					//incriment the index early
					lineindex++;

					//Add the month
					m_pPXL->WriteLabel(lineindex, 0, TEXT("Totals"), 0);
					//Payment not subtotaled
					//Interest
					m_pPXL->WriteDouble(lineindex, 2, fISubTot, 0);
					//Principle
					m_pPXL->WriteDouble(lineindex, 3, fPSubTot, 0);
					//Balance
					m_pPXL->WriteDouble(lineindex, 4, fBalance, 0);

					//incriment the other index
					fISubTot = 0;
					fPSubTot = 0;

					//incriment the counter again
					//to insert a blank line
					lineindex++;
				}
			}

		}
		delete m_pPXL;
		//Open the file in Excel
		CreateProcess(_T("pxl.exe"), pFileDlg.GetPathName().LockBuffer(), NULL, NULL, FALSE, 0, NULL, NULL, NULL, &p);
		CloseHandle(p.hProcess);
		CloseHandle(p.hThread);

	}

	
	return;
}

void CSchedForm::OnBtnChart() 
{
	m_pChartForm = new CChartForm(this);

	if (m_cmbType.GetCurSel() == 0) //Schedule
	{
		//Assign the columns to graph
		m_pChartForm->m_Columns.Add(1);
		m_pChartForm->m_strColumns.Add(_T("Interest"));
		
		m_pChartForm->m_Columns.Add(2);
		m_pChartForm->m_strColumns.Add(_T("Principle"));

		//give the labels
		m_pChartForm->m_strGraphLabel = TEXT("Principle -vs- Interest");
		m_pChartForm->m_strXAxisLabel = TEXT("Periods");
		m_pChartForm->m_strYAxisLabel = TEXT("Amount");
	}
	else if (m_cmbType.GetCurSel() == 1) //Points Paid
	{
		
		//Assign the columns to graph
		m_pChartForm->m_Columns.Add(1);
		m_pChartForm->m_strColumns.Add(_T("No Points"));
		
		m_pChartForm->m_Columns.Add(2);
		m_pChartForm->m_strColumns.Add(_T("1/4 Point"));

		m_pChartForm->m_Columns.Add(3);
		m_pChartForm->m_strColumns.Add(_T("1/2 Point"));

		m_pChartForm->m_Columns.Add(4);
		m_pChartForm->m_strColumns.Add(_T("1 Point"));

		m_pChartForm->m_Columns.Add(5);
		m_pChartForm->m_strColumns.Add(_T("2 Points"));


		//give the labels
		m_pChartForm->m_strGraphLabel = TEXT("Points Paid Analysis");
		m_pChartForm->m_strXAxisLabel = TEXT("Periods");
		m_pChartForm->m_strYAxisLabel = TEXT("Amount");
	}

	m_pChartForm->DoModal();

	delete m_pChartForm;
}


