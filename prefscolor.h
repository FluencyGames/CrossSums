#if !defined(AFX_PREFSCOLOR_H__E2F99844_B548_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_PREFSCOLOR_H__E2F99844_B548_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrefsColor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSampleViewBtn window

class CSampleViewBtn : public CButton
{
// Construction
public:
	CSampleViewBtn();

// Attributes
public:
	static int		m_bShowGrid;

	static COLORREF m_clrBkgnd;
	static COLORREF m_clrCells;
	static COLORREF m_clrText;
	static COLORREF m_clrSum;
	static COLORREF m_clrFlash;
	static COLORREF m_clrHilite;
	static COLORREF m_clrWrong;
	static COLORREF m_clrGrid; 
	static COLORREF m_clrBkgndBorder; 
	static COLORREF m_clrCellBorder;
	static COLORREF m_clrSumBorder;

	static int m_nFontTextSize;
	static CString m_csFontTextName;

	static int m_nFontSumSize;
	static CString m_csFontSumName;

	CFont m_fontText;
	CFont m_fontSum;

	void UpdateFont();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleViewBtn)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSampleViewBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSampleViewBtn)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CPrefsColor dialog

class CPrefsColor : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsColor)

// Construction
protected:
	PREFS m_defaults;

public:
	CPrefsColor();
	CPrefsColor(PREFS &defaults);
	~CPrefsColor();

	COLORREF m_clrBkgnd;
	COLORREF m_clrCells;
	COLORREF m_clrText;
	COLORREF m_clrSum;
	COLORREF m_clrFlash;
	COLORREF m_clrHilite;
	COLORREF m_clrWrong;
	COLORREF m_clrGrid; 
	COLORREF m_clrBkgndBorder; 
	COLORREF m_clrCellBorder;
	COLORREF m_clrSumBorder;


	void UpdateSampleView();

// Dialog Data
	//{{AFX_DATA(CPrefsColor)
	enum { IDD = IDD_PREFSCOLOR };
	CSampleViewBtn	m_cSample;
	CListBox	m_cList;
	BOOL	m_bShowGrid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsColor)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsColor)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkList3();
	afx_msg void OnCustom();
	afx_msg void OnShowgrid();
	afx_msg void OnRestoredefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPrefsFonts dialog

class CPrefsFonts : public CPropertyPage
{
	DECLARE_DYNCREATE(CPrefsFonts)

protected:
	PREFS m_defaults;

// Construction
public:
	CPrefsFonts();
	CPrefsFonts(PREFS &defaults);
	~CPrefsFonts();

	void ListFonts();
	void SetCurFontData();
	void UpdateCurrentFont();
	void UpdateSampleFont();

	LOGFONT m_lfText;
	LOGFONT m_lfSums;

// Dialog Data
	//{{AFX_DATA(CPrefsFonts)
	enum { IDD = IDD_PREFSFONT };
	CSampleViewBtn	m_cSample;
	CComboBox	m_cSize;
	CListBox	m_cList;
	CComboBox	m_cFont;
	CString	m_csFontName;
	CString	m_csFontSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPrefsFonts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrefsFonts)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeFontsize();
	afx_msg void OnRestoredefaults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREFSCOLOR_H__E2F99844_B548_11D7_A1CF_0050DA71997A__INCLUDED_)
