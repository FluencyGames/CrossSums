// PrefsColor.cpp : implementation file
//

#include "stdafx.h"
#include "CrossSums.h"
#include "PrefsColor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;

/////////////////////////////////////////////////////////////////////////////
// CPrefsColor property page

IMPLEMENT_DYNCREATE(CPrefsColor, CPropertyPage)

CPrefsColor::CPrefsColor() : CPropertyPage(CPrefsColor::IDD)
{
	//{{AFX_DATA_INIT(CPrefsColor)
	m_bShowGrid = FALSE;
	//}}AFX_DATA_INIT
}

CPrefsColor::CPrefsColor(PREFS &defaults) : CPropertyPage(CPrefsColor::IDD)
{
	memcpy((void*)&m_defaults,(void*)&defaults,sizeof(PREFS));
	m_bShowGrid = FALSE;
}

CPrefsColor::~CPrefsColor()
{
}

void CPrefsColor::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsColor)
	DDX_Control(pDX, IDC_SAMPLE, m_cSample);
	DDX_Control(pDX, IDC_LIST3, m_cList);
	DDX_Check(pDX, IDC_SHOWGRID, m_bShowGrid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsColor, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsColor)
	ON_LBN_DBLCLK(IDC_LIST3, OnDblclkList3)
	ON_BN_CLICKED(IDC_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_SHOWGRID, OnShowgrid)
	ON_BN_CLICKED(IDC_RESTOREDEFAULTS, OnRestoredefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPrefsColor::UpdateSampleView()
{
	int i;

	i = m_cList.FindStringExact(0,"Puzzle");		
	CSampleViewBtn::m_clrBkgnd  = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0,"Box");			
	CSampleViewBtn::m_clrCells  = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0,"Text");			
	CSampleViewBtn::m_clrText   = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0,"Sums");			
	CSampleViewBtn::m_clrSum   = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0,"Sums Border");			
	CSampleViewBtn::m_clrSumBorder   = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0,"Incorrect");	
	CSampleViewBtn::m_clrWrong  = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0, "Puzzle Border");
	CSampleViewBtn::m_clrBkgndBorder = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0, "Box Border");
	CSampleViewBtn::m_clrCellBorder = (COLORREF)m_cList.GetItemData(i);

	i = m_cList.FindStringExact(0, "Grid");
	CSampleViewBtn::m_clrGrid = (COLORREF)m_cList.GetItemData(i);

	m_cSample.Invalidate();
	m_cSample.UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CPrefsColor message handlers

BOOL CPrefsColor::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	int i;

	i = m_cList.AddString("Puzzle");	 m_cList.SetItemData(i, m_clrBkgnd);
	i = m_cList.AddString("Box");		 m_cList.SetItemData(i, m_clrCells);
	i = m_cList.AddString("Text");		 m_cList.SetItemData(i, m_clrText);
	i = m_cList.AddString("Sums");		 m_cList.SetItemData(i, m_clrSum);
	i = m_cList.AddString("Incorrect");	 m_cList.SetItemData(i, m_clrWrong);
	i = m_cList.AddString("Grid");			m_cList.SetItemData(i,m_clrGrid);
	i = m_cList.AddString("Puzzle Border");	m_cList.SetItemData(i,m_clrBkgndBorder);
	i = m_cList.AddString("Box Border");	m_cList.SetItemData(i,m_clrCellBorder);
	i = m_cList.AddString("Sums Border");	m_cList.SetItemData(i,m_clrSumBorder);

	m_cList.SetCurSel(0);

	UpdateSampleView();
	m_cSample.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsColor::OnDblclkList3() 
{
	OnCustom();
}

void CPrefsColor::OnCustom() 
{
	int i = m_cList.GetCurSel();
	if(i<0)
	{
		::MessageBeep(-1);
		return;
	}

	COLORREF clr = (COLORREF)m_cList.GetItemData(i);
	if(clr==(COLORREF)-1)
		clr = 0x00;
	
	CColorDialog ccd(clr,0,this);
	if(ccd.DoModal()==IDOK)
	{
		m_cList.SetItemData(i,(DWORD)ccd.GetColor());
		UpdateSampleView();
	}
}

void CPrefsColor::OnShowgrid() 
{
	UpdateData(TRUE);
	CSampleViewBtn::m_bShowGrid = m_bShowGrid;
	m_cSample.Invalidate();
	m_cSample.UpdateWindow();
}

void CPrefsColor::OnOK() 
{
	int i;
	i = m_cList.FindStringExact(0,"Puzzle");		m_clrBkgnd  = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Box");			m_clrCells  = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Text");			m_clrText   = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Sums");			m_clrSum	= (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Incorrect");		m_clrWrong  = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Puzzle Border"); m_clrBkgndBorder = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Box Border");	m_clrCellBorder = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Sums Border");	m_clrSumBorder = (COLORREF)m_cList.GetItemData(i);
	i = m_cList.FindStringExact(0,"Grid");			m_clrGrid = (COLORREF)m_cList.GetItemData(i);
	

	CPropertyPage::OnOK();
}


void CPrefsColor::OnRestoredefaults() 
{
	int i;

	i = m_cList.FindStringExact(0,"Puzzle");		
	m_cList.SetItemData(i, m_defaults.m_clrBkgnd);

	i = m_cList.FindStringExact(0,"Box");			
	m_cList.SetItemData(i, m_defaults.m_clrCells);

	i = m_cList.FindStringExact(0,"Text");			
	m_cList.SetItemData(i, m_defaults.m_clrText);

	i = m_cList.FindStringExact(0,"Sums");			
	m_cList.SetItemData(i, m_defaults.m_clrSum);

	i = m_cList.FindStringExact(0,"Sums Border");			
	m_cList.SetItemData(i, m_defaults.m_clrSumBorder);

	i = m_cList.FindStringExact(0,"Incorrect");	
	m_cList.SetItemData(i, m_defaults.m_clrWrong);

	i = m_cList.FindStringExact(0, "Puzzle Border");
	m_cList.SetItemData(i, m_defaults.m_clrBkgndBorder);

	i = m_cList.FindStringExact(0, "Box Border");
	m_cList.SetItemData(i, m_defaults.m_clrCellBorder);

	i = m_cList.FindStringExact(0, "Grid");
	m_cList.SetItemData(i, m_defaults.m_clrGrid);

	m_bShowGrid = m_defaults.m_bShowGrid;
	CSampleViewBtn::m_bShowGrid = m_bShowGrid;

	UpdateData(FALSE);
	UpdateSampleView();
	m_cSample.Invalidate();
	m_cSample.UpdateWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CSampleViewBtn

int		 CSampleViewBtn::m_bShowGrid = FALSE;

COLORREF CSampleViewBtn::m_clrBkgnd = 0x0;
COLORREF CSampleViewBtn::m_clrCells = 0x00ffffff;
COLORREF CSampleViewBtn::m_clrText = 0x0;
COLORREF CSampleViewBtn::m_clrSum = 0x00ffffff;
COLORREF CSampleViewBtn::m_clrFlash = CLR_UNDEFINED;
COLORREF CSampleViewBtn::m_clrHilite = CLR_UNDEFINED;
COLORREF CSampleViewBtn::m_clrWrong = 0x000000ff;
COLORREF CSampleViewBtn::m_clrGrid = 0x0;
COLORREF CSampleViewBtn::m_clrBkgndBorder = 0x0;
COLORREF CSampleViewBtn::m_clrCellBorder = 0x00000000;
COLORREF CSampleViewBtn::m_clrSumBorder = 0x0;

CString CSampleViewBtn::m_csFontTextName = _T("Comic Sans Serif");
CString CSampleViewBtn::m_csFontSumName = _T("Times New Roman");
int		CSampleViewBtn::m_nFontTextSize = 140;
int		CSampleViewBtn::m_nFontSumSize = 80;

CSampleViewBtn::CSampleViewBtn()
{
	m_fontText.CreatePointFont(m_nFontTextSize,m_csFontTextName); //CFont
	m_fontSum.CreatePointFont(m_nFontSumSize,m_csFontSumName);
}

CSampleViewBtn::~CSampleViewBtn()
{
}


BEGIN_MESSAGE_MAP(CSampleViewBtn, CButton)
	//{{AFX_MSG_MAP(CSampleViewBtn)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSampleViewBtn::UpdateFont()
{
	m_fontText.DeleteObject();
	m_fontText.CreatePointFont(m_nFontTextSize,m_csFontTextName); //CFont
	m_fontSum.DeleteObject();
	m_fontSum.CreatePointFont(m_nFontSumSize,m_csFontSumName);

	Invalidate();
	UpdateWindow();

}

/////////////////////////////////////////////////////////////////////////////
// CSampleViewBtn message handlers

void CSampleViewBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(2,2);

	CBrush brBkgnd(m_clrBkgnd);
	CBrush brText(m_clrText);
	CBrush brCell(m_clrCells);
	CBrush brHilite(m_clrHilite);
	CBrush brWrong(m_clrWrong);
	CBrush brFlash(m_clrFlash);
	CPen penGrid(PS_SOLID,1,m_clrGrid);
	CPen penBorder(PS_SOLID,1,m_clrBkgndBorder);
	CPen penSumBorder(PS_SOLID,1,m_clrSumBorder);
	CPen penCell(PS_SOLID,1,m_clrCellBorder);
	CPen pen0(PS_SOLID,1,m_clrBkgnd);
	CPen pen1(PS_SOLID,1,CSampleViewBtn::m_clrText);

	CBrush *pbr = NULL; 
	CPen *pPen = NULL;

	int w = rect.Width()/3;
	int h = rect.Height()/3;
	w = min(w,h);

	// draw rectangle that acts as background
	rect.SetRect(2,2,2 + 3*w,2 + 3*w);
	pbr = (CBrush*)dc.SelectObject(&brBkgnd);
	pPen = (CPen*)dc.SelectObject(&penBorder);
	dc.Rectangle(&rect);

	// draw grid
	if(options.edit || m_bShowGrid)
	{
		int x,y;

		dc.SelectObject(penGrid);

		for(x=2;x<2+3*w;x+=w)
		{
			dc.MoveTo(x,2);
			dc.LineTo(x,2 + 3*w);
		}

		for(y=2;y<2+3*2;y+=w)
		{
			dc.MoveTo(2,y);
			dc.LineTo(2 + 3*2,y);
		}
	}

	// draw cell at (2,2)
	CRect rText1(2 + w, 2 + w, 2 + 2*w, 2 + 2*w);
	dc.SelectObject((CBrush*)&brCell);
	dc.SelectObject((CPen*)&penCell);
	dc.Rectangle(&rText1);

	dc.SetBkColor(m_clrCells); //black
	dc.SetTextColor(m_clrText);
	dc.SetBkMode(TRANSPARENT);
	CFont *pF1 = (CFont*)dc.SelectObject((CFont*)&m_fontText);
	dc.DrawText("9", &rText1, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	// draw cell at (2,3)
	CRect rText2(2 + w, 2 + 2*w, 2 + 2*w, 2 + 3*w);
	dc.Rectangle(&rText2);
	dc.DrawText("8", &rText2, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	// draw cell at (3,2)
	CRect rText3(2 + 2*w, 2 + w, 2 + 3*w, 2 + 2*w);
	dc.SetTextColor(m_clrWrong);
	dc.Rectangle(&rText3);
	dc.DrawText("7", &rText3, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	//
	// draw sum cells
	int hh;
	CRect rText;
	dc.SelectObject(&brBkgnd);
	dc.SelectObject(&penSumBorder);
	dc.SetTextColor(m_clrSum);
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject((CFont*)&m_fontSum);

	// draw cell at 2,1)
	CRect rText4(2 + w, 2, 2 + 2*w, 2 + w);
	dc.Rectangle(&rText4);
	hh = rText4.Height()/3;
	rText.SetRect(rText4.left, rText4.bottom - hh, rText4.right, rText4.bottom);
	dc.DrawText("17", &rText, DT_SINGLELINE|DT_LEFT);

	// draw cell at (1,2)
	CRect rText5(2, 2 + w, 2 + w, 2 + 2*w);
	dc.Rectangle(&rText5);
	hh = rText5.Height()/3;
	rText.SetRect(rText5.left, rText5.top, rText5.right-4, rText5.top + hh);
	dc.DrawText("17", &rText, DT_SINGLELINE|DT_RIGHT);

	// draw cell at (1,3)
	CRect rText6(2, 2 + 2*w, 2 + w, 2 + 3*w);
	dc.Rectangle(&rText6);
	hh = rText6.Height()/3;
	rText.SetRect(rText6.left, rText6.top, rText6.right-4, rText6.top + hh);
	dc.DrawText("8", &rText, DT_SINGLELINE|DT_RIGHT);

	// now draw slash marks
	CPen pen(PS_SOLID,1,m_clrSum);
	pPen = (CPen *)dc.SelectObject(&pen);
	dc.MoveTo(rText4.left+5, rText4.top+5);
	dc.LineTo(rText4.right-5,rText4.bottom-5);

	dc.MoveTo(rText5.left+5, rText5.top+5);
	dc.LineTo(rText5.right-5,rText5.bottom-5);

	dc.MoveTo(rText6.left+5, rText6.top+5);
	dc.LineTo(rText6.right-5,rText6.bottom-5);

	if(pbr)  dc.SelectObject(pbr);
	if(pPen) dc.SelectObject(pPen);
	dc.SelectObject(pF1);
	
	
	// Do not call CButton::OnPaint() for painting messages
}

/////////////////////////////////////////////////////////////////////////////
// CPrefsFonts property page

IMPLEMENT_DYNCREATE(CPrefsFonts, CPropertyPage)

CPrefsFonts::CPrefsFonts() : CPropertyPage(CPrefsFonts::IDD)
{
	//{{AFX_DATA_INIT(CPrefsFonts)
	m_csFontName = _T("");
	m_csFontSize = _T("");
	//}}AFX_DATA_INIT
}

CPrefsFonts::CPrefsFonts(PREFS &defaults) : CPropertyPage(CPrefsFonts::IDD)
{
	memcpy((void*)&m_defaults,(void*)&defaults,sizeof(PREFS));
	m_csFontName = _T("");
	m_csFontSize = _T("");
}

CPrefsFonts::~CPrefsFonts()
{
}

void CPrefsFonts::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrefsFonts)
	DDX_Control(pDX, IDC_SAMPLE, m_cSample);
	DDX_Control(pDX, IDC_FONTSIZE, m_cSize);
	DDX_Control(pDX, IDC_LIST1, m_cList);
	DDX_Control(pDX, IDC_COMBO1, m_cFont);
	DDX_CBString(pDX, IDC_COMBO1, m_csFontName);
	DDV_MaxChars(pDX, m_csFontName, 32);
	DDX_CBString(pDX, IDC_FONTSIZE, m_csFontSize);
	DDV_MaxChars(pDX, m_csFontSize, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrefsFonts, CPropertyPage)
	//{{AFX_MSG_MAP(CPrefsFonts)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_FONTSIZE, OnSelchangeFontsize)
	ON_BN_CLICKED(IDC_RESTOREDEFAULTS, OnRestoredefaults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CALLBACK EnumFontProc( LOGFONT *lplf, TEXTMETRIC *lptm, DWORD dw, LPARAM lparam)
{
	HWND hwnd = (HWND)lparam;
	if(::SendMessage(hwnd,CB_FINDSTRINGEXACT, 0, (LPARAM)lplf->lfFaceName)==CB_ERR)
	{
		::SendMessage(hwnd,CB_ADDSTRING,0,(LPARAM)lplf->lfFaceName);
		return 1;
	}
	return 0;
}

void CPrefsFonts::ListFonts()
{
	CClientDC dc(this);
	LOGFONT lf;

	lf.lfCharSet = 0;//DEFAULT_CHARSET;
	strcpy(lf.lfFaceName,_T("\0"));
	lf.lfPitchAndFamily = 0;

	while(EnumFontFamiliesEx(dc.m_hDC,&lf,(FONTENUMPROC)&EnumFontProc,(LPARAM)m_cFont.GetSafeHwnd(),0))
	{
	}
	
	
}

void CPrefsFonts::UpdateSampleFont()
{
	CSampleViewBtn::m_csFontTextName = m_lfText.lfFaceName;
	CSampleViewBtn::m_nFontTextSize = m_lfText.lfHeight;
	CSampleViewBtn::m_csFontSumName = m_lfSums.lfFaceName;
	CSampleViewBtn::m_nFontSumSize = m_lfSums.lfHeight;
	m_cSample.UpdateFont();
}

void CPrefsFonts::UpdateCurrentFont()
{
	if(!UpdateData(TRUE))
		return;
	
	int i = m_cList.GetCurSel();
	LOGFONT *plf = (LOGFONT *)m_cList.GetItemDataPtr(i);

	i = m_cFont.GetCurSel();
	if(i!=CB_ERR)
	{
		m_cFont.GetLBText(i,m_csFontName);
		if(m_csFontName.CompareNoCase(plf->lfFaceName))
			strcpy(plf->lfFaceName,(LPCTSTR)m_csFontName);
	}

	i = m_cSize.GetCurSel();
	if(i!=CB_ERR)
	{
		m_cSize.GetLBText(i,m_csFontSize);
		int nSize =10*atoi((LPCTSTR)m_csFontSize);
		int nFontSize = plf->lfHeight<0?-plf->lfHeight:plf->lfHeight;
		if(nSize != nFontSize)
			plf->lfHeight = plf->lfHeight<0?-nSize:nSize;
	}

	UpdateSampleFont();

}

void CPrefsFonts::SetCurFontData()
{
	int i = m_cList.GetCurSel();
	LOGFONT *plf = (LOGFONT*)m_cList.GetItemDataPtr(i);
	ASSERT(plf);
	i = m_cFont.FindStringExact(-1,plf->lfFaceName);
	if(i!=CB_ERR)
	{
		m_cFont.SetCurSel(i);
	}
	else
	{
		i = m_cFont.AddString(plf->lfFaceName);
		m_cFont.SetCurSel(i);
	}

	char sz[16];
	int nSize = (plf->lfHeight<0?-plf->lfHeight:plf->lfHeight)/10;
	wsprintf(sz,"%d", nSize);
	i = m_cSize.FindStringExact(-1,sz);
	if(i!=CB_ERR)
	{
		m_cSize.SetCurSel(i);
	}
	else
	{
		i = m_cSize.AddString(sz);
		m_cSize.SetCurSel(i);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CPrefsFonts message handlers

BOOL CPrefsFonts::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	ListFonts();

	m_cSize.AddString("6");
	m_cSize.AddString("8");
	m_cSize.AddString("10");
	m_cSize.AddString("12");
	m_cSize.AddString("14");
	m_cSize.AddString("16");
	m_cSize.AddString("18");

	int i = m_cList.AddString("Text");	m_cList.SetItemDataPtr(i,(void*)&m_lfText);
	i = m_cList.AddString("Sums");		m_cList.SetItemDataPtr(i,(void*)&m_lfSums);

	m_cList.SetCurSel(0);
	SetCurFontData();
	UpdateSampleFont();

	m_cSample.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPrefsFonts::OnSelchangeList1() 
{
	SetCurFontData();
}

// changed font name

void CPrefsFonts::OnSelchangeCombo1() 
{
	UpdateCurrentFont();
}

void CPrefsFonts::OnSelchangeFontsize() 
{
	UpdateCurrentFont();
}

void CPrefsFonts::OnRestoredefaults() 
{
	LOGFONT *plf=NULL;
	int i;
	i = m_cList.FindStringExact(0,"Text");
	plf = (LOGFONT*)m_cList.GetItemDataPtr(i);
	ASSERT(plf);
	plf->lfHeight = m_defaults.m_nTextSize;
	strcpy(plf->lfFaceName,m_defaults.m_szTextFontName);

	i = m_cList.FindStringExact(0, "Sums");
	plf = (LOGFONT*)m_cList.GetItemDataPtr(i);
	ASSERT(plf);
	plf->lfHeight = m_defaults.m_nSumSize;
	strcpy(plf->lfFaceName,m_defaults.m_szSumFontName);

	UpdateSampleFont();
	m_cSample.Invalidate();
	m_cSample.UpdateWindow();
		
}
