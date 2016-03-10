#if !defined(AFX_DLGOPTION_H__4B554359_6DE1_41D6_AE51_E36CB7BEEA76__INCLUDED_)
#define AFX_DLGOPTION_H__4B554359_6DE1_41D6_AE51_E36CB7BEEA76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlgoption.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgoption dialog

class CDlgoption : public CDialog
{
// Construction
public:
	CDlgoption(CWnd* pParent = NULL);   // standard constructor
	void setoption(int model,int AItype);
	int get_model();
	int get_AI();

	// standard constructor
private:
// Dialog Data
	//{{AFX_DATA(CDlgoption)
	enum { IDD = IDD_DLGOPTION_DIALOG };
	int		AItype;
	int		model;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgoption)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgoption)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTION_H__4B554359_6DE1_41D6_AE51_E36CB7BEEA76__INCLUDED_)
