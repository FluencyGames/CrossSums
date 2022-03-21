#ifndef _TYPES_H
#define _TYPES_H

#define WM_SETCELLDATA		(WM_USER+1)
#define WM_GETCELLDATA		(WM_USER+2)
#define WM_FLASH			(WM_USER+3)
#define WM_SELECTING		(WM_USER+4)

#define ALL_NUMBERS 0xffff
#define NO_NUMBERS 0x0000

typedef UINT NUMBERLIST;

#define DROP_NUMBER(_n,_l) { if(_n>0) { UINT k = 1<<(_n-1); k = ~k; _l &= k; }}
#define ADD_NUMBER(_n,_l)  { if(_n>0) { UINT k = 1<<(_n-1); _l |= k; }}
#define IS_NUMBER_LISTED(_n,_l) ((_n>=1&&_n<=9) ? ( _l&(1<<(_n-1)) ? 1 : 0) : 0 )

#define	CELL_PTR	0
#define CELL_VALUE	1
#define CELL_LIST	2
#define CELL_ROWCOL	3
#define CELL_STARTER 4

#define MIN_CROSSSUM_LENGTH	2
#define MAX_CROSSSUM_LENGTH	9

#define CLR_UNDEFINED			((COLORREF)-1)
#define IS_CLR_DEFINED(_clr)	((_clr)!=CLR_UNDEFINED?1:0)

typedef enum
{
	LVL_BEGIN =	0x0001,
	LVL_NORM  =	0x0002,
	LVL_ADV	  =	0x0004,
} USR_LEVEL;

typedef enum
{
	BLANK = -1,
	NUMBER = 0,
	SUM = 1,
	
} CELL_TYPE;

typedef struct scell
{
	int row;
	int col;
	int starter;
	NUMBERLIST list;
	CELL_TYPE type;
	union {
		struct {
			int h;
			int v;
		} sum;
		struct {
			int actual;
			int user;
		} value;
	};
} SCELL;

typedef struct opts
{
	int rows;
	int cols;
	int show_correct;
	int auto_fill;
	int timed;
	int level;
	int edit;
	int	side_side;
	int top_bottom;
	USR_LEVEL user_level;
} OPTIONS;

typedef struct prefs
{
	int		 m_bShowGrid;
	int		 m_bShowHelpers;
	COLORREF m_clrBkgnd;
	COLORREF m_clrCells;
	COLORREF m_clrText;
	COLORREF m_clrFlash;
	COLORREF m_clrHilite;
	COLORREF m_clrWrong;
	COLORREF m_clrBkgndBorder;
	COLORREF m_clrCellBorder;
	COLORREF m_clrSumBorder;
	COLORREF m_clrGrid;
	COLORREF m_clrSum;
	int		 m_nTextSize;
	int      m_nSumSize;
	int      m_nListSize;
	TCHAR	 m_szTextFontName[32];
	TCHAR	 m_szSumFontName[32];
} PREFS;

#endif /* types.h */