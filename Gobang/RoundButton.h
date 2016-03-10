#if !defined(AFX_ROUNDBUTTON_H__D5117C1F_7922_4E10_897E_EEBFBE7B0CCE__INCLUDED_)
#define AFX_ROUNDBUTTON_H__D5117C1F_7922_4E10_897E_EEBFBE7B0CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoundButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRoundButton window

class CRoundButton : public CButton
{
// Construction
public:
	CRoundButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRoundButton();

	//CRgn���װ��Windowsͼ���豸�Ľӿڡ���һ��������ĳһ�������еľ��λ���������
	CRgn   m_rgn;
	CPoint m_ptCentre;					//��ť������λ��
	int    m_nRadius;					//��ť�İ뾶
	BOOL   m_bDrawDashedFocusCircle;

	// Generated message map functions
protected:
	//{{AFX_MSG(CRoundButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROUNDBUTTON_H__D5117C1F_7922_4E10_897E_EEBFBE7B0CCE__INCLUDED_)
