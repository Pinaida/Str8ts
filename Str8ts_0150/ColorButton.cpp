// ColorButton.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Str8ts.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CColorButton 



void CColorButton::OnPaint() 
{
	CRect rc, rc1;
	CPaintDC dc(this);		// device context for painting
	GetClientRect(&rc);	

	int	x1, x2, x3, x4, x5, x6, y1, y2, y3, y4;
	dc.FillRect(&rc, &CBrush(m_Farben.Feld));			// fill background
	rc1.top		= (int)(rc.bottom * 0.05);
	rc1.bottom	= (int)(rc.bottom * 0.95);
	rc1.left	= (int)(rc.right * 0.05);
	rc1.right	= (int)(rc.right * 0.30);
	x1 = rc1.left + 5;
	x2 = rc1.right - 5;
	y1 = (int)(rc.bottom * 0.2);
	y2 = (int)(rc.bottom * 0.4);
	y3 = (int)(rc.bottom * 0.6);
	y4 = (int)(rc.bottom * 0.8);
	dc.FillRect(&rc1, &CBrush(m_Farben.Zelle1));		// field color 1
	rc1.left	= (int)(rc.right * 0.35);
	rc1.right	= (int)(rc.right * 0.60);
	x3 = rc1.left + 5;
	x4 = rc1.right - 5;
	dc.FillRect(&rc1, &CBrush(m_Farben.Zelle2));		// field color 2
	rc1.left	= (int)(rc.right * 0.65);
	rc1.right	= (int)(rc.right * 0.90);
	x5 = rc1.left + 5;
	x6 = rc1.right - 5;
	dc.FillRect(&rc1, &CBrush(m_Farben.ZelleAkt));		// field activ
	rc1.top		= y1;
	rc1.bottom	= y2;
	rc1.left	= x1;
	rc1.right	= x2;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRW));		// text color in F1
	rc1.left	= x3;
	rc1.right	= x4;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRW));		// text color in F1
	rc1.left	= x5;
	rc1.right	= x6;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRW));		// text color in F1
	rc1.top		= y3;
	rc1.bottom	= y4;
	rc1.left	= x1;
	rc1.right	= x2;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRO));		// text color in F1
	rc1.left	= x3;
	rc1.right	= x4;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRO));		// text color in F1
	rc1.left	= x5;
	rc1.right	= x6;
	dc.FillRect(&rc1, &CBrush(m_Farben.TextRO));		// text color in F1

}
