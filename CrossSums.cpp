// CrossSums.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "types.h"
#include "CrossSums.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "CrossSumsDoc.h"
#include "CrossSumsView.h"
#include "CrossSumsEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

OPTIONS options;
PREFS	prefs;

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsApp

BEGIN_MESSAGE_MAP(CCrossSumsApp, CWinApp)
	//{{AFX_MSG_MAP(CCrossSumsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_EDIT_PUZZLE, OnEditPuzzle)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PUZZLE, OnUpdateEditPuzzle)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsApp construction

CCrossSumsApp::CCrossSumsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCrossSumsApp object

CCrossSumsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsApp initialization

BOOL CCrossSumsApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// seed generator
	srand((unsigned)LOWORD(GetTickCount()));

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("CrossSumsApp"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	options.rows = 14;
	options.cols = 14;
	options.level = 1;
	options.side_side = FALSE;
	options.top_bottom = TRUE;
	options.user_level = LVL_NORM;
	options.show_correct = FALSE;
	options.auto_fill = 1;
	options.timed = 0;

	prefs.m_bShowGrid = FALSE;
	prefs.m_clrBkgnd = 0x00000000;
	prefs.m_clrCells = 0x00ffffff;
	prefs.m_clrFlash = CLR_UNDEFINED;
	prefs.m_clrHilite = CLR_UNDEFINED;
	prefs.m_clrText = 0x00000000;
	prefs.m_clrSum = 0x00ffffff;
	prefs.m_clrWrong = 0x000000ff;
	prefs.m_clrGrid = 0x00000000;
	prefs.m_clrBkgndBorder = prefs.m_clrBkgnd;
	prefs.m_clrCellBorder = prefs.m_clrBkgnd;
	prefs.m_clrSumBorder = prefs.m_clrBkgnd;

	prefs.m_nListSize = 80;
	prefs.m_nTextSize = 140;
	prefs.m_nSumSize = 80;

	strcpy(prefs.m_szSumFontName, "Times New Roman");
	strcpy(prefs.m_szTextFontName, "Comic Sans Serif");

	m_pPuzzleTemplate = new CMultiDocTemplate(
		IDR_CROSSSTYPE,
		RUNTIME_CLASS(CCrossSumsDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame CWinAPp
		RUNTIME_CLASS(CCrossSumsView));
	AddDocTemplate(m_pPuzzleTemplate);

	m_pEditorTemplate = new CMultiDocTemplate(
		IDR_EDITORTYPE,
		RUNTIME_CLASS(CCrossSumsDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCrossSumsEditor));
	AddDocTemplate(m_pEditorTemplate);


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CCrossSumsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCrossSumsApp message handlers




void CCrossSumsApp::OnFileNew() 
{
	options.edit = 0;
	m_pPuzzleTemplate->OpenDocumentFile(NULL);	
}

void CCrossSumsApp::OnEditPuzzle() 
{
	// if we are already editing, do nothing
	if(options.edit)
		return;

	CMDIChildWnd *pActive = ((CMDIFrameWnd*)m_pMainWnd)->MDIGetActive();

	// if no active document, then we are starting the editor
	// from no puzzle
	if(pActive==NULL)
	{
		options.edit = 1;
		m_pEditorTemplate->OpenDocumentFile(NULL);
		return;
	}

	// if there is a current document, then create a new editor view
	// and attach to current document
	CDocument *pDoc = pActive->GetActiveDocument(); //CDocument //CDocTemplate
	if(pDoc->IsKindOf(RUNTIME_CLASS(CCrossSumsDoc)))
	{
		CFrameWnd *pFrame = m_pEditorTemplate->CreateNewFrame(pDoc,pActive);
		if(pFrame == NULL)
		{
			// failed to open editor
			AfxMessageBox(IDS_EDITVIEWFAIL);
			return;
		}

		m_pEditorTemplate->InitialUpdateFrame(pFrame,pDoc);
		((CCrossSumsDoc*)pDoc)->ToggleView();
	}

}

void CCrossSumsApp::OnUpdateEditPuzzle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
//#ifdef NDEBUG
//	pCmdUI->Enable(FALSE);
//#endif

}

int CCrossSumsApp::ExitInstance() 
{
	// write the registry	
	return CWinApp::ExitInstance();
}

void CCrossSumsApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
#ifdef NDEBUG
	pCmdUI->Enable(FALSE);
#endif
}
