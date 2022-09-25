// DlgDefaultSolver.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDefaultSolver 


CDlgDefaultSolver::CDlgDefaultSolver(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDefaultSolver::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDefaultSolver)
	m_AE0 = FALSE;
	m_AE1 = FALSE;
	m_AE2 = FALSE;
	m_AE3 = FALSE;
	m_AE4 = FALSE;
	m_AE5 = FALSE;
	m_MZ0 = FALSE;
	m_MZ1 = FALSE;
	m_MZ2 = FALSE;
	m_MZ3 = FALSE;
	m_MZ4 = FALSE;
	m_MZ5 = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDefaultSolver::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDefaultSolver)
	DDX_Check(pDX, IDC_AE0, m_AE0);
	DDX_Check(pDX, IDC_AE1, m_AE1);
	DDX_Check(pDX, IDC_AE2, m_AE2);
	DDX_Check(pDX, IDC_AE3, m_AE3);
	DDX_Check(pDX, IDC_AE4, m_AE4);
	DDX_Check(pDX, IDC_AE5, m_AE5);
	DDX_Check(pDX, IDC_MZ0, m_MZ0);
	DDX_Check(pDX, IDC_MZ1, m_MZ1);
	DDX_Check(pDX, IDC_MZ2, m_MZ2);
	DDX_Check(pDX, IDC_MZ3, m_MZ3);
	DDX_Check(pDX, IDC_MZ4, m_MZ4);
	DDX_Check(pDX, IDC_MZ5, m_MZ5);
	DDX_Check(pDX, IDC_SC0, m_SC0);
	DDX_Check(pDX, IDC_SC1, m_SC1);
	DDX_Check(pDX, IDC_SC2, m_SC2);
	DDX_Check(pDX, IDC_SC3, m_SC3);
	DDX_Check(pDX, IDC_SC4, m_SC4);
	DDX_Check(pDX, IDC_SC5, m_SC5);
	DDX_Check(pDX, IDC_SD0, m_SD0);
	DDX_Check(pDX, IDC_SD1, m_SD1);
	DDX_Check(pDX, IDC_SD2, m_SD2);
	DDX_Check(pDX, IDC_SD3, m_SD3);
	DDX_Check(pDX, IDC_SD4, m_SD4);
	DDX_Check(pDX, IDC_SD5, m_SD5);
	DDX_Check(pDX, IDC_SI0, m_SI0);
	DDX_Check(pDX, IDC_SI1, m_SI1);
	DDX_Check(pDX, IDC_SI2, m_SI2);
	DDX_Check(pDX, IDC_SI3, m_SI3);
	DDX_Check(pDX, IDC_SI4, m_SI4);
	DDX_Check(pDX, IDC_SI5, m_SI5);
	DDX_Check(pDX, IDC_RC0, m_RC0);
	DDX_Check(pDX, IDC_RC1, m_RC1);
	DDX_Check(pDX, IDC_RC2, m_RC2);
	DDX_Check(pDX, IDC_RC3, m_RC3);
	DDX_Check(pDX, IDC_RC4, m_RC4);
	DDX_Check(pDX, IDC_RC5, m_RC5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDefaultSolver, CDialog)
	//{{AFX_MSG_MAP(CDlgDefaultSolver)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgDefaultSolver 

BOOL CDlgDefaultSolver::OnInitDialog() 
{
	m_AE0 = bAE[0];
	m_AE1 = bAE[1];
	m_AE2 = bAE[2];
	m_AE3 = bAE[3];
	m_AE4 = bAE[4];
	m_AE5 = bAE[5];
	m_MZ0 = bMZ[0];
	m_MZ1 = bMZ[1];
	m_MZ2 = bMZ[2];
	m_MZ3 = bMZ[3];
	m_MZ4 = bMZ[4];
	m_MZ5 = bMZ[5];
	m_SC0 = bSC[0];
	m_SC1 = bSC[1];
	m_SC2 = bSC[2];
	m_SC3 = bSC[3];
	m_SC4 = bSC[4];
	m_SC5 = bSC[5];
	m_SD0 = bSD[0];
	m_SD1 = bSD[1];
	m_SD2 = bSD[2];
	m_SD3 = bSD[3];
	m_SD4 = bSD[4];
	m_SD5 = bSD[5];
	m_SI0 = bSI[0];
	m_SI1 = bSI[1];
	m_SI2 = bSI[2];
	m_SI3 = bSI[3];
	m_SI4 = bSI[4];
	m_SI5 = bSI[5];
	m_RC0 = bRC[0];
	m_RC1 = bRC[1];
	m_RC2 = bRC[2];
	m_RC3 = bRC[3];
	m_RC4 = bRC[4];
	m_RC5 = bRC[5];

	UpdateData(FALSE);
	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgDefaultSolver::OnOK() 
{
	UpdateData(TRUE);
	bAE[0] = m_AE0;
	bAE[1] = m_AE1;
	bAE[2] = m_AE2;
	bAE[3] = m_AE3;
	bAE[4] = m_AE4;
	bAE[5] = m_AE5;
	bMZ[0] = m_MZ0;
	bMZ[1] = m_MZ1;
	bMZ[2] = m_MZ2;
	bMZ[3] = m_MZ3;
	bMZ[4] = m_MZ4;
	bMZ[5] = m_MZ5;
	bSC[0] = m_SC0;
	bSC[1] = m_SC1;
	bSC[2] = m_SC2;
	bSC[3] = m_SC3;
	bSC[4] = m_SC4;
	bSC[5] = m_SC5;
	bSD[0] = m_SD0;
	bSD[1] = m_SD1;
	bSD[2] = m_SD2;
	bSD[3] = m_SD3;
	bSD[4] = m_SD4;
	bSD[5] = m_SD5;
	bSI[0] = m_SI0;
	bSI[1] = m_SI1;
	bSI[2] = m_SI2;
	bSI[3] = m_SI3;
	bSI[4] = m_SI4;
	bSI[5] = m_SI5;
	bRC[0] = m_RC0;
	bRC[1] = m_RC1;
	bRC[2] = m_RC2;
	bRC[3] = m_RC3;
	bRC[4] = m_RC4;
	bRC[5] = m_RC5;
		
	CDialog::OnOK();
}
