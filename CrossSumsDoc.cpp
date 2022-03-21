// CrossSumsDoc.cpp : implementation of the CCrossSumsDoc class
//

#include "stdafx.h"
#include "CrossSums.h"
#include "Dlgs.h"
#include "PrefsColor.h"
#include "PrefsFonts.h"

#include "CrossSumsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern OPTIONS options;
extern PREFS   prefs;

int DEBUG_CELL_INFO[15][15] = {
	{   -1, 1300, 2800,  600, 3800,  900,   -1, 1300, 1800,   -1, 2000,  300,   -1,   -1, -1 },
	{   34,    0,    0,    0,    0,    0,   16,    0,    0,   10,    0,    0, 2100, 1400, -1 },
	{   15,    0,    0,    0,    0,    0,    5,    0,    0, 1611,    0,    0,    0,    0, -1 },
	{    8,    0,    0,  505,    0,    0,  400, 4224,    0,    0,    0,   11,    0,    0, -1 },
	{   21,    0,    0,    0,    0,   10,    0,    0,    0,    0, 1200,   17,    0,    0, -1 },
	{   -1, 1000, 1907,    0,    0, 1206,    0,    0,  917,    0,    0,  400, 2100, 1000, -1 },
	{    7,    0,    0,  914,    0,    0,  317,    0,    0, 1110,    0,    0,    0,    0, -1 },
	{   24,    0,    0,    0, 1618,    0,    0,    0,    0,    0, 2219,    0,    0,    0, -1 },
	{   14,    0,    0,    0,    0, 1607,    0,    0, 1410,    0,    0, 1209,    0,    0, -1 },
	{   -1, 2100,  900,   17,    0,    0, 2316,    0,    0,   14,    0,    0, 2800, 1100, -1 },
	{    9,    0,    0,   -1, 1029,    0,    0,    0,    0,  913,    0,    0,    0,    0, -1 },
	{    8,    0,    0, 1507,    0,    0,    0,  500,    5,    0,    0, 1409,    0,    0, -1 },
	{   29,    0,    0,    0,    0,    4,    0,    0,   16,    0,    0,    0,    0,    0, -1 },
	{   -1,   -1,    7,    0,    0,   11,    0,    0,   35,    0,    0,    0,    0,    0, -1 },
	{   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, -1 },
};

PREFS CCrossSumsDoc::defaultPrefs =
{
	0,			//		 m_bShowGrid;
	0,			// m_bShowSelectHelpers
	0x0,		// m_clrBkgnd;
	0x00ffffff,	// m_clrCells;
	0x0,		// m_clrText;
	-1,			// m_clrFlash;
	-1,			// m_clrHilite;
	0x000000ff,	// m_clrWrong;
	0x0,		// m_clrBkgndBorder;
	0x0,		// m_clrCellBorder;
	0x0,		// m_clrSumBorder;
	0x00ffffff,	// m_clrGrid;
	0x00ffffff,	// m_clrSum;
	140,		// m_nTextSize;
	80,			// m_nSumSize;
	80,			// m_nListSize;
	"Comic Sans Serif", //	 m_szTextFontName[32];
	"Times New Roman"	//	 m_szSumFontName[32];
};

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsDoc

IMPLEMENT_DYNCREATE(CCrossSumsDoc, CDocument)

BEGIN_MESSAGE_MAP(CCrossSumsDoc, CDocument)
	//{{AFX_MSG_MAP(CCrossSumsDoc)
	ON_COMMAND(ID_PUZZLE_OPTIONS, OnPuzzleOptions)
	ON_COMMAND(ID_PUZZLE_PREFERENCES, OnPuzzlePreferences)
	ON_COMMAND(ID_PUZZLE_NEWVALUES, OnPuzzleNewvalues)
	ON_COMMAND(ID_PUZZLE_SOLUTION, OnPuzzleSolution)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PUZZLE, OnUpdateEditPuzzle)
	ON_COMMAND(ID_PUZZLE_CALCULATE, OnPuzzleCalculate)
	ON_COMMAND(ID_PUZZLE_TIMEDPUZZLE, OnPuzzleTimedpuzzle)
	ON_UPDATE_COMMAND_UI(ID_PUZZLE_TIMEDPUZZLE, OnUpdatePuzzleTimedpuzzle)
	ON_COMMAND(ID_PUZZLE_RESETPUZZLE, OnPuzzleResetpuzzle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CCrossSumsDoc::SetShowHelpersFlag(BOOL bShow)
{
	prefs.m_bShowHelpers = bShow;
}

BOOL CCrossSumsDoc::GetShowHelpersFlag()
{
	return prefs.m_bShowHelpers;
}

void CCrossSumsDoc::InitializeFromArray(int rows, int cols, int *pcells)
{
	ASSERT(m_cells);
	ASSERT(rows>0 && cols>0);
	
	int r = 0;
	int c = 0;

	SCELL *cell = m_cells;

	do
	{
		do
		{
			if(*pcells == -1)
			{
				cell[r * cols + c].row = r;
				cell[r * cols + c].col = c;
				cell[r * cols + c].starter = 0;
				cell[r * cols + c].type = BLANK;
				cell[r * cols + c].sum.h = -1;
				cell[r * cols + c].sum.v = -1;
				cell[r * cols + c].list = NO_NUMBERS;
			}
			else if(*pcells == 0)
			{
				cell[r * cols + c].row = r;
				cell[r * cols + c].col = c;
				cell[r * cols + c].starter = 0;
				cell[r * cols + c].type = NUMBER;
				cell[r * cols + c].value.actual = 0;
				cell[r * cols + c].value.user = 0;
				cell[r * cols + c].list = NO_NUMBERS;
			}
			else
			{
				int hsum = 0;
				int vsum = 0;
				vsum = (int)(*pcells/100);
				hsum = (int)(*pcells) - (vsum*100);
				cell[r * cols + c].row = r;
				cell[r * cols + c].col = c;
				cell[r * cols + c].starter = 0;
				cell[r * cols + c].type = SUM;
				cell[r * cols + c].sum.h = hsum;
				cell[r * cols + c].sum.v = vsum;
				cell[r * cols + c].list = NO_NUMBERS;
			}
			pcells++;
		} while(++c < cols);
		c = 0;
	}
	while(++r < rows);
}

int CCrossSumsDoc::FindVActualSum(int row, int col)
{
	ASSERT(m_cells);

	int sum = 0;
	int r = row;
	int c = col;

	SCELL *pcell = GET_CELL(r,c);

	ASSERT(pcell->type!=BLANK);

	// if we are on the column sum and it is valid, return it
	if(pcell->type==SUM && pcell->sum.v>0 )
		return pcell->sum.v;

	// else, find the column sum cell since we are on a number cell
	while(r>=0 && pcell->type!=SUM)
	{
		r--;
		pcell = GET_CELL(r,c);
	}
	
	// hmm... we have reached the border, and did not find a sum cell
	if(r<0)
		return 0;
	
	// ok, we are on the column sum cell
	ASSERT(pcell->type==SUM);
	sum = pcell->sum.v;

	// if it is *not* valid, calculate sum from actual (solution) values
	if(sum <= 0)
	{
		// reset the row and column to start calcuating
		r = row;
		c = col;
		sum = 0;

		while(r>=0 && pcell->type==NUMBER)
		{
			sum += pcell->value.actual;
			r--;
			pcell = GET_CELL(r,c);
		}

		r = row+1;
		pcell= GET_CELL(r,c);

		while(r<m_rows && pcell->type==NUMBER)
		{
			sum += pcell->value.actual;
			r++;
			pcell = GET_CELL(r,c);
		}
	}

	return sum;

}

int CCrossSumsDoc::FindHActualSum(int row, int col)
{
	ASSERT(m_cells);

	int sum = 0;
	int r = row;
	int c = col;

	SCELL *pcell = GET_CELL(r,c);

	ASSERT(pcell->type!=BLANK);

	if(pcell->type==SUM && pcell->sum.h>0)
		return pcell->sum.h;

	while(c>=0 && pcell->type!=SUM)
	{
		c--;
		pcell = GET_CELL(r,c);
	}

	if(c<0)
		return 0;

	ASSERT(pcell->type==SUM);
	sum = pcell->sum.h;
	if(sum<=0)
	{
		r = row;
		c = col;
		sum = 0;

		while(c>=0 && pcell->type==NUMBER)
		{
			sum += pcell->value.actual;
			c--;
			pcell = GET_CELL(r,c);
		}

		c = col+1;
		pcell= GET_CELL(r,c);

		while(c<m_cols && pcell->type==NUMBER)
		{
			sum += pcell->value.actual;
			c++;
			pcell = GET_CELL(r,c);
		}
	}

	return sum;

}

int CCrossSumsDoc::FindVUserSum(int row, int col)
{
	ASSERT(m_cells);

	int sum = 0;
	int r = row;
	int c = col;

	SCELL *pcell = GET_CELL(r,c);

	ASSERT(pcell->type!=BLANK);

	if(pcell->type==SUM)
		return pcell->sum.v;

	while(r>=0 && pcell->type==NUMBER)
	{
		sum += pcell->value.user;
		r--;
		pcell = GET_CELL(r,c);
	}

	r = row+1;
	pcell= GET_CELL(r,c);

	while(r<m_rows && pcell->type==NUMBER)
	{
		sum += pcell->value.user;
		r++;
		pcell = GET_CELL(r,c);
	}

	return sum;

}

int CCrossSumsDoc::FindHUserSum(int row, int col)
{
	ASSERT(m_cells);

	int sum = 0;
	int r = row;
	int c = col;

	SCELL *pcell = GET_CELL(r,c);

	ASSERT(pcell->type!=BLANK);

	if(pcell->type==SUM)
		return pcell->sum.h;

	while(c>=0 && pcell->type==NUMBER)
	{
		sum += pcell->value.user;
		c--;
		pcell = GET_CELL(r,c);
	}

	c = col+1;
	pcell= GET_CELL(r,c);

	while(c<m_cols && pcell->type==NUMBER)
	{
		sum += pcell->value.user;
		c++;
		pcell = GET_CELL(r,c);
	}

	return sum;

}

NUMBERLIST CCrossSumsDoc::ToggleCellListNumber(int row, int col, int nVal)
{
	SCELL *pCell = GET_CELL(row,col);
	ASSERT(pCell);
	ASSERT(pCell->type==NUMBER);
	if(IS_NUMBER_LISTED(nVal,pCell->list))
		DROP_NUMBER(nVal,pCell->list)
	else
		ADD_NUMBER(nVal,pCell->list);
	SetModifiedFlag();
	return pCell->list;
}

int CCrossSumsDoc::FindLegalValues(int row, int col, NUMBERLIST &list)
{
	int start_row = row;
	int start_col = col;

	NUMBERLIST l = ALL_NUMBERS;
	SCELL *pcell = GET_CELL(row,col);

	while(row>=0 && pcell->type == NUMBER)
	{
		DROP_NUMBER(pcell->value.user,l);
		row--;
		pcell = GET_CELL(row,col);
	}

	row = start_row + 1;
	pcell = GET_CELL(row,col);
	while(row<m_rows && pcell->type==NUMBER)
	{
		DROP_NUMBER(pcell->value.user,l);
		row++;
		pcell = GET_CELL(row,col);
	}

	row = start_row;
	col = start_col-1;
	pcell = GET_CELL(row,col);
	while(col>=0 && pcell->type==NUMBER)
	{
		DROP_NUMBER(pcell->value.user,l);
		col--;
		pcell = GET_CELL(row,col);
	}

	col = start_col+1;
	pcell = GET_CELL(row,col);
	while(col<m_cols && pcell->type==NUMBER)
	{
		DROP_NUMBER(pcell->value.user,l);
		col--;
		pcell = GET_CELL(row,col);
	}

	list = l;
	return 0;

}

int CCrossSumsDoc::FindPossibleValues(int row, int col, NUMBERLIST &list)
{
	NUMBERLIST l = NO_NUMBERS;

	if(!FindLegalValues(row,col,l))
	{
		int hsum_a = FindHActualSum(row,col);
		int vsum_a = FindVActualSum(row,col);
		int hsum_u = FindHUserSum(row,col);
		int vsum_u = FindVUserSum(row,col);

		if(hsum_a==0 || vsum_a == 0)
		{
			list = l;
			return 0;
		}

		if(hsum_u >= hsum_a || vsum_u >= vsum_a)
			l = NO_NUMBERS;
		else
		{
			for(int i=1;i<=9;i++)
			{
				if(!IS_NUMBER_LISTED(i,l) || 
					(hsum_u + i > hsum_a) ||
					(vsum_u + i > vsum_a))
					DROP_NUMBER(i,l);
			}
		}

		list = l;
		return 0;
	}

	return 1;

}

SCELL *CCrossSumsDoc::FindAdjacentCell(int &row, int &col, int h, int v, UINT uFlags)
{
	int r = row;
	int c = col;

	SCELL *pCell = GET_CELL(r,c);
	if(!pCell)
		return NULL;

	if(uFlags == NEXT_CELL)
	{
		r+=v; c+=h;
		if(c>=m_cols || c<0 ||
		   r>=m_rows || r<0)
		   return NULL;
	}
	else if(uFlags == NEXT_SUM)
	{
		while(c<m_cols && c>=0 &&
				r<m_rows && r>=0 &&
				pCell->type == NUMBER)
		{
			r+=v; c+=h;
			pCell = GET_CELL(r,c);
		} 

		if(c>=m_cols || c<0 ||
		   r>=m_rows || r<0)
		   return NULL;
		   
		while(c<m_cols && c>=0 &&
			r<m_rows && r>=0 &&
			pCell->type != NUMBER)
		{
			r+=v; c+=h;
			pCell = GET_CELL(r,c);
		}


		if(c>=m_cols || c<0 ||
		   r>=m_rows || r<0)
		   return NULL;

	}
	else if(uFlags == SUM_HOME || uFlags == SUM_END)
	{
		while(c<m_cols && c>=0 &&
				r<m_rows && r>=0 &&
				pCell->type == NUMBER)
		{
			r+=v; c+=h;
			pCell = GET_CELL(r,c);
		} 

		if(c>=m_cols || c<0 ||
		   r>=m_rows || r<0)
		   return NULL;
	}

	pCell = GET_CELL(r,c);
	if(pCell && pCell->type == NUMBER)
	{
		row = r;
		col = c;
	}
	return pCell;
}

int CCrossSumsDoc::SetCellValue(int row, int col, int val)
{
	SCELL *pCell = GET_CELL(row,col);
	ASSERT(pCell);
	ASSERT(pCell->type == NUMBER);
	NUMBERLIST l=NO_NUMBERS;

	int oldval = pCell->value.user;
	pCell->value.user = 0;

	if(val==0)
	{
		pCell->value.user = val;
		SetModifiedFlag();
		return 0;
	}

	if(options.user_level == LVL_BEGIN && !FindPossibleValues(row,col,l) && IS_NUMBER_LISTED(val,l))
	{
		pCell->value.user = val;
		SetModifiedFlag();
		return 0;
	}

	if(options.user_level == LVL_NORM && !FindLegalValues(row,col,l) && IS_NUMBER_LISTED(val,l))
	{
		pCell->value.user = val;
		SetModifiedFlag();
		return 0;
	}

	if(options.user_level == LVL_ADV)
	{
		pCell->value.user = val;
		SetModifiedFlag();
		return 0;
	}

	pCell->value.user = oldval;
	return -1;
}

int CCrossSumsDoc::AutoFill(int row, int col)
{
	int target = 0;
	NUMBERLIST list;

	SCELL *pCell = GET_CELL(row,col);
	ASSERT(pCell);
	
	if(pCell->type != NUMBER)
		return -1;

	if(pCell->value.user==0 && pCell->list!=0)
	{
		//if(!FindPossibleValues(row,col,list))
		if(!FindLegalValues(row,col,list))
		{
			for(int nn=1;nn<=9;nn++)
			{
				if(IS_NUMBER_LISTED(nn,pCell->list) && IS_NUMBER_LISTED(nn,list))
				{
					if(target == 0)
						target = nn;
					else
						return 0;	// could not auto fill this cell
				}
			}

		}

		if(target != 0)
		{
			if(!SetCellValue(row,col,target))
				return target; 
			else
				return 0;// could not auto fill this cell
		}
	}

	return 0;
}

void CCrossSumsDoc::ZeroCells()
{
	ASSERT(m_cells);

	SCELL *pCell;
	for(int r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			pCell->sum.h=0;
			pCell->sum.v=0;
			pCell->list = NO_NUMBERS;
		}

	}
}

int CCrossSumsDoc::GenerateCellNumber(int row, int col)
{
	NUMBERLIST list;
	int num[9] = { 0 };
	int i,count = 0;
	int val;

	int array[NUMBER_OF_VALUES];

	memcpy(array, NUMBER_LEVEL[m_numberlevel], NUMBER_OF_VALUES*sizeof(int));

	if(!FindLegalValues(row,col,list))
	{
		for(i=1;i<=9;i++)
		{
			if(IS_NUMBER_LISTED(i,list))
			{
				num[count] = i;
				count++;
			}
		}

		if(count==0)
			return -1;

		if(count==1)
			return num[0];

		int k = (int)(( ((float)rand()/RAND_MAX)*100.0));
		int kk = array[0];

		val = 0;
		for(i=1;i<=9;i++)
		{
			if(IS_NUMBER_LISTED(i,list))
			{
				if( k <= kk )
				{
					val = i;
					break;
				}
			}
			kk += array[i];
		}

		if(val == 0)
			val = num[0];

		return val;
	}

	return -1;

}

int CCrossSumsDoc::GenerateSums()
{
	SCELL *pCell;

	for(int r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type==SUM)
			{
				pCell->sum.h = -1;	// make sure we re-calculate sums
				pCell->sum.v = -1;	// in case numbers have changed...
				pCell->sum.h = FindHActualSum(r,c);
				pCell->sum.v = FindVActualSum(r,c);
			}
		}
	}

	return 0;
}

int CCrossSumsDoc::GenerateNumbers()
{
	ASSERT(m_cells);

	SCELL *pCell;
	int val;
	int values[10] = { 0,0,0,0,0,0,0,0,0,0 };

	ZeroCells();

	for(int r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type==NUMBER)
			{
				val = GenerateCellNumber(r,c);
				if(val<=0)
				{
					TRACE1("Generate Cell Number returns %d",val);
					return -1;
				}
				pCell->value.user = val;   // temp. set this value since FindLegalValues() uses the user inputs...
				pCell->value.actual = val;
				values[val-1]++;
			}
		}
	}

#ifdef _DEBUG
	for(int kk=0;kk<9;kk++)
	{
		TRACE2("%d: %d\r\n", kk+1, values[kk]);
	}
#endif

	// blank out the user-values that were set
	// with the create-numbers
	for(r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type==NUMBER)
				pCell->value.user = 0;
		}
	}

	return 0;
}

void CCrossSumsDoc::InitPuzzleEditor()
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
			p->starter = 0;
			p->sum.h = -1;
			p->sum.v = -1;
			p->list = 0;
		}
	}
}


void CCrossSumsDoc::ClearUserValues()
{
	SCELL *pCell;
	int r,c;

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			ASSERT(pCell);
			if(pCell->type == NUMBER)
			{
				pCell->value.user = 0;
				pCell->list = 0;
			}
		}
	}
}


BOOL CCrossSumsDoc::PublishPuzzle()
{
	int r,c;

	ValidateCells();

// bug --> fixed 7/19/03 mse
// when publishing, if we have a number cell with value.actual = 0;
// we need to abort, and let the user fill with a number... CPropertPage

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			SCELL *pCell = GET_CELL(r,c);
			if(pCell->type == NUMBER && pCell->value.actual == 0)
			{
				AfxMessageBox(IDS_CELLVALUEZERO,MB_OK);
				return FALSE;
			}
		}
	}


	GenerateSums();
	ClearUserValues();

	return TRUE;

}

void CCrossSumsDoc::SetCellStarter(int row, int col, int nStarter)
{
	SCELL *pCell;
	ASSERT(row<m_rows && col<m_cols && row>=0 && col>=0);

	pCell = GET_CELL(row,col);
	ASSERT(pCell);

	if(pCell->type == NUMBER)
	{
		pCell->starter = nStarter;
		SetModifiedFlag();
	}
}

void CCrossSumsDoc::UpdateCellData(int row, int col, CELL_TYPE type, long lData)
{
	SCELL *pCell;
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

void CCrossSumsDoc::ValidateCells()
{
	SCELL *p,*pCell;

	int r,c;

	// cycle through all the cells and blank any sum cell that does
	// not have a number cell below or to the right of it

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type == SUM)
			{
				if(r<m_rows-1)
				{
					p = GET_CELL(r+1,c);
					if(p->type!=NUMBER)
					{
						pCell->type = BLANK;
						pCell->sum.h = -1;
						pCell->sum.v = -1;
					}
				}

				if(c<m_cols-1)
				{
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
	}

	// cycle through all the cells and add a sum cell immediately before
	// a number cell above or to the left of it (if it was a 'blank' cell)

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type == NUMBER)
			{
				if(r>0)
				{
					SCELL *p = GET_CELL(r-1,c);
					if(p->type==BLANK)
					{
						p->type = SUM;
						p->sum.h = 0;
						p->sum.v = 0;
					}
				}
				
				if(c>0)
				{
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
}


void CCrossSumsDoc::StartPuzzleTime()
{
	time(&m_lGameTime);
}

BOOL CCrossSumsDoc::ResetPuzzleTime(BOOL bWarn)
{
	StopPuzzleTime();

	if(options.timed && bWarn)
	{
		if(AfxMessageBox(IDS_RESETPUZZLETIME, MB_YESNO)==IDNO)
		{
			StartPuzzleTime();
			return FALSE;
		}
	}

	CTimeSpan cts(0);
	m_time = cts;

	StartPuzzleTime();
	return TRUE;
}

void CCrossSumsDoc::StopPuzzleTime()
{
	GetPuzzleTime();
	m_lGameTime = 0;
}

long CCrossSumsDoc::GetPuzzleTime(CTimeSpan *pTSpan)
{
	if(options.timed)
	{
		SetModifiedFlag();
		if(m_lGameTime>0)
		{
			time_t ltime;
			time(&ltime);
			CTimeSpan cts(ltime - m_lGameTime);
			m_time += cts;
			if(pTSpan)
				*pTSpan = m_time;
			time(&m_lGameTime);
		}
		return m_time.GetTotalSeconds();
	}
	return 0L;
	
}

int CCrossSumsDoc::MakeRandomHLength(int max_len)
{
	int len=1;
	double array[10];

	memcpy(array,BOARD_LEVEL[m_boardlevel],NUMBER_OF_LENGTHS*sizeof(double));

	double num = (((float)rand()/RAND_MAX) * 100.0);
	double ff = 0.0;

	int lower_bound = MIN_CROSSSUM_LENGTH;
	int upper_bound = max_len;// - MIN_CROSSSUM_LENGTH;

	len = lower_bound;
	
	int i=0;
	while(i < len)
	{
		ff+=array[i];
		i++;
	}

	while((len < upper_bound) && (num > ff))
	{
		ff += array[len];
		len++;
	}

	return len;
}

int CCrossSumsDoc::MakeRandomVLength(int max_len)
{
	int len=1;
	double array[10];

	memcpy(array,BOARD_LEVEL[m_boardlevel],NUMBER_OF_LENGTHS*sizeof(double));

	double num = (((float)rand()/RAND_MAX) * 100.0);
	double ff = 0.0;

	int lower_bound = MIN_CROSSSUM_LENGTH;
	int upper_bound = max_len;// - MIN_CROSSSUM_LENGTH;

	len = lower_bound;
	
	int i=0;
	while(i < len)
	{
		ff+=array[i];
		i++;
	}

	while((len < upper_bound) && (num > ff))
	{
		ff += array[len];
		len++;
	}

	return len;
}

int CCrossSumsDoc::AssignHLen(int row, int col, SPUZZLECELL **pPuz)
{
	int len = 0;
	int max_valid_len = 0;

	BOOL bHitBlank = FALSE;
	BOOL bBreak = FALSE;

	if( (pPuz[row][col].cell.type == SUM) || 
		(pPuz[row][col].h_len > 1) || 
		(pPuz[row][col].h_len == 0 && pPuz[row][col].v_len == 0) || 
		(pPuz[row][col-1].cell.type == NUMBER))
		return 0;

	for(int i=1;i<=8;i++)
	{
		if(col+i <= (m_cols-1))
		{
			if(pPuz[row][col + i].cell.type == BLANK)
			{
				max_valid_len = i+1;
				bHitBlank = TRUE;
			}
			else if(pPuz[row][col + i].cell.type == NUMBER)
			{
				if(!bHitBlank)
					max_valid_len = i+1;
				else
				{
					if(pPuz[row][col + i + 1].h_len + i <= MAX_CROSSSUM_LENGTH)
					{
						max_valid_len = pPuz[row][col + i + 1].h_len + i;
						break;
					}
				}

			}
			else if(pPuz[row][col + i].cell.type == SUM)
			{
				max_valid_len = i-1;
				break;
			}
		}
	}

	if(max_valid_len<2)
		return 0;

	len = MakeRandomHLength(max_valid_len);

	pPuz[row][col - 1].h_len = len;
	pPuz[row][col - 1].cell.type = SUM;
	pPuz[row][col - 1].cell.sum.h = 0;
	pPuz[row][col - 1].cell.sum.v = 0;

	for(i=0;i<len;i++)
	{
		pPuz[row][col + i].h_len = len;
		pPuz[row][col + i].cell.type = NUMBER;
		pPuz[row][col + i].cell.value.user = 0;
		pPuz[row][col + i].cell.value.actual = 0;
	}

	if(col + len < m_cols)
	{
		pPuz[row][col + len].h_len = 0;
		pPuz[row][col + len].v_len = 0;
	}

	return 0;
}

int CCrossSumsDoc::AssignVLen(int row, int col, SPUZZLECELL **pPuz)
{
	int len = 0;
	int max_valid_len = 0;

	BOOL bHitBlank = FALSE;

	if( (pPuz[row][col].cell.type == SUM) ||
		(pPuz[row][col].h_len < 2) ||
		(pPuz[row][col].v_len > 1) ||
		(pPuz[row][col].h_len == 0 && pPuz[row][col].v_len == 0) ||
		(pPuz[row-1][col].cell.type == NUMBER))
		return 0;

	for(int i=1;i<=8;i++)
	{
		if(row+i <= (m_rows-1))
		{
			if(pPuz[row + i][col].cell.type == BLANK)
			{
				max_valid_len = i+1;
				bHitBlank = TRUE;
			}
			else if(pPuz[row + i][col].cell.type == NUMBER)
			{
				if(!bHitBlank)
					max_valid_len = i+1;
				else
				{
					if(pPuz[row + i + 1][col].v_len + i <= MAX_CROSSSUM_LENGTH)
					{
						max_valid_len = pPuz[row + i + 1][col].v_len + i;
						break;
					}
				}

			}
			else if(pPuz[row + i][col].cell.type == SUM)
			{
				max_valid_len = i-1;
				break;
			}
		}
	}

	if(max_valid_len<2)
		return 0;

	len = MakeRandomVLength(max_valid_len);

	pPuz[row - 1][col].v_len = len;
	pPuz[row - 1][col].cell.type = SUM;
	pPuz[row - 1][col].cell.sum.h = 0;
	pPuz[row - 1][col].cell.sum.v = 0;

	for(i=0;i<len;i++)
	{
		pPuz[row + i][col].v_len = len;
		pPuz[row + i][col].cell.type = NUMBER;
		pPuz[row + i][col].cell.value.user = 0;
		pPuz[row + i][col].cell.value.actual = 0;
	}

	if(row + len < m_rows)
	{
		pPuz[row + len][col].h_len = 0;
		pPuz[row + len][col].v_len = 0;
	}

	return 0;

}

int CCrossSumsDoc::MakePuzzle(SPUZZLECELL **pPuz)
{
	SCELL *pCell;

	if(m_cells)
		DeleteContents();

	m_cells = new SCELL[m_rows * m_cols];

	for(int row=0;row<m_rows;row++)
	{
		for(int col=0;col<m_cols;col++)
		{
			pCell = GET_CELL(row,col);
			pCell->row = row;
			pCell->col = col;
			pCell->starter = 0;
			pCell->type = pPuz[row][col].cell.type;
			pCell->value.actual = 0;
			pCell->value.user = 0;
			pCell->list = 0;
		}
	}

	if(GenerateNumbers())
		return -1;

	GenerateSums();
	SetModifiedFlag();

	return 0;
}

int CCrossSumsDoc::CreateNewPuzzle()
{
	SPUZZLECELL **pPuz;

	int r,c;

	pPuz = new LPTRPUZZLECELL[m_rows];

	for(r=0;r<m_rows;r++)
	{
		pPuz[r] = new SPUZZLECELL[m_cols];
		for(c=0;c<m_cols;c++)
		{
			pPuz[r][c].h_len = -1;
			pPuz[r][c].v_len = -1;
			pPuz[r][c].cell.type = BLANK;
		}
	}

	for(r=1;r<m_rows;r++)
	{
		for(c=1;c<m_cols;c++)
		{
			if(AssignHLen(r, c, pPuz) || AssignVLen(r, c, pPuz))
			{
				CleanUp(pPuz);
				return -1;
			}
			
		}

	}

	if(MakePuzzle(pPuz))
	{
		CleanUp(pPuz);
		return -1;
	}

	CleanUp(pPuz);
	return 0;
}

void CCrossSumsDoc::CleanUp(SPUZZLECELL **pPuz)
{
	for(int r=m_rows-1;r>=0;r--)
	{
		delete pPuz[r];
	}
	delete pPuz;
}


void CCrossSumsDoc::ToggleView()
{
	if(options.edit/*m_pHidden*/)
	{
		options.edit = 0; 

		// here we are returning from editing a puzzle;
		// recalculate cells, sums, and zero out user values
		// so we should have 
		if(m_pHidden)
		{
			if(!PublishPuzzle())
			{
				options.edit = 1;
				AfxMessageBox(IDS_PUBLISHFAILED,MB_OK);
				return;
			}
			m_pHidden->GetParent()->ShowWindow(SW_SHOW);
			((CFrameWnd*)m_pHidden->GetParent())->ActivateFrame(); //CDocument //CFrameWnd //CView
			UpdateAllViews(NULL, 1);
			m_pHidden = NULL;
		}
		
		StartPuzzleTime();

	}
	else /*if(options.edit)*/
	{
		StopPuzzleTime();

		options.edit = 1;
		options.timed = 0;

		// here we are going to edit the puzzle, so
		// hide the view
		POSITION pos = GetFirstViewPosition();
		if(pos)
		{
			m_pHidden = GetNextView(pos);
			ASSERT(m_pHidden);
			m_pHidden->GetParent()->ShowWindow(SW_HIDE);
			OnPuzzleSolution();
			UpdateAllViews(NULL,1);
		}
	}
	
}

BOOL CCrossSumsDoc::IsSolved()
{
	SCELL *pCell;
	int r,c;

	for(r=0;r<m_rows;r++)
	{
		for(c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			ASSERT(pCell);
			if(pCell->type == NUMBER)
			{
				if(pCell->value.actual ==0)
					return FALSE;
				if(pCell->value.actual != pCell->value.user)
					return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsDoc construction/destruction

CCrossSumsDoc::CCrossSumsDoc()
{
	// TODO: add one-time construction code here
	m_cells = NULL;
	m_lGameTime = 0;
	m_boardlevel = 0;
	m_numberlevel = 0;
	m_bReadOnly = FALSE;
	m_pHidden = NULL;
	m_csAuthor.LoadString(ID_INDICATOR_AUTHOR);
	ResetPuzzleTime();
}

CCrossSumsDoc::~CCrossSumsDoc()
{
}

BOOL CCrossSumsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CNewCrossSumDlg dlg;

	dlg.m_cols = options.cols;
	dlg.m_rows = options.rows;
	dlg.m_level = options.level;
	dlg.m_bReadOnly = FALSE;
	dlg.m_csAuthor = "";

	if(dlg.DoModal()==IDOK)
	{
		m_rows = dlg.m_rows;
		m_cols = dlg.m_cols;
		m_level = dlg.m_level;
		m_bReadOnly = dlg.m_bReadOnly;
		m_csAuthor = dlg.m_csAuthor;

		if(options.edit == 1)
		{
			InitPuzzleEditor();
			options.user_level = LVL_NORM;
		}
		else
		{
			if(CreateNewPuzzle())
			{
				AfxMessageBox(IDS_CREATEPUZZLEFAIL);
				DeleteContents();
				return FALSE;
			}

			ResetPuzzleTime();

		}
		
		// success in creating new puzzle
		return TRUE;

	}

	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CCrossSumsDoc serialization

int CCrossSumsDoc::ReadPuzzleData(CArchive &ar, CString csWhat)
{
	CArchiveException cae;

	if(!csWhat.CompareNoCase("$PREFS"))
	{
		TRY
		{
			ar.Read((void*)&prefs,sizeof(prefs));
		}
		CATCH(CArchiveException,cae)
		{
			cae->ReportError();
			return -1;
		}
		END_CATCH

	}

	if(!csWhat.CompareNoCase("$AUTHOR"))
	{
		TRY
		{
			ar >> m_csAuthor;
		}
		CATCH(CArchiveException,cae)
		{
			cae->ReportError();
			return -1;
		}
		END_CATCH
	}

	return 0;

}

void CCrossSumsDoc::Serialize(CArchive& ar)
{
	StopPuzzleTime();

	if (ar.IsStoring())
	{
		m_lGameTime = m_time.GetTotalSeconds();

		CString csVer; csVer.LoadString(IDS_VERSION);
		CString csApp; csApp.LoadString(IDR_MAINFRAME);
		SCELL *pCell;
		ar << csApp;
		ar << csVer;
		ar << m_bReadOnly;
		ar << m_level;
		ar << options.timed;
		ar << m_lGameTime;
		ar << m_rows;
		ar << m_cols;
		for(int r=0;r<m_rows;r++)
		{
			for(int c=0;c<m_cols;c++)
			{
				pCell = GET_CELL(r,c);
				ASSERT(pCell);
				ar << (int)pCell->type;
				ar << pCell->starter;
				if(pCell->type == SUM)
				{
					ar << pCell->sum.h;
					ar << pCell->sum.v;
				}
				else if(pCell->type == NUMBER)
				{
					ar << pCell->value.actual;
					ar << pCell->value.user;
					ar << pCell->list;
				}
			}
		}

		CString cs("$PREFS");
		ar << cs;
		ar.Write((void*)&prefs,sizeof(prefs));

		cs = _T("$AUTHOR");
		ar << cs;
		ar << m_csAuthor;

		cs = _T("$END");
		ar << cs;
		
	}
	else
	{
		CString cs;
		CString csV,csVer; csVer.LoadString(IDS_VERSION);
		CString csA,csApp; csApp.LoadString(IDR_MAINFRAME);
		int rows,cols;
		SCELL *pCell;

		ar >> csA;
		if(csA.CompareNoCase(csApp))
		{
			// error - incorrect file type
			return;
		}
		ar >> csV;

		double fVer = atof(csV);

		ar >> m_bReadOnly;
		ar >> m_level;
		ar >> options.timed;
		ar >> m_lGameTime;
		ar >> rows;
		ar >> cols;

		m_cells = new SCELL[rows * cols];
		ASSERT(m_cells);
		m_rows = rows;
		m_cols = cols;
		int type;

		for(int r = 0;r<rows;r++)
		{
			for(int c=0;c<cols;c++)
			{
				pCell = (SCELL*)&m_cells[r * rows + c];
				ASSERT(pCell);
				ar >> type;
				pCell->type = (CELL_TYPE)type;
				pCell->row = r;
				pCell->col = c;
				pCell->starter = 0;
				if(fVer>1.1)
					ar >> pCell->starter;
				if(pCell->type == BLANK)
				{
					pCell->list = NO_NUMBERS;
					pCell->sum.h = -1;
					pCell->sum.v = -1;
				}
				if(pCell->type == SUM)
				{
					ar >> pCell->sum.h;
					ar >> pCell->sum.v;
				}
				else if(pCell->type == NUMBER)
				{
					ar >> pCell->value.actual;
					ar >> pCell->value.user;
					ar >> pCell->list;
				}
			}
		}

		
		BOOL bEnd = FALSE;
		if(fVer>1.0)
		{
			ar >> cs;
			while(!bEnd && !cs.IsEmpty() && cs.CompareNoCase("$END"))
			{
				bEnd = (ReadPuzzleData(ar,cs)!=0);
				ar >> cs;
			}
		}

		CTimeSpan cts(m_lGameTime);
		m_time = cts;

	}

	StartPuzzleTime();
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsDoc diagnostics

#ifdef _DEBUG
void CCrossSumsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCrossSumsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsDoc commands

void CCrossSumsDoc::DeleteContents() 
{
	if(m_cells)
	{
		delete m_cells;	
		m_cells = NULL;
	}
	CDocument::DeleteContents();
}


void CCrossSumsDoc::OnPuzzleOptions() 
{
	if(options.edit)
	{
		CDlgAdvanced dlg;

		dlg.m_bReadOnly = m_bReadOnly;
		dlg.m_csAuthor = m_csAuthor;
		dlg.m_bSideSide = options.side_side;
		dlg.m_bTopBottom = options.top_bottom;

		if(dlg.DoModal()==IDOK)
		{
			m_bReadOnly = dlg.m_bReadOnly;
			m_csAuthor = dlg.m_csAuthor;
			options.side_side = dlg.m_bSideSide;
			options.top_bottom = dlg.m_bTopBottom;
		}
	}
	else
	{
		StopPuzzleTime();

		CDlgOptions cdo;

		cdo.m_bShowIncorrect = options.show_correct;
		cdo.m_bAutoFill = options.auto_fill;

		if(options.user_level == LVL_BEGIN)
			cdo.m_nStyle = 0;
		else if(options.user_level == LVL_NORM)
			cdo.m_nStyle = 1;
		else if(options.user_level == LVL_ADV)
			cdo.m_nStyle = 2;
		
		if(cdo.DoModal()==IDOK)
		{
			options.show_correct = cdo.m_bShowIncorrect;
			options.auto_fill = cdo.m_bAutoFill;

			if(cdo.m_nStyle == 0)
				options.user_level = LVL_BEGIN;
			else if(cdo.m_nStyle == 1)
				options.user_level = LVL_NORM;
			else if(cdo.m_nStyle == 2)
				options.user_level = LVL_ADV;
			
			UpdateAllViews(NULL);
		}

		StartPuzzleTime();
	}
		
}

void CCrossSumsDoc::OnPuzzlePreferences() 
{
	StopPuzzleTime();

	CPropertySheet cps(IDS_PREFS);
	CPrefsColor clrPage(defaultPrefs);
	CPrefsFonts fontPage(defaultPrefs);
	
	BOOL bFontChange = FALSE;

	clrPage.m_clrBkgnd = prefs.m_clrBkgnd;
	clrPage.m_clrCells = prefs.m_clrCells;
	clrPage.m_clrText = prefs.m_clrText;
	clrPage.m_clrSum = prefs.m_clrSum;
	clrPage.m_clrHilite = prefs.m_clrHilite;
	clrPage.m_clrFlash = prefs.m_clrFlash;
	clrPage.m_clrWrong = prefs.m_clrWrong;
	clrPage.m_clrBkgndBorder = prefs.m_clrBkgndBorder;
	clrPage.m_clrCellBorder = prefs.m_clrCellBorder;
	clrPage.m_clrSumBorder = prefs.m_clrSumBorder;
	clrPage.m_clrGrid = prefs.m_clrGrid;
	clrPage.m_bShowGrid = prefs.m_bShowGrid;

	strcpy(fontPage.m_lfText.lfFaceName, prefs.m_szTextFontName);
	strcpy(fontPage.m_lfSums.lfFaceName, prefs.m_szSumFontName);
	fontPage.m_lfText.lfHeight = prefs.m_nTextSize;
	fontPage.m_lfSums.lfHeight = prefs.m_nSumSize;

	cps.AddPage(&clrPage);
	cps.AddPage(&fontPage);
	cps.m_psh.dwFlags&=~PSH_NOAPPLYNOW;

	if(cps.DoModal()==IDOK)
	{
		prefs.m_clrBkgnd = clrPage.m_clrBkgnd;
		prefs.m_clrCells = clrPage.m_clrCells;
		prefs.m_clrText = clrPage.m_clrText;
		prefs.m_clrSum = clrPage.m_clrSum;
		prefs.m_clrHilite = clrPage.m_clrHilite;
		prefs.m_clrFlash = clrPage.m_clrFlash;
		prefs.m_clrWrong = clrPage.m_clrWrong;
		prefs.m_clrBkgndBorder = clrPage.m_clrBkgndBorder;
		prefs.m_clrCellBorder = clrPage.m_clrCellBorder;
		prefs.m_clrSumBorder = clrPage.m_clrSumBorder;
		prefs.m_clrGrid = clrPage.m_clrGrid;
		prefs.m_bShowGrid = clrPage.m_bShowGrid;

		if(strcmp(prefs.m_szTextFontName,fontPage.m_lfText.lfFaceName) ||
			(prefs.m_nTextSize != fontPage.m_lfText.lfHeight))
		{
			bFontChange = TRUE;
			strcpy(prefs.m_szTextFontName,fontPage.m_lfText.lfFaceName);
			prefs.m_nTextSize = fontPage.m_lfText.lfHeight;
		}

		if(strcmp(prefs.m_szSumFontName, fontPage.m_lfSums.lfFaceName) ||
			(prefs.m_nSumSize  = fontPage.m_lfSums.lfHeight))
		{
			bFontChange = TRUE;
			strcpy(prefs.m_szSumFontName, fontPage.m_lfSums.lfFaceName);
			prefs.m_nSumSize  = fontPage.m_lfSums.lfHeight;
		}

		UpdateAllViews(NULL,(int)bFontChange);
		SetModifiedFlag();

	}

	StartPuzzleTime();
	
}

BOOL CCrossSumsDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(options.edit)
	{
		if(!PublishPuzzle())
		{
			AfxMessageBox(IDS_PUBLISHFAILED,MB_OK);
			return FALSE;
		}
	}

	if(!CDocument::OnSaveDocument(lpszPathName))
		return FALSE;

	if(options.edit)
	{
		OnPuzzleSolution();
		UpdateAllViews(NULL,1);
	}

	return TRUE;

}

void CCrossSumsDoc::OnPuzzleNewvalues() 
{
	if(!ResetPuzzleTime(TRUE))
		return;

	ValidateCells();
	if(!GenerateNumbers())
	{
		GenerateSums();
		if(options.edit)
			OnPuzzleSolution();
		UpdateAllViews(NULL,1);
		SetModifiedFlag();
		StartPuzzleTime();
	}
}

void CCrossSumsDoc::OnPuzzleSolution() 
{
	StopPuzzleTime();

	SCELL *pCell;

	for(int r=0;r<m_rows;r++)
	{
		for(int c=0;c<m_cols;c++)
		{
			pCell = GET_CELL(r,c);
			if(pCell->type == NUMBER)
				pCell->value.user = pCell->value.actual;
		}
	}

	UpdateAllViews(NULL,0);
}


BOOL CCrossSumsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	//options.edit = 0;
	
	return TRUE;
}

void CCrossSumsDoc::OnUpdateEditPuzzle(CCmdUI* pCmdUI) 
{
#ifdef _DEBUG
	pCmdUI->SetCheck(options.edit);
	pCmdUI->Enable(!m_bReadOnly);
#else
	pCmdUI->Enable(FALSE);
#endif
}

void CCrossSumsDoc::OnPuzzleCalculate() 
{
	ValidateCells();
	GenerateSums();
	OnPuzzleSolution();
	UpdateAllViews(NULL,1);
	SetModifiedFlag();
}

void CCrossSumsDoc::OnChangedViewList() 
{
	CDocument::OnChangedViewList();
}

BOOL CCrossSumsDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::CanCloseFrame(pFrame);
}

void CCrossSumsDoc::OnPuzzleTimedpuzzle() 
{
	if(options.timed)
	{
		options.timed = FALSE;
		StopPuzzleTime();
		if(!ResetPuzzleTime(TRUE))
			StartPuzzleTime();
	}
	else
	{
		options.timed = TRUE;
		ResetPuzzleTime();
		StartPuzzleTime();
	}
	
}

void CCrossSumsDoc::OnUpdatePuzzleTimedpuzzle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(options.timed);	
}

void CCrossSumsDoc::OnPuzzleResetpuzzle() 
{
	// reset the user values (and lists) back to zero
	if(ResetPuzzleTime(TRUE))
	{
		ClearUserValues();
		UpdateAllViews(NULL);
		StartPuzzleTime();
		SetModifiedFlag();
	}
}
