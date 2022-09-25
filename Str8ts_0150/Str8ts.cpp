// CStr8ts.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "Module.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString sVers1, sVers2;			// Version strings
CString sAppPath;
CString sLinkStr8ts;			// link to str8ts web site

/////////////////////////////////////////////////////////////////////////////
// CStr8tsApp

BEGIN_MESSAGE_MAP(CStr8tsApp, CWinApp)
	//{{AFX_MSG_MAP(CStr8tsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStr8tsApp Konstruktion

CStr8tsApp::CStr8tsApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CStr8tsApp-Objekt

CStr8tsApp theApp;
struct	FARBEN	Farben;
struct	WND_POS wndMain;
BOOL	bMZ[6];			// mögliche Zahlen
BOOL	bAE[6];			// Auto-Eingabe
BOOL	bSC[6];			// Sure candidates
BOOL	bRC[6];			// Range check
BOOL	bSI[6];			// Single
BOOL	bSD[6];			// Stranded digit

/////////////////////////////////////////////////////////////////////////////
// CStr8tsApp Initialisierung

BOOL CStr8tsApp::InitInstance()
{
	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Größe Ihrer fertigen 
	//  ausführbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht benötigen, entfernen.

	CString str, msg;
	int		i;
	SetRegistryKey(_T("Pinaida"));
	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CStr8tsDoc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		RUNTIME_CLASS(CStr8tsView));
	AddDocTemplate(pDocTemplate);

	Farben.Feld		= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_BG, DEF_COL_BG);
	Farben.Zelle1	= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_F1, DEF_COL_F1);
	Farben.Zelle2	= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_F2, DEF_COL_F2);
	Farben.ZelleAkt	= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_F3, DEF_COL_F3);
	Farben.TextRW	= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_T1, DEF_COL_T1);
	Farben.TextRO	= theApp.GetProfileInt(KEY_SETTINGS, KEY_COL_T2, DEF_COL_T2);
	wndMain.x		= theApp.GetProfileInt(KEY_SETTINGS, KEY_WND_X, DEF_WND_X);
	wndMain.y		= theApp.GetProfileInt(KEY_SETTINGS, KEY_WND_Y, DEF_WND_Y);
	wndMain.cx		= theApp.GetProfileInt(KEY_SETTINGS, KEY_WND_CX, DEF_WND_CX);
	wndMain.cy		= theApp.GetProfileInt(KEY_SETTINGS, KEY_WND_CY, DEF_WND_CY);
	wndMain.max		= theApp.GetProfileInt(KEY_SETTINGS, KEY_WND_MAX, DEF_WND_MAX);
	sLinkStr8ts		= theApp.GetProfileString(KEY_SETTINGS, KEY_WEB_ST, DEF_WEB_ST);
	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_MZ, DEF_DEF_MZ);
	for(i=0; i<6; i++)
		bMZ[i]=str.GetAt(i)=='1'?TRUE:FALSE;
	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_AE, DEF_DEF_AE);
	for(i=0; i<6; i++)
		bAE[i]=str.GetAt(i)=='1'?TRUE:FALSE;

	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_SI, DEF_DEF_SI);
	for(i=0; i<6; i++)
		bSI[i]=str.GetAt(i)=='1'?TRUE:FALSE;

	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_SD, DEF_DEF_SD);
	for(i=0; i<6; i++)
		bSD[i]=str.GetAt(i)=='1'?TRUE:FALSE;
	
	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_SC, DEF_DEF_SC);
	for(i=0; i<6; i++)
		bSC[i]=str.GetAt(i)=='1'?TRUE:FALSE;

	str				= theApp.GetProfileString(KEY_SETTINGS, KEY_DEF_RC, DEF_DEF_RC);
	for(i=0; i<6; i++)
		bRC[i]=str.GetAt(i)=='1'?TRUE:FALSE;
	
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	GetAppPath();
	GetVers();							// get version info
	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
	m_pMainWnd->UpdateWindow();
	str = "IDR_TADA";
	HRSRC hRes = FindResource(NULL, str, "WAVE");
	if(!hRes)
	{
		msg.Format("Resource %s not found", str);
		AfxMessageBox(msg);
	}
	else
	{
		CFile fp;
		CString fn = sAppPath + SNDFILE_TADA;
		HGLOBAL hGlob = LoadResource(NULL, hRes);
		void *pBinData = LockResource(hGlob);
		DWORD szRes = SizeofResource(NULL, hRes);
		UINT OpenFlags=CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive;  
		if(!fp.Open(fn, OpenFlags))
		{
			msg.Format("Cannot create file %s", fn);
			AfxMessageBox(msg);
		}
		else
		{
			fp.Write(pBinData, szRes);
			fp.Close();
		}
	}
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_Line1;
	CString	m_Line2;
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_Line1 = _T("");
	m_Line2 = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_INFO_LINE1, m_Line1);
	DDX_Text(pDX, IDC_INFO_LINE2, m_Line2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Anwendungsbefehl zum Ausführen des Dialogfelds
void CStr8tsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.m_Line1=sVers1;
	aboutDlg.m_Line2=sVers2;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CStr8tsApp-Nachrichtenbehandlungsroutinen

void CStr8tsApp::GetVers(void)
{
	DWORD	lpdwHandle;
	UINT	dwLen;
	char	Filename[80];
	WCHAR	*pFileInfo = NULL;
	WCHAR	*pWchar1, *pWchar2;

	sprintf_s(Filename, 80, "%s.exe", m_pszAppName);
	dwLen = GetFileVersionInfoSize(Filename, &lpdwHandle);
	if(dwLen == 0)
		goto ausis;
	pFileInfo = new WCHAR[dwLen];
	if(!GetFileVersionInfo(Filename, lpdwHandle, dwLen, pFileInfo))
		goto ausis;
	if(!VerQueryValue(pFileInfo, "\\StringFileInfo\\040704B0\\FileDescription", (void **)&pWchar1, &dwLen))
		goto ausis;
	sVers1.Format("%s", pWchar1);
	// Name holen
	if(!VerQueryValue(pFileInfo, "\\StringFileInfo\\040704B0\\LegalCopyright", (void **)&pWchar1, &dwLen))
		goto ausis;
	if(!VerQueryValue(pFileInfo, "\\StringFileInfo\\040704B0\\CompanyName", (void **)&pWchar2, &dwLen))
		goto ausis;
	sVers2.Format("%s by %s", pWchar1, pWchar2);
ausis:
	delete pFileInfo;
	pFileInfo = NULL;
}




int CStr8tsApp::ExitInstance() 
{
	int		i;
	char	s[7];
	s[6]=0;
	// TODO: Speziellen Code hier einfügen und/oder Basisklasse aufrufen
	theApp.WriteProfileInt(KEY_SETTINGS, KEY_WND_X,   wndMain.x);
	theApp.WriteProfileInt(KEY_SETTINGS, KEY_WND_Y,   wndMain.y);
	theApp.WriteProfileInt(KEY_SETTINGS, KEY_WND_CX,  wndMain.cx);
	theApp.WriteProfileInt(KEY_SETTINGS, KEY_WND_CY,  wndMain.cy);
	theApp.WriteProfileInt(KEY_SETTINGS, KEY_WND_MAX, wndMain.max);
	for(i=0; i<6; i++)
		s[i]=(bMZ[i]==TRUE)?'1':'0';
	theApp.WriteProfileString(KEY_SETTINGS, KEY_DEF_MZ, s);
	for(i=0; i<6; i++)
		s[i]=(bAE[i]==TRUE)?'1':'0';
	theApp.WriteProfileString(KEY_SETTINGS, KEY_DEF_AE, s);
	
	return CWinApp::ExitInstance();
}

void CStr8tsApp::GetAppPath()
{
	CString str = m_pszHelpFilePath;
	int i0, i = 0;
	do
	{
		i0 = i;
		i = str.Find('\\', i+1);
	} while(i != -1);

	if(i0 <= 0)
		sAppPath.Empty();
	else
		sAppPath = str.Left(i0)+'\\';
}
