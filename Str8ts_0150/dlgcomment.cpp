// DlgComment.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Str8ts.h"
#include "DlgComment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld C_DlgComment 


CDlgComment::CDlgComment(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgComment::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgComment)
	m_Comment = _T("");
	m_Stufe = 0;
	m_sGeraten = _T("-");
	//}}AFX_DATA_INIT
}


void CDlgComment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgComment)
	DDX_Text(pDX, IDC_COMMENT, m_Comment);
	DDX_Radio(pDX, IDC_STUFE1, m_Stufe);
	DDX_CBString(pDX, IDC_GERATEN, m_sGeraten);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgComment, CDialog)
	//{{AFX_MSG_MAP(CDlgComment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten C_DlgComment 


