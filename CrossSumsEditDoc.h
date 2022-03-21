#if !defined(AFX_CROSSSUMSEDITDOC_H__F6F19321_B09D_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CROSSSUMSEDITDOC_H__F6F19321_B09D_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CrossSumsEditDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsEditDoc document

class CCrossSumsEditDoc : public CCrossSumsDoc
{
protected:
	CCrossSumsEditDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CCrossSumsEditDoc)

// Attributes
public:

// Operations
public:
	void ValidateCells();
	void InitPuzzleEditor();
	void UpdateCellData(int row, int col, CELL_TYPE type, long lData);	
	BOOL PublishPuzzle();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossSumsEditDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCrossSumsEditDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CCrossSumsEditDoc)
	afx_msg void OnPuzzleCalculate();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnPuzzleNewvalues();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSSUMSEDITDOC_H__F6F19321_B09D_11D7_A1CF_0050DA71997A__INCLUDED_)
