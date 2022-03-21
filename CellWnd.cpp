// CellWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CrossSums.h"
#include "CellWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCSTR lpszFormats[] = {
	"%d\n\n\0",
	"%d\n\n\t\t%d\0",
	"%d\n\t%d\n\t\t%d\0",
	"%d\t\t%d\n\n%d\t\t%d\0",
	"%d\t\t%d\n\t%d\n%d\t\t%d\0",
	"%d\t\t%d\n%d\t\t%d\n%d\t\t%d\0",
	"%d\t\t%d\n%d\t%d\t%d\n%d\t\t%d\0",
	"%d\t%d\t%d\n%d\t\t%d\n%d\t%d\t%d\0",
	"%d\t%d\t%d\n%d\t%d\t%d\n%d\t%d\t%d\0"
};

#define TABSTOPSIZE	0x0300

extern OPTIONS options;
extern PREFS   prefs;

/////////////////////////////////////////////////////////////////////////////
// CNumberWnd

CNumberWnd::CNumberWnd()
{
	m_pFont = NULL;
	m_bFocus = FALSE;
	m_pData = NULL;
	m_row = 0;
	m_col = 0;
	m_value = 0;
	m_actual = 0;
	m_nFlash = 0;
	m_lTime = 0;
	m_list = 0;
	m_starter = 0;
}

CNumberWnd::CNumberWnd(CWnd *pParent, const RECT &rect,CFont *pFont,CFont *pListFont)
{
	m_pFont = pFont;
	m_pListFont = pListFont;
	m_bFocus = FALSE;
	m_pData = NULL;
	m_row = 0;
	m_col = 0;
	m_value = 0;
	m_actual = 0;
	m_nFlash = 0;
	m_lTime = 0;
	m_list = 0;
	m_starter = 0;
	m_bmp.LoadBitmap(IDB_FOCUSBRUSH); //CBitmap
	Create(NULL,"",WS_CHILD|WS_VISIBLE,rect,pParent,0);
}

CNumberWnd::~CNumberWnd()
{
}


BEGIN_MESSAGE_MAP(CNumberWnd, CWnd)
	//{{AFX_MSG_MAP(CNumberWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_SETCELLDATA, OnSetCellData)
	ON_MESSAGE(WM_GETCELLDATA, OnGetCellData)
	ON_MESSAGE(WM_FLASH, OnFlash)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CNumberWnd::GenerateListString(LPSTR szList)
{
	// count the number in the list
	int i,n=0,num[9];
	NUMBERLIST l = m_list;
	for(i=1;i<=9;i++)
	{
		if(IS_NUMBER_LISTED(i,l))
		{
			num[n] = i;
			n++;
		}
	}

	if(n==0)
	{
		strcpy(szList,"\0");
		return 0;
	}

	char szFmt[256];
	strcpy(szFmt,lpszFormats[n-1]);
	switch(n)
	{
	case 1:
		wsprintf(szList,szFmt,num[0]);
		break;
	case 2:
		wsprintf(szList,szFmt,num[0],num[1]);
		break;
	case 3:
		wsprintf(szList,szFmt,num[0],num[1],num[2]);
		break;
	case 4:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3]);
		break;
	case 5:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3],num[4]);
		break;
	case 6:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3],num[4],num[5]);
		break;
	case 7:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3],num[4],num[5],num[6]);
		break;
	case 8:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3],num[4],num[5],num[6],num[7]);
		break;
	case 9:
		wsprintf(szList,szFmt,num[0],num[1],num[2],num[3],num[4],num[5],num[6],num[7],num[8]);
		break;
	default: ASSERT(FALSE); break;
	}

	return n;
}

/////////////////////////////////////////////////////////////////////////////
// CNumberWnd message handlers
/////////////////////////////////////////////////////////////////////////////
// CSumWnd

CSumWnd::CSumWnd()
{
	m_pFont = NULL;
	m_pData = NULL;
	m_hsum = 0;
	m_vsum = 0;
	m_row = 0;
	m_col = 0;
}

CSumWnd::CSumWnd(CWnd *pParent,const RECT &rect,CFont *pFont)
{
	m_pData = NULL;
	m_pFont = pFont;
	m_hsum = 0;
	m_vsum = 0;
	m_row = 0;
	m_col = 0;
	Create(NULL,"",WS_CHILD|WS_VISIBLE,rect,pParent,0);
}

CSumWnd::~CSumWnd()
{
}


BEGIN_MESSAGE_MAP(CSumWnd, CWnd)
	//{{AFX_MSG_MAP(CSumWnd)
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETCELLDATA, OnSetCellData)
	ON_MESSAGE(WM_GETCELLDATA, OnGetCellData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSumWnd message handlers

void CSumWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect r,rText;
	char sz[8];
	int nTextH;

	GetClientRect(&r);
	nTextH = r.Height()/3;

	CFont *pfont=dc.SelectObject(m_pFont);
	CBrush *pBr = NULL;
	CPen *pPen = NULL;
	
	CBrush br(prefs.m_clrBkgnd);
	CPen pen(PS_SOLID,1,prefs.m_clrSumBorder);

	pBr = (CBrush *)dc.SelectObject(&br);
	pPen = (CPen *)dc.SelectObject(&pen);
		
	dc.SetBkColor(prefs.m_clrBkgnd); //black
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(prefs.m_clrSum);//white
	dc.Rectangle(&r);

	if(m_hsum!=0)
	{
		rText.SetRect(3,3,r.Width()-3,3+nTextH);
		wsprintf(sz,"%d", m_hsum);
		dc.DrawText((LPCSTR)sz,&rText,DT_SINGLELINE|DT_RIGHT);
	}
	if(m_vsum!=0)
	{
		rText.SetRect(3,r.Height() - 3 - nTextH,r.Width()-3,r.Height()-3);
		wsprintf(sz,"%d", m_vsum);
		dc.DrawText((LPCSTR)sz,&rText,DT_SINGLELINE|DT_LEFT);
	}

	if( options.edit || (m_hsum!=0 || m_vsum!=0))
	{
		CPen pen2(PS_SOLID,1,prefs.m_clrSum);
		CPen *p = (CPen *)dc.SelectObject(&pen2);
		dc.MoveTo(5,5);
		dc.LineTo(r.Width()-5,r.Height()-5);
		dc.SelectObject(p);
	}

	dc.SelectObject(pPen);
	dc.SelectObject(pBr);
	dc.SelectObject(pfont);

}

long CSumWnd::OnSetCellData(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case CELL_PTR:
		m_pData = (void*)lParam;
		break;
	case CELL_VALUE:
		m_hsum = LOWORD(lParam);
		m_vsum = HIWORD(lParam);
		break;
	case CELL_ROWCOL:
		m_row = LOWORD(lParam);
		m_col = HIWORD(lParam);
		break;
	}
	return 0L;
}

long CSumWnd::OnGetCellData(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case CELL_PTR:
		return (long)m_pData;
		break;
	case CELL_VALUE:
		return MAKELONG((WORD)m_hsum,(WORD)m_vsum);
		break;
	case CELL_ROWCOL:
		return MAKELONG((WORD)m_row,(WORD)m_col);
		break;
	}
	return 0L;
}

int CNumberWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


long CNumberWnd::OnSetCellData(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case CELL_PTR:
		m_pData = (void*)lParam;
		break;
	case CELL_VALUE:
		m_value = LOWORD(lParam);
		m_actual = HIWORD(lParam);
		break;
	case CELL_LIST:
		m_list = (NUMBERLIST)lParam;
		break;
	case CELL_ROWCOL:
		m_row = LOWORD(lParam);
		m_col = HIWORD(lParam);
		break;
	case CELL_STARTER:
		m_starter = (int)lParam;
		break;
	}

	return 0L;
}

long CNumberWnd::OnGetCellData(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case CELL_PTR:
		return (long)m_pData;
		break;
	case CELL_VALUE:
		return  MAKELONG((WORD)m_value,(WORD)m_actual);
		break;
	case CELL_LIST:
		return (long)m_list;
		break;
	case CELL_ROWCOL:
		return MAKELONG((WORD)m_row,(WORD)m_col);
	case CELL_STARTER:
		return (long)m_starter;
		break;
	}

	return 0L;
}

void CNumberWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect r;
	GetClientRect(&r);

	CBrush *pBr = NULL;
	CPen *pPen = NULL;

	CBrush br0(prefs.m_clrCells);
	CPen pen(PS_SOLID,1,prefs.m_clrCellBorder);

	pBr = (CBrush*)dc.SelectObject(&br0);
	pPen = (CPen*)dc.SelectObject(&pen);
	dc.Rectangle(&r);

	if(m_starter)// && (options.edit || m_value != 0))
	{
		CRect _r = r;
		_r.DeflateRect(1,1);
		CBrush br(HS_DIAGCROSS,0x00C0C0C0); 
		dc.FillRect(&_r,&br);
	}

	if(m_bFocus)
	{
		CRect _r = r;
		_r.DeflateRect(1,1);
		CBrush br(&m_bmp);//br(HS_DIAGCROSS,0x00C0C0C0); //
		dc.FillRect(&_r,&br);
	}
	
	if(m_value!=0)
	{
		char sz[8];
		wsprintf(sz,"%d", m_value);
		r.DeflateRect(1,1);
		CFont *pfont=dc.SelectObject(m_pFont);
		dc.SetBkMode(TRANSPARENT);
		if(options.show_correct && m_actual!=0 && (m_value!=m_actual))
			dc.SetTextColor(prefs.m_clrWrong);
		else
			dc.SetTextColor(prefs.m_clrText);
		dc.DrawText((LPCSTR)sz,&r,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		dc.SelectObject(pfont);
	}
	else if(m_list != NO_NUMBERS)// cell value = 0
	{
		char sz[256];
		GenerateListString(sz);
		r.left+=4; r.top += 2; r.right += 4; //r.bottom += 4;
		CFont *pfont=dc.SelectObject(m_pListFont);
		dc.SetTextColor(0x00808080);
//		dc.SetTextColor(prefs.m_clrText>>1);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText((LPCSTR)sz,&r,TABSTOPSIZE|DT_TABSTOP|DT_LEFT|DT_EXPANDTABS);
		dc.SelectObject(pfont);
	}

	dc.SelectObject(pBr);
	dc.SelectObject(pPen);

	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CNumberWnd::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::DestroyWindow();
}

void CNumberWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd::OnLButtonDown(nFlags, point);
	ClientToScreen(&point);
	GetParent()->ScreenToClient(&point);
	GetParent()->SendMessage(WM_LBUTTONDOWN,(WPARAM)nFlags, (LPARAM)MAKELPARAM(point.x,point.y) );
}

void CNumberWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CNumberWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


void CNumberWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CNumberWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CNumberWnd::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	m_bFocus = TRUE;
	Invalidate();
}

void CNumberWnd::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	m_bFocus = FALSE;
	Invalidate();
}

long CNumberWnd::OnFlash(WPARAM wParam, LPARAM lParam)
{
	m_nFlash = wParam << 1; // twice number of times to flash
	m_lTime = lParam;
	
	BOOL bFocus = m_bFocus;
	m_bFocus = TRUE;
	Invalidate();
	UpdateWindow(); //Redraw
	m_bFocus = bFocus;

	SetTimer(WM_FLASH,m_lTime,NULL);

	
	return 0L;
}

void CNumberWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bFocus = m_bFocus;

	m_nFlash--;

	if(m_nFlash & 0x01 == 0x01)
		m_bFocus = FALSE;
	else
		m_bFocus = TRUE;

	Invalidate();
	UpdateWindow();

	m_bFocus = bFocus;

	KillTimer(WM_FLASH);
	if(m_nFlash)
	{
		SetTimer(nIDEvent,m_lTime,NULL);
	}
	else
	{
		Invalidate();
		UpdateWindow();
	}


	CWnd::OnTimer(nIDEvent);
}
