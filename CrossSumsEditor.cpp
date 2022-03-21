// CrossSumsEditor.cpp : implementation file
//

#include "stdafx.h"
#include "CrossSums.h"
#include "CrossSumsDoc.h"
#include "CrossSumsView.h"
#include "CrossSumsEditor.h"

#include "CellWnd.h"
#include "Dlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;
extern PREFS   prefs;

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditor

IMPLEMENT_DYNCREATE(CCrossSumsEditor, CCrossSumsView)

CCrossSumsEditor::CCrossSumsEditor()
	: CCrossSumsView()
{
	m_focusRect.SetRectEmpty();
	m_bSelectMode = FALSE;
}

CCrossSumsEditor::~CCrossSumsEditor()
{
}


BEGIN_MESSAGE_MAP(CCrossSumsEditor, CCrossSumsView)
	//{{AFX_MSG_MAP(CCrossSumsEditor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_PUZZLE_SYMMETRY_OFF, OnPuzzleSymmetryOff)
	ON_UPDATE_COMMAND_UI(ID_PUZZLE_SYMMETRY_OFF, OnUpdatePuzzleSymmetryOff)
	ON_COMMAND(ID_PUZZLE_SYMMETRY_SIDESIDE, OnPuzzleSymmetrySideside)
	ON_UPDATE_COMMAND_UI(ID_PUZZLE_SYMMETRY_SIDESIDE, OnUpdatePuzzleSymmetrySideside)
	ON_COMMAND(ID_PUZZLE_SYMMETRY_TOPBOTTOM, OnPuzzleSymmetryTopbottom)
	ON_UPDATE_COMMAND_UI(ID_PUZZLE_SYMMETRY_TOPBOTTOM, OnUpdatePuzzleSymmetryTopbottom)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_PUZZLE_SELECTSTARTINGHELPBOXES, OnPuzzleSelectstartinghelpboxes)
	ON_MESSAGE(WM_SELECTING, OnSelectingHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCrossSumsEditor::CellRectFromRC(CRect *pRect, int row, int col)
{
	pRect->left = col * m_width;
	pRect->right = (col+1)*m_width;
	pRect->top = row * m_height;
	pRect->bottom = (row+1)*m_height;
}

void CCrossSumsEditor::CellRectFromPoint(CRect *pRect, CPoint point)
{
	int c = (int)(point.x / m_width);
	int r = (int)(point.y / m_height);
	CellRectFromRC(pRect,r,c);
}

CWnd *CCrossSumsEditor::CreateCellWnd(int r, int c)
{
	CRect rect;
	int cols = GetDocument()->GetNumberOfCols();
	int rows = GetDocument()->GetNumberOfRows();

	if(c<1 || r<1 || c>=cols || r>=rows)
		return NULL;

	SCELL *pCell = GetDocument()->GetCell(r,c);
	if(pCell && pCell->type == NUMBER)
		return NULL;

	// bug -->
	// if pcell type == sum, then we need to delete the sum cell
	// to replace it with a number cell...

	CellRectFromRC(&rect,r,c);

	CNumberWnd *p = new CNumberWnd(this,rect,&m_fontNumber,&m_fontList);
	m_paNum.Add(p);
	p->SendMessage(WM_SETCELLDATA,
					CELL_ROWCOL,
					(LPARAM)MAKELONG((WORD)r,(WORD)c));

	GetDocument()->UpdateCellData(r,c,NUMBER,0);

	return p;

}

CWnd *CCrossSumsEditor::CreateCellWndFromPoint(CPoint point)
{
	int c = (int)(point.x / m_width);
	int r = (int)(point.y / m_height);

	CWnd *p = CreateCellWnd(r,c);
	if(p && !m_bDrag)
	{
		int rows = GetDocument()->GetNumberOfRows();
		int cols = GetDocument()->GetNumberOfCols();

		if(options.top_bottom)
		{
			int rr = rows - r;
			int cc = cols - c;
			CreateCellWnd(rr,cc);
		}

		if(options.side_side)
		{
			int cc = cols - c;
			CreateCellWnd(r,cc);
		}

		if(options.side_side && options.top_bottom)
		{
			int rr = rows - r;
			CreateCellWnd(rr,c);
		}
	}

	return p;
}

void CCrossSumsEditor::HandleCharInput(UINT nChar)
{
	CCrossSumsView::HandleCharInput(nChar);

	if(m_pFocusWnd)
	{
		long l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_ROWCOL);
		int row = LOWORD(l);
		int col = HIWORD(l);

		long lval = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_VALUE);
		int val = LOWORD(lval); 
		lval = MAKELONG((WORD)val,(WORD)val);
		m_pFocusWnd->SendMessage(WM_SETCELLDATA,(WPARAM)CELL_VALUE,(LPARAM)(MAKELONG((WORD)val,(WORD)val)));

		GetDocument()->UpdateCellData(row,col,NUMBER,lval);
	}

}

void CCrossSumsEditor::DropCell(CPoint point)
{
	// we should be dragging around the focus window
	ASSERT(m_pFocusWnd);

	// get the current location of the drag window to find row,col coord.
	CRect rect;
	m_pFocusWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);

	// new row,col for this cell based on current window rect
	int newcol = (int)(rect.CenterPoint().x / m_width);
	int newrow = (int)(rect.CenterPoint().y / m_height);

	int l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,CELL_ROWCOL);
	int oldrow = LOWORD(l);
	int oldcol = HIWORD(l);

	// if we've actually moved the cell to a new location...
	if(newrow!=oldrow || newcol!=oldcol)
	{
		int rows = GetDocument()->GetNumberOfRows();
		int cols = GetDocument()->GetNumberOfCols();

		SCELL *pCell = GetDocument()->GetCell(newrow,newcol);

		// we cannot drop in the 0th row, 0th col, or on a current number cell...
		if( (newcol < 1 || newrow < 1 || newcol>=cols || newrow >= rows) ||
			(pCell && pCell->type == NUMBER))
		{
			AfxMessageBox(IDS_DROPFAILED,MB_OK);
			m_pFocusWnd->MoveWindow(m_origRect);
			InvalidateRect(m_origRect);
			UpdateWindow();
			return;
		}

		// update the windows to report new row and new col
		int lval = m_pFocusWnd->SendMessage(WM_GETCELLDATA,CELL_VALUE);
		m_pFocusWnd->SendMessage(WM_SETCELLDATA,CELL_ROWCOL,MAKELONG((WORD)newrow,(WORD)newcol));
		
		// update the document
		GetDocument()->UpdateCellData(oldrow,oldcol,BLANK,0);
		GetDocument()->UpdateCellData(newrow,newcol,NUMBER,lval);
		
		InvalidateRect(m_focusRect);
		UpdateWindow();
	}
}

void CCrossSumsEditor::HandleStarterCell(CWnd *pWnd)
{
	ASSERT(pWnd);

	long l = pWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_STARTER);
	l = (l==1)?0:1;
	pWnd->SendMessage(WM_SETCELLDATA,(WPARAM)CELL_STARTER,l);
	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
}

void CCrossSumsEditor::SetStarterCells()
{
	SCELL *pCell;

	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();

	for(int r=1; r<rows; r++)
	{
		for(int c=1; c<cols; c++)
		{
			pCell = GetDocument()->GetCell(r,c);
			ASSERT(pCell);
			if(pCell->type == NUMBER)
			{
				CWnd *pWnd = GetCellWnd(r,c);
				if(pWnd)
					pWnd->SendMessage(WM_SETCELLDATA,CELL_STARTER,(LPARAM)pCell->starter);
			}
		}

	}

//	Invalidate();
//	UpdateWindow();
}

void CCrossSumsEditor::SaveStarterCells()
{
	CWnd *pWnd;
//	SCELL *pCell;

	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();

	for(int r=1; r<rows; r++)
	{
		for(int c=1; c<cols; c++)
		{
			pWnd = GetCellWnd(r,c);
			if(pWnd)
			{
				long l = pWnd->SendMessage(WM_GETCELLDATA,CELL_STARTER);
				GetDocument()->SetCellStarter(r,c,(int)l);
			}
		}

	}

}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditor drawing

void CCrossSumsEditor::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT(pDoc);
	CRect r;
	GetClientRect(&r);

	CBrush *pBr = NULL;
	CPen *pPen = NULL;

	CBrush br(prefs.m_clrBkgnd);
	CPen pen(PS_SOLID,1,prefs.m_clrBkgndBorder);

	pBr = pDC->SelectObject(&br);
	pPen = pDC->SelectObject(&pen);
	pDC->Rectangle(&r);

	int xend,xstart;
	int yend,ystart;

	int rows = GetDocument()->GetNumberOfRows();
	int cols = GetDocument()->GetNumberOfCols();

	xstart = m_width;
	ystart = m_height;
	yend = rows * m_height;
	xend = cols * m_width;


	CPen penGrid(PS_SOLID,1,prefs.m_clrGrid);
	if(prefs.m_clrGrid != prefs.m_clrBkgnd)
		pDC->SelectObject((CPen*)&penGrid);
	else
		pDC->SelectStockObject(WHITE_PEN);

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

	if(pBr)  pDC->SelectObject(pBr);
	if(pPen) pDC->SelectObject(pPen);
		
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditor diagnostics

#ifdef _DEBUG
void CCrossSumsEditor::AssertValid() const
{
	CCrossSumsView::AssertValid();
}

void CCrossSumsEditor::Dump(CDumpContext& dc) const
{
	CCrossSumsView::Dump(dc);
}

CCrossSumsDoc* CCrossSumsEditor::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCrossSumsDoc)));
	return (CCrossSumsDoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditor message handlers

void CCrossSumsEditor::OnInitialUpdate() 
{
	CCrossSumsView::OnInitialUpdate();
//	SetStarterCells();	
//	Invalidate();
//	UpdateWindow();

	// TODO: Add your specialized code here and/or call the base class
	
}

void CCrossSumsEditor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CWnd *pWnd = ChildWindowFromPoint(point,CWP_ALL);

	if(m_bSelectMode)
	{
		if(pWnd!=this && pWnd!=NULL)
			HandleStarterCell(pWnd);
		return;
	}


	if(pWnd==this)
	{
		CRect rect;
		CellRectFromPoint(&rect, point);
		CNumberWnd *p = (CNumberWnd *)CreateCellWndFromPoint(point);
		if(p)
		{
			SetCapture();
			if(m_pFocusWnd)
				m_pFocusWnd->SendMessage(WM_KILLFOCUS);
			m_focusRect = rect;
			InvalidateRect(m_focusRect);
			UpdateWindow();
		}
	}
	else
	{
		// we've clicked on an active cell... prepare to drag it around
		CCrossSumsView::OnLButtonDown(nFlags, point);
		if(m_pFocusWnd)
		{
			m_bDrag = TRUE;
			SetCapture();
			CRect rect;
			CellRectFromPoint(&rect, point);
			m_focusRect = rect;
			m_origRect = rect;
		}
	}
}

void CCrossSumsEditor::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bSelectMode)
		return;

	if(GetCapture()==this)
		ReleaseCapture();

	if(m_bDrag)
	{
		DropCell(point);
		m_origRect.SetRectEmpty();
		m_bDrag = FALSE;
		return;
	}

	CWnd *pWnd = ChildWindowFromPoint(point,CWP_ALL);

	if(pWnd==this)
	{
		if(m_focusRect.PtInRect(point))
		{
			CNumberWnd *p = (CNumberWnd *)CreateCellWndFromPoint(point);
			if(p)
			{
				if(m_pFocusWnd)
					m_pFocusWnd->SendMessage(WM_KILLFOCUS);
				m_pFocusWnd = p;
				p->SendMessage(WM_SETFOCUS);
				InvalidateRect(m_focusRect);
				UpdateWindow();
			}
		}
		return;
	}

	CCrossSumsView::OnLButtonUp(nFlags, point);
}


void CCrossSumsEditor::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CView::OnChar(nChar, nRepCnt, nFlags);

	if(m_bSelectMode)
		return;

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
		HandleMoveFocus(+1,0, NEXT_CELL);
		break;

	default:
		break;
	}
}

void CCrossSumsEditor::OnEditCut() 
{
	if(m_pFocusWnd)
	{
		long l = m_pFocusWnd->SendMessage(WM_GETCELLDATA,(WPARAM)CELL_ROWCOL);
		int row = LOWORD(l);
		int col = HIWORD(l);
		GetDocument()->UpdateCellData(row,col,BLANK,0);
		RemoveCellWnd(m_pFocusWnd);
		m_pFocusWnd = NULL;
	}
}

void CCrossSumsEditor::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pFocusWnd!=NULL);
	
}

void CCrossSumsEditor::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CCrossSumsView::OnUpdate(pSender,lHint,pHint);
	if(lHint==1)
		SetStarterCells();
	
}

void CCrossSumsEditor::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bSelectMode)
		return;

	if(GetCapture()==this)
	{
		// now we moved outside the focus rect
		CWnd *pWnd = ChildWindowFromPoint(point,CWP_ALL);
		if(m_bDrag)
		{
			if(pWnd==this)
			{
				CellRectFromPoint(&m_focusRect, point);
				m_pFocusWnd->MoveWindow(&m_focusRect);
			}
			return;
		}
		
		if(pWnd==this)
		{
			//
			// we've moved on to a blank space
			// so, if we do not have a focus wnd, create new number cells
			//
			if(!m_focusRect.PtInRect(point))
			{
				CNumberWnd *p;
				p = (CNumberWnd*)CreateCellWndFromPoint(point);
				if(p)
				{
					if(m_pFocusWnd)
						m_pFocusWnd->SendMessage(WM_KILLFOCUS);
					m_pFocusWnd = p;
					m_pFocusWnd->SendMessage(WM_SETFOCUS);
				}
			}
		}
	}
	CCrossSumsView::OnMouseMove(nFlags, point);
}

void CCrossSumsEditor::OnDestroy() 
{
	// close out the editor...
	GetDocument()->ToggleView();
	CCrossSumsView::OnDestroy();
}

void CCrossSumsEditor::OnPuzzleSymmetryOff() 
{
	options.side_side = 0;
	options.top_bottom = 0;
}

void CCrossSumsEditor::OnUpdatePuzzleSymmetryOff(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(!options.side_side && !options.top_bottom);
}

void CCrossSumsEditor::OnPuzzleSymmetrySideside() 
{
	options.side_side = (options.side_side==1?0:1);
}

void CCrossSumsEditor::OnUpdatePuzzleSymmetrySideside(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(options.side_side);
}

void CCrossSumsEditor::OnPuzzleSymmetryTopbottom() 
{
	options.top_bottom = (options.top_bottom==1?0:1);
}

void CCrossSumsEditor::OnUpdatePuzzleSymmetryTopbottom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(options.top_bottom);
}

void CCrossSumsEditor::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->IsModified());
	
}

void CCrossSumsEditor::OnPuzzleSelectstartinghelpboxes() 
{
	CSelectHelpersDlg *pdlg = new CSelectHelpersDlg(this); // Modeless Dialog Boxes	
	pdlg->m_bAlwaysShow = GetDocument()->GetShowHelpersFlag();
	pdlg->UpdateData(FALSE);
}

long CCrossSumsEditor::OnSelectingHelp(WPARAM wParam, LPARAM lParam)
{
	if(wParam == 0) // starting selection
	{
		if(m_pFocusWnd)
		{
			m_pFocusWnd->SendMessage(WM_KILLFOCUS);
			m_pFocusWnd = NULL;
		}
		m_bSelectMode = TRUE;
	}

	if(wParam==IDCANCEL)
	{
		m_bSelectMode = FALSE;
		SetStarterCells();
		Invalidate();
		UpdateWindow();
	}

	if(wParam==IDOK)
	{
		m_bSelectMode = FALSE;
		SaveStarterCells();
	}

	if(wParam==IDC_CHECK1)
	{
		GetDocument()->SetShowHelpersFlag((BOOL)lParam);
	}

	return 0L;

}