#if !defined(AFX_CROSSSUMSEDITOR_H__78D6FAC1_AEFE_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CROSSSUMSEDITOR_H__78D6FAC1_AEFE_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrossSumsEditor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditor view

class CCrossSumsEditor : public CCrossSumsView
{
protected:
	CCrossSumsEditor();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCrossSumsEditor)

// Attributes
public:
	CRect m_focusRect;
	CRect m_origRect;
	BOOL  m_bSelectMode;

// Operations
public:
	CCrossSumsDoc* GetDocument();

	void CellRectFromRC(CRect *pRect, int row, int col);
	void CellRectFromPoint(CRect *rect, CPoint point);
	CWnd *CreateCellWnd(int row, int col);
	CWnd *CreateCellWndFromPoint(CPoint point);
	void RemoveOneWnd(CWnd *pWnd);
	void DropCell(CPoint point);
	void HandleStarterCell(CWnd *pWnd);
	void SetStarterCells();
	void SaveStarterCells();



	virtual void HandleCharInput(UINT nChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossSumsEditor)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCrossSumsEditor();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCrossSumsEditor)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnPuzzleSymmetryOff();
	afx_msg void OnUpdatePuzzleSymmetryOff(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleSymmetrySideside();
	afx_msg void OnUpdatePuzzleSymmetrySideside(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleSymmetryTopbottom();
	afx_msg void OnUpdatePuzzleSymmetryTopbottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleSelectstartinghelpboxes();
	afx_msg long OnSelectingHelp(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CrossSumsView.cpp
inline CCrossSumsDoc* CCrossSumsEditor::GetDocument()
   { return (CCrossSumsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSSUMSEDITOR_H__78D6FAC1_AEFE_11D7_A1CF_0050DA71997A__INCLUDED_)
