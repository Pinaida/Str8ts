// DlgSettings.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "str8ts.h"
#include "DlgDefaultSolver.h"
#include "DlgSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSettings 


CDlgSettings::CDlgSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettings)
	m_WebLink = _T("");
	m_FieldSize = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettings)
	DDX_Text(pDX, IDC_WEB_LINK, m_WebLink);
	DDX_Check(pDX, IDC_FIELD_SIZE, m_FieldSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettings, CDialog)
	//{{AFX_MSG_MAP(CDlgSettings)
	ON_BN_CLICKED(IDC_DEFAULT_SOLVER, OnDefaultSolver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSettings 

void CDlgSettings::OnDefaultSolver() 
{
	CDlgDefaultSolver dlg;
	dlg.DoModal();
}
