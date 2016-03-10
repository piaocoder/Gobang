// Dlgoption.cpp : implementation file
//

#include "stdafx.h"
#include "Gobang.h"
#include "Dlgoption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgoption dialog


CDlgoption::CDlgoption(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgoption::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgoption)
	AItype = -1;
	model = -1;
	//}}AFX_DATA_INIT
}


void CDlgoption::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgoption)
	DDX_Radio(pDX, IDC_RADIO4, AItype);
	DDX_Radio(pDX, IDC_RADIO1, model);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgoption, CDialog)
	//{{AFX_MSG_MAP(CDlgoption)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgoption message handlers

void CDlgoption::setoption(int model,int AItype)
{
	CDlgoption::AItype = AItype;
	CDlgoption::model = model;
}
	


BOOL CDlgoption::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (CDlgoption::model == 0) 
		CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO1);
	else
		if (CDlgoption::model == 1)
			CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO2);
		else
			if (CDlgoption::model == 2)
				CDlgoption::CheckRadioButton(IDC_RADIO1, IDC_RADIO3,IDC_RADIO3);

	if (CDlgoption::AItype == 0) 
	CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO4);
	else
		if (CDlgoption::AItype == 1)
			CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO5);
		else
			if (CDlgoption::AItype == 2)
				CDlgoption::CheckRadioButton(IDC_RADIO4, IDC_RADIO6,IDC_RADIO6);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CDlgoption::get_model()
{
	return CDlgoption::model; 
}

int CDlgoption::get_AI()
{
	return CDlgoption::AItype; 
}

void CDlgoption::OnOK() 
{
	int temp = CDlgoption::GetCheckedRadioButton (IDC_RADIO1,IDC_RADIO3);
	if (temp == IDC_RADIO1)
		CDlgoption::model = 0;
	else
		if(temp == IDC_RADIO2)
			CDlgoption::model = 1;
		else
			if(temp == IDC_RADIO3)
				CDlgoption::model = 2;
			else
				CDlgoption::model = 0;

	temp = CDlgoption::GetCheckedRadioButton (IDC_RADIO4,IDC_RADIO6);
	if (temp == IDC_RADIO4)
		CDlgoption::AItype = 0; 
		else
		if(temp == IDC_RADIO5)
		CDlgoption::AItype = 1;
		else
			if(temp == IDC_RADIO6)
				CDlgoption::AItype = 2;
			else
				CDlgoption::AItype = 1;

	CDialog::OnOK();
}
