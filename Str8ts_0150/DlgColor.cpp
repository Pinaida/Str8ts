// DlgColor.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgColor 


CDlgColor::CDlgColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgColor)
	//}}AFX_DATA_INIT
}


void CDlgColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgColor)
	DDX_Control(pDX, IDC_COLOR_SHOW, m_ColorShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgColor, CDialog)
	//{{AFX_MSG_MAP(CDlgColor)
	ON_BN_CLICKED(IDC_COLOR_BG, OnColorBg)
	ON_BN_CLICKED(IDC_COLOR_F1, OnColorF1)
	ON_BN_CLICKED(IDC_COLOR_F2, OnColorF2)
	ON_BN_CLICKED(IDC_COLOR_F3, OnColorF3)
	ON_BN_CLICKED(IDC_COLOR_T1, OnColorT1)
	ON_BN_CLICKED(IDC_COLOR_T2, OnColorT2)
	ON_BN_CLICKED(IDC_COL_RESET, OnColReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgColor 

void CDlgColor::OnColorBg() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.Feld = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}

void CDlgColor::OnColorF1() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.Zelle1 = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}

void CDlgColor::OnColorF2() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.Zelle2 = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}

void CDlgColor::OnColorF3() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.ZelleAkt = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}

void CDlgColor::OnColorT1() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.TextRW = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}


void CDlgColor::OnColorT2() 
{
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_Farben.TextRO = dlg.GetColor();
		m_ColorShow.m_Farben = m_Farben;
		Invalidate();
	}
}



BOOL CDlgColor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ColorShow.m_Farben = m_Farben;	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgColor::OnColReset() 
{
	m_Farben.Feld		= DEF_COL_BG;
	m_Farben.Zelle1		= DEF_COL_F1;
	m_Farben.Zelle2		= DEF_COL_F2;
	m_Farben.ZelleAkt	= DEF_COL_F3;
	m_Farben.TextRW		= DEF_COL_T1;
	m_Farben.TextRO		= DEF_COL_T2;
	m_ColorShow.m_Farben = m_Farben;
	Invalidate();
}
