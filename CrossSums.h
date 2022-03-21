// CrossSums.h : main header file for the CROSSSUMS application
//

#if !defined(AFX_CROSSSUMS_H__3A8C6E69_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
#define AFX_CROSSSUMS_H__3A8C6E69_9D08_11D7_A1CF_0050DA71997A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsApp:
// See CrossSums.cpp for the implementation of this class
//

class CCrossSumsApp : public CWinApp
{
public:
	CCrossSumsApp();

public:
	CMultiDocTemplate* m_pPuzzleTemplate;
	CMultiDocTemplate* m_pEditorTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrossSumsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCrossSumsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnEditPuzzle();
	afx_msg void OnUpdateEditPuzzle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileNew(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CROSSSUMS_H__3A8C6E69_9D08_11D7_A1CF_0050DA71997A__INCLUDED_)
