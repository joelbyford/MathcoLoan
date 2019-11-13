#if !defined(AFX_LINEGRAPH_H__8D682054_0E0E_4822_A046_2AF2F8B4A713__INCLUDED_)
#define AFX_LINEGRAPH_H__8D682054_0E0E_4822_A046_2AF2F8B4A713__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LineGraph.h : header file
//
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CLineGraphPoint object - floating point replacement for CPoint
class CLineGraphPoint
{
public:
	CLineGraphPoint() {;}
	CLineGraphPoint(double xVal, double yVal) {x=xVal;y=yVal;}
	double x;
	double y;
};

/////////////////////////////////////////////////////////////////////////////
// CLineGraphItem object
class CLineGraphItem : public CObject
{
public:
	CLineGraphItem();
	~CLineGraphItem();

	CString m_strInfo;
	CArray<CLineGraphPoint, CLineGraphPoint&> m_pointArray;
	COLORREF m_colorLine;
	int m_widthLine;
};

typedef CTypedPtrArray <CObArray, CLineGraphItem*> CGraphLineArray;
/////////////////////////////////////////////////////////////////////////////
// CLineGraph window


class CLineGraph : public CWnd
{
// Construction
public:
	CLineGraph();

// Attributes
public:

	CGraphLineArray m_chartLines;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineGraph)
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont m_fontTitle;
	CFont m_fontInfo;
	CFont m_fontXAxis;
	CFont m_fontYAxis;
	CFont m_fontYVals;
	CFont m_fontXVals;
	int m_nGridLines;
	int m_nLegendCols;
	BOOL m_bShowLegend;
	COLORREF m_colorGrid;
	CString m_strYFmt;
	CString m_strXFmt;

	void SetTitle(const CString& str);
	void SetXLabel(const CString& str);
	void SetYLabel(const CString& str);
	void GetItemColor(int i, COLORREF& color);
	void Reset();
	void RecalcRect();
	static BOOL RegisterWndClass(HINSTANCE hInstance);
	int AddLine(COLORREF colorLine, int nWidth, const CString& str, CLineGraphPoint* pointArray, int nPointCount);

	virtual ~CLineGraph();
private:
	CString m_strTitle;
	CString m_strYAxis;
	CString m_strXAxis;
	int m_nTitleHeight;
	int m_LegTextHeight;
	int m_nYLabelWidth;
	int m_nXLabelHeight;
	CRect m_rectLegend;
	CRect m_rectChart;
	double m_maxYPoint;
	double m_maxXPoint;
	// Generated message map functions
protected:
	//{{AFX_MSG(CLineGraph)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEGRAPH_H__8D682054_0E0E_4822_A046_2AF2F8B4A713__INCLUDED_)
