// LineGraph.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "LineGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineGraphItem

CLineGraphItem::CLineGraphItem() 
{
	m_colorLine=RGB(255,255,255);
	m_widthLine = 1;

}

CLineGraphItem::~CLineGraphItem() 
{
}




/////////////////////////////////////////////////////////////////////////////
// CLineGraph

CLineGraph::CLineGraph()
{
	CLineGraph::RegisterWndClass(AfxGetInstanceHandle());

	
	m_rectChart.SetRect(0,0,0,0);

	m_strTitle = _T("");
	
	m_nGridLines = 3;
	m_colorGrid = RGB(0,0,0);
	m_maxXPoint = 0;
	m_maxYPoint = 0;
	m_nXLabelHeight = 0;
	m_nYLabelWidth = 0;
	m_nTitleHeight = 0;
	m_bShowLegend = TRUE;
	m_nLegendCols = 3;
	m_strYFmt = TEXT("%.2f");
	m_strXFmt = TEXT("%.0f");

	m_fontTitle.CreateFont(15, 0,0,0,FW_BOLD, 0,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	
	m_fontInfo.CreateFont(13, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

	m_fontXAxis.CreateFont(13, 0,0,0,FW_NORMAL, TRUE,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
	
	m_fontYAxis.CreateFont(13, 0,900,0,FW_NORMAL, TRUE,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

	m_fontXVals.CreateFont(13, 0,0,0,FW_NORMAL, FALSE,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

	m_fontYVals.CreateFont(13, 0,0,0,FW_NORMAL, FALSE,0,0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));

}

CLineGraph::~CLineGraph()
{
	m_fontTitle.DeleteObject();
	m_fontInfo.DeleteObject();
	m_fontXAxis.DeleteObject();
	m_fontYAxis.DeleteObject();
	Reset();
}


BEGIN_MESSAGE_MAP(CLineGraph, CWnd)
	//{{AFX_MSG_MAP(CLineGraph)
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLineGraph message handlers
BOOL CLineGraph::RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.lpszClassName = TEXT("LINE_GRAPH_CTRL"); // matches class name in client
	wc.hInstance = hInstance;
	wc.lpfnWndProc = ::DefWindowProc;
	wc.hIcon = 0;
	wc.lpszMenuName = NULL;
	wc.hbrBackground = (HBRUSH) ::GetStockObject(LTGRAY_BRUSH);
	wc.style = CS_GLOBALCLASS; // To be modified
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	return (::RegisterClass(&wc) != 0);
}

void CLineGraph::RecalcRect()
{
	CRect rect, clientRect;
	GetClientRect(&rect);
	clientRect = rect;
	CString strTemp(TEXT("X"));
	int nCount = m_chartLines.GetSize();

	CClientDC dc(this);

	//leave enough room at the top for the title
	if (!m_strTitle.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontTitle);
		CSize sz = dc.GetTextExtent(m_strTitle);
		m_nTitleHeight = (sz.cy+5);
		
		if ((sz.cy+5) > rect.top)
			rect.top += (sz.cy+5);// Leave  lines.

		dc.SelectObject(pOldFont);
	}

	//leave room for the x-Axis Title
	if (!m_strXAxis.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontXAxis);
		CSize sz = dc.GetTextExtent(m_strXAxis);
		m_nXLabelHeight = (sz.cy+2);

		rect.bottom -= (sz.cy+2);// Leave  lines.

		dc.SelectObject(pOldFont);
	}
	
	//leave room for the x-Axis Values
	if (!m_strXFmt.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontXAxis);
		CSize sz = dc.GetTextExtent(m_strXAxis);
		m_nXLabelHeight += sz.cy;

		rect.bottom -= sz.cy;// Leave  lines.

		dc.SelectObject(pOldFont);
	}

	//leave room for the y-axis title
	if (!m_strYAxis.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontYAxis);
		CSize sz = dc.GetTextExtent(strTemp); //need to know the width of a signle char
		m_nYLabelWidth = (sz.cy+2);

		rect.left += (sz.cy+2);// Leave  lines.
		
		//leave equal room on the right side just for asthetics
		rect.right -= (sz.cy+2);
		dc.SelectObject(pOldFont);
	}


	//leave enough room at the bottom for Legend
	if (m_bShowLegend)
	{
		CFont* pOldFont = dc.SelectObject(&m_fontInfo);
		CSize sz = dc.GetTextExtent(strTemp);
		int iLegRows = (nCount/m_nLegendCols) + 1;
		rect.bottom -= (((sz.cy+4)*iLegRows) + 3);// Leave  lines.
		dc.SelectObject(pOldFont);

		//save the text height for painting later (color squares)
		m_LegTextHeight = sz.cy;
		//establish the legend dimentions
		m_rectLegend.left = rect.left;
		m_rectLegend.right = rect.right;
		m_rectLegend.bottom = clientRect.bottom - 2;
		m_rectLegend.top = m_rectLegend.bottom - (iLegRows * (sz.cy) + 3);
	}


	//store the chart dimentions
	m_rectChart = rect;
	return;
}

void CLineGraph::Reset()
{
	int nCount = m_chartLines.GetSize();
	
	for (int i = 0; i < nCount; i++)
		delete m_chartLines.GetAt(i);
	m_chartLines.RemoveAll();
}

void CLineGraph::GetItemColor(int i, COLORREF& color)
{
	int nCount = m_chartLines.GetSize();
	if (i>=nCount)
		i=nCount-1;

	color = (m_chartLines.GetAt(i))->m_colorLine;
}

void CLineGraph::SetTitle(const CString & str)
{
	m_strTitle = str;
	RecalcRect();
	InvalidateRect(NULL, FALSE);
}

void CLineGraph::SetXLabel(const CString & str)
{
	m_strXAxis = str;
	RecalcRect();
	InvalidateRect(NULL, FALSE);
}

void CLineGraph::SetYLabel(const CString & str)
{
	m_strYAxis = str;
	RecalcRect();
	InvalidateRect(NULL, FALSE);
}

void CLineGraph::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	RecalcRect();
}

int CLineGraph::AddLine(COLORREF colorLine, int nWidth, const CString& str, CLineGraphPoint* pointArray, int nPointCount)
{
	int nItem;
	CLineGraphItem* pNewLine = new CLineGraphItem;
	pNewLine->m_colorLine = colorLine;
	pNewLine->m_strInfo = str;
	pNewLine->m_widthLine = nWidth;

	//add the points to the line
	for (int i=0;i<nPointCount;i++)
	{
		nItem = pNewLine->m_pointArray.Add(*(pointArray+i));
		//do max checking
		if (pNewLine->m_pointArray[nItem].x > m_maxXPoint)
			m_maxXPoint = pNewLine->m_pointArray[nItem].x;
		if (pNewLine->m_pointArray[nItem].y > m_maxYPoint)
			m_maxYPoint = pNewLine->m_pointArray[nItem].y;
	}

	RecalcRect();
	return(m_chartLines.Add(pNewLine));
}

void CLineGraph::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if (m_rectChart.IsRectEmpty()) // First Time
		RecalcRect();

	int i,j;
	int xNew, yNew, xOld, yOld;
	int iTop, iLeft;
	int y = m_rectChart.top;
	int x = m_rectChart.left;
	int nPointCount=0;
	int nLegendSpread = 0;
	int nCurrentCol = 0;
	int nCurrentRow = 0;

	double fXRatio, fYRatio;
	CPen penGrid, penLine;
	CPoint* pointArray;
	CString str;


	CRect clientRect;
	GetClientRect(&clientRect);

	//draw the control area
	dc.SelectStockObject(WHITE_BRUSH);//control background
	dc.SelectStockObject(BLACK_PEN);//control outline
	dc.Rectangle(clientRect);

	//draw the graph area
	dc.SelectStockObject(WHITE_BRUSH);//graph background
	dc.SelectStockObject(BLACK_PEN);//graph outline
	dc.Rectangle(m_rectChart);

	//draw the legend area
	if (m_bShowLegend)
	{
		dc.SelectStockObject(WHITE_BRUSH);//graph background
		dc.SelectStockObject(BLACK_PEN);//graph outline
		dc.Rectangle(m_rectLegend);
		//center it if there are fewer items than columns
		if (m_nLegendCols > m_chartLines.GetSize())
			m_nLegendCols = m_chartLines.GetSize();
		nLegendSpread = m_rectLegend.Width()/m_nLegendCols;
	}

	//draw the chart title
	if (!m_strTitle.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontTitle);

		dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		dc.SetBkMode(TRANSPARENT);
		dc.ExtTextOut(1, 1, NULL, NULL, m_strTitle, NULL);
		dc.SelectObject(pOldFont);
	}

	//draw the x-axis title
	if (!m_strXAxis.IsEmpty())
	{
		CFont* pOldFont = dc.SelectObject(&m_fontXAxis);
		CSize sz = dc.GetTextExtent(m_strXAxis); 
		iLeft = m_rectChart.left + ((m_rectChart.Width() - sz.cx)/2);

		if(!m_strXFmt.IsEmpty())
		{
			//leave extra space to display the values if necessary

			iTop = m_rectChart.bottom + 1 + sz.cy;
		}
		else
		{
			iTop = m_rectChart.bottom + 1;
		}

		dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		dc.SetBkMode(TRANSPARENT);
		dc.ExtTextOut(iLeft, iTop, NULL, NULL, m_strXAxis, NULL);
		dc.SelectObject(pOldFont);
	}

	//draw the y-axis title
	if (!m_strYAxis.IsEmpty())
	{

		CFont* pOldFont = dc.SelectObject(&m_fontYAxis);
		dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		dc.SetBkMode(TRANSPARENT);
		CSize sz = dc.GetTextExtent(m_strYAxis);
		iTop = m_rectChart.bottom - ((m_rectChart.Height() - sz.cx)/2);

		dc.ExtTextOut(2, iTop, NULL, NULL, m_strYAxis, NULL);
		dc.SelectObject(pOldFont);
	}


	//calc the pixel ratios
	fXRatio = (float)m_maxXPoint/(float)m_rectChart.Width();
	fYRatio = (float)m_maxYPoint/(float)m_rectChart.Height();
	int nVLines;
	//draw the grid lines
	if (m_nGridLines > 0)
	{
		penGrid.CreatePen(PS_DASH, 1, m_colorGrid);
		dc.SelectObject(&penGrid);
		
		//Horizontal lines
		int nSpread = (int)(m_rectChart.Height()/(m_nGridLines+1));
		for (i=0;i<m_nGridLines;i++)
		{
			y += nSpread;
			dc.MoveTo(m_rectChart.left+1, y);
			dc.LineTo(m_rectChart.right-1, y);
			//write line values
			if(!m_strYFmt.IsEmpty())
			{
				CFont* pOldFont = dc.SelectObject(&m_fontYVals);
				str.Format(m_strYFmt, ((y-m_rectChart.top)*fYRatio));
				//CSize sz = dc.GetTextExtent(str);
				
				iTop = m_rectChart.bottom - (y - m_rectChart.top);

				dc.ExtTextOut(m_rectChart.left+1, iTop, NULL, NULL, str, NULL);
				dc.SelectObject(pOldFont);
			}
		}
		//write text for the upper limit of the grid
		if(!m_strYFmt.IsEmpty())
		{
			y += nSpread;

			CFont* pOldFont = dc.SelectObject(&m_fontYVals);
			str.Format(m_strYFmt, m_maxYPoint);
			//CSize sz = dc.GetTextExtent(str);
			
			iTop = m_rectChart.bottom - (y - m_rectChart.top);

			dc.ExtTextOut(m_rectChart.left+1, iTop, NULL, NULL, str, NULL);
			dc.SelectObject(pOldFont);
		}


		//vertical lines
		if(m_maxXPoint > 10)
			nVLines = 10;
		else
			nVLines = (int)m_maxXPoint;

		nSpread = (int)(m_rectChart.Width()/(nVLines+1));
		for (i=0;i<nVLines;i++)
		{
			x += nSpread;
			dc.MoveTo(x, m_rectChart.bottom-1);
			dc.LineTo(x, m_rectChart.top+1);
			//write line values
			if(!m_strXFmt.IsEmpty())
			{
				CFont* pOldFont = dc.SelectObject(&m_fontXVals);
				double fVal = ((x-m_rectChart.left)*fXRatio)+.6;
				str.Format(m_strXFmt, fVal);
				CSize sz = dc.GetTextExtent(str);
				iLeft = x - (sz.cx/2);
					

				dc.ExtTextOut(iLeft, m_rectChart.bottom + 1, NULL, NULL, str, NULL);
				dc.SelectObject(pOldFont);
			}
		}
		//write text for the upper limit of the grid
		if(!m_strXFmt.IsEmpty())
		{
			x += nSpread;

			CFont* pOldFont = dc.SelectObject(&m_fontXVals);
			str.Format(m_strXFmt, m_maxXPoint);
			CSize sz = dc.GetTextExtent(str);
			iLeft = x - (sz.cx/2);
				

			dc.ExtTextOut(iLeft, m_rectChart.bottom + 1, NULL, NULL, str, NULL);
			dc.SelectObject(pOldFont);
		}

	}

	//draw the lines
	//================================================================
	
	int nCount = m_chartLines.GetSize();
	for (i=0;i<nCount;i++)
	{
		//create a pen with the line's color and width
		penLine.CreatePen(PS_SOLID, m_chartLines[i]->m_widthLine, m_chartLines[i]->m_colorLine);
		//draw the line
		dc.SelectObject(penLine);

		//create a CPoint array to hold the screen coordinates
		nPointCount = m_chartLines[i]->m_pointArray.GetSize();
		pointArray = (CPoint*) malloc((nPointCount*sizeof(CPoint)));
			for (j=0;j<nPointCount;j++)
			{
				xOld = (int)(m_chartLines[i]->m_pointArray[j].x/fXRatio);
				yOld = (int)(m_chartLines[i]->m_pointArray[j].y/fYRatio);
				//calculate the correct point possition.
				xNew = xOld + m_nYLabelWidth;
				//yNew = clientRect.Height() - m_nXLabelHeight - yOld;
				yNew = clientRect.Height() - (clientRect.bottom - m_rectChart.bottom) - yOld;

				//add the newly calculated point to the array of CPoints
				*(pointArray+j) = CPoint(xNew, yNew);
			}

		//draw the line
		dc.Polyline(pointArray, nPointCount);

		//add the line to the legend
		if(m_bShowLegend)
		{

			//Calculate the box location
			int nTop = (m_LegTextHeight * nCurrentRow) + m_rectLegend.top + 2;
			int nLeft = (nLegendSpread * nCurrentCol) + m_rectLegend.left + 2;
			//Draw the box
			CRect rectColor(nLeft, nTop, (nLeft + m_LegTextHeight), (nTop + m_LegTextHeight));
			dc.FillSolidRect(rectColor, m_chartLines[i]->m_colorLine);
			dc.DrawEdge(rectColor, EDGE_SUNKEN, BF_RECT);
			//Write the text
			dc.ExtTextOut(rectColor.right + 1, rectColor.top - 1, ETO_CLIPPED, CRect(rectColor.right+1, rectColor.top-1, rectColor.left+nLegendSpread, rectColor.bottom), m_chartLines[i]->m_strInfo, NULL);

			//increment the column counter for next time
			nCurrentCol += 1;
			if (nCurrentCol >= m_nLegendCols)
			{
				nCurrentRow += 1;
				nCurrentCol = 0;
			}


		}

		penLine.DeleteObject();
		free(pointArray);

	}


}

