// Str8tsView.cpp : Implementierung der Klasse CStr8tsView
//

#include "stdafx.h"
#include "Module.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStr8tsView

IMPLEMENT_DYNCREATE(CStr8tsView, CFormView)

BEGIN_MESSAGE_MAP(CStr8tsView, CFormView)
	//{{AFX_MSG_MAP(CStr8tsView)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStr8tsView Konstruktion/Destruktion

CStr8tsView::CStr8tsView()
	: CFormView(CStr8tsView::IDD)
{
	//{{AFX_DATA_INIT(CStr8tsView)
	m_CtrlState = FALSE;
	m_LbuttonDn = FALSE;
	//}}AFX_DATA_INIT
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
}

CStr8tsView::~CStr8tsView()
{
}

void CStr8tsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStr8tsView)
	//}}AFX_DATA_MAP
}

BOOL CStr8tsView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}

void CStr8tsView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
//	ResizeParentToFit();
	m_pDoc = GetDocument();
	
}

/////////////////////////////////////////////////////////////////////////////
// CStr8tsView Drucken

BOOL CStr8tsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CStr8tsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CStr8tsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

void CStr8tsView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	Draw(pDC, pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CStr8tsView Diagnose

#ifdef _DEBUG
void CStr8tsView::AssertValid() const
{
	CFormView::AssertValid();
}


void CStr8tsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


CStr8tsDoc* CStr8tsView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStr8tsDoc)));
	return (CStr8tsDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CStr8tsView Nachrichten-Handler

void CStr8tsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{	
	if(nChar == 0x11)						// Strg
		m_CtrlState = TRUE;
	if((nChar >= 0x60) && (nChar <= 0x69))	//Ziffern auf dem Cursorblock
		nChar -= 0x30;
	if(!OnChar(nChar, nRepCnt, nFlags))
		CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CStr8tsView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == 0x11)						// Strg
		m_CtrlState = FALSE;
	CFormView::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL CStr8tsView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	RECT rc;

	CWnd * pWnd = pDC->GetWindow();
	pWnd->GetClientRect(&rc);
	return TRUE;
}


void CStr8tsView::OnDraw(CDC* pDC) 
{
	Draw(pDC, NULL);
}


void CStr8tsView::Draw(CDC* pDC, CPrintInfo *pInfo) 
{

	int		i, n;
	RECT	rc, rc2;
	CBitmap bm;											// Bitmap Info-Struktur
	CDC mdc;											// Devicekotext
	CString msg, str;
	int FieldSize = m_pDoc->m_FieldSize;
	int nFields = m_pDoc->m_nFields;


	m_IsPrinting = pDC->IsPrinting();
	if(m_IsPrinting)
		rc = pInfo->m_rectDraw;
	else
	{
		CWnd * pWnd = pDC->GetWindow();
		pWnd->GetClientRect(&rc);
	}
	bm.CreateCompatibleBitmap(pDC, rc.right, rc.bottom);
	mdc.CreateCompatibleDC(pDC);						// Speicher-Devicecontext anlegen
	mdc.SelectObject(&bm);								// Bitmap in Speicher laden
	if(m_IsPrinting)
	{
		mdc.FillRect(&rc, &CBrush(RGB(255,255,255)));	// fill background
		rc.left		= rc.left/3;
		rc.bottom	= rc.bottom / 3;
	}
	else
	{
		mdc.FillRect(&rc, &CBrush(Farben.Feld));		// fill background
	}
	if(rc.right > rc.bottom)
		i = rc.bottom;
	else
		i = rc.right;
	m_FootLine = i / 11;								// Höhe der Kommentarzeile
	m_Margin1	= 30;
	m_Margin2	= 10;
	m_CellDist	= 1;

	i = rc.bottom - 10;									// unterer Rand
	if(rc.right < rc.bottom)
		i = rc.right;
	m_CellExt	= (i - m_Margin1 - m_Margin2 - (FieldSize+1) * m_CellDist) / FieldSize;
	m_CellPos[0] = m_Margin1 + m_CellDist;
	m_CellPos[1] = m_CellPos[0] + m_CellExt + m_CellDist;
	m_CellPos[2] = m_CellPos[1] + m_CellExt + m_CellDist;
	m_CellPos[3] = m_CellPos[2] + m_CellExt + m_CellDist;
	m_CellPos[4] = m_CellPos[3] + m_CellExt + m_CellDist;
	m_CellPos[5] = m_CellPos[4] + m_CellExt + m_CellDist;
	m_CellPos[6] = m_CellPos[5] + m_CellExt + m_CellDist;
	m_CellPos[7] = m_CellPos[6] + m_CellExt + m_CellDist;
	m_CellPos[8] = m_CellPos[7] + m_CellExt + m_CellDist;
	m_CellPos[9] = m_CellPos[8] + m_CellExt + m_CellDist;
	m_MarginRight  = m_CellPos[9] + 30;
	LPCTSTR FaceName = "Arial";
	m_FontField.CreateFont(		// Font for fields
		m_CellExt-8,			// int nHeight
		0,						// int nWidth
		0,						// int nEscapement
		0,						// int nOrientation
		FW_BOLD,				// int nWeight,
		0,						// BYTE bItalic
		0,						// BYTE bUnderline
		0,						// BYTE cStrikeOut
		ANSI_CHARSET,			// BYTE nCharSet
		OUT_DEFAULT_PRECIS,		// BYTE nOutPrecision
		CLIP_DEFAULT_PRECIS,	// BYTE nClipPrecision
		DEFAULT_QUALITY,		// BYTE nQuality
		DEFAULT_PITCH,			// BYTE nPitchAndFamily
		FaceName);				// LPCTSTR lpszFacename

	m_FontHint.CreateFont(		// Font for Hints
		(m_CellExt-8)/4,		// int nHeight
		0,						// int nWidth
		0,						// int nEscapement
		0,						// int nOrientation
		FW_BOLD,				// int nWeight,
		0,						// BYTE bItalic
		0,						// BYTE bUnderline
		0,						// BYTE cStrikeOut
		ANSI_CHARSET,			// BYTE nCharSet
		OUT_DEFAULT_PRECIS,		// BYTE nOutPrecision
		CLIP_DEFAULT_PRECIS,	// BYTE nClipPrecision
		DEFAULT_QUALITY,		// BYTE nQuality
		DEFAULT_PITCH,			// BYTE nPitchAndFamily
		FaceName);				// LPCTSTR lpszFacename

	m_FontHdr.CreateFont(		// Font for foot line and headers
		m_Margin1/2,			// int nHeight
		0,						// int nWidth
		0,						// int nEscapement
		0,						// int nOrientation
		FW_BOLD,				// int nWeight,
		0,						// BYTE bItalic
		0,						// BYTE bUnderline
		0,						// BYTE cStrikeOut
		ANSI_CHARSET,			// BYTE nCharSet
		OUT_DEFAULT_PRECIS,		// BYTE nOutPrecision
		CLIP_DEFAULT_PRECIS,	// BYTE nClipPrecision
		DEFAULT_QUALITY,		// BYTE nQuality
		DEFAULT_PITCH,			// BYTE nPitchAndFamily
		FaceName);				// LPCTSTR lpszFacename

	m_TextHeight = m_Margin1;
	if(!m_IsPrinting)
		mdc.FillRect(&rc, &CBrush(Farben.Feld));		// fill background
	rc2.top = rc2.left = m_Margin1;	
	n = FieldSize * (m_CellExt + m_CellDist);
	rc2.top    = m_CellPos[0];
	rc2.bottom = rc2.top + n;
	rc2.left = m_CellPos[0];
	rc2.right = rc2.left + n;
	mdc.FillRect(&rc2, &CBrush(Farben.Zelle1));

	CFont	*pOldFont = mdc.SelectObject(&m_FontField);
	for(i=0; i<m_pDoc->m_nFields; i++)					// draw cells
	{
		n = m_pDoc->m_Field[i];
		CellDraw(&mdc, i, n, m_pDoc->m_SolveDisplay);
	}
	mdc.SelectObject(m_FontHdr);
	mdc.SetTextAlign(TA_LEFT | TA_TOP);

	m_CommentY = m_Margin1+0*m_TextHeight;
	if(m_pDoc->m_Comment.IsEmpty())
		mdc.TextOut(m_MarginRight, m_CommentY, "[Kommentar]");
	else
		mdc.TextOut(m_MarginRight, m_CommentY, m_pDoc->m_Comment);


	msg.Format("Stufe %d", m_pDoc->m_Stufe);
	mdc.TextOut(m_MarginRight, m_Margin1+1*m_TextHeight, msg);
	msg.Format("Geraten %d", m_pDoc->m_nGeraten);
	mdc.TextOut(m_MarginRight, m_Margin1+2*m_TextHeight, msg);

	msg.Format("Zeit %2d:%02d", m_pDoc->m_nClocks/CLOCKS_PER_SEC/60, (m_pDoc->m_nClocks/CLOCKS_PER_SEC) % 60);
	mdc.TextOut(m_MarginRight, m_Margin1+3*m_TextHeight, msg);

	m_PauseY = m_Margin1+4*m_TextHeight;
	mdc.TextOut(m_MarginRight, m_PauseY, "Pause");

	m_LinkY = m_Margin1+5*m_TextHeight;
	if(m_IsPrinting)
	{
		mdc.TextOut(m_MarginRight, m_LinkY, m_pDoc->m_DocName);
	}
	else
	{
		mdc.TextOut(m_MarginRight, m_LinkY, sLinkStr8ts);
	}

	if(!m_IsPrinting && m_pDoc->m_Ausblendmode)
		mdc.TextOut(m_MarginRight, m_Margin1+6*m_TextHeight, "[Ausblenden]");

	for(i=0; i<FieldSize; i++)			// Column headline
	{
		msg.Format("%d", i+1);
		mdc.TextOut(m_Margin1 + m_CellExt/2 + i * (m_CellDist + m_CellExt), m_Margin1/2, msg);
	}
		
	for(i=0; i<FieldSize; i++)			// Row headline
	{
		msg.Format("%c", i+'A');
		mdc.TextOut(m_Margin1/2, m_Margin1 - 5 + m_CellExt/2 + i * (m_CellDist + m_CellExt), msg);
	}

	if(m_IsPrinting)
	{
		mdc.SetTextAlign(TA_LEFT | TA_TOP);
		mdc.TextOut(m_Margin1, rc.bottom, m_pDoc->GetPathName());
	}
	mdc.SelectObject(pOldFont);
	m_FontField.DeleteObject();
	m_FontHint.DeleteObject();
	m_FontHdr.DeleteObject();
	pDC->BitBlt(
	rc.left,				// Ziel links
	rc.top,					// Ziel oben
	rc.right,				// Breite
	rc.bottom,				// Höhe
	&mdc,					// aus Speicherkontext
	0,						// Quelle links
	0,						// Quelle oben
	SRCCOPY);				// kopieren

	return;
}


void CStr8tsView::CellDraw(CDC * pDC, int Cell, int Val, BOOL Hint)
{
	int		i, r, c, x, y, h;
	int		FieldSize = m_pDoc->m_FieldSize;
	int		nFields = m_pDoc->m_nFields;
	char	Text[2];
	RECT rcClient, rcUser, rcText;

	if(Val == 0)
		Text[0] = ' ';
	else
		Text[0] = (Val & FELDMASK_ZAHL) + '0';
	Text[1] = 0;
	r = Cell / FieldSize;				// row
	c = Cell % FieldSize;				// column
	rcClient.top	= m_CellPos[r];
	rcClient.bottom = rcClient.top + m_CellExt;
	rcClient.left	= m_CellPos[c];
	rcClient.right	= rcClient.left + m_CellExt;

	rcUser.left		= rcClient.left + 3;				// Zeichenbereich Bitmap oder Hintergrund
	rcUser.top		= rcClient.top + 3;
	rcUser.right	= rcClient.right - 3;
	rcUser.bottom	= rcClient.bottom - 3;
	rcText.left		= rcClient.left + 4;
	rcText.right	= rcClient.right - 4;
	h = rcClient.bottom - rcClient.top;
	rcText.top		= rcClient.top + 4;
	rcText.bottom	= rcClient.bottom - 4;
	COLORREF cl1;

	cl1 = RGB(255, 255, 255);
	pDC->FillSolidRect(&rcClient, cl1);
	COLORREF	OldTxtColor;
	pDC->SetBkMode(TRANSPARENT); 
	OldTxtColor = pDC->SetTextColor(RGB(0,0,0));
	if((Val == 0) && Hint)			// leeres Feld + Hilfe
	{
		pDC->SetTextAlign(TA_LEFT | TA_TOP);
		pDC->SelectObject(m_FontHint);
		h = (rcText.bottom - rcText.top) / 3;
		for(i=0; i<9; i++)
		{
			x = rcText.left + 5 + (i % 3) * h;
			y = rcText.top  + (i / 3) * h;
			Text[0] = i+'1';
			r = m_pDoc->CheckPossible(i+1, Cell);
			if(r == 1)							// possible
			{
				pDC->SetTextColor(RGB(0,0,0));
				pDC->TextOut(x, y, Text);
			}
			if(r == -2)							// disabled
			{
				pDC->SetTextColor(RGB(192,192,192));
				pDC->TextOut(x, y, Text);
			}
		}
	}
	else if(Val & FELDMASK_BLOCK)				// Block
	{
		if(Val & FELDMASK_GEFROREN)
			cl1 = RGB(0, 0, 0);
		else
			cl1 = Farben.TextRW;
		pDC->FillRect(&rcClient, &CBrush(cl1));
		if(Val & FELDMASK_ZAHL)
		{
			pDC->SetTextAlign(TA_CENTER | TA_TOP);
			OldTxtColor = pDC->SetTextColor(RGB(255,255,255));
			pDC->SelectObject(m_FontField);
			pDC->TextOut(rcText.left+(rcText.right-rcText.left)/2, rcText.top, Text);
		}
	}
	else if(Val & FELDMASK_FEHLER)				// Strasse mit Fehler
	{
		if(!m_IsPrinting)
		{
			cl1 = RGB(255, 192, 192);
			pDC->FillRect(&rcUser, &CBrush(cl1));
		}
		if(Val & FELDMASK_ZAHL)
		{
			pDC->SetTextAlign(TA_CENTER | TA_TOP);
			if(Val & FELDMASK_GEFROREN)			// read-only
				OldTxtColor = pDC->SetTextColor(Farben.TextRO);
			else
				OldTxtColor = pDC->SetTextColor(Farben.TextRW);
			pDC->SelectObject(m_FontField);
			pDC->TextOut(rcText.left+(rcText.right-rcText.left)/2, rcText.top, Text);
		}
	}
	else if(Val & FELDMASK_STRASSE)				// Strasse o.k.
	{
		if(!m_IsPrinting)
		{
			cl1 = RGB(236, 255, 236);
			pDC->FillRect(&rcUser, &CBrush(cl1));
		}
		pDC->FillRect(&rcUser, &CBrush(cl1));
		if(Val & FELDMASK_ZAHL)
		{
			pDC->SetTextAlign(TA_CENTER | TA_TOP);
			if(Val & FELDMASK_GEFROREN)			// read-only
				OldTxtColor = pDC->SetTextColor(Farben.TextRO);
			else
				OldTxtColor = pDC->SetTextColor(Farben.TextRW);
			pDC->SelectObject(m_FontField);
			pDC->TextOut(rcText.left+(rcText.right-rcText.left)/2, rcText.top, Text);
		}
	}
	else
	{
		pDC->SetTextAlign(TA_CENTER | TA_TOP);
		if(Val & FELDMASK_GEFROREN)			// read-only
			OldTxtColor = pDC->SetTextColor(Farben.TextRO);
		else
			OldTxtColor = pDC->SetTextColor(Farben.TextRW);
		pDC->SelectObject(m_FontField);
		pDC->TextOut(rcText.left+(rcText.right-rcText.left)/2, rcText.top, Text);
	}
	if((m_pDoc->m_Info[Cell] & INFOMASK_SELECT) && !m_IsPrinting)	//frame around active field
	{
		CPen * pOldPen, pen(PS_SOLID, 3, RGB(255,0,0));
		x = rcClient.left + 1;
		y = rcClient.top + 1;
		c = rcClient.right -2;
		r = rcClient.bottom - 2;
		pOldPen = pDC->SelectObject(&pen);
		pDC->MoveTo(x, y);
		pDC->LineTo(c, y);
		pDC->LineTo(c, r);
		pDC->LineTo(x, r);
		pDC->LineTo(x, y);
		pDC->SelectObject(pOldPen);
	}
	pDC->SetTextColor(OldTxtColor);
}



void CStr8tsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_LbuttonDn = TRUE;
	KlickSelect(point);
}


void CStr8tsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_LbuttonDn = FALSE;
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen und/oder Standard aufrufen
	
	CFormView::OnLButtonUp(nFlags, point);
}


void CStr8tsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU1));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	KlickSelect(point);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x+20, point.y+20, AfxGetMainWnd());

}


BOOL CStr8tsView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int		cNew, Select = m_pDoc->GetSelect();
	int		FieldSize = m_pDoc->m_FieldSize;
	int		nFields = m_pDoc->m_nFields;
	char cOld = m_pDoc->m_Field[Select];
	if((nChar >= '0') && (nChar <= '9'))
	{
		if(m_CtrlState || m_pDoc->m_Ausblendmode)
		{
			m_pDoc->Suppress(nChar - '0');
			m_pDoc->Solver();
			Invalidate();
			return TRUE;
		}
		if(cOld & FELDMASK_GEFROREN)
		{
			AfxMessageBox("Dieses Feld darf nicht geändert werden", MB_ICONEXCLAMATION);
			return TRUE;
		}
		cNew = nChar - '0';
		if(m_pDoc->CheckPossible(cNew, Select))
			m_pDoc->m_Field[Select] = cOld & ~FELDMASK_ZAHL | cNew;
		else
		{
			AfxMessageBox("Nicht zulässig in diesem Feld", MB_ICONEXCLAMATION);
			return TRUE;
		}
		if(!m_pDoc->CheckField(TRUE))
		{
			m_pDoc->m_Field[Select] = cOld;
			Invalidate();
		}
		else
		{
			if(cOld != cNew)
				m_pDoc->Log(Select, cOld, cNew);
			m_pDoc->Solver();
			m_pDoc->CheckField();
			m_pDoc->SetModifiedFlag();
			if(m_pDoc->CheckSolved())
				m_pDoc->Finish();
		}
		Invalidate();
		return TRUE;
	}
	switch(nChar)
	{
	case 'x':
	case 'X':
	case ' ':
		if(cOld & FELDMASK_GEFROREN)
		{
			AfxMessageBox("Dieses Feld darf nicht geändert werden", MB_ICONEXCLAMATION);
			return true;
		}
		cOld ^= FELDMASK_BLOCK;
		m_pDoc->m_Field[Select] = cOld;
		m_pDoc->SetModifiedFlag();
		if(m_pDoc->CheckSolved())
			m_pDoc->Finish();
		m_pDoc->Solver();
		Invalidate();
		return TRUE;
	case 0x25:		// left
		Select--;
		if(Select < 0)
			Select = nFields-1;
		break;
	case 0x26:		// up
		Select-=FieldSize;
		if(Select < 0)
			Select += nFields-1;
		break;
	case 0x27:		// right
		Select++;
		if(Select > nFields-1)
			Select = 0;
		break;
	case 0x28:		// down
		Select+=FieldSize;
		if(Select >= nFields)
			Select -= nFields;
		break;
	default:
		return FALSE;
	}
	m_pDoc->SetSelect(Select);
	Invalidate();
	return TRUE;
}


int CStr8tsView::KlickSelect(CPoint point, BOOL Dbl, BOOL Multi)
{	// Feldindex berechnen aus Mausklick
	// mit Doppelklick unterdrückte Zahlen aus-/einblenden
	int		i, p1, p2, x=-1, y=-1, x2, y2;
	int		FieldSize = m_pDoc->m_FieldSize;
	int		nFields = m_pDoc->m_nFields;

	RECT	rc;
	GetClientRect(&rc);

	if((point.x > m_MarginRight) && (point.x < (m_MarginRight + 200)))
	{
		if((point.y > m_LinkY) && (point.y < (m_LinkY + m_TextHeight)))
			ShellExecute(NULL, _T("open"), sLinkStr8ts, NULL,NULL, SW_SHOW);
		else if((point.y > m_CommentY) && (point.y < (m_CommentY + m_TextHeight)))
		{
			CWnd * pParent = GetParent();
			pParent->SendMessage(WM_COMMAND, ID_DATEI_COMMENT, 0);
		}
		else if((point.y > m_PauseY) && (point.y < (m_PauseY + m_TextHeight)))
		{
			CWnd * pParent = GetParent();
			pParent->SendMessage(WM_COMMAND, ID_TIME_PAUSE, 0);
		}
		m_LbuttonDn = false;
		return -1;
	}
	for(i=0; i<FieldSize; i++)
	{
		p1 = m_CellPos[i];
		p2 = p1 + m_CellExt;
		if((point.x > p1) && (point.x < p2))
		{
			x = i;
			x2 = (point.x - p1) * 3 / m_CellExt;
		}
		if((point.y > p1) && (point.y < p2))
		{
			y = i;
			y2 = (point.y - p1) * 3 / m_CellExt;
		}
	}
	if((x >= 0) && (y >= 0))
	{
		x += FieldSize * y;
		m_pDoc->SetSelect(x, Multi);
		if(Dbl)
		{
			i = 3 * y2 + x2 + 1;
			m_pDoc->Suppress(i);
			m_pDoc->Solver();
		}
		Invalidate();
	}
	else
		x=-1;
	return x;
}


void CStr8tsView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	KlickSelect(point, TRUE);
}



void CStr8tsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_LbuttonDn)
		KlickSelect(point, FALSE, TRUE);
	CFormView::OnMouseMove(nFlags, point);
}

void CStr8tsView::OnCapture(void) 
{
	CRect	rc, rcLast;
	CWnd * pDesktop = GetDesktopWindow();
	pDesktop->GetWindowRect(&rc);
	COLORREF	ColPix, col1=RGB(0,0,0), col2=RGB(255,255,255);

	int			x=0, y=0;

	CDC * cdc = pDesktop->GetWindowDC();
	ColPix = cdc->GetPixel(x, y);
	cdc->Draw3dRect(500,500, 300, 200, col1, col2);
}

