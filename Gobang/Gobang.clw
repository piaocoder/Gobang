; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGobangDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Gobang.h"

ClassCount=5
Class1=CGobangApp
Class2=CGobangDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_GOBANG_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class5=CRoundButton
Class4=CDlgoption
Resource4=IDD_DLGOPTION_DIALOG
Resource5=IDR_MAIN_MENU

[CLS:CGobangApp]
Type=0
HeaderFile=Gobang.h
ImplementationFile=Gobang.cpp
Filter=N

[CLS:CGobangDlg]
Type=0
HeaderFile=GobangDlg.h
ImplementationFile=GobangDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_NEW

[CLS:CAboutDlg]
Type=0
HeaderFile=GobangDlg.h
ImplementationFile=GobangDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352

[DLG:IDD_GOBANG_DIALOG]
Type=1
Class=CGobangDlg
ControlCount=7
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,button,1342177287
Control3=IDC_NEW,button,1342242816
Control4=IDC_OPTION,button,1342242816
Control5=IDC_BACK,button,1342242816
Control6=IDC_ABOUT,button,1342242816
Control7=IDC_EXIT,button,1342242816

[DLG:IDD_DLGOPTION_DIALOG]
Type=1
Class=CDlgoption
ControlCount=10
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,button,1342177287
Control3=IDOK,button,1342242816
Control4=IDCANCEL,button,1342242816
Control5=IDC_RADIO1,button,1342308361
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_RADIO3,button,1342177289
Control8=IDC_RADIO4,button,1342308361
Control9=IDC_RADIO5,button,1342177289
Control10=IDC_RADIO6,button,1342177289

[CLS:CDlgoption]
Type=0
HeaderFile=Dlgoption.h
ImplementationFile=Dlgoption.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgoption
VirtualFilter=dWC

[CLS:CRoundButton]
Type=0
HeaderFile=RoundButton.h
ImplementationFile=RoundButton.cpp
BaseClass=CButton
Filter=W

[MNU:IDR_MAIN_MENU]
Type=1
Class=CGobangDlg
Command1=ID_MENU_NEW
Command2=ID_MENU_OPTION
Command3=ID_MENU_BACK
Command4=ID_MENU_ABOUT
Command5=IN_MENU_EXIT
CommandCount=5

