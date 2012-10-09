// MoveDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MoveDialog.h"


// CMoveDialog dialog

IMPLEMENT_DYNAMIC(CMoveDialog, CDialog)

CMoveDialog::CMoveDialog(CWnd* pParent /*=NULL*/)
: CRhinoUiDialog(CMoveDialog::IDD, pParent)
{

}

CMoveDialog::~CMoveDialog()
{
}

void CMoveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMoveDialog, CDialog)
	ON_BN_CLICKED(IDC_MOVE, &CMoveDialog::OnBnClickedMove)
END_MESSAGE_MAP()


// CMoveDialog message handlers

void CMoveDialog::OnBnClickedMove()
{
	RhinoApp().ExecuteCommand(L"_GripMover");
}
