// Dlgs.cpp : implementation file
//

#include "stdafx.h"
#include "CrossSums.h"
#include "Dlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;

/////////////////////////////////////////////////////////////////////////////
// CNewCrossSumDlg dialog


CNewCrossSumDlg::CNewCrossSumDlg(CWnd* pParent /*=NULL*/) //CSpinCtrl
	: CDialog(CNewCrossSumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCrossSumDlg)
	m_cols = 0;
	m_rows = 0;
	m_level = 0;
	//}}AFX_DATA_INIT
}


void CNewCrossSumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCrossSumDlg)
	DDX_Control(pDX, IDC_LEVEL, m_cLevel);
	DDX_Control(pDX, IDC_SPIN1, m_cSpin);
	DDX_Text(pDX, IDC_HSIZE, m_cols);
	DDV_MinMaxInt(pDX, m_cols, 10, 50);
	DDX_Text(pDX, IDC_VSIZE, m_rows);
	DDV_MinMaxInt(pDX, m_rows, 10, 50);
	DDX_Text(pDX, IDC_LEVEL, m_level);
	DDV_MinMaxInt(pDX, m_level, 1, 5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCrossSumDlg, CDialog)
	//{{AFX_MSG_MAP(CNewCrossSumDlg)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCrossSumDlg message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog


CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptions)
	m_nStyle = -1;
	m_bShowIncorrect = FALSE;
	m_bAutoFill = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptions)
	DDX_Radio(pDX, IDC_PLAYINGSTYLE, m_nStyle);
	DDX_Check(pDX, IDC_SHOWINCORRECT, m_bShowIncorrect);
	DDX_Check(pDX, IDC_AUTOFILL, m_bAutoFill);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptions)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers
/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog


CDlgSave::CDlgSave(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSave::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSave)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSave::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSave)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSave, CDialog)
	//{{AFX_MSG_MAP(CDlgSave)
	ON_BN_CLICKED(IDNO, OnNo)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSave message handlers

void CDlgSave::OnNo() 
{
	EndDialog(IDNO);	
}

void CDlgSave::OnYes() 
{
	EndDialog(IDYES);	
}

BOOL CNewCrossSumDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//m_cSpin.SetBuddy(&m_cLevel);
	m_cSpin.SetRange(1,5);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced dialog


CDlgAdvanced::CDlgAdvanced(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAdvanced::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAdvanced)
	m_csAuthor = _T("");
	m_bReadOnly = FALSE;
	m_bSideSide = FALSE;
	m_bTopBottom = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAdvanced)
	DDX_Text(pDX, IDC_AUTHOR, m_csAuthor);
	DDV_MaxChars(pDX, m_csAuthor, 128);
	DDX_Check(pDX, IDC_READONLY, m_bReadOnly);
	DDX_Check(pDX, IDC_SIDESIDE, m_bSideSide);
	DDX_Check(pDX, IDC_TOPBOTTOM, m_bTopBottom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAdvanced, CDialog)
	//{{AFX_MSG_MAP(CDlgAdvanced)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced message handlers

void CNewCrossSumDlg::OnAdvanced() 
{
	CDlgAdvanced dlg;
	
	dlg.m_bReadOnly = m_bReadOnly;
	dlg.m_csAuthor = m_csAuthor;
	dlg.m_bSideSide = options.side_side;
	dlg.m_bTopBottom = options.top_bottom;

	if(dlg.DoModal()==IDOK)
	{
		options.side_side = dlg.m_bSideSide;
		options.top_bottom = dlg.m_bTopBottom;
		m_bReadOnly = dlg.m_bReadOnly;
		m_csAuthor = dlg.m_csAuthor;
	}
}
/////////////////////////////////////////////////////////////////////////////
// CSelectHelpersDlg dialog


CSelectHelpersDlg::CSelectHelpersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectHelpersDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectHelpersDlg)
	m_bAlwaysShow = FALSE;
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	Create(IDD_SELECTSTART, pParent);
}


void CSelectHelpersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectHelpersDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bAlwaysShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectHelpersDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectHelpersDlg)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectHelpersDlg message handlers

void CSelectHelpersDlg::OnOK() 
{
	m_pParent->SendMessage(WM_SELECTING,IDOK);
	DestroyWindow();
}

void CSelectHelpersDlg::OnCancel() 
{
	m_pParent->SendMessage(WM_SELECTING,IDCANCEL);
	DestroyWindow();
}

void CSelectHelpersDlg::PostNcDestroy() 
{
	delete this;
}

BOOL CSelectHelpersDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_pParent->SendMessage(WM_SELECTING,0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSelectHelpersDlg::DestroyWindow() 
{
	return CDialog::DestroyWindow();
}

void CSelectHelpersDlg::OnCheck1() 
{
	UpdateData();
	m_pParent->SendMessage(WM_SELECTING,IDC_CHECK1,(LPARAM)m_bAlwaysShow);
}
