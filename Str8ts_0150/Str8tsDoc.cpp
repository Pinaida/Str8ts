// Str8tsDoc.cpp : Implementierung der Klasse CStr8tsDoc
//

#include "stdafx.h"
#include "Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CStr8tsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStr8tsDoc

IMPLEMENT_DYNCREATE(CStr8tsDoc, CDocument)

BEGIN_MESSAGE_MAP(CStr8tsDoc, CDocument)
	//{{AFX_MSG_MAP(CStr8tsDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStr8tsDoc Konstruktion/Destruktion

CStr8tsDoc::CStr8tsDoc()
{
	m_Log = new int[LOG_SIZE];
	SetFieldSize(9);
	SolveDisable();

	DeleteContents();
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}


CStr8tsDoc::~CStr8tsDoc()
{
	delete[] m_Log;
	m_Log = NULL;
}


void CStr8tsDoc::OnNew()
{
	if(CheckModified())
		return;
	DeleteContents();
	SolveDisable();
	m_nGeraten = 0;
	m_Stufe	= 0;
	m_Comment.Empty();
	Einblend();
	m_Solved = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CStr8tsDoc Serialisierung

void CStr8tsDoc::Serialize(CArchive& ar)
{
	char	header1[] = "STR8TS V1 DATA";
	char	header2[] = "STR8TS V2 DATA";
	if (ar.IsStoring())
	{
		if(m_nFields==81)
			ar.WriteString(header1);
		else
			ar.WriteString(header2);
		ar.Write("\r\n", 2);
		ar.Write(m_Templ, m_nFields*sizeof(char));		// Vorlage
		ar.Write(m_Field, m_nFields*sizeof(char));		// Spiel
		ar.Write(m_Info,  m_nFields*sizeof(int));		// Suppressmask
		ar.Write(&m_Stufe, sizeof(int));				// Stufe
		ar.Write(&m_nGeraten, sizeof(int));				// Geraten
		ar.WriteString(m_Comment);						// Bemerkung
		ar.Write("\r\n", 2);
		ar.Flush();
	}
	else
	{
		char buf[32];
		ar.ReadString(buf, 31);
		if(!strcmp(header1, buf))						// aktuelles Dateiformat
			SetFieldSize(9);
		else if(!strcmp(header2, buf))					// Dateiformat V2
			SetFieldSize(10);
		else
		{
			AfxMessageBox("Keine gültige Str8ts-Datei");
			return;
		}
		ar.Read(m_Templ, m_nFields*sizeof(char));
		ar.Read(m_Field, m_nFields*sizeof(char));
		ar.Read(m_Info,  m_nFields*sizeof(int));
		ar.Read(&m_Stufe, sizeof(int));
		ar.Read(&m_nGeraten, sizeof(int));
		ar.ReadString(m_Comment);
		OnLogDelete();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStr8tsDoc Diagnose

#ifdef _DEBUG
void CStr8tsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStr8tsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStr8tsDoc Befehle
bool CStr8tsDoc::CheckField(BOOL ShowInfo)
{	// check Str8ts field, return true = valid, false = invalid 
	int		i;
	CString	msg;

	for(i=0; i<100; i++)				// Strassenzustand löschen
		m_Field[i] &= ~(FELDMASK_STRASSE | FELDMASK_FEHLER);

	for(i=0; i<m_FieldSize; i++)		// check lines
	{
		if(!CheckLine(i))
		{
			if(ShowInfo)
			{
				msg.Format("Fehler in Zeile %d", i+1);
				AfxMessageBox(msg);
			}
			return false;
		}
		CheckStrasse(i, FALSE);
	}
	for(i=0; i<m_FieldSize; i++)		// check columns
	{
		if(!CheckColumn(i))
		{
			if(ShowInfo)
			{
				msg.Format("Fehler in Spalte %d", i+1);
				AfxMessageBox(msg);
			}
			return false;
		}
		CheckStrasse(i, TRUE);
	}
	return true;
}


bool CStr8tsDoc::CheckLine(int Line)
{	// check Str8ts line n, return true = valid, false = invalid 
	ASSERT((Line >= 0) && (Line < m_FieldSize));
	int		n, i, i0, v[10];
	for(i=0; i<m_FieldSize; i++)				// reset
		v[i]=0;
	i0 = m_FieldSize*Line;
	for(i=0; i<m_FieldSize; i++)
	{
		n = (m_Field[i0+i] & FELDMASK_ZAHL) - 1;
		if((n >= 0) && (n < m_FieldSize))
		{
			v[n]++;
			if(v[n] > 1)				// same digit more than once
				return false;
		}
	}
	return true;
}


bool CStr8tsDoc::CheckColumn(int Column)
{	// check Str8ts column n, return true = valid, false = invalid 
	ASSERT((Column >= 0) && (Column < m_FieldSize));
	int		n, i, i0, v[10];
	for(i=0; i<10; i++)					// reset
		v[i]=0;
	i0 = Column;
	for(i=0; i<m_FieldSize; i++)
	{
		n = (m_Field[i0 + m_FieldSize*i] & FELDMASK_ZAHL) - 1;
		if((n >= 0) && (n < m_FieldSize))
		{
			v[n]++;
			if(v[n] > 1)				// same digit more than once
				return false;
		}
	}
	return true;
}


void CStr8tsDoc::Log(int nCell, char cOld, char cNew)
{
	if((cOld>FELDMASK_ZAHL) || (cNew > FELDMASK_ZAHL))
		return;
	ASSERT((nCell >= 0) && (nCell < m_nFields));
	m_Log[m_MaxLog++] = (nCell<<8) | (cOld<<4) | cNew;
	if(m_MaxLog >= LOG_SIZE)
	{
		m_MaxLog = 0;
	}
	m_Log[m_MaxLog]=-1;
}


int CStr8tsDoc::GetSelect()
{	// Mehrfachauswahl löschen
	int	Select=-1;
	for(int i=0; i<m_nFields; i++)
	{
		if((Select < 0) && (m_Info[i] & INFOMASK_SELECT))
			Select = i;
	}
	return Select;
}


void CStr8tsDoc::SetSelect(int Select, BOOL Multi)
{	// set single selection
	ASSERT((Select >= 0) && (Select < m_nFields));
	if(!Multi)
	{
		for(int i=0; i<m_nFields; i++)
			m_Info[i] &= ~INFOMASK_SELECT;
	}
	m_Info[Select] |= INFOMASK_SELECT;
	m_Pause = FALSE;
}



void CStr8tsDoc::OnLogDelete()
{
	m_Log[0] = -1;
	m_MaxLog = 0;
}


void CStr8tsDoc::OnLogUndo()
{
	int	Select;
	if(!m_MaxLog)						// Undo-log empty
	{
		AfxMessageBox("Mehr kann nicht rückgängig gemacht werden");
		return;
	}
	m_MaxLog--;
	Select = m_Log[m_MaxLog] >> 8;		// get index
	SetSelect(Select);					// set single selection
	int cOld = (m_Log[m_MaxLog] >> 4) & FELDMASK_ZAHL;		// content
	m_Field[Select] = cOld;
	SetModifiedFlag();
}


void CStr8tsDoc::OnLogRedo()
{
	if(m_Log[m_MaxLog] < 0)							// Redo-log empty
	{
		AfxMessageBox("Mehr kann nicht wiederhergestellt werden");
		return;
	}
	int Select = m_Log[m_MaxLog] >> 8;				// Index
	SetSelect(Select);								// set single selection
	int cNew = m_Log[m_MaxLog] & FELDMASK_ZAHL;		// content
	m_Field[Select] = cNew;
	SetModifiedFlag();
	m_MaxLog++;
}


void CStr8tsDoc::OnFreeze()
{	// mark all entries as read-only
	int		i;
	for(i=0; i<m_nFields; i++)							// check if there are already frozen entries
	{
		if(m_Field[i] & FELDMASK_GEFROREN)
		{
			i = AfxMessageBox("Es gibt schon gefrorene Felder, wirklich alles einfrieren", MB_ICONEXCLAMATION | MB_YESNO);
			if(i != IDYES)
				return;
			else
				break;
		}
	}

	for(i=0; i<m_nFields; i++)
	{
		if(m_Field[i])
			m_Field[i] |= FELDMASK_GEFROREN;
		m_Templ[i]=m_Field[i];
	}
	OnLogDelete();
	SetModifiedFlag();
}


void CStr8tsDoc::OnAgain()
{	// delete all r/w fields
	for(int i=0; i<m_nFields; i++)
		if(!(m_Field[i] & FELDMASK_GEFROREN))
			m_Field[i] = 0;
	Einblend();
	SetModifiedFlag();
}


void CStr8tsDoc::OnPause()
{	// Timer Pause / Run
	m_Pause = !m_Pause;
	if(!m_Pause)
		m_Clock0 = clock();
}


void CStr8tsDoc::OnOpen()
{	// open existing file
	if(CheckModified())
		return;
	char *Filter = "Str8ts (*.st8)|*.st8|Alle Dateien (*.*)|*.*||";
	CFileDialog dlg(TRUE, "*.st8", NULL, OFN_HIDEREADONLY, Filter, NULL);
	if(dlg.DoModal() != IDOK)
		return;
	CFile f;
	char buf[512];
	m_strPathName = dlg.GetPathName();
	CString msg;
	if(!f.Open(m_strPathName, CFile::modeRead | CFile::shareDenyNone))
	{
		msg.Format("Datei %s nicht gefunden", m_strPathName);
		AfxMessageBox(msg);
		return;
	}
	m_DocName = f.GetFileTitle();
	CArchive ar( &f, CArchive::load, 512, buf);
	Serialize(ar);
	ar.Close();
	f.Close();
	theApp.AddToRecentFileList(m_strPathName);
	SolveDefaults();
	CheckField(TRUE);
	TimeReset();
	m_Solved = FALSE;
}


void CStr8tsDoc::OnOpenTemplate()
{	// open existing template file
	OnOpen();
	Einblend();
	for(int i=0; i<m_nFields; i++)
	{
		if(m_Templ[i] & FELDMASK_GEFROREN)
			m_Field[i]=m_Templ[i];
		else
			m_Field[i]=0;
	}
	OnLogDelete();
	CheckField(TRUE);
	TimeReset();
	m_Solved = FALSE;
}


void CStr8tsDoc::OnSave()
{
	if(m_strPathName.IsEmpty())
	{
		char *Filter = "Str8ts (*.st8)|*.st8|Alle Dateien (*.*)|*.*||";
		CFileDialog dlg(FALSE, "*.st8", NULL, 0, Filter, NULL);
		if(dlg.DoModal() != IDOK)
			return;

		m_strPathName = dlg.GetPathName();
	}
	Save();
}


void CStr8tsDoc::OnSaveAs()
{
	char *Filter = "Str8ts (*.st8)|*.st8|Alle Dateien (*.*)|*.*||";
	CFileDialog dlg(FALSE, "*.st8", NULL, 0, Filter, NULL);
	if(dlg.DoModal() != IDOK)
		return;
	m_strPathName = dlg.GetPathName();
	Save();
}


void CStr8tsDoc::Save()
{	// save to file m_strPathName

	if(!IsComplete(m_Templ))
	{
		for(int i=0; i<m_nFields; i++)			// Vorlage aktualisieren
			m_Templ[i]=m_Field[i];
	}
	CFile f;
	char buf[512];
	CString msg;

	CheckStandardPath();						// set m_Stufe if standard path used
	if(m_Stufe < 1)								// Kommentar und Stufe abfragen
		OnComment();
	if(!f.Open(m_strPathName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
	{
		msg.Format("Datei %s kann nicht angelegt werden", m_strPathName);
		AfxMessageBox(msg);
		return;
	}
	m_DocName = f.GetFileName();
	CArchive ar( &f, CArchive::store, 512, buf);
	Serialize(ar);
	f.Close();
	SetModifiedFlag(FALSE);
	theApp.AddToRecentFileList(m_strPathName);
	TimeReset();
	SolveDefaults();
}


BOOL CStr8tsDoc::CheckModified()
{
	if (IsModified())
	{
		if(AfxMessageBox("Achtung: das aktuelle Spiel ist noch nicht gespeichert, trotzdem weiter machen?", MB_YESNO) == IDNO)
			return TRUE;
	}
	return FALSE;
}


void CStr8tsDoc::DeleteContents()
{
	m_strPathName.Empty();      // no path name yet
	m_DocName = "Unbenannt";
	SetModifiedFlag(FALSE);     // make clean
	for(int i=0; i<m_nFields; i++)
	{
		m_Templ[i] = 0;
		m_Field[i] = 0;
	}
	Einblend();
	SetSelect(0);
	m_MaxLog = 0;
	SetModifiedFlag(FALSE);
	m_Comment.Empty();
	m_Stufe = 0;
	m_nGeraten = 0;
	TimeReset();
	m_nClocks = 0;
	m_Solved = FALSE;
	m_Pause = FALSE;
}


void CStr8tsDoc::StripExt(CString &Name)
{	// strip file extension from file name (everything right of last dot)
	int i=0, j;
	while(1)
	{
		j = Name.Find('.', i);
		if(j < 0)
			break;
		else
			i = j+1;
	}
	if(i == 0)
		return;				// no extension
	Name = Name.Left(i-1);
}


LPCTSTR CStr8tsDoc::GetPathName()
{
	return m_strPathName;
}


void CStr8tsDoc::Finish()
{	// Game over
	CString fn = sAppPath + SNDFILE_TADA;
	char	user[80];
	size_t	sz=0;
	FILE *	fp;
	errno_t	errno;
	PlaySound(fn, NULL, SND_FILENAME | SND_ASYNC);
	errno = getenv_s(&sz, user, 80, "USERNAME");
	if(errno)
		strcpy_s(user, 80, "Unbekannt");
	fopen_s(&fp, "Str8ts.csv", "at");
	if(fp == NULL)
		return;
	CTime t = CTime::GetCurrentTime();
	int seconds = m_nClocks / CLOCKS_PER_SEC;
	int thh = seconds / 3600;
	int tmm = (seconds - thh * 3600) / 60;
	int tss = seconds % 60;
	fprintf(fp, "%-17s;%d;%02d.%02d.%04d %02d:%02d:%02d;%02d:%02d:%02d;%s\n",
		m_DocName.GetBuffer(), m_Stufe,
		t.GetDay(), t.GetMonth(), t.GetYear(), 
		t.GetHour(), t.GetMinute(), t.GetSecond(), thh, tmm, tss, user);
	fclose(fp);
	m_Solved = TRUE;
}


BOOL CStr8tsDoc::CheckSolved(void)
{
	for(int i=0; i<m_nFields; i++)
		if(m_Field[i] == 0)
			return FALSE;
	return TRUE;
}


int CStr8tsDoc::CheckPossible(int x, int field)
{	// check if x is possible in field
	// a number is possible if it is
	// - not in same row AND						--> -1
	// - not in same column AND						--> -1
	// - not suppressed								--> -2
	// - the field is not set to other number AND	--> -3
	// else						-->  1
	ASSERT((field >= 0) && (field < m_nFields));
	ASSERT((x >= 0) && (x < 10));
	int		i, ix, ix0, row, col;

	if(x == 0)					// 0 is always possible
		return TRUE;
	i = m_Field[field] & FELDMASK_ZAHL;
	if((i > 0) && (x == i))		// already this number set
		return 1;
	if(i > 0)					// already other number set
		return -3;
	row = field / m_FieldSize;
	col = field % m_FieldSize;
	ix0 = row * m_FieldSize;				// row start
	for(i=0; i<m_FieldSize; i++)			// check row
	{
		ix = ix0 + i;
		if((m_Field[ix] & FELDMASK_ZAHL) == x)
			return -1;
	}
	ix0 = col;					// col start
	for(i=0; i<m_FieldSize; i++)			// check column
	{
		ix = ix0 + m_FieldSize * i;
		if((m_Field[ix] & FELDMASK_ZAHL) == x)
			return -1;
	}
	if(m_Info[field] & (1 << x))
		return -2;				// Unterdrückung ein
	return 1;
}


BOOL CStr8tsDoc::IsComplete(char *Field)
{
	// prüfen ob Spiel fertig ist
	for(int i=0; i<m_nFields; i++)
	{
		if(Field[i]==0)
			return FALSE;
	}
	return TRUE;
}


void CStr8tsDoc::UpdateTemplate()
{
	if(!IsComplete(m_Templ))
	{
		for(int i=0; i<m_nFields; i++)			// Vorlage aktualisieren
			m_Templ[i]=m_Field[i];
	}
}


void CStr8tsDoc::OnMelt()
{	// mark all entries as read-write
	for(int i=0; i<m_nFields; i++)
		if(m_Field[i])
			m_Field[i] &= ~FELDMASK_BLOCK;
	OnLogDelete();
	SetModifiedFlag();
}


void CStr8tsDoc::Check()
{	// alle falschen Felder löschen
	for(int i=0; i<m_nFields; i++)
	{
		if(m_Field[i] != m_Templ[i])
			m_Field[i]=0;
	}
}


void CStr8tsDoc::OnSolve()
{	// Lösung anzeigen
	for(int i=0; i<m_nFields; i++)
	{
		m_Field[i] = m_Templ[i];
	}
}

void CStr8tsDoc::OnQuery(int i)
{
	m_Field[i]=m_Templ[i];
	SetModifiedFlag();
}


void CStr8tsDoc::Einblend()
{	// Ausblendungen löschen
	for(int i=0; i<m_nFields; i++)
		m_Info[i] &= 0xFC01;
}


void CStr8tsDoc::Suppress(int n)
{	//bei Mehrfachauswahl nur ausblenden, bei Einfachauswahl ein/ausblenden
	int	i, a=0;
	for(i=0; i<m_nFields; i++)				//Mehrfachauswahl?
		if(m_Info[i] & INFOMASK_SELECT)
		{
			a++;
			if(a>1)
				break;
		}
	for(i=0; i<m_nFields; i++)
		if(m_Info[i] & INFOMASK_SELECT)
		{
			if(a > 1)
				m_Info[i] |= (1 << n);
			else
			{
				m_Info[i] ^= (1 << n);
				break;
			}
		}
}


void CStr8tsDoc::OnSolveF()
{
	for(int i=0; i<m_nFields; i++)
		if(m_Info[i] & INFOMASK_SELECT)
			m_Field[i]=m_Templ[i];
	Solver();
}


void CStr8tsDoc::OnFreezeMelt()
{
	for(int i=0; i<m_nFields; i++)
		if(m_Info[i] & INFOMASK_SELECT)
		{
			m_Field[i] ^= FELDMASK_GEFROREN;
			m_Templ[i] = m_Field[i];
		}
}


void CStr8tsDoc::Solver()
{	// try solver strategies
	SolveAutoEnter();
	SolveCompartment();
}


BOOL CStr8tsDoc::SolveAutoEnter(void)
{
	// alle eindeutigen Zahlen eintragen
	int cell, x, n, val, Anz;
	BOOL	Changed = FALSE;

	if(!m_SolveAutoEnter)						// Funktion deaktiviert
		return FALSE;
	do
	{
		Anz=0;								// keine autom. Eingaben
		for(cell=0; cell<m_nFields; cell++)
		{
			if(m_Field[cell] == 0)
			{
				n = 0;							// Möglichkeiten
				for(x=1; x<=9; x++)				// Zahlen von 1-9 probieren
				{
					if(CheckPossible(x, cell) > 0)
					{
						val=x;
						n++;
					}
				}
				if(n == 1)
				{
					Anz++;
					Log(cell, m_Field[cell], val);
					m_Field[cell] = val;
					Changed = TRUE;
				}
			}
		}
	} while(Anz);
	return Changed;
}


void CStr8tsDoc::CheckStrasse(int Num, BOOL InSpalte)
{
	int		i, sanf=-1, send=-1, ix;
	char	c, f[10], cMask;

	for(i=0; i<m_FieldSize; i++)
	{
		if(InSpalte)
			ix = Num + m_FieldSize*i;
		else
			ix = m_FieldSize*Num + i;
		c = m_Field[ix];


		if(!(c & FELDMASK_BLOCK))		// kein Block
		{
			if(sanf==-1)			// Anfang merken
			{
				memset(f, 0, 10*sizeof(char));
				sanf = i;
			}
			ix = c & 0x0f;
			if((ix >= 1) && (ix <= 9))	//Zahl
			f[ix] = 1;
			send = i;				// vorl. Ende
		}
		if((c & FELDMASK_BLOCK) || (i == m_FieldSize-1))		// Block oder Zeilenende
		{
			if(send > sanf)							// Strassenende
			{
				ix = CheckStrasse1(f, send-sanf+1);
				cMask = (ix > 0)? FELDMASK_STRASSE : FELDMASK_FEHLER;
				if(ix != 0)			// OK oder Fehler
				{
					for(int j=sanf; j<=send; j++)
					{
						if(InSpalte)
							ix = Num + m_FieldSize*j;
						else
							ix = m_FieldSize*Num + j;
						m_Field[ix] |= cMask;
					}
				}
				sanf = -1;
				send = -1;
			}
		}
	}
}


int CStr8tsDoc::CheckStrasse1(char *f, int len)
{
	int		Flankenzaehler = 0, Zahlenzaehler = 0;
	char	Flankenmerker=0;
	for(int i=1; i<=9; i++)		//Zahlen
	{
		if(f[i])
		{
			Zahlenzaehler++;
			if(!Flankenmerker)
				Flankenzaehler++;
		}
		Flankenmerker = f[i];
	}
	if((Flankenzaehler == 1) && (Zahlenzaehler == len))
		return 1;
	if((Flankenzaehler > 1) && (Zahlenzaehler == len))
		return -1;
	return 0;
}


void CStr8tsDoc::OnComment()
{
	CDlgComment dlg;
	dlg.m_Comment = m_Comment;
	dlg.m_Stufe = m_Stufe - 1;
	dlg.m_sGeraten.Format("%d", m_nGeraten);
	if(dlg.DoModal() == IDOK)
	{
		m_Comment = dlg.m_Comment;
		m_Stufe = dlg.m_Stufe + 1;
		m_nGeraten = atoi(dlg.m_sGeraten);
	}
}


BOOL CStr8tsDoc::SolveCompartment()
{
	BOOL	Change = FALSE;
	BOOL	Found = FALSE;
	int		x, y, Feld, ix0, len, ix;
	for(y=0; y<m_FieldSize; y++)				// Such Strassen in Zeilen
	{
		ix0 = m_FieldSize * y;
		len = 0;
		for(x=0; x<m_FieldSize; x++)
		{
			ix = m_FieldSize * y + x;
			Feld = m_Field[ix];
			if(Feld & FELDMASK_BLOCK)
				Found = TRUE;
			else
			{
				if(len == 0)
					ix0 = ix;
				len++;
			}
			if(Found || (x == 8))
			{
				Change |= SolveCompartment1(ix0, len, FALSE);
				len = 0;
				Found = FALSE;
			}
		}
	}

	for(x=0; x<m_FieldSize; x++)				// Such Strassen in Spalten
	{
		ix0 = m_FieldSize * y;
		len = 0;
		for(y=0; y<m_FieldSize; y++)
		{
			ix = m_FieldSize * y + x;
			Feld = m_Field[ix];
			if(Feld & FELDMASK_BLOCK)
				Found = TRUE;
			else
			{
				if(len == 0)
					ix0 = ix;
				len++;
			}
			if(Found || (y == 8))
			{
				Change |= SolveCompartment1(ix0, len, TRUE);
				len = 0;
				Found = FALSE;
			}
		}
	}
	return Change;
}



BOOL CStr8tsDoc::SolveCompartment1(int Start, int Len, BOOL Vert)
{
	BOOL bChange = FALSE;
	int		ix, inc;
	inc = (Vert)? m_FieldSize : 1;						// Increment for row/col
	for(ix=0; ix<Len; ix+=inc)					// walk through compartment
	{
		if(m_Field[Start+ix]==0)				// empty field
		{
			bChange = TRUE;
			break;
		}
	}
	if(!bChange)
		return FALSE;
	bChange =  SolveRangeCheck(Start, Len, Vert);
	bChange |= SolveSingle(Start, Len, Vert);
	bChange |= SolveSureCandidates(Start, Len, Vert);
	bChange |= SolveStrandedDigits(Start, Len, Vert);
	return bChange;
}



BOOL CStr8tsDoc::SolveRangeCheck(int Start, int Len, BOOL Vert)
{
	if(!Len || !m_SolveRangeCheck)
		return FALSE;

	int		i, ix=Start, inc, n;
	int		minF, maxF;							// extremes in field
	int		minC=1, maxC=9;						// extremes in compartment
	// search for the highest low-number and lowest high-number in compartment
	inc = (Vert)? m_FieldSize : 1;						// Increment for row/col
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		minF = 9;
		maxF = 1;
		for(n=1; n<10; n++)						// walk through all numbers
		{
			if(CheckPossible(n, ix) == 1)
			{
				if(n < minF)
					minF = n;
				if(n > maxF)
					maxF = n;
			}
		}
		if(minC < minF)
			minC = minF;
		if(maxC > maxF)
			maxC = maxF;
		ix += inc;
	}
	// now the valid range is (minC .. maxC) - length of compartment
	maxC += Len - 1;
	if(maxC > 9)
		maxC = 9;
	minC -= Len - 1;
	if(minC < 1)
		minC = 1;
	// suppress all numbers that are out of range
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		for(n=1; n<10; n++)						// walk through all numbers
		{
			if(n < minC)
				m_Info[ix] |= (1 << n);
			if(n > maxC)
				m_Info[ix] |= (1 << n);
		}
		ix += inc;
	}
	return FALSE;
}


BOOL CStr8tsDoc::SolveSingle(int Start, int Len, BOOL Vert)
{
	if(!Len || !m_SolveSingle)
		return FALSE;

	int		i, ix=Start, inc, n;
	int		minF, maxF;							// extremes in field
	int		minC=9, maxC=1;						// extremes in compartment
	int		Singles[10];						// array for singles counting
	char	cOld, cNew;
	BOOL	Changed = FALSE;
	// search for the highest low-number and lowest high-number in compartment
	inc = (Vert)? m_FieldSize : 1;						// Increment for row/col
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		minF = 9;
		maxF = 1;
		for(n=1; n<10; n++)						// walk through all numbers
		{
			if(CheckPossible(n, ix) == 1)
			{
				if(n < minF)
					minF = n;
				if(n > maxF)
					maxF = n;
			}
		}
		if(minC > minF)
			minC = minF;
		if(maxC < maxF)
			maxC = maxF;
		ix += inc;
	}
	// now the valid range for sure candidates is
	minF = maxC - Len + 1;
	maxF = minC + Len - 1;
	// count the singles candidates
	ix = Start;
	memset(Singles, 0, 10*sizeof(int));
	for(i=0; i<Len; i++)						// walk through compartment
	{
		for(n = minF; n <= maxF; n++)
		{
			if(CheckPossible(n, ix) == 1)
				Singles[n]++;
		}
		ix += inc;
	}
	// check if 1 or more of the sure candidates are single
	for(n = minF; n <= maxF; n++)
	{
		if(Singles[n] == 1)						// got one
		{	// locate the field and set number
			ix = Start;
			for(i=0; i<Len; i++)
			{
				if(CheckPossible(n, ix) == 1)
				{
					cOld = m_Field[ix];
					cNew = cOld & ~FELDMASK_ZAHL | n;
					if(cOld != cNew)
					{
						Log(ix, cOld, cNew);
						m_Field[ix] = cNew;
						Changed = TRUE;
					}
					break;						// no more occurances
				}
				ix += inc;
			}
		}
	}
	return Changed;
}

void CStr8tsDoc::SolveDisable()
{
	m_Ausblendmode			= FALSE;
	m_SolveAutoEnter		= FALSE;
	m_SolveDisplay			= FALSE;
	m_SolveSureCandidate	= FALSE;
	m_SolveRangeCheck		= FALSE;
	m_SolveSingle			= FALSE;
	m_SolveStrandedDigits	= FALSE;
}


BOOL CStr8tsDoc::SolveSureCandidates(int Start, int Len, BOOL Vert)
{
	if(!Len || !m_SolveSureCandidate)
		return FALSE;

	int		i, ix=Start, inc, n;
	int		Mask, End;							// Bitmask, Compartment end
	int		minF, maxF;							// extremes in field
	int		minC=9, maxC=1;						// extremes in compartment
	BOOL	Changed = FALSE;
	// search for the highest low-number and lowest high-number in compartment
	inc = (Vert)? m_FieldSize : 1;						// Increment for row/col
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		minF = 9;
		maxF = 1;
		for(n=1; n<10; n++)						// walk through all numbers
		{
			if(CheckPossible(n, ix) == 1)
			{
				if(n < minF)
					minF = n;
				if(n > maxF)
					maxF = n;
			}
		}
		if(minC > minF)
			minC = minF;
		if(maxC < maxF)
			maxC = maxF;
		ix += inc;
	}
	// now the valid range for sure candidates is
	minF = maxC - Len + 1;
	maxF = minC + Len - 1;
	if(minF > maxF)								// no sure candidates
		return FALSE;

	// disable the sure candidates from fields in the same row/col that do not belong to the compartment
	ix = (Start / m_FieldSize) * m_FieldSize;	// Start of row
	if(Vert)
		ix += (Start % m_FieldSize);			// Start of Column
	End = Start + (Len - 1) * inc;
	for(i = 0; i<m_FieldSize; i++)				// walk through row/col
	{
		if((ix < Start) || (ix > End))			// not in compartment
		{
			if(!(m_Field[ix] & FELDMASK_BLOCK))
			{
				for(n=1; n<10; n++)
				{
					Mask = (1 << n);
					if((n >= minF) && (n <= maxF) && !(m_Info[ix] & Mask))	// got one
					{
						TRACE("SolveSureCandidates Disable %c%c %d\r\n", ix/m_FieldSize+'A', ix%m_FieldSize+'1', n);
						m_Info[ix] |= Mask;
						Changed = TRUE;
					}
				}
			}
		}
		ix += inc;
	}
	return Changed;
}



BOOL CStr8tsDoc::SolveStrandedDigits(int Start, int Len, BOOL Vert)
{
	return FALSE;
/*
	if(!Len || !m_SolveStrandedDigits)
		return FALSE;

	int		i, ix=Start, inc, n;
	int		Mask=0;								// Bitmask
	int		Stranded=0;							// stranded digits
	int		Anf, End1, End2;
	BOOL	Changed = FALSE;
	BOOL	bStranded;
	// search for missing digits
	inc = (Vert)? m_FieldSize : 1;						// Increment for row/col
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		for(n=1; n<10; n++)						// walk through all numbers
		{
			if(CheckPossible(n, ix) == 1)
				Mask |= (1<<n);
		}
		ix += inc;
	}
	if((Mask == 0x3fe)	|| (Mask == 0))			// no gaps -> no stranded digits
		return Changed;

	n = 1;
	do											// check for stranded digits
	{
		while(1)								// find a digit
		{
			if(Mask & (1 << n))						// Digit
				break;								// found
			else
			{
				n++;
				if(n == 10)							// end
					return Changed;
			}
		}
		Anf = n;
		i = 1;									// count digits to next gap
		while(1)								// find a digit
		{
			n++;								// found
			if(Mask & (1 << n))					// Digit
			{
				i++;
			}
			else								// gap found
				break;
		}
		if(i < Len)								// we got stranded digits
		{
			for 



		bStranded = FALSE;
		for(i=0; i<Len; i++, n++)
		{
			if(!(Mask & (1 << n)))
			{
				bStranded = TRUE;
				break;
			}
		}



		if(!(Mask & (1 << n)))
		End2 = n + Len;

		for(i=n; i<End2; i++)
		{
			if(!(Mask & (1 << i)))
			{
				break;
			}
		}
		if(bStranded)							// some stranded digits found
		{
			for(i=n; i<End2; i++)
			{
				if(Mask & (1 << i))
					Stranded |= (1<<i);			// mark stranded digits
				else
					break;
			}
		}
		n += i;
	} while (n < 10);
	ix = Start;
	for(i=0; i<Len; i++)						// walk through compartment
	{
		for(n=1; n<10; n++)						// walk through all numbers
		{
			Mask = (1 << n);
			if((Stranded & Mask) && !(m_Info[ix] & Mask))
			{
				m_Info[ix] |= Mask;
				Changed = TRUE;
			}
		}
		ix += inc;
	}
	return Changed;
*/
}


BOOL CStr8tsDoc::AutoFreeze()
{	// if no frozen fields -> auto freeze everything
	int		i;
	for(i=0; i<m_nFields; i++)			// check if there are already frozen entries
		if(m_Field[i] & FELDMASK_GEFROREN)
			break;
	if(i == m_nFields)
	{
		OnFreeze();
		return TRUE;			// invalidate
	}
	return FALSE;				// no change
}


void CStr8tsDoc::SolveDefaults()
{
	m_Ausblendmode			= FALSE;
	m_SolveDisplay			= bMZ[m_Stufe];
	m_SolveAutoEnter		= bAE[m_Stufe];
	m_SolveRangeCheck		= bRC[m_Stufe];
	m_SolveSingle			= bSI[m_Stufe];
	m_SolveSureCandidate	= bSC[m_Stufe];
	m_SolveStrandedDigits	= bSD[m_Stufe];
}



void CStr8tsDoc::SetFieldSize(int n)
{
		m_FieldSize = n;
		m_nFields = n * n;
}


void CStr8tsDoc::TimeUpdate()
{
	long	clocks = clock();
	if(!m_Solved && !m_Pause)
	{
		m_nClocks += (clocks - m_Clock0);
	}
	m_Clock0 = clocks;
}


void CStr8tsDoc::TimeReset()
{
	m_Clock0 = clock();
	m_nClocks = 0;
}

void CStr8tsDoc::CheckStandardPath()
{
	int		i, i0;
	CString str;

	i0 = m_strPathName.GetLength();
	if(i0 < 12)
		return;
	i0 -= 12;
	str = m_strPathName.Mid(i0+0, 2);			// yymmddax
	i = atoi(str);							// yy year
	if((i < 12) || (i > 99))
		return;
	str = m_strPathName.Mid(i0+2, 2);			// yymmddax
	i = atoi(str);							// mm month
	if((i < 1) || (i > 12))
		return;
	str = m_strPathName.Mid(i0+4, 2);			// yymmddax
	i = atoi(str);
	if((i < 1) || (i > 31))
		return;
	i = tolower(m_strPathName.GetAt(i0+6));	// yymmddax
	if((i <'a') || (i > 'z'))				// a day count (a, b, ...)
		return;
	i = m_strPathName.GetAt(i0+7) - '0';		// yymmddax
	if((i >= 1) && (i <= 5))				// x level (1..5)
		m_Stufe = i;
}
