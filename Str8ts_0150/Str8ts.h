// Str8ts.h : Haupt-Header-Datei für die Anwendung Str8ts
//

#if !defined(AFX_STR8TS_H_INCLUDED_)
#define AFX_STR8TS_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

#define MSG_CLICK	WM_USER+20
#define MSG_UNDO	WM_USER+21
#define MSG_REDO	WM_USER+22
#define MSG_LOGDEL	WM_USER+23

#define IDC_FIELD	1100		// Control-IDs für Str8tsfelder 1100..1180
#define LOG_SIZE	1000		// log size [int]

//Registry-Schlüssel
#define KEY_SETTINGS	"Settings"
#define	KEY_COL_BG		"ColorBG"
#define	KEY_COL_F1		"ColorF1"
#define	KEY_COL_F2		"ColorF2"
#define	KEY_COL_F3		"ColorF3"
#define	KEY_COL_T1		"ColorT1"
#define	KEY_COL_T2		"ColorT2"
#define KEY_WND_X		"WndPosX"
#define KEY_WND_Y		"WndPosY"
#define KEY_WND_CX		"WndSizX"
#define KEY_WND_CY		"WndSizY"
#define KEY_WND_MAX		"WndMax"
#define KEY_WEB_ST		"Website"
#define KEY_DEF_MZ		"MoeglicheZahlen"
#define KEY_DEF_AE		"AutoEingabe"
#define KEY_DEF_SC		"Sure Candidates"
#define KEY_DEF_SD		"Stranded Digit"
#define KEY_DEF_SI		"Singles"
#define KEY_DEF_RC		"Range Check"

//Standardeinstellungen
#define DEF_COL_BG		RGB(170,170,255)
#define	DEF_COL_F1		RGB(255,141, 28)
#define	DEF_COL_F2		RGB(191,106, 21)
#define	DEF_COL_F3		RGB(255,128,192)
#define	DEF_COL_T1		RGB(152, 14,100)
#define	DEF_COL_T2		RGB(0, 0, 0)
#define DEF_WND_X		0
#define DEF_WND_Y		0
#define DEF_WND_CX		600
#define DEF_WND_CY		300
#define DEF_WND_MAX		FALSE
#define DEF_DEF_MZ		"001111"
#define DEF_DEF_AE		"001111"
#define DEF_DEF_SC		"000000"
#define DEF_DEF_SD		"000000"
#define DEF_DEF_SI		"000000"
#define DEF_DEF_RC		"000000"

//Strings
#define SNDFILE_TADA	"Tada.wav"
#define DEF_WEB_ST		"http://str8ts.com"
struct FARBEN
{
	COLORREF	Feld;		// Hintergrund Bildschirm
	COLORREF	Zelle1;		// Hintergrund Feld 1
	COLORREF	Zelle2;		// Hintergrund Feld 2
	COLORREF	ZelleAkt;	// Hintergrund aktives Feld
	COLORREF	TextRW;		// Text normal
	COLORREF	TextRO;		// Text eingefroren
};

struct WND_POS
{
	int		x;				// Fensterposition x
	int		y;				// Fensterposition y
	int		cx;				// Fenstergrösse x
	int		cy;				// Fenstergrösse y
	BOOL	max;			// Fenster maximiert
};

/////////////////////////////////////////////////////////////////////////////
// CStr8tsApp:
// Siehe Str8ts.cpp für die Implementierung dieser Klasse
//

class CStr8tsApp : public CWinApp
{
public:
	CStr8tsApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStr8tsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementierung
	//{{AFX_MSG(CStr8tsApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	void GetAppPath(void);
	void GetVers(void);
};

extern CStr8tsApp theApp;
extern CString sAppPath;
extern CString sLinkStr8ts;			// link to str8ts web site

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STR8TS_H_INCLUDED_)
