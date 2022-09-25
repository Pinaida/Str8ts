// Suppress.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Str8ts.h"
#include "Suppress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSuppress 


CSuppress::CSuppress(CWnd* pParent)
	: CDialog(CSuppress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSuppress)
	m_State=0;
	//}}AFX_DATA_INIT
	ClearAll();
}


void CSuppress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuppress)
	DDX_Check(pDX, IDC_SUPPR_1, m_Hide1);
	DDX_Check(pDX, IDC_SUPPR_2, m_Hide2);
	DDX_Check(pDX, IDC_SUPPR_3, m_Hide3);
	DDX_Check(pDX, IDC_SUPPR_4, m_Hide4);
	DDX_Check(pDX, IDC_SUPPR_5, m_Hide5);
	DDX_Check(pDX, IDC_SUPPR_6, m_Hide6);
	DDX_Check(pDX, IDC_SUPPR_7, m_Hide7);
	DDX_Check(pDX, IDC_SUPPR_8, m_Hide8);
	DDX_Check(pDX, IDC_SUPPR_9, m_Hide9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSuppress, CDialog)
	//{{AFX_MSG_MAP(CSuppress)
	ON_BN_CLICKED(IDC_SUPPR_NONE, OnSupprNone)
	ON_BN_CLICKED(IDC_SUPPR_OK, OnSupprOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CSuppress 

void CSuppress::OnSupprNone() 
{
	ClearAll();
	UpdateData(FALSE);	
}


void CSuppress::ClearAll()
{
	m_Hide1 = FALSE;
	m_Hide2 = FALSE;
	m_Hide3 = FALSE;
	m_Hide4 = FALSE;
	m_Hide5 = FALSE;
	m_Hide6 = FALSE;
	m_Hide7 = FALSE;
	m_Hide8 = FALSE;
	m_Hide9 = FALSE;
}


BOOL CSuppress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Hide1 = (m_State & 0x0002)? TRUE : FALSE;
	m_Hide2 = (m_State & 0x0004)? TRUE : FALSE;
	m_Hide3 = (m_State & 0x0008)? TRUE : FALSE;
	m_Hide4 = (m_State & 0x0010)? TRUE : FALSE;
	m_Hide5 = (m_State & 0x0020)? TRUE : FALSE;
	m_Hide6 = (m_State & 0x0040)? TRUE : FALSE;
	m_Hide7 = (m_State & 0x0080)? TRUE : FALSE;
	m_Hide8 = (m_State & 0x0100)? TRUE : FALSE;
	m_Hide9 = (m_State & 0x0200)? TRUE : FALSE;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


void CSuppress::OnSupprOk() 
{
	UpdateData(TRUE);
	m_State=0;
	if(m_Hide1) m_State |= 0x0002;
	if(m_Hide2) m_State |= 0x0004;
	if(m_Hide3) m_State |= 0x0008;
	if(m_Hide4) m_State |= 0x0010;
	if(m_Hide5) m_State |= 0x0020;
	if(m_Hide6) m_State |= 0x0040;
	if(m_Hide7) m_State |= 0x0080;
	if(m_Hide8) m_State |= 0x0100;
	if(m_Hide9) m_State |= 0x0200;
	EndDialog(0);
}
