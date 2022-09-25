// MainFrm.cpp : Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_UNDO,	OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO,	OnEditRedo)
	ON_COMMAND(ID_EXTRA_LOGDEL, OnDeleteLog)
	ON_COMMAND(ID_EXTRA_FREEZE, OnFreeze)
	ON_COMMAND(ID_EXTRA_MELT,   OnMelt)
	ON_COMMAND(ID_EXTRA_AGAIN,  OnAgain)
	ON_COMMAND(ID_DATEI_NEU,    OnFileNew)
	ON_COMMAND(ID_DATEI_OEFFNEN,OnOpen)
	ON_COMMAND(ID_DATEI_VORLAGE,OnOpenTemplate)
	ON_COMMAND(ID_DATEI_SAVE,   OnSave)
	ON_COMMAND(ID_DATEI_SAVE_U, OnSaveAs)
	ON_COMMAND(ID_SOLVE_DISPLAY,		OnPossible)
	ON_COMMAND(ID_EXTRA_EINBLEND, OnEinblend)
	ON_COMMAND(ID_EXTRA_CHECK,  OnCheck)
	ON_COMMAND(ID_EXTRA_SOLVE,  OnSolve)
	ON_COMMAND(ID_X_SOLVE,      OnSolveF)
	ON_COMMAND(ID_X_FR_ME,      OnFreezeMelt)
	ON_COMMAND(ID_X_SUPPR,      OnSuppr)
	ON_COMMAND(ID_SOLVE_AUTO_ENTER,		OnAutoEnter)
	ON_COMMAND(ID_DATEI_COMMENT,OnComment)
	ON_COMMAND(ID_TIME_PAUSE,OnPause)
	ON_COMMAND(ID_CAPTURE,OnCapture)
	ON_COMMAND(ID_EXTRA_COLOR,  OnColor)
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SOLVE_RANGE_CHECK,	OnSolveRangeCheck)
	ON_COMMAND(ID_SOLVE_SINGLE,			OnSolveSingle)
	ON_COMMAND(ID_SOLVE_SURE_CAND,		OnSolveSureCandidate)
	ON_COMMAND(ID_SOLVE_STRANDED,		OnSolveStrandedDigits)
	ON_WM_INITMENU()
	ON_COMMAND(ID_EXTRA_SETTINGS,OnSettings)
	ON_WM_TIMER()
	ON_COMMAND(ID_EXTRA_AUSBLEND,		OnAusblend)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Konstruktion/Zerstörung

CMainFrame::CMainFrame()
{
}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Symbolleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Statusleiste konnte nicht erstellt werden\n");
		return -1;      // Fehler bei Erstellung
	}

	// ZU ERLEDIGEN: Löschen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_Timer = SetTimer(0x1234, 1000, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
    cs.x = wndMain.x;
    cs.y = wndMain.y; 
    cs.cx = wndMain.cx; 
    cs.cy = wndMain.cy;
	return TRUE;
}

void CMainFrame::OnEditUndo(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnLogUndo();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}

void CMainFrame::OnEditRedo(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnLogRedo();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
} 


void CMainFrame::OnDeleteLog(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnLogDelete();
}


void CMainFrame::OnFreeze(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnFreeze();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnMelt(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnMelt();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnAgain(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnAgain();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnFileNew(void)
{
	CMenu * pMen = GetMenu();
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnNew();
	SetTitle();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	ShowWindow(SW_RESTORE);
	pView->Invalidate();
}

void CMainFrame::OnOpen(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnOpen();
	SetTitle();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnOpenTemplate(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnOpenTemplate();
	SetTitle();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnSave(void)
{
	bool bMaximize = false;
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	if(pDoc->AutoFreeze())
	{
		pView->Invalidate();
		bMaximize = true;
	}
	pDoc->OnSave();
	SetTitle();
	if(bMaximize)
		ShowWindow(SW_SHOWMAXIMIZED);
	pView->Invalidate();
}


void CMainFrame::OnSaveAs(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnSaveAs();
	SetTitle();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnPossible(void)						// Mögliche Zahlen anzeigen
{
//	CMenu * pMen = GetMenu();
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveDisplay = !pDoc->m_SolveDisplay;
	UpdateMenue();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnAutoEnter(void)						// Autoatische Eingabe
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveAutoEnter = !pDoc->m_SolveAutoEnter;
	UpdateMenue();
	pDoc->Solver();
	pDoc->CheckField();
	pDoc->SetModifiedFlag();
	if(pDoc->CheckSolved())
		pDoc->Finish();
}


void CMainFrame::OnComment(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnComment();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnPause(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnPause();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}

void CMainFrame::OnCapture(void)
{
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->OnCapture();
}

void CMainFrame::OnEinblend(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->Einblend();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnCheck(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->Check();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnSolve(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnSolve();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnSolveF(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnSolveF();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnFreezeMelt(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->OnFreezeMelt();
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnSuppr(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	CSuppress dlg;
	int ix=pDoc->GetSelect();
	dlg.m_State=pDoc->m_Info[ix];
	dlg.DoModal();
	pDoc->m_Info[ix]=dlg.m_State;
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::SetTitle(void)
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	CString str;
	str.Format("%s - %s", pDoc->m_DocName, sVers1);
	SetWindowText(str);
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	SetTitle();
	return CFrameWnd::OnEraseBkgnd(pDC);
}

void CMainFrame::OnColor(void)
{
	CDlgColor dlg;
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	dlg.m_Farben = Farben;
	if(dlg.DoModal() == IDOK)
	{
		Farben = dlg.m_Farben;
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_BG, Farben.Feld);
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_F1, Farben.Zelle1);
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_F2, Farben.Zelle2);
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_F3, Farben.ZelleAkt);
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_T1, Farben.TextRW);
		theApp.WriteProfileInt(KEY_SETTINGS, KEY_COL_T2, Farben.TextRO);
		pView->Invalidate();
	}
}

void CMainFrame::OnSettings(void)
{
	CDlgSettings dlg;
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	int		FieldSize = pDoc->m_FieldSize;
	dlg.m_WebLink = sLinkStr8ts;
	dlg.m_FieldSize = (FieldSize == 10)? TRUE : FALSE;
	if(dlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		sLinkStr8ts = dlg.m_WebLink;
		if(dlg.m_FieldSize != FieldSize)
		{
			if(dlg.m_FieldSize)
				pDoc->SetFieldSize(10);
			else
				pDoc->SetFieldSize(9);
			pDoc->OnNew();
		}
		pView->Invalidate();
		theApp.WriteProfileString(KEY_SETTINGS, KEY_WEB_ST, sLinkStr8ts);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame Nachrichten-Handler




void CMainFrame::OnClose() 
{
	RECT	rc;
	GetWindowRect(&rc);
	wndMain.max = (GetStyle() & WS_MAXIMIZE)? TRUE : FALSE;
	if(!wndMain.max)
	{
		wndMain.x = rc.left;
		wndMain.y = rc.top;
		wndMain.cx = rc.right - rc.left;
		wndMain.cy = rc.bottom - rc.top;
	}
	CFrameWnd::OnClose();
}


void CMainFrame::OnAusblend()
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_Ausblendmode = !pDoc->m_Ausblendmode;
	UpdateMenue();
}


void CMainFrame::OnSolveSureCandidate() 
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveSureCandidate = !pDoc->m_SolveSureCandidate;
	pDoc->Solver();
}

void CMainFrame::OnSolveStrandedDigits() 
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveSureCandidate = !pDoc->m_SolveStrandedDigits;
	pDoc->Solver();
}

void CMainFrame::OnSolveRangeCheck() 
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveRangeCheck = !pDoc->m_SolveRangeCheck;
	pDoc->Solver();
}


void CMainFrame::OnSolveSingle() 
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->m_SolveSingle = !pDoc->m_SolveSingle;
	pDoc->Solver();
}


void CMainFrame::UpdateMenue()
{
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	UpdateMenueItem(ID_EXTRA_AUSBLEND,		pDoc->m_Ausblendmode);
	UpdateMenueItem(ID_SOLVE_SURE_CAND,		pDoc->m_SolveSureCandidate);
	UpdateMenueItem(ID_SOLVE_RANGE_CHECK,	pDoc->m_SolveRangeCheck);
	UpdateMenueItem(ID_SOLVE_AUTO_ENTER,	pDoc->m_SolveAutoEnter);
	UpdateMenueItem(ID_SOLVE_DISPLAY,		pDoc->m_SolveDisplay);
	UpdateMenueItem(ID_SOLVE_SINGLE,		pDoc->m_SolveSingle);
	UpdateMenueItem(ID_SOLVE_STRANDED,		pDoc->m_SolveStrandedDigits);
}

void CMainFrame::UpdateMenueItem(UINT Id, BOOL bStatus)
{
	UINT check, style;
	int	 ix;
	check = (bStatus)? MF_CHECKED : MF_UNCHECKED;
	check |= MF_BYCOMMAND;
	CMenu * pMen = GetMenu();
	pMen->CheckMenuItem(Id, check);
	ix = m_wndToolBar.CommandToIndex(Id);
	if (ix > 0)
	{
		style = m_wndToolBar.GetButtonStyle(ix);
		if (bStatus)
			style |= 0x10000;
		else
			style &= ~0x10000;
		m_wndToolBar.SetButtonStyle(ix, style);
	}
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	pView->Invalidate();
}


void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	UpdateMenue();
	CFrameWnd::OnInitMenu(pMenu);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	CStr8tsView *pView = (CStr8tsView *)GetActiveView();
	CStr8tsDoc * pDoc = (CStr8tsDoc *)GetActiveDocument();
	pDoc->TimeUpdate();
	pView->Invalidate();
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();

	KillTimer(m_Timer);
	m_Timer=NULL;
}
