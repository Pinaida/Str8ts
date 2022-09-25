// Str8tsDoc.h : Schnittstelle der Klasse CStr8tsDoc
//
/////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_STR8TSDOC_H_)
#define AFX_STR8TSDOC_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Definitionen für Feldinhalt m_Field
#define FELDMASK_ZAHL		0x0f	// Zahl 0..9, mit 0=leer
#define FELDMASK_GEFROREN	0x10	// darf nicht geändert werden
#define FELDMASK_BLOCK		0x20	// begrenzt eine Strasse
#define FELDMASK_STRASSE	0x40	// das Feld gehört zu einer Strasse
#define FELDMASK_FEHLER		0x80	// gehört zu einer fehlerhaften Strasse

#define INFOMASK_SELECT		0x0001	// Feld ist ausgewählt
#define INFOMASK_HIDE1		0x0002	// 1 ist ausgeblendet
#define INFOMASK_HIDE2		0x0004	// 2 ist ausgeblendet
#define INFOMASK_HIDE3		0x0008	// 3 ist ausgeblendet
#define INFOMASK_HIDE4		0x0010	// 4 ist ausgeblendet
#define INFOMASK_HIDE5		0x0020	// 5 ist ausgeblendet
#define INFOMASK_HIDE6		0x0040	// 6 ist ausgeblendet
#define INFOMASK_HIDE7		0x0080	// 7 ist ausgeblendet
#define INFOMASK_HIDE8		0x0100	// 8 ist ausgeblendet
#define INFOMASK_HIDE9		0x0200	// 9 ist ausgeblendet


class CStr8tsDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CStr8tsDoc();
	DECLARE_DYNCREATE(CStr8tsDoc)

// Attribute
public:
	bool		CheckLine(int Line);
	bool		CheckColumn(int Column);
	bool		CheckField(BOOL ShowInfo=FALSE);

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CStr8tsDoc)
	public:
	virtual void OnNew();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementierung

	
public:
	void TimeReset(void);
	void TimeUpdate(void);
	void SetFieldSize(int n);
	BOOL AutoFreeze(void);
	void	OnComment(void);
	void	Check(void);
	void	Einblend(void);
	void	Solver(void);
	void	OnSolveF(void);
	void	OnFreezeMelt(void);
	void	Suppress(int n);
	void	OnQuery(int i);
	void	OnCheck(void);
	void	OnMelt(void);
	void	OnSolve(void);
	int		CheckPossible(int n, int Field);
	BOOL	CheckSolved(void);
	LPCTSTR GetPathName(void);
	void	OnOpen(void);
	void	OnOpenTemplate(void);
	void	OnPause(void);
	void	OnSave(void);
	void	OnSaveAs(void);
	void	OnAgain(void);
	void	OnFreeze(void);
	void	Finish();
	void	OnLogDelete(void);
	void	OnLogUndo(void);
	void	OnLogRedo(void);
	void	SetSelect(int Select, BOOL Multi=FALSE);
	int		GetSelect(void);
	void	Log(int nCell, char cOld, char cNew);
	BOOL	m_Ausblendmode;
	BOOL	m_SolveDisplay;
	char	m_Field[100];
	char	m_Templ[100];
	int		m_Info[100];					// Ausgeblendete Zahlen
	CString	m_DocName;
	int	  * m_Log;
	int		m_MaxLog;
	CString m_Comment;
	int		m_nGeraten;
	int		m_Stufe;
//	int		m_Select;
	BOOL	m_SolveAutoEnter;
	BOOL	m_SolveSureCandidate;
	BOOL	m_SolveStrandedDigits;
	BOOL	m_SolveRangeCheck;
	BOOL	m_SolveSingle;
	int		m_SolveActPtr;					// Index auf Anfang der akt. Strasse
	BOOL	m_SolveActCol;					// Richtung der akt. Strasse
	int		m_SolveActLen;					// Länge der akt. Strasse
	clock_t	m_Clock0;						// Startzeit
	int		m_nClocks;						// Zeit für Lösung [s]
	int		m_FieldSize;					// Feldlänge
	int		m_nFields;						// Anzahl Felder (m_FieldSize²)
	BOOL	m_Solved;						// gelöst
	BOOL	m_Pause;						// Pause

	virtual ~CStr8tsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CArchive  *	m_pArchive;
// Generierte Message-Map-Funktionen
protected:
	void CheckStandardPath(void);
	void SolveDefaults(void);
	void	SolveDisable(void);
	BOOL	SolveAutoEnter(void);
	BOOL	SolveCompartment(void);
	BOOL	SolveCompartment1(int Start, int Len, BOOL Vert);
	BOOL	SolveRangeCheck(int Start, int Len, BOOL Vert);
	BOOL	SolveSingle(int Start, int Len, BOOL Vert);
	BOOL	SolveSureCandidates(int Start, int Len, BOOL Vert);
	BOOL	SolveStrandedDigits(int Start, int Len, BOOL Vert);
	int		CheckStrasse1(char *f, int len);
	void	CheckStrasse(int Num, BOOL InSpalte);
	void	UpdateTemplate(void);
	BOOL	IsComplete(char *Field);
	void	Save(void);
	void	StripExt(CString &Name);
	void	DeleteContents(void);
	BOOL	CheckModified(void);
	struct STRASSE
	{
		int		Start;		//Index auf Anfang
		BOOL	Col;		//0=Zeile, 1=Spalte
		int		Len;		//Länge
	} m_Strasse;

	//{{AFX_MSG(CStr8tsDoc)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STR8TSDOC_H_)
