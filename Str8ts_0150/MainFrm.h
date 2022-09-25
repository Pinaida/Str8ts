// MainFrm.h : Schnittstelle der Klasse CMainFrame
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__2DD71266_BBD3_48E4_BA2F_4BC07BC619F0__INCLUDED_)
#define AFX_MAINFRM_H__2DD71266_BBD3_48E4_BA2F_4BC07BC619F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // Nur aus Serialisierung erzeugen
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementierung
public:
	void SetTitle(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebundene Elemente der Steuerleiste
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	UINT		m_Timer;
	CToolBarCtrl	xx;

// Generierte Message-Map-Funktionen
protected:
	void OnAusblend(void);
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnDeleteLog();
	afx_msg void OnFreeze();
	afx_msg void OnMelt();
	afx_msg void OnAgain();
	afx_msg void OnFileNew();
	afx_msg void OnOpen();
	afx_msg void OnOpenTemplate();
	afx_msg void OnSave();
	afx_msg void OnSaveAs();
	afx_msg void OnPossible();
	afx_msg void OnEinblend();
	afx_msg void OnCheck();
	afx_msg void OnSolve();
	afx_msg void OnSolveF();
	afx_msg void OnFreezeMelt();
	afx_msg void OnSuppr();
	afx_msg void OnAutoEnter();
	afx_msg void OnComment();
	afx_msg void OnColor();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg void OnSolveRangeCheck();
	afx_msg void OnSolveSingle();
	afx_msg void OnSolveSureCandidate();
	afx_msg void OnSolveStrandedDigits();
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnSettings();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnPause();
	afx_msg void OnCapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateMenueItem(UINT Id, BOOL bStatus);
	void UpdateMenue(void);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAINFRM_H__2DD71266_BBD3_48E4_BA2F_4BC07BC619F0__INCLUDED_)
