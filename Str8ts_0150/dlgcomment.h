#if !defined(AFX__DLGCOMMENT_H__6FEB05FF_4E6E_45B1_8BF3_6279BAE2C19B__INCLUDED_)
#define AFX__DLGCOMMENT_H__6FEB05FF_4E6E_45B1_8BF3_6279BAE2C19B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// _DlgComment.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgComment 

class CDlgComment : public CDialog
{
// Konstruktion
public:
	CDlgComment(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgComment)
	enum { IDD = IDD_COMMENT };
	CString	m_Comment;
	int		m_Stufe;
	CString	m_sGeraten;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgComment)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgComment)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX__DLGCOMMENT_H__6FEB05FF_4E6E_45B1_8BF3_6279BAE2C19B__INCLUDED_
