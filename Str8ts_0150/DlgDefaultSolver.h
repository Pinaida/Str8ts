#if !defined(AFX_DLGDEFAULTSOLVER_H__82CFCEAE_2C6D_49C5_9C8A_D008515380D7__INCLUDED_)
#define AFX_DLGDEFAULTSOLVER_H__82CFCEAE_2C6D_49C5_9C8A_D008515380D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDefaultSolver.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDefaultSolver 

class CDlgDefaultSolver : public CDialog
{
// Konstruktion
public:
	CDlgDefaultSolver(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDefaultSolver)
	enum { IDD = IDD_DEFAULT_SOLVER };
	BOOL	m_AE0;
	BOOL	m_AE1;
	BOOL	m_AE2;
	BOOL	m_AE3;
	BOOL	m_AE4;
	BOOL	m_AE5;
	BOOL	m_MZ0;
	BOOL	m_MZ1;
	BOOL	m_MZ2;
	BOOL	m_MZ3;
	BOOL	m_MZ4;
	BOOL	m_MZ5;
	BOOL	m_SC0;
	BOOL	m_SC1;
	BOOL	m_SC2;
	BOOL	m_SC3;
	BOOL	m_SC4;
	BOOL	m_SC5;
	BOOL	m_SD0;
	BOOL	m_SD1;
	BOOL	m_SD2;
	BOOL	m_SD3;
	BOOL	m_SD4;
	BOOL	m_SD5;
	BOOL	m_SI0;
	BOOL	m_SI1;
	BOOL	m_SI2;
	BOOL	m_SI3;
	BOOL	m_SI4;
	BOOL	m_SI5;
	BOOL	m_RC0;
	BOOL	m_RC1;
	BOOL	m_RC2;
	BOOL	m_RC3;
	BOOL	m_RC4;
	BOOL	m_RC5;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDefaultSolver)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDefaultSolver)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDEFAULTSOLVER_H__82CFCEAE_2C6D_49C5_9C8A_D008515380D7__INCLUDED_
