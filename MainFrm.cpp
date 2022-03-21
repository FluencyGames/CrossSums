// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "afxpriv.h" // to get WM_POPMESSAGESTRING
#include "CrossSums.h"
#include "CrossSumsDoc.h"
#include "CrossSumsView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_EDIT,
	ID_INDICATOR_TIMER
};

extern OPTIONS options;
extern PREFS prefs;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_EDIT, OnUpdateEditIndicator)
	ON_MESSAGE(WM_POPMESSAGESTRING, OnPopMessageString)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIMER),
			"",
			TRUE);

	m_uTimer = SetTimer(ID_INDICATOR_TIMER,1000,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::DestroyWindow() 
{
	KillTimer(m_uTimer);	
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	CCrossSumsApp *pApp = (CCrossSumsApp*)AfxGetApp();
	CCrossSumsDoc *pDoc = NULL;
	CString cs("Puzzle Time: ");

	POSITION pos = pApp->m_pPuzzleTemplate->GetFirstDocPosition(); 
	if(pos)
		pDoc = (CCrossSumsDoc *)pApp->m_pPuzzleTemplate->GetNextDoc(pos);
	
	if(pDoc)
	{
		long ltime = pDoc->GetPuzzleTime();
		if(ltime>0)
		{
			CTimeSpan cts(ltime);

			if(cts.GetHours()<1)
				cs = cts.Format("Puzzle Time: %M:%S");
			else
				cs = cts.Format("Puzzle Time: %H:%M");
		}
	}
		
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_TIMER),
			(LPCTSTR)cs,
			TRUE); //CStatusBar

	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnUpdateEditIndicator(CCmdUI* pCmdUI) 
{
//#ifdef _DEBUG
	pCmdUI->Enable(options.edit);	
	pCmdUI->SetText("EDIT");
//#else
//	pCmdUI->Enable(FALSE);
//#endif
}

LRESULT CMainFrame::OnPopMessageString(WPARAM wParam, LPARAM lParam)
{
	if (m_nFlags & WF_NOPOPMSG)
		return 0;

	CCrossSumsApp *pApp = (CCrossSumsApp*)AfxGetApp();
	CCrossSumsDoc *pDoc = NULL;
	CString cs;

	cs.LoadString(AFX_IDS_IDLEMESSAGE);

	POSITION pos = pApp->m_pPuzzleTemplate->GetFirstDocPosition(); 
	if(pos)
		pDoc = (CCrossSumsDoc *)pApp->m_pPuzzleTemplate->GetNextDoc(pos);
	
	if(pDoc && !pDoc->m_csAuthor.IsEmpty())
		cs = pDoc->m_csAuthor;

	return SendMessage(WM_SETMESSAGESTRING, 0, (LPARAM)(LPCTSTR)cs);
}
