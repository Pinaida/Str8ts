#if !defined(AFX_DLGCOLOR_H__52B4BE32_51DA_4C8C_9605_6F8511013083__INCLUDED_)
#define AFX_DLGCOLOR_H__52B4BE32_51DA_4C8C_9605_6F8511013083__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgColor.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgColor 

class CDlgColor : public CDialog
{
// Konstruktion
public:
	CDlgColor(CWnd* pParent = NULL);   // Standardkonstruktor
	struct	FARBEN m_Farben;

// Dialogfelddaten
	//{{AFX_DATA(CDlgColor)
	enum { IDD = IDD_COLOR };
	CColorButton	m_ColorShow;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgColor)
	afx_msg void OnColorBg();
	afx_msg void OnColorF1();
	afx_msg void OnColorF2();
	afx_msg void OnColorF3();
	afx_msg void OnColorT1();
	afx_msg void OnColorT2();
	virtual BOOL OnInitDialog();
	afx_msg void OnColReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGCOLOR_H__52B4BE32_51DA_4C8C_9605_6F8511013083__INCLUDED_
