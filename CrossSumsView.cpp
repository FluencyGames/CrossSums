// CrossSumsView.cpp : implementation of the CCrossSumsView class
//

#include "stdafx.h"
#include "CrossSums.h"

#include "CrossSumsDoc.h"
#include "CrossSumsView.h"
#include "CellWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;
extern PREFS   prefs;

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView

IMPLEMENT_DYNCREATE(CCrossSumsView, CView)

BEGIN_MESSAGE_MAP(CCrossSumsView, CView)
	//{{AFX_MSG_MAP(CCrossSumsView)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_PUZZLE_SHOWSTARTERHELP, OnPuzzleShowstarterhelp)
	ON_UPDATE_COMMAND_UI(ID_PUZZLE_SHOWSTARTERHELP, OnUpdatePuzzleShowstarterhelp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView construction/destruction

CCrossSumsView::CCrossSumsView()
{
	m_width = 0;
	m_height = 0;
	m_pFocusWnd = NULL;
	m_bDrag = FALSE;
	m_bStarterHelpAvailable = FALSE;
}

CCrossSumsView::~CCrossSumsView()
{
}

void CCrossSumsView::DoSolvedPuzzle()
{
	GetDocument()->StopPuzzleTime();

	if(!options.timed)
		AfxMessageBox(IDS_SOLVED);
	else
	{
		CString csTime;
		CString cs;

		long ltime = GetDocument()->GetPuzzleTime();
		CTimeSpan cts(ltime);
		if(cts.GetHours()>0)
			csTime = cts.Format(" %H:%M");
		else
			csTime = cts.Format(" %M:%S");
		cs.LoadString(IDS_SOLVEDTIMED);
		cs += csTime;
		AfxMessageBox(cs);
	}
}

CWnd *CCrossSumsView::GetCellWnd(int row, int col)
{
	CWnd *p=GetTopWindow();
	ASSERT(p);
	CRect r;
	p->GetWindowRect(&r);
	int width = r.Width();
	int height = r.Height();
	CPoint pt(1,1);
	pt.x += col * width;
	pt.y += row * height;
	p = ChildWindowFromPoint(pt);
	return p;
}

void CCrossSumsView::HandleMoveFocus(int h, int v, UINT uFlags)
{
	if(m_pFocusWnd)
	{
		long l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_ROWCOL);

		int row = LOWORD(l);
		int col = HIWORD(l);

		if(GetDocument()->FindAdjacentCell(row, col, h, v, uFlags))
		{
			CWnd *p = GetCellWnd(row,col);
			if(p!=NULL && p!=this)
			{
				m_pFocusWnd->SendMessage(WM_KILLFOCUS);
				p->SendMessage(WM_SETFOCUS);
				m_pFocusWnd = p;
			}
		}
	}
}

int CCrossSumsView::HandleAutoFillOneCell(int row, int col)
{
	int newval = GetDocument()->AutoFill(row,col);
	if(newval>0)
	{
		CWnd *pWnd = GetCellWnd(row,col);
		if(pWnd==NULL || pWnd == this)
		{
			ASSERT(FALSE);
			return -1;
		}

		TRACE0("update value\r\n");
		int oldval = HIWORD(pWnd->SendMessage(WM_GETCELLDATA,CELL_VALUE));
		pWnd->SendMessage(WM_SETCELLDATA,(WPARAM)CELL_VALUE,(LPARAM)MAKELONG((WORD)newval,(WORD)oldval));
		pWnd->Invalidate();
		pWnd->UpdateWindow();

		pWnd->SendMessage(WM_FLASH,3,350);

		// if successfully filled in a new cell, then
		// auto-fill cells from that cell...
		HandleAutoFill(row,col);
	}

	return (newval>=0?0:-1); // return -1 if this cell @ [row,col] is not a number cell
}

void CCrossSumsView::HandleAutoFill(int row, int col)
{
	if(options.auto_fill)
	{
		int maxrow = GetDocument()->GetNumberOfRows();
		int maxcol = GetDocument()->GetNumberOfCols();
		int r = row;
		int c = col;
		int ret = 0;

		c = col + 1;
		while(c<maxcol && !HandleAutoFillOneCell(r,c))
			c++;

		c = col - 1;
		while(col>=0 && !HandleAutoFillOneCell(r,c))
			c--;

		c = col;
		r = row + 1;
		while(r<maxrow && !HandleAutoFillOneCell(r,c))
			r++;

		r = row - 1;
		while(r>=0 && !HandleAutoFillOneCell(r,c))
			r--;
	}
}

void CCrossSumsView::HandleCharInput(UINT nChar)
{
	if(m_pFocusWnd)
	{
		long lval = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_VALUE);
		int oldval = LOWORD(lval); 
		int val = nChar - '0';
		
		m_pFocusWnd->SendMessage(WM_SETCELLDATA,(WPARAM)CELL_VALUE,(LPARAM)MAKELONG((WORD)val,HIWORD(lval)));
		m_pFocusWnd->Invalidate();
		m_pFocusWnd->UpdateWindow();  

		long l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_ROWCOL);
		int row = LOWORD(l);
		int col = HIWORD(l);

		if(GetDocument()->SetCellValue(row,col,val))
		{
			AfxMessageBox(IDS_ILLEGALVALUE);
			m_pFocusWnd->SendMessage(WM_SETCELLDATA,(WPARAM)CELL_VALUE,(LPARAM)MAKELONG((WORD)oldval,HIWORD(lval)));
			m_pFocusWnd->Invalidate();
			m_pFocusWnd->UpdateWindow();  
			return;
		}

		if(val != 0)
			HandleAutoFill(row,col);

		if(GetDocument()->IsSolved())
			DoSolvedPuzzle();
	}
}

void CCrossSumsView::HandleCellListInput(int nVal)
{
	if(m_pFocusWnd)
	{
		long l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_ROWCOL);
		int row = LOWORD(l);
		int col = HIWORD(l);
		l = GetDocument()->ToggleCellListNumber(row,col,nVal);
		m_pFocusWnd->SendMessage(WM_SETCELLDATA, (WPARAM)CELL_LIST,(LPARAM)l);
		m_pFocusWnd->Invalidate();
		m_pFocusWnd->UpdateWindow();  
	}
}

void CCrossSumsView::InitFonts()
{
	m_fontNumber.DeleteObject();
	m_fontNumber.CreatePointFont(prefs.m_nTextSize,
		prefs.m_szTextFontName);

	m_fontSum.DeleteObject();
	m_fontSum.CreatePointFont(prefs.m_nSumSize,
		prefs.m_szSumFontName);

	m_fontList.DeleteObject();
	m_fontList.CreatePointFont(80, prefs.m_szTextFontName);
}

void CCrossSumsView::CalculateCellSize()
{
	LOGFONT fi;
	m_fontSum.GetLogFont(&fi);
	int font_size = fi.lfHeight<0 ? -fi.lfHeight: fi.lfHeight;
	m_width = (font_size * 3) + 8;
	m_height = m_width;
}

void CCrossSumsView::InitializeCellWnd()
{
	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();
	int x,y;

	SCELL *pCell;

	x = 0;
	y = 0;

	for(int r=0;r<rows;r++)
	{
		for(int c=0;c<cols;c++)
		{
			CRect rect(x,y,x+m_width,y+m_height);
			pCell = GetDocument()->GetCell(r,c);
			if(pCell->type==SUM) 
			{
				CSumWnd *p = new CSumWnd(this,rect,&m_fontSum);
				m_paSum.Add(p);
				p->SendMessage(WM_SETCELLDATA,
								CELL_ROWCOL,
								(LPARAM)MAKELONG((WORD)r,(WORD)c));
			}
			else if(pCell->type==NUMBER)
			{
				CNumberWnd *p = new CNumberWnd(this,rect,&m_fontNumber,&m_fontList);
				m_paNum.Add(p);
				p->SendMessage(WM_SETCELLDATA,
								CELL_ROWCOL,
								(LPARAM)MAKELONG((WORD)r,(WORD)c));
				p->SendMessage(WM_SETCELLDATA,
								CELL_STARTER,
								(LPARAM)pCell->starter);
				
				// use for enabling menu item
				m_bStarterHelpAvailable = m_bStarterHelpAvailable | (pCell->starter == 1);
		
			}
			x += m_width;
		}
		x = 0;
		y += m_height;
	}
}

void CCrossSumsView::ShowStarterCells()
{
	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();

	CWnd *pWnd;
	SCELL *pCell;

	for(int r = 1;r<rows;r++)
	{
		for(int c = 1;c<cols;c++)
		{
			pCell = GetDocument()->GetCell(r,c);

			if(pCell->type == NUMBER && pCell->starter)
			{
				pCell->value.user = pCell->value.actual;
	
				pWnd = GetCellWnd(r,c);
				pWnd->SendMessage(WM_SETCELLDATA,
							CELL_VALUE,
							MAKELONG((WORD)pCell->value.user,(WORD)pCell->value.actual));
		
				pWnd->SendMessage(WM_FLASH,3,350);
//				pWnd->Invalidate();
//				pWnd->UpdateData();
			}
		}
	}


}

void CCrossSumsView::ReSizeFrame()
{
	CRect rParent,rView;
	int cx,cy,dW,dH;
	int rows = 1 + GetDocument()->GetNumberOfRows();
	int cols = 1 + GetDocument()->GetNumberOfCols();
	GetParent()->GetWindowRect(&rParent);
	GetWindowRect(&rView);
	dW = rParent.Width()-rView.Width();
	dH = rParent.Height()-rView.Height();
	cx = (cols * m_width) + dW;
	cy = (rows * m_height) + dH;
	GetParent()->SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER|SWP_NOMOVE|SWP_FRAMECHANGED);
}

int CCrossSumsView::RemoveCellWnd(CWnd *pWnd)
{
	int i,nCnt = 0, n = m_paSum.GetSize();
	if(n>0)
	{
		for(i=n-1;i>=0;i--)
		{
			CSumWnd *p = (CSumWnd*)m_paSum.GetAt(i); //CptrArray
			if(pWnd == NULL || p == pWnd)
			{
				nCnt++;
				m_paSum.RemoveAt(i);
				p->DestroyWindow();
				delete p;
			}
		}
	}

	n = m_paNum.GetSize();
	if(n>0)
	{
		for(i=n-1;i>=0;i--)
		{
			CNumberWnd *p = (CNumberWnd*)m_paNum.GetAt(i);
			if(pWnd == NULL || p == pWnd)
			{
				nCnt++;
				m_paNum.RemoveAt(i);
				p->DestroyWindow();
				delete p;
			}
		}
	}

	return nCnt;
}


BOOL CCrossSumsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView drawing

void CCrossSumsView::OnDraw(CDC* pDC)
{
	CCrossSumsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect r;
	GetClientRect(&r);
	CBrush *pBr = NULL;
	CPen *pPen = NULL;

	CBrush br(prefs.m_clrBkgnd);
	CPen pen(PS_SOLID,1,prefs.m_clrBkgndBorder);

	pBr = pDC->SelectObject(&br);
	pPen = pDC->SelectObject(&pen);
	pDC->Rectangle(&r);

	if(prefs.m_bShowGrid)
	{
		CPen penGrid(PS_SOLID,1,prefs.m_clrGrid);

		int xend,xstart;
		int yend,ystart;

		int rows = GetDocument()->GetNumberOfRows();
		int cols = GetDocument()->GetNumberOfCols();

		xstart = m_width;
		ystart = m_height;
		yend = rows * m_height;
		xend = cols * m_width;

		pDC->SelectObject(penGrid);

		do
		{
			pDC->MoveTo(xstart,m_height);
			pDC->LineTo(xstart,yend);
			xstart += m_width;
		} while(xstart <= xend);

		xstart = 0;

		do
		{
			pDC->MoveTo(m_width,ystart);
			pDC->LineTo(xend,ystart);
			ystart += m_height;
		} while(ystart <= yend);

		pDC->SelectObject(pPen);

	}
	
	pDC->SelectObject(pBr);
	pDC->SelectObject(pPen);

}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView printing

BOOL CCrossSumsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCrossSumsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCrossSumsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView diagnostics

#ifdef _DEBUG
void CCrossSumsView::AssertValid() const
{
	CView::AssertValid();
}

void CCrossSumsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCrossSumsDoc* CCrossSumsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCrossSumsDoc)));
	return (CCrossSumsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsView message handlers

void CCrossSumsView::OnInitialUpdate() 
{
	InitFonts();
	CalculateCellSize();
	InitializeCellWnd();
	ReSizeFrame();
	if(prefs.m_bShowHelpers && options.level != LVL_ADV)
		ShowStarterCells();

	GetDocument()->StartPuzzleTime();

	CView::OnInitialUpdate();
}

void CCrossSumsView::OnDestroy() 
{
	CView::OnDestroy();

	RemoveCellWnd();

	m_paSum.RemoveAll();
	m_paNum.RemoveAll();

}


void CCrossSumsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_bDrag = TRUE;

	CWnd *pWnd = ChildWindowFromPoint(point,CWP_ALL);
	if(pWnd!=NULL && pWnd!=this)
	{
		if(m_pFocusWnd)
			m_pFocusWnd->SendMessage(WM_KILLFOCUS);
		pWnd->SendMessage(WM_SETFOCUS,0,0);
		m_pFocusWnd = pWnd;
		return;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CCrossSumsView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnChar(nChar, nRepCnt, nFlags);
	switch(nChar)
	{
	case 8:  //VK_BACK_SPACE:
		HandleCharInput(48);
		HandleMoveFocus(-1,0, NEXT_CELL);
		break;

	case VK_SPACE:
		nChar = 48;
	case '1': //VK_1:
	case '2': //VK_2:
	case '3': //VK_3:
	case '4': //VK_4:
	case '5': //VK_5:
	case '6': //VK_6:
	case '7': //VK_7:
	case '8': //VK_8:
	case '9': //VK_9:
		HandleCharInput(nChar);
		HandleMoveFocus(+1,0,NEXT_CELL);
		break;

	case '!': // <SHIFT>1
		HandleCellListInput(1);
		break;
	case '@': // <SHIFT>2
		HandleCellListInput(2);
		break;
	case '#': // <SHIFT>3
		HandleCellListInput(3);
		break;
	case '$': // <SHIFT>4
		HandleCellListInput(4);
		break;
	case '%': // <SHIFT>5
		HandleCellListInput(5);
		break;
	case '^': // <SHIFT>6
		HandleCellListInput(6);
		break;
	case '&': // <SHIFT>7
		HandleCellListInput(7);
		break;
	case '*': // <SHIFT>8
		HandleCellListInput(8);
		break;
	case '(': // <SHIFT>9
		HandleCellListInput(9);
		break;
	default:
		break;
	}
}

void CCrossSumsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch(nChar)
	{
	//case VK_HOME:
	//case VK_END:
	//case 13: //VK_ENTER:
	case 33: //VK_PAGE_UP:
		HandleMoveFocus(0, -1, NEXT_SUM);
		break;
	case 34: //VK_PAGE_DOWN:
		HandleMoveFocus(0, 1, NEXT_SUM);
		break;
	case VK_TAB:
		HandleMoveFocus(1, 0, NEXT_SUM);
		break;
	
	case VK_LEFT:
		HandleMoveFocus(-1, 0, NEXT_CELL);
		break;
	case VK_RIGHT:
		HandleMoveFocus(1, 0, NEXT_CELL);
		break;
	case VK_UP:
		HandleMoveFocus(0,-1, NEXT_CELL);
		break;
	case VK_DOWN:
		HandleMoveFocus(0, 1, NEXT_CELL);
		break;
	case VK_DELETE:
		nChar = 48;
		HandleCharInput(nChar);
		break;

	}

}

void CCrossSumsView::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetDocument()->ReadOnly() && GetDocument()->IsModified()); // CDocument	
}

void CCrossSumsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CCrossSumsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	SCELL *pCell;
	CWnd *p;

	if(lHint == 1)
	{
		m_pFocusWnd = NULL;
		RemoveCellWnd();
		InitFonts();
		CalculateCellSize();
		InitializeCellWnd();
		ReSizeFrame();
	}

	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();

	for(int r=0;r<rows;r++)
	{
		for(int c=0;c<cols;c++)
		{
			pCell = GetDocument()->GetCell(r,c);
			if(pCell->type == NUMBER || pCell->type == SUM)
			{
				p = GetCellWnd(r,c);
				ASSERT(p);

				if(pCell->type==SUM) 
				{
					p->SendMessage(WM_SETCELLDATA,
									CELL_VALUE,
									(LPARAM)MAKELONG((WORD)pCell->sum.h,
													(WORD)pCell->sum.v));
				}
				else if(pCell->type==NUMBER)
				{
					p->SendMessage(WM_SETCELLDATA,
									CELL_VALUE,
									(LPARAM)MAKELONG((WORD)pCell->value.user,
													(WORD)pCell->value.actual));
					p->SendMessage(WM_SETCELLDATA,
									CELL_LIST,
									(LPARAM)pCell->list);
				}				
			}
		}
	}

	Invalidate();
	UpdateWindow();

}

void CCrossSumsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);
}

void CCrossSumsView::OnPuzzleShowstarterhelp() 
{
	ShowStarterCells();
}

void CCrossSumsView::OnUpdatePuzzleShowstarterhelp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bStarterHelpAvailable);
}
