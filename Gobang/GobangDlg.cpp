// GobangDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Gobang.h"
#include "GobangDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CGobangDlg dialog

CGobangDlg::CGobangDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGobangDlg::IDD, pParent)
{

	CBitmap b,c,d,e,f;						//创建四个位图对象
	CSize x;
	b.LoadBitmap(IDB_CHESSBOARD);			//加载棋盘
	BITMAP bm;
	b.GetBitmap(&bm);						//获得棋盘的信息
	x.cx = bm.bmWidth;						
	x.cy = bm.bmHeight;
	chessboard.CreateCompatibleDC(NULL);			//创建棋盘
	chessboard.SelectObject(&b);
	chessboard.SetSize(x);
	b.DeleteObject(); 

	c.LoadBitmap(IDB_CHESS_BLACK);			//加载黑色棋子
	x.cx = 27 ;
	x.cy =27 ;
	chess_black.CreateCompatibleDC(NULL);
	chess_black.SelectObject(&c);
	chess_black.SetSize(x);
	c.DeleteObject(); 

	d.LoadBitmap(IDB_CHESS_WHITE);			//加载白色棋子
	x.cx = 27 ;
	x.cy =27; 
	chess_white.CreateCompatibleDC(NULL);
	chess_white.SelectObject(&d);
	chess_white.SetSize(x);
	d.DeleteObject(); 

	e.LoadBitmap(IDB_MASK);
	x.cx = 27 ;
	x.cy =27; 
	mask.CreateCompatibleDC(NULL);
	mask.SelectObject(&e);
	mask.SetSize(x);
	d.DeleteObject();

	f.LoadBitmap(IDB_DEAD);					//加载红色棋子
	x.cx=27;
	x.cy=27;
	dead.CreateCompatibleDC(NULL);
	dead.SelectObject(&f);
	dead.SetSize(x);
	f.DeleteObject();

	//{{AFX_DATA_INIT(CGobangDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CGobangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGobangDlg)
	DDX_Control(pDX, IDC_OPTION, m_option);
	DDX_Control(pDX, IDC_EXIT, m_exit);
	DDX_Control(pDX, IDC_BACK, m_back);
	DDX_Control(pDX, IDC_ABOUT, m_about);
	DDX_Control(pDX, IDC_NEW, m_new);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGobangDlg, CDialog)
	//{{AFX_MSG_MAP(CGobangDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_OPTION, OnOption)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_COMMAND(ID_MENU_NEW, OnMenuNew)
	ON_COMMAND(ID_MENU_OPTION, OnMenuOption)
	ON_COMMAND(ID_MENU_BACK, OnMenuBack)
	ON_COMMAND(ID_MENU_ABOUT, OnMenuAbout)
	ON_COMMAND(IN_MENU_EXIT, OnMenuExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGobangDlg message handlers

BOOL CGobangDlg::OnInitDialog()									//初始化对话框事件
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);						//系统菜单
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	CString sModFileName;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();

	sModFileName.MakeReverse();
	runpath = sModFileName.Right(sModFileName.GetLength() - sModFileName.Find('\\'));
	runpath.MakeReverse();
	sModFileName.MakeReverse();
	loadfile();																					//读取INI配置文件中信息
	twzq.SetDc(&chessboard,&chess_black,&chess_white,&mask,&dead,this->GetDC());  
	twzq.NewGame(); 
	CGobangDlg::m_back.EnableWindow(twzq.getbackble()); 

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGobangDlg::OnSysCommand(UINT nID, LPARAM lParam)					//这函数主要是截取控制命令，系统自动生层
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();												//显示关于对话框
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGobangDlg::OnPaint() 
{
	if (IsIconic())												//IsIconic()该函数是确定给定的窗口是否为最小化
	{
		CPaintDC dc(this); // device context for painting		创建画图的设备

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		CSize x;
		x=chessboard.GetSize();
		twzq.redraw(); 
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGobangDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGobangDlg::loadfile()	//加载
{
	CString a=get_ini("wuzi","model","1");			//读取文件model的配置
	twzq.Model=atoi(a);

	a=get_ini("wuzi","ai","1");		//读取文件中AI的配置
	twzq.AItype=atoi(a);					//atoi是把字符串转换成整型数的一个函数
}

void CGobangDlg::set_ini(CString keyS ,CString AppS ,CString StrS)		//将配置信息写到INI文件中
{
	CString file=CGobangDlg::runpath+"wuzi.ini";
	::WritePrivateProfileString(keyS, AppS, StrS, file);				//系统提供的方法 将信息写入。INI文件中的方法
}

CString CGobangDlg::get_ini(CString keyS ,CString AppS, CString def)	//将配置信息从INI文件中读取出来
{
	char b[255];
	CString c;
	CString file = CGobangDlg::runpath+"wuzi.ini";
	GetPrivateProfileString(keyS, AppS, def, b, 255, file);				//系统提供的方法 将信息文件从.INI文件中读入程序中
	c.Format("%s",b);
	return c;  
}

void CGobangDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	int x1,y1;
	x1 = (int)(point.x-7)/29 ;
	y1 = (int)(point.y-7)/29 ;
	twzq.downzi(x1,y1);
	if (twzq.twinner.winner == 1)
	{
		CGobangDlg::MessageBox("白棋获胜！");
		twzq.redraw();
	}
	if (twzq.twinner.winner == 2)
	{
		CGobangDlg::MessageBox("黑棋获胜！");
		twzq.redraw();
	}
	CGobangDlg::m_back.EnableWindow(twzq.getbackble()); 

	CDialog::OnLButtonDown(nFlags, point);
}

void CGobangDlg::OnNew() 
{
	// TODO: Add your control notification handler code here
	twzq.NewGame();
	CGobangDlg::m_back.EnableWindow(twzq.getbackble()); 
}

void CGobangDlg::OnOption() 
{
	// TODO: Add your control notification handler code here
	CDlgoption option;
	option.setoption(twzq.Model,twzq.AItype) ;
	CString temp;
	if (option.DoModal() == IDOK)
	{
		twzq.AItype = option.get_AI();
		twzq.Model = option.get_model();
		temp.Format("%i",twzq.Model) ; 
		set_ini("wuzi","model",temp);
		temp.Format("%i",twzq.AItype);  
		set_ini("wuzi","ai",temp);
		twzq.NewGame(); 
	}
}

void CGobangDlg::OnBack() 
{
	// TODO: Add your control notification handler code here
	twzq.goback();
	CGobangDlg::m_back.EnableWindow(twzq.getbackble()); 
}

void CGobangDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg aboutme;
	aboutme.DoModal(); 
}

void CGobangDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	CGobangDlg::OnOK(); 
}

void CGobangDlg::OnMenuNew() 
{
	// TODO: Add your command handler code here
	OnNew();
}

void CGobangDlg::OnMenuOption() 
{
	// TODO: Add your command handler code here
	OnOption();
}

void CGobangDlg::OnMenuBack() 
{
	// TODO: Add your command handler code here
	OnBack();
}

void CGobangDlg::OnMenuAbout() 
{
	// TODO: Add your command handler code here
	OnAbout();
}

void CGobangDlg::OnMenuExit() 
{
	// TODO: Add your command handler code here
	OnExit();
}
