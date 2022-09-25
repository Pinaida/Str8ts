#if !defined(AFX_DLGSETTINGS_H__AAE48F5D_EFE6_42BD_A12F_8F0F7A4BC5F4__INCLUDED_)
#define AFX_DLGSETTINGS_H__AAE48F5D_EFE6_42BD_A12F_8F0F7A4BC5F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettings.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSettings 

class CDlgSettings : public CDialog
{
// Konstruktion
public:
	CDlgSettings(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSettings)
	enum { IDD = IDD_SETTINGS };
	CString	m_WebLink;
	BOOL	m_FieldSize;
	//}}AFX_DATA

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSettings)
	afx_msg void OnDefaultSolver();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSETTINGS_H__AAE48F5D_EFE6_42BD_A12F_8F0F7A4BC5F4__INCLUDED_
