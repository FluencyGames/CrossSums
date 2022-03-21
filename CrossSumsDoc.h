// CrossSumsDoc.h : interface of the CCrossSumsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CROSSSUMSDOC_H__3A8C6E71_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CROSSSUMSDOC_H__3A8C6E71_9D08_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NEXT_CELL	0
#define NEXT_SUM	1
#define SUM_HOME	2
#define SUM_END		4

typedef struct puzzlecell
{
	int h_len;
	int v_len;
	SCELL cell;
} SPUZZLECELL;

typedef SPUZZLECELL* LPTRPUZZLECELL;

#ifndef GET_CELL
#define GET_CELL(_r,_c) ((SCELL*)&m_cells[(_r) * m_cols + (_c)])
#endif

class CCrossSumsDoc : public CDocument
{
protected: // create from serialization only
	CCrossSumsDoc();
	DECLARE_DYNCREATE(CCrossSumsDoc)

// Attributes
public:
	static PREFS defaultPrefs;
	CString m_csAuthor;

// Operations
public:
	void ZeroCells();
	BOOL IsSolved();
	BOOL ReadOnly() { return m_bReadOnly; }

	int FindVActualSum(int row, int col);
	int FindHActualSum(int row, int col);
	int FindVUserSum(int row, int col);
	int FindHUserSum(int row, int col);

	int FindLegalValues(int row, int col, NUMBERLIST &list);
	int FindPossibleValues(int row, int col, NUMBERLIST &list);

	int GenerateCellNumber(int row, int col);
	int GenerateNumbers();

	int GetNumberOfRows() { return m_rows; }
	int GetNumberOfCols() { return m_cols; }
	SCELL *GetCell(int row, int col) { return (SCELL*)&m_cells[ row*m_cols + col]; }

	SCELL *FindAdjacentCell(int &row, int &col, int h, int v, UINT uFlags = NEXT_CELL);
	NUMBERLIST ToggleCellListNumber(int row, int col, int nVal);
	int SetCellValue(int row, int col, int val);
	int AutoFill(int row, int col);
	void SetCellStarter(int row, int col, int nStarter = 1);
	void SetShowHelpersFlag(BOOL bShow = TRUE);
	BOOL GetShowHelpersFlag();
	
	void StartPuzzleTime();
	BOOL ResetPuzzleTime(BOOL bWarn = FALSE);
	void StopPuzzleTime();
	long GetPuzzleTime(CTimeSpan *pTSpan = NULL);

	int CreateNewPuzzle();
	int ReadPuzzleData(CArchive &ar, CString csWhat);
	int MakePuzzle(SPUZZLECELL **pPuz);
	int  GenerateSums();
	void CleanUp(SPUZZLECELL **pPuz);
	int AssignHLen(int row, int col, SPUZZLECELL **pPuz);
	int AssignVLen(int row, int col, SPUZZLECELL **pPuz);
	int MakeRandomHLength(int max_len);
	int MakeRandomVLength(int max_len);

	void ValidateCells();
	void ClearUserValues();
	void InitPuzzleEditor();
	void UpdateCellData(int row, int col, CELL_TYPE type, long lData);	
	BOOL PublishPuzzle();
	void ToggleView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossSumsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnChangedViewList();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL

// Implementation
public:
	int FindVActualSum();
	virtual ~CCrossSumsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	SCELL *m_cells;
	int		m_cols;
	int		m_rows;
	int		m_level;
	long	m_lGameTime;
	int		m_boardlevel;
	int		m_numberlevel;
	BOOL	m_bShowHelpers;
	BOOL	m_bReadOnly;
	CView  *m_pHidden;
	CTimeSpan m_time;


// Generated message map functions
protected:
	void InitializeFromArray(int rows, int cols, int *pcells);

	//{{AFX_MSG(CCrossSumsDoc)
	afx_msg void OnPuzzleOptions();
	afx_msg void OnPuzzlePreferences();
	afx_msg void OnPuzzleNewvalues();
	afx_msg void OnPuzzleSolution();
	afx_msg void OnUpdateEditPuzzle(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleCalculate();
	afx_msg void OnPuzzleTimedpuzzle();
	afx_msg void OnUpdatePuzzleTimedpuzzle(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleResetpuzzle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSSUMSDOC_H__3A8C6E71_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
