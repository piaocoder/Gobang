// GobangDlg.h : header file
//

#if !defined(AFX_GOBANGDLG_H__AED099B6_BE1A_46AA_BA2A_F1334E9A70F0__INCLUDED_)
#define AFX_GOBANGDLG_H__AED099B6_BE1A_46AA_BA2A_F1334E9A70F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CDC2.h"
#include "wzq.h"
#include "RoundButton.h"
#include "Dlgoption.h"

/////////////////////////////////////////////////////////////////////////////
// CGobangDlg dialog

class CGobangDlg : public CDialog
{
// Construction
public:
	void loadfile();
	CGobangDlg(CWnd* pParent = NULL);	// standard constructor
protected:
	void set_ini(CString keyS ,CString AppS ,CString StrS );
	CString get_ini(CString keyS ,CString AppS, CString def );

	CDC2 chessboard;							//定义图形变量	棋盘
	CDC2 chess_black;							//定义图形变量	黑棋子
	CDC2 chess_white;							//定义图形变量	白棋子
	CDC2 mask;
	CDC2 dead;									//棋局结束后显示红色的棋子
	wzq  twzq;
	CString runpath;

// Dialog Data
	//{{AFX_DATA(CGobangDlg)
	enum { IDD = IDD_GOBANG_DIALOG };
	CRoundButton	m_option;
	CRoundButton	m_exit;
	CRoundButton	m_back;
	CRoundButton	m_about;
	CRoundButton	m_new;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGobangDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGobangDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNew();
	afx_msg void OnOption();
	afx_msg void OnBack();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnMenuNew();
	afx_msg void OnMenuOption();
	afx_msg void OnMenuBack();
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOBANGDLG_H__AED099B6_BE1A_46AA_BA2A_F1334E9A70F0__INCLUDED_)
