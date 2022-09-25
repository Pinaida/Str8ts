// Str8tsView.h : Schnittstelle der Klasse CStr8tsView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STR8TSVIEW_H_INCLUDED_)
#define AFX_STR8TSVIEW_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStr8tsView : public CFormView
{
protected: // Nur aus Serialisierung erzeugen
	CStr8tsView();
	DECLARE_DYNCREATE(CStr8tsView)

public:
	//{{AFX_DATA(CStr8tsView)
	enum { IDD = IDD_STR8TS_FORM };
	//}}AFX_DATA

// Attribute
public:
	CStr8tsDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStr8tsView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnInitialUpdate(); // das erste mal nach der Konstruktion aufgerufen
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CStr8tsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void	OnCapture(void);

protected:

// Generierte Message-Map-Funktionen
protected:
	int		KlickSelect(CPoint point, BOOL Dbl=FALSE, BOOL Multi=FALSE);
	void	End(void);
	BOOL	OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	int		m_CellExt;			// cell extension width / height
	int		m_CellDist;			// Distance between cells
	int		m_Margin1;			// margin left/top
	int		m_Margin2;			// margin right/bottom
	int		m_MarginRight;		// Textanfang 
	int		m_TextHeight;		// text size
	int		m_CellPos[10];		// cell positions
	int		m_Line1, m_Line2;	// line width cell/block
	int		m_FootLine;			// Foot line position [Pixel]
	BOOL	m_IsPrinting;		// view is printing
	int		m_LinkY;			// Hyperlink ypos
	int		m_CommentY;			// Kommentarzeile ypos
	int		m_PauseY;			// Pause ypos
	void	Draw(CDC* pDC, CPrintInfo *pInfo=NULL);
	void	CellDraw(CDC * pDC, int Cell, int Val, BOOL Hint);
	BOOL	m_CtrlState;		// Keyboard Shift Key
	BOOL	m_LbuttonDn;		// left mouse button down
	CFont	m_FontField, m_FontHint, m_FontHdr;	// Font for draw/print
	CStr8tsDoc * m_pDoc;

	//{{AFX_MSG(CStr8tsView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in Str8tsView.cpp
inline CStr8tsDoc* CStr8tsView::GetDocument()
   { return (CStr8tsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STR8TSVIEW_H_INCLUDED_)
