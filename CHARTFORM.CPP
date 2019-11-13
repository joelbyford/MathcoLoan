// ChartForm.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "SchedForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartForm dialog

CChartForm::CChartForm(CWnd* pParent /*=NULL*/)
	: CDialog(CChartForm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartForm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	//initialize the colors to be used by the graph
	m_LineColors[0] = RGB(255,0,0);
	m_LineColors[1] = RGB(0,64,0);
	m_LineColors[2] = RGB(0,64,255);
	m_LineColors[3] = RGB(255,255,0);
	m_LineColors[4] = RGB(128,0,128);
	m_LineColors[5] = RGB(0,128,64);
	m_LineColors[6] = RGB(247,188,91);
	m_LineColors[7] = RGB(0,0,196);
	m_LineColors[8] = RGB(0,196,0);
	m_LineColors[9] = RGB(196,0,0);

	//default labels
	m_strGraphLabel = TEXT("Title");
	m_strXAxisLabel = TEXT("X-Axis");
	m_strYAxisLabel = TEXT("Y-Axis");
}


void CChartForm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartForm)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartForm, CDialog)
	//{{AFX_MSG_MAP(CChartForm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartForm message handlers

BOOL CChartForm::OnInitDialog() 
{
	CString str;
	CLineGraphPoint* pts;
	int i,j;
	TCHAR* trash;

	CDialog::OnInitDialog();

	CenterWindow();

	m_LineGraph.SubclassDlgItem(IDC_GRAPH, this);
	m_LineGraph.SetTitle(m_strGraphLabel);
	m_LineGraph.SetXLabel(m_strXAxisLabel);
	m_LineGraph.SetYLabel(m_strYAxisLabel);
	m_LineGraph.m_nLegendCols = 2;

	//Figure out how many rows need to be displayed
	CSchedForm* pParent = (CSchedForm*) this->m_pParentWnd;
	int iNumRows = pParent->m_lstSched.GetItemCount();

	for (j=0;j<m_Columns.GetSize();j++)
	{
		//Allocate memory for an array that size
		pts = (CLineGraphPoint*)malloc((sizeof(CLineGraphPoint)*iNumRows));
		for (i=0;i<iNumRows;i++)
		{
			str = pParent->m_lstSched.GetItemText(i, m_Columns[j]);
			(pts+i)->y = wcstod(str.LockBuffer(), &trash);
			(pts+i)->x = i;
		}
		//Add the line to the graph
		int nLine = m_LineGraph.AddLine(m_LineColors[j], 2, m_strColumns[j], pts, iNumRows);

		//clean up the memory
		free(pts);
	}



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
