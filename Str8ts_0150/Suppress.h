#if !defined(AFX_SUPPRESS_H__23C3642D_B278_4DE9_B2B0_D43A6C0DB43C__INCLUDED_)
#define AFX_SUPPRESS_H__23C3642D_B278_4DE9_B2B0_D43A6C0DB43C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Suppress.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CSuppress 

class CSuppress : public CDialog
{
// Konstruktion
public:
	int m_State;
	CSuppress(CWnd* pParent=NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CSuppress)
	enum { IDD = IDD_SUPPRESS };
	BOOL	m_Hide1;
	BOOL	m_Hide2;
	BOOL	m_Hide3;
	BOOL	m_Hide4;
	BOOL	m_Hide5;
	BOOL	m_Hide6;
	BOOL	m_Hide7;
	BOOL	m_Hide8;
	BOOL	m_Hide9;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CSuppress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	void ClearAll(void);

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CSuppress)
	afx_msg void OnSupprNone();
	virtual BOOL OnInitDialog();
	afx_msg void OnSupprOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_SUPPRESS_H__23C3642D_B278_4DE9_B2B0_D43A6C0DB43C__INCLUDED_
