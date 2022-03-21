#if !defined(AFX_DLGS_H__99947CE4_9D0D_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_DLGS_H__99947CE4_9D0D_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewCrossSumDlg dialog

class CNewCrossSumDlg : public CDialog
{
// Construction
public:
	CNewCrossSumDlg(CWnd* pParent = NULL);   // standard constructor

	CString m_csAuthor;
	BOOL m_bReadOnly;

// Dialog Data
	//{{AFX_DATA(CNewCrossSumDlg)
	enum { IDD = IDD_NEWOPTIONS };
	CEdit	m_cLevel;
	CSpinButtonCtrl	m_cSpin;
	int		m_cols;
	int		m_rows;
	int		m_level;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCrossSumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCrossSumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanced();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog

class CDlgOptions : public CDialog
{
// Construction
public:
	CDlgOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptions)
	enum { IDD = IDD_OPTIONS };
	int		m_nStyle;
	BOOL	m_bShowIncorrect;
	BOOL	m_bAutoFill;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptions)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog

class CDlgSave : public CDialog
{
// Construction
public:
	CDlgSave(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSave)
	enum { IDD = IDD_QUERYSAVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSave)
	afx_msg void OnNo();
	afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced dialog

class CDlgAdvanced : public CDialog
{
// Construction
public:
	CDlgAdvanced(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAdvanced)
	enum { IDD = IDD_ADVOPTIONS };
	CString	m_csAuthor;
	BOOL	m_bReadOnly;
	BOOL	m_bSideSide;
	BOOL	m_bTopBottom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAdvanced)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CSelectHelpersDlg dialog

class CSelectHelpersDlg : public CDialog
{
// Construction
public:
	CSelectHelpersDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectHelpersDlg)
	enum { IDD = IDD_SELECTSTART };
	BOOL	m_bAlwaysShow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectHelpersDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd *m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CSelectHelpersDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGS_H__99947CE4_9D0D_11D7_A1CF_0050DA71997A__INCLUDED_)
