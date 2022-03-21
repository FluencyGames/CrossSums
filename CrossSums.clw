; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCrossSumsApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CrossSums.h"
LastPage=0

ClassCount=18
Class1=CCrossSumsApp
Class2=CCrossSumsDoc
Class3=CCrossSumsView
Class4=CMainFrame

ResourceCount=12
Resource1=IDR_MAINFRAME
Resource2=IDD_PREFSFONT
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_EDITOPTIONS
Class7=CNewCrossSumDlg
Class8=CNumberWnd
Class9=CSumWnd
Resource4=IDD_NEWOPTIONS
Resource5=IDD_ADVOPTIONS
Class10=CDlgOptions
Class11=CCrossSumsEditor
Resource6=IDD_ABOUTBOX
Class12=CCrossSumsEditDoc
Resource7=IDD_OPTIONS
Class13=CDlgSave
Resource8=IDR_EDITORTYPE
Class14=CDlgAdvanced
Resource9=IDR_CROSSSTYPE
Class15=CPrefsColor
Class16=CPrefsFonts
Class17=CSampleViewBtn
Resource10=IDD_QUERYSAVE
Resource11=IDD_PREFSCOLOR
Class18=CSelectHelpersDlg
Resource12=IDD_SELECTSTART

[CLS:CCrossSumsApp]
Type=0
HeaderFile=CrossSums.h
ImplementationFile=CrossSums.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_NEW

[CLS:CCrossSumsDoc]
Type=0
HeaderFile=CrossSumsDoc.h
ImplementationFile=CrossSumsDoc.cpp
Filter=N
LastObject=ID_PUZZLE_RESETPUZZLE
BaseClass=CDocument
VirtualFilter=DC

[CLS:CCrossSumsView]
Type=0
HeaderFile=CrossSumsView.h
ImplementationFile=CrossSumsView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_PUZZLE_SHOWSTARTERHELP


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=CrossSums.cpp
ImplementationFile=CrossSums.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_EDIT_COPY
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_PUZZLE
Command11=ID_VIEW_TOOLBAR
Command12=ID_APP_ABOUT
CommandCount=12

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_CROSSSTYPE]
Type=1
Class=CCrossSumsView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_PUZZLE
Command16=ID_PUZZLE_TIMEDPUZZLE
Command17=ID_PUZZLE_SHOWSTARTERHELP
Command18=ID_PUZZLE_RESETPUZZLE
Command19=ID_PUZZLE_SOLUTION
Command20=ID_PUZZLE_NEWVALUES
Command21=ID_PUZZLE_PREFERENCES
Command22=ID_PUZZLE_OPTIONS
Command23=ID_VIEW_TOOLBAR
Command24=ID_APP_ABOUT
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_NEWOPTIONS]
Type=1
Class=CNewCrossSumDlg
ControlCount=12
Control1=IDC_LEVEL,edit,1350631552
Control2=IDC_SPIN1,msctls_updown32,1342177334
Control3=IDC_HSIZE,edit,1350631552
Control4=IDC_VSIZE,edit,1350631552
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_ADVANCED,button,1342242816

[CLS:CNewCrossSumDlg]
Type=0
HeaderFile=Dlgs.h
ImplementationFile=Dlgs.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ADVANCED
VirtualFilter=dWC

[CLS:CNumberWnd]
Type=0
HeaderFile=CellWnd.h
ImplementationFile=CellWnd.cpp
BaseClass=CWnd
Filter=W
LastObject=CNumberWnd
VirtualFilter=WC

[CLS:CSumWnd]
Type=0
HeaderFile=CellWnd.h
ImplementationFile=CellWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CSumWnd

[DLG:IDD_OPTIONS]
Type=1
Class=CDlgOptions
ControlCount=8
Control1=IDOK,button,1342373889
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_PLAYINGSTYLE,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825
Control7=IDC_SHOWINCORRECT,button,1342373891
Control8=IDC_AUTOFILL,button,1342242819

[CLS:CDlgOptions]
Type=0
HeaderFile=Dlgs.h
ImplementationFile=Dlgs.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_AUTOFILL

[CLS:CCrossSumsEditor]
Type=0
HeaderFile=CrossSumsEditor.h
ImplementationFile=CrossSumsEditor.cpp
BaseClass=CCrossSumsView
Filter=C
VirtualFilter=VWC
LastObject=CCrossSumsEditor

[MNU:IDR_EDITORTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_EDIT_PUZZLE
Command16=ID_PUZZLE_SELECTSTARTINGHELPBOXES
Command17=ID_PUZZLE_NEWVALUES
Command18=ID_PUZZLE_CALCULATE
Command19=ID_PUZZLE_SYMMETRY_OFF
Command20=ID_PUZZLE_SYMMETRY_SIDESIDE
Command21=ID_PUZZLE_SYMMETRY_TOPBOTTOM
Command22=ID_PUZZLE_PREFERENCES
Command23=ID_PUZZLE_OPTIONS
Command24=ID_VIEW_TOOLBAR
Command25=ID_APP_ABOUT
CommandCount=25

[TB:IDR_EDITORTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[CLS:CCrossSumsEditDoc]
Type=0
HeaderFile=CrossSumsEditDoc.h
ImplementationFile=CrossSumsEditDoc.cpp
BaseClass=CCrossSumsDoc
Filter=N
VirtualFilter=DC
LastObject=CCrossSumsEditDoc

[DLG:IDD_QUERYSAVE]
Type=1
Class=CDlgSave
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDYES,button,1342242816
Control3=IDNO,button,1342242816

[CLS:CDlgSave]
Type=0
HeaderFile=Dlgs.h
ImplementationFile=Dlgs.cpp
BaseClass=CDialog
Filter=D
LastObject=IDYES
VirtualFilter=dWC

[CLS:CDlgAdvanced]
Type=0
HeaderFile=Dlgs.h
ImplementationFile=Dlgs.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgAdvanced

[DLG:IDD_PREFSCOLOR]
Type=1
Class=CPrefsColor
ControlCount=6
Control1=IDC_LIST3,listbox,1352728835
Control2=IDC_CUSTOM,button,1342242816
Control3=IDC_SAMPLE,button,1073741831
Control4=IDC_STATIC,button,1342177287
Control5=IDC_SHOWGRID,button,1342242819
Control6=IDC_RESTOREDEFAULTS,button,1342242816

[DLG:IDD_PREFSFONT]
Type=1
Class=CPrefsFonts
ControlCount=8
Control1=IDC_LIST1,listbox,1352728835
Control2=IDC_COMBO1,combobox,1344340226
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FONTSIZE,combobox,1344339970
Control6=IDC_STATIC,button,1342177287
Control7=IDC_SAMPLE,button,1073741831
Control8=IDC_RESTOREDEFAULTS,button,1342242816

[CLS:CPrefsColor]
Type=0
HeaderFile=PrefsColor.h
ImplementationFile=PrefsColor.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPrefsColor

[CLS:CPrefsFonts]
Type=0
HeaderFile=prefscolor.h
ImplementationFile=prefscolor.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=CPrefsFonts

[CLS:CSampleViewBtn]
Type=0
HeaderFile=PrefsColor.h
ImplementationFile=PrefsColor.cpp
BaseClass=CButton
Filter=W
LastObject=CSampleViewBtn
VirtualFilter=BWC

[DLG:IDD_EDITOPTIONS]
Type=1
Class=CDlgAdvanced
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_READONLY,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_AUTHOR,edit,1350631552

[DLG:IDD_ADVOPTIONS]
Type=1
Class=CDlgAdvanced
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SIDESIDE,button,1342242819
Control4=IDC_TOPBOTTOM,button,1342242819
Control5=IDC_STATIC,button,1342177287
Control6=IDC_READONLY,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_AUTHOR,edit,1350631552

[DLG:IDD_SELECTSTART]
Type=1
Class=CSelectHelpersDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308353
Control4=IDC_CHECK1,button,1342242819

[CLS:CSelectHelpersDlg]
Type=0
HeaderFile=Dlgs.h
ImplementationFile=Dlgs.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CHECK1

