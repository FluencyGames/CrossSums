// CrossSumsView.h : interface of the CCrossSumsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CROSSSUMSVIEW_H__3A8C6E73_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CROSSSUMSVIEW_H__3A8C6E73_9D08_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCrossSumsView : public CView
{
protected: // create from serialization only
	CCrossSumsView();
	DECLARE_DYNCREATE(CCrossSumsView)

// Attributes
public:
//	CCrossSumsView();
	CCrossSumsDoc* GetDocument();

	void DoSolvedPuzzle();

	void HandleMoveFocus(int h, int v, UINT uFlags);
	virtual void HandleCharInput(UINT nChar);
	void HandleCellListInput(int nVal);

	CWnd *GetCellWnd(int row, int col);
	int HandleAutoFillOneCell(int row, int col);
	void HandleAutoFill(int row, int col);

	void InitFonts();
	void CalculateCellSize();
	void InitializeCellWnd();
	virtual void ShowStarterCells();
	void ReSizeFrame();
	int  RemoveCellWnd(CWnd *pWnd=NULL);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossSumsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCrossSumsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFont m_fontNumber;
	CFont m_fontSum;
	CFont m_fontList;
	CPtrArray m_paSum;
	CPtrArray m_paNum;
	CWnd *m_pFocusWnd;
	int m_width,m_height;
	BOOL m_bDrag;
	BOOL m_bStarterHelpAvailable;

// Generated message map functions
protected:
	//{{AFX_MSG(CCrossSumsView)
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPuzzleShowstarterhelp();
	afx_msg void OnUpdatePuzzleShowstarterhelp(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CrossSumsView.cpp
inline CCrossSumsDoc* CCrossSumsView::GetDocument()
   { return (CCrossSumsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSSUMSVIEW_H__3A8C6E73_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
