// CrossSumsEditDoc.cpp : implementation file
//

#include "stdafx.h"
#include "CrossSums.h"
#include "CrossSumsDoc.h"
#include "CrossSumsEditDoc.h"

#include "Dlgs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditDoc

IMPLEMENT_DYNCREATE(CCrossSumsEditDoc, CCrossSumsDoc)

CCrossSumsEditDoc::CCrossSumsEditDoc()
	: CCrossSumsDoc()
{
}

BOOL CCrossSumsEditDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CNewCrossSumDlg dlg;

	dlg.m_cols = options.cols;
	dlg.m_rows = options.rows;
	dlg.m_level = options.level;

	if(dlg.DoModal()==IDOK)
	{
		m_rows = dlg.m_rows;
		m_cols = dlg.m_cols;
		m_level = dlg.m_level;
		InitPuzzleEditor();
		options.edit = 1;
		options.user_level = LVL_NORM;
		return TRUE;
	}
	return FALSE;
}

CCrossSumsEditDoc::~CCrossSumsEditDoc()
{
}


BEGIN_MESSAGE_MAP(CCrossSumsEditDoc, CCrossSumsDoc)
	//{{AFX_MSG_MAP(CCrossSumsEditDoc)
	ON_COMMAND(ID_PUZZLE_CALCULATE, OnPuzzleCalculate)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_COMMAND(ID_PUZZLE_NEWVALUES, OnPuzzleNewvalues)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCrossSumsEditDoc::InitPuzzleEditor()
{
	SCELL *p;

	DeleteContents();

	m_cells = new SCELL[ m_rows * m_cols ];

	for(int r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			p = GET_CELL(r,c);
			p->type = BLANK;
			p->row = r;
			p->col = c;
			p->sum.h = -1;
			p->sum.v = -1;
			p->list = 0;
		}
	}
}

BOOL CCrossSumsEditDoc::PublishPuzzle()
{
	int r,c;

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			SCELL *pCell = GET_CELL(r,c);
			if(pCell->type == NUMBER)
				pCell->value.user =0;
		}
	}

	return TRUE;

}

void CCrossSumsEditDoc::UpdateCellData(int row, int col, CELL_TYPE type, long lData)
{
	SCELL *pCell;
	ASSERT(pCell);
	ASSERT(row<m_rows && col<m_cols && row>=0 && col>=0);

	pCell = GET_CELL(row,col);
	pCell->type = type;
	pCell->list = 0;

	if(type==NUMBER)
	{
		pCell->value.actual = HIWORD(lData);
		pCell->value.user = LOWORD(lData);
	}
	else if(type == SUM)
	{
		pCell->sum.h = HIWORD(lData);
		pCell->sum.v = LOWORD(lData);
	}
	else if(type == BLANK)
	{
		pCell->sum.h = -1;
		pCell->sum.v = -1;
	}

	SetModifiedFlag();
}

void CCrossSumsEditDoc::ValidateCells()
{
	SCELL *pCell;

	int r,c;

	for(r=0;r<m_rows-1;r++)
	{
		for(c=0;c<m_cols-1;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type == SUM)
			{
				SCELL *p = GET_CELL(r+1,c);
				if(p->type!=NUMBER)
				{
					pCell->type = BLANK;
					pCell->sum.h = -1;
					pCell->sum.v = -1;
				}
				p = GET_CELL(r,c+1);
				if(p->type!=NUMBER)
				{
					pCell->type = BLANK;
					pCell->sum.h = -1;
					pCell->sum.v = -1;
				}
			}
		}
	}


	for(r=1;r<m_rows;r++)
	{
		for(c=1;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type == NUMBER)
			{
				SCELL *p = GET_CELL(r-1,c);
				if(p->type==BLANK)
				{
					p->type = SUM;
					p->sum.h = 0;
					p->sum.v = 0;
				}
				p = GET_CELL(r,c-1);
				if(p->type==BLANK)
				{
					p->type = SUM;
					p->sum.h = 0;
					p->sum.v = 0;
				}
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditDoc diagnostics

#ifdef _DEBUG
void CCrossSumsEditDoc::AssertValid() const
{
	CCrossSumsDoc::AssertValid();
}

void CCrossSumsEditDoc::Dump(CDumpContext& dc) const
{
	CCrossSumsDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditDoc serialization

void CCrossSumsEditDoc::Serialize(CArchive& ar)
{
	CCrossSumsDoc::Serialize(ar);

	if (ar.IsStoring())
	{

	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditDoc commands

BOOL CCrossSumsEditDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(!PublishPuzzle())
	{
		AfxMessageBox(IDS_PUBLISHFAILED,MB_OK);
		return FALSE;
	}

	if(CCrossSumsDoc::OnSaveDocument(lpszPathName))
	{
		OnPuzzleSolution();
		UpdateAllViews(NULL,1);
		return TRUE;
	}

	return FALSE;
}

void CCrossSumsEditDoc::OnPuzzleCalculate() 
{
	ValidateCells();
	GenerateSums();
	OnPuzzleSolution();
	UpdateAllViews(NULL,1);
	SetModifiedFlag();
}

BOOL CCrossSumsEditDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CCrossSumsDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	if(m_bReadOnly)
		AfxMessageBox(IDS_READONLY,MB_OK);

	return TRUE;
}

void CCrossSumsEditDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bReadOnly);	
}

void CCrossSumsEditDoc::OnPuzzleNewvalues() 
{
	if(!GenerateNumbers())
	{
		ValidateCells();
		GenerateSums();
		OnPuzzleSolution();
		UpdateAllViews(NULL,1);
		SetModifiedFlag();
	}
	
}
