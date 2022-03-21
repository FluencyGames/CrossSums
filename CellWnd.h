#if !defined(AFX_CELLWND_H__379332A1_9E68_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CELLWND_H__379332A1_9E68_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CellWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumberWnd window

class CNumberWnd : public CWnd
{
// Construction
public:
	CNumberWnd();
	CNumberWnd(CWnd *pParent, const RECT &rect,CFont *pFont, CFont *pListFont);

// Attributes
public:
	void  *m_pData;
	CFont *m_pFont;
	CFont *m_pListFont;
	BOOL   m_bFocus;
	CBitmap m_bmp;

	int m_row;
	int m_col;
	int m_value;
	int m_actual;
	int m_starter;
	NUMBERLIST m_list;

protected:
	int m_nFlash;
	long m_lTime;

// Operations
public:
	int GenerateListString(LPSTR szList);

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberWnd)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumberWnd();

	// Generated message map functions WM_USER
protected:
	//{{AFX_MSG(CNumberWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg long OnSetCellData(WPARAM wParam, LPARAM lParam);
	afx_msg long OnGetCellData(WPARAM wParam, LPARAM lParam);
	afx_msg long OnFlash(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSumWnd window

class CSumWnd : public CWnd
{
// Construction
public:
	CSumWnd();
	CSumWnd(CWnd *pParent,const RECT &rect,CFont *pFont);

// Attributes
public:
	CFont *m_pFont;
	void  *m_pData;
	int m_row;
	int m_col;
	int m_hsum;
	int m_vsum;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSumWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSumWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSumWnd)
	afx_msg void OnPaint();
	afx_msg long OnSetCellData(WPARAM wParam, LPARAM lParam);
	afx_msg long OnGetCellData(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CELLWND_H__379332A1_9E68_11D7_A1CF_0050DA71997A__INCLUDED_)
