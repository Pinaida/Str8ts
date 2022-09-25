#if !defined(AFX_COLORBUTTON_H__9E6071CD_3605_4F09_A0B9_E773D69E46E6__INCLUDED_)
#define AFX_COLORBUTTON_H__9E6071CD_3605_4F09_A0B9_E773D69E46E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CColorButton 

class CColorButton : public CButton
{
// Konstruktion
public:
	CColorButton();
	struct FARBEN m_Farben;

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CColorButton)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CColorButton();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CColorButton)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_COLORBUTTON_H__9E6071CD_3605_4F09_A0B9_E773D69E46E6__INCLUDED_
